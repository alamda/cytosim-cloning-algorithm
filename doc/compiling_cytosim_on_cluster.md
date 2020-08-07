# Compiling Cytosim on cluster

Last updated: 7 August 2020
Alexandra Lamtyugina

## Foreword

The Linux environment of the cluster login nodes is missing several libraries and packages that are key to Cytosim.  They cannot be installed without root privileges (probably for the best), so I found a workaround which involves using an Anaconda environment.

The procedure described below is quite “hacky,” so if you are a C++ purist, avert your eyes.

## Set up an Anaconda environment

First, load Anaconda with

```bash
module load anaconda3
```

Then, create and activate an environment for Cytosim and load the necessary packages:

```bash
conda create -n cytosim-env
conda activate cytosim-env

conda install -n cytosim-env python=3.7 numpy scipy matplotlib jupyter jupyterlab vtk pip
conda install -n cytosim-env -c conda-forge libblas lapack xorg-libxt freeglut zlib
conda install -n cytosim-env -c anaconda make cmake libpng
conda install -n cytosim-env -c psi4 gcc-5
conda install -n cytosim-env -c menpo glew
```

`-n`: `--name`, name of the environment to which the package should be installed

`-c`: `--channel`, channel from which package should be fetched

## Modify `makefile.inc`

There are several modifications that need to be made to `makefile.inc` for compilation to run successfully.  The modifications are in the same order that they appear in the file.  If you have trouble

### Compiler configuration

Enable PNG export by changing the `HAS_PNG` variable (line ~38):

```makefile
HAS_PNG := 1
```

---

Copy the `GL` directory with `*.h` files from the `glew`  (or was it `freeglut`?) conda package directory to new directory `cytosim/src/extras`.

Add an include flag in the `makefile.inc` file under the `gcc` section of the compiler settings (line ~92):

```makefile
CXX := g++ -Wfatal-errors -Wno-deprecated-declaration -Isrc/extras
```

### Linux-specific settings

Make sure to make the following edits in the **Linux section** of `makefile.inc`.  The compiler recognizes the login node as a Linux environment (not cluster).

---

Specify `$BLASDIR` (line ~234):

```makefile
BLASDIR := $(HOME)/.conda/pkgs/libblas*/lib/libblas.*
```

---

Change `GRAFIX` variable (line ~255):

```makefile
GRAFIX := -L$(LIBDIR) -lglut -lGL -lGLU -lXt -lX11 $(HOME)/.conda/pkgs/glew-2.0.0-0/lib/libGLEW.so
```

For some reason, midway does not have GLEW, so this is a BYOGLEW kind of party.

---

Link to `libpng.a` of `libpng` package and to `libz.a` of `zlib` package (line ~258):

```makefile
LIB_PNG := $(HOME)/.conda/pkgs/libpng-1.6.37-hbc83047_0/lib/libpng.a $(HOME)/.conda/pkgs/zlib-1.2.11-h516909a_1006/lib/libz.a
```

## Edit the `LD_RUN_PATH` environment variable

Run the following command in the shell __prior to compiling Cytosim__:

```bash
export LD_RUN_PATH="$HOME/.conda/pkgs/glew-2.0.0-0/lib/"
```

I recommend adding the above command to your `~/.shell_rc` (or similar, may vary depending on which shell you use).  Otherwise, you will need to remember to run the above command in each new terminal session that you plan to use to compile Cytosim.  

As specified in the `GRAFIX` variable, the compiler relies on a GLEW shared object in a non-standard location (standard location is `/urs/lib/`).  Therefore, we need to indicate where the executable should look for `libGLEW.so` whenever it is run.  

Adding the location of `libGLEW.so` to `LD_RUN_PATH` will compile the Cytosim executables with information on where to find the file.  This is necessary despite the fact that the compiler knows where to find the shared objects, because the executable must have the location as well so that it can access those shared objects every time it is called.


See https://homepages.inf.ed.ac.uk/imurray2/compnotes/library_linking.txt for more in-depth information about dynamic linking.

