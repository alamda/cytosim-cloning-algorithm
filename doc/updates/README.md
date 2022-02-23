# Cytosim Cloning algorithm

Cytosim repository: https://gitlab.com/f.nedelec/cytosim

## Current files:

- `cloning_cytosim.cpp`: main cloning algorithm file
- `parse_output.cpp`: beginnings of a parser (that we will hopefully not need to write)
- `link.txt`: example of cytosim output file for cross-linkers linking two filaments
- `suri_code`: Suri's cloning code (for reference)

## Concise outline for cloning **SCRIPT**

1. c++ script calls cytosim to launch several trajectories [already have the code for this]
2. cytosim runs and outputs data
3. c++ script parses the output file [item that needs most work]
4. c++ script calculates trajectory-dependent quantities [similar to the code that Suri sent, might be able to reuse some of it]
5. c++ script clones/deletes trajectories based on the quantities that were calculated  [code similar to that for step 1, fairly straightforward]
6. repeat steps 2-5

## Proposed program structure

Outline:

- Extract program parameters from a `*.clones` input file ???
	- Lower priority, can take direct inputs for now
- Start cytosim simulations using a `*.cym` file - $`N`$ clones (from input) in individual directories
	- `sbatch`
- Detect whether simulation is complete for each clones
	- see file `messages.cmo` ?
	- or have sbatch file create a completion file with simulation exit code
- For each trajectory when simulation complete:
	- extract cross-linker binding data (see `read_link.cpp`) - parser
		- or use existing cytosim report code to extract data directly from binary
	- calculate $`\dot{w}`$ for each step of the trajectory
	- calculate $`s_a`$
- Calculate sum of $`s_a`$ values for all trajectories
- Again, for each trajectory:
	- calculate $`n_a`$
	- clone/delete trajectory to match $`n_a`$
		- clone trajectory with cytosim: `frametool objects.cmo frame_number > objects.cmi`
	- randomly duplicate/delete trajectories to match desired total number of clones $`N`$
- Launch the simulations again, and repeat. Number of times to repeat is specified in the `*.clones` configuration file.

## Most recent notes

### Cytosim source code files of interest:

- `simul.h`: defines the simulator class `Simul` which contains all objects of the simulations
- `sim.cc`: source code for the `sim` executable which launches the simulation
