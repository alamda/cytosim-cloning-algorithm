# Cloning algorithm executables for simulations with Cytosim

Cytosim: https://gitlab.com/f-nedelec/cytosim

The following executables are fully functional:
- `calculate` (`src/observable`)
    - given Cytosim data output, calculate the rate of work performed by motors 
- `calc_n_a` (`src/calc_n_a`)
    - given the integrals of the rate of work for several trajectories, calculate the number of times each trajectory should be "cloned"

The following executable compiles, but does not have all of the intended functionalities:
- `cloning` (`src/cloning`)
    - based on the output given by `calc_n_a`, perform the necessary operations for setting up the next generation of clones (e.g. restart file generation, directory creation) 