## (Optional) Modifying Cytosim source code to be compatible with Cloning Algorithm Code

This is the point at which you should make any and all modifications to Cytosim source code (prior to compilation, which is the next step).  

Below are the instructions for modifications necessary for the Cloning Algorithm Code to be compatible with the Cytosim output.

---

These are some minor modifications to the output of cytosim for the command `report couple:link`.  No other source code needs to be modified, these modifications simply add two additional data items (already computed and stored by Cytosim) to be included in the output.  

File to be modified: `cytosim/src/sim/simul_report.cc`

Function to be modified:
```c++
void Simul::reportCoupleLink(std::ostream& out, std::string const& which) const
```

### Original Cytosim source code
```c++
void Simul::reportCoupleLink(std::ostream& out, std::string const& which) const
{
	Property * selected = nullptr;

	if ( which.size() )
		selected = properties.find_or_die("couple", which);

	out << COM << "class" << SEP << "identity";
	out << SEP << "fiber1" << SEP << "abscissa1";// << SEP << repeatXYZ("pos1");
	out << SEP << "fiber2" << SEP << "abscissa2";// << SEP << repeatXYZ("pos2");
	out << SEP << "force" << SEP << "cos_angle";

	for ( Couple * obj=couples.firstAA(); obj ; obj=obj->next() )
	{
		if ( !selected || obj->prop == selected )
		{
			out << LIN << obj->prop->number();
			out << SEP << obj->identity();

			out << SEP << obj->fiber1()->identity();
			out << SEP << obj->abscissa1();
			//out << SEP << obj->posHand1();

			out << SEP << obj->fiber2()->identity();
			out << SEP << obj->abscissa2();
			//out << SEP << obj->posHand2();

			out << SEP << obj->force().norm();
			out << SEP << obj->cosAngle();
		}
	}
}

```

### Modified Cytosim source code

```c++
void Simul::reportCoupleLink(std::ostream& out, std::string const& which) const
{
	Property * selected = nullptr;

	if ( which.size() )
		selected = properties.find_or_die("couple", which);

	out << COM << "class" << SEP << "identity";
	out << SEP << "fiber1" << SEP << "abscissa1" << SEP << repeatXYZ("pos1") << SEP << repeatXYZ("dirFiber1") ; // MODIFIED
	out << SEP << "fiber2" << SEP << "abscissa2" << SEP << repeatXYZ("pos2") << SEP << repeatXYZ("dirFiber2") ; // MODIFIED
	out << SEP << "force" << SEP << "cos_angle";

	for ( Couple * obj=couples.firstAA(); obj ; obj=obj->next() )
	{
		if ( !selected || obj->prop == selected )
		{
			out << LIN << obj->prop->number();
			out << SEP << obj->identity();

			out << SEP << obj->fiber1()->identity();
			out << SEP << obj->abscissa1();
			out << SEP << obj->posHand1(); // UNCOMMENTED
			out << SEP << obj->dirFiber1(); // ADDED

			out << SEP << obj->fiber2()->identity();
			out << SEP << obj->abscissa2();
			out << SEP << obj->posHand2(); // UNCOMMENTED
			out << SEP << obj->dirFiber2(); // ADDED

			out << SEP << obj->force().norm();
			out << SEP << obj->cosAngle();
		}
	}
}
```

## Run `make`

If previously attempted to run `make` command in `cytosim` directory, first run

```
make clean
```

then

```
make alldim
```

The above command will compile executables for 1-, 2-, and 3D (to be found in `bin1`, `bin2`, and `bin3`, respectively).  

Though the executables for each dimension are in different directories, they will have the same name.  To add the executables to `$PATH`, create new `bin` directory and copy executables into it as `sim1`, `play1`, `report1`, etc. to have dedicated executables for each dimension which can be called from anywhere.  

Otherwise, you can just copy these executables into your simulation directory on `$SCRATCH` (but the downside is that the executables can become outdated if you make further modifications to Cytosim source code and recompile).
