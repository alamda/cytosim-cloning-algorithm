# Proposed program structure

Outline:

- Extract program parameters from a *.clones input file ???
    - Lower priority, can take direct inputs for now
- Start cytosim simulations using a *.cym file - N clones (from input) in individual directories
    - `sbatch`
- Detect whether simulation is complete for each clones
    - see file messages.cmo ?
    - or have sbatch file create a completion file with simulation exit code
- For each trajectory when simulation complete:
    - extract cross-linker binding data (see read_link.cpp) - parser
        - or use existing cytosim report code to extract data directly from binary
    - calculate wdot for each step of the trajectory
    - calculate s_a
- Calculate sum of s_a values for all trajectories
- Again, for each trajectory:
    - calculate n_a
    - clone/delete trajectory to match n_a
        - clone trajectory with cytosim: frametool objects.cmo frame_number > objects.cmi
    - randomly duplicate/delete trajectories to match desired total number of clones N
- Launch the simulations again, and repeat. Number of times to repeat is specified in the `*.clones` configuration file.
 
