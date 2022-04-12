#!/bin/csh                                                                                                                  
#SBATCH --job-name=0.1_480
#SBATCH --qos=normal
#SBATCH --exclusive
#SBATCH --nodes=10
#SBATCH --output=./%j.out
#SBATCH --error=./%j.err
#SBATCH --account=pi-svaikunt
#SBATCH --time=1-12:00:00
#SBATCH --partition=caslake
#SBATCH --cpus-per-task=1

# The script below works with Cytosim simulations. 
# Lines of code that need to be modified for other systems
# are indicated with # MODIFY

# These are the numbers you want to edit before each cloning run.
# These cloning parameters get written to config.clone (see below).
set N_iters = 100
set N_clones = 480
set bias_param = 0.1

# You only need to edit these two if you are restarting a cloning run
set iter_idx = 0
set prev_iter_idx = 0

# Set the previous iter idx to be 1 less than current iter idx
@ prev_iter_idx = $iter_idx - 1

# Print out the current time to stdout
# Can delete
date +%T

# Singularity is used to run the container which contains the 
# cloning code. 
module load singularity

# Clean up some files before starting.
# multiprog.conf file is used to run clones in parallel on multiple cores
find . -name "multiprog.conf" -delete

# Write some values to the config file read by calc_n_a executable
# so that you do not need to worry about remembering to manually
# edit the config.clone file for different cloning runs.
# DO NOT DELETE, otherwise calc_n_a will be sad.
sed -i "s@n_clones =.*@n_clones = $N_clones@" config.clone
sed -i "s@bias_param =.*@bias_param = $bias_param@" config.clone

set root_dir="$PWD"

# Run through iterations
while ($iter_idx < $N_iters )
	
	mkdir iter$iter_idx
	set iter_dir="$PWD"
	
	cd $iter_dir
	
	set clone_idx = 0	

	set task_cnt = 0

	# Copy over the configuration file needed for calc_n_a cloning exec
	cp ../config.clone .

	# Make clone directories
	while ($clone_idx < $N_clones)
		set clone_name="clone$clone_idx"
		set clone_dir="$iter_dir/$clone_name"

		# Delete clone directory if it already exists
		[ -d $clone_name ] && rm -r $clone_name
		mkdir $clone_name

		# Copy over the configuration file (if any) for your sim
		# MODIFY
		cp ../config.cym  $clone_name/
		# END MODIFY
		
		# Generate multiporg.conf that contains the commands for
		# simulating individual clones
		echo "$clone_idx sh ${clone_dir}/run_clone.sh " >> multiprog.conf
			
		# TMPDIR variable is /scratch/local/jobs/<job-id-number> .
		# TMPDIR exists on the compute node and cannot be accessed
		# from the login nodes.
		# This step is necessary so that only the necessary data are
		# transferred to the compute core from $SCRATCH. 
		# In the case of our Cytosim simulations, the trajectory files
		# were too large and were stressing the system when they were
		# being transferred over from $TMPDIR on the core to $SCRATCH.
		# (Core storage is on a different system from 
		# $SCRATCH, $PROJECT, and $HOME storage.)
		# First, create head.txt, which contains instructions for copying
		# data to compute storage
		echo "cp $clone_dir $TMPDIR -r" >> head.txt
		echo "cd ${TMPDIR}/$clone_name" >> head.txt
		echo "cp ${TMPDIR}/$clone_name $iter_dir -r" >> tail.txt
		# Instructions for the core to run the simulations are in the
		# $root_dir/run_clone.sh, which you will need to edit.
		# Create tail.txt, which instructs the transfer of data back to
		# $SCRATCH after the simulations are done.
		echo "cd $iter_dir" >> tail.txt
		# Concatenate the three files together
		cat head.txt $root_dir/run_clone.sh tail.txt >> $clone_dir/run_clone.sh
		# head.txt and tail.txt are temporary files and can be removed
		rm head.txt tail.txt
		
		# If it is not the 0th iteration 		
		if ($iter_idx != 0) then
			# copy restart files from the previous iteration, making the
			# necessary edits to successfully restart the simulation
			# MODIFY
			cp ../iter$iter_idx/$clone_idx.cmi $clone_name/objects.cmi
			wait
			sed -i '53s/^/import objects objects.cmi\n/' $clone_name/config.cym
			# END MODIFY
		endif

		# Increment up the clone and task counters.
		# Note that a separate counter is needed for tasks (for multiprog
		# files) because it is set to 0 after 480 clones (the number of
		# clones running simultaneusly).
		@ clone_idx = $clone_idx + 1
		@ task_cnt = $task_cnt + 1

		if ($task_cnt >= 480) set task_cnt = 0
	end

	###############################
	# run using srun --multi-prog #
	###############################

	# Split the big multiprog.conf file into separate files
	# of 480 lines each.
	# This part is necessary because for some reason srun freaks out when 
	# you give it a multiprog file that's longer than 500 lines :(
	# It is basically the reason why we run only 480 clones simultaneusly.
	split -d -l 480 multiprog.conf multiprog
	rm multiprog.conf
	
	# Iterate over the multiprog files
	foreach file (multiprog*)
		# Can delete the echo command, it was mostly for debugging
		echo "Submitting  $file"
		# Tell the cluster to run 480 jobs simultaneously,
		# with instructions given for each job given by the multiprog* file.
		srun -N 10 -n 480 --kill-on-bad-exit=1 --ntasks-per-core=1 --cpu-bind=cores --multi-prog $file
		# wait command is necessary to make sure all concurrent processes
		# finish before continuing. 
		wait
	end
	
	# There are wait commands sprinkled throughout this script
	# because we just wanted the script to work. 
	# Deleting this one will probably not break anything,
	# but do so at your own risk.
	wait

	# Can uncomment to keep the multiprog* files for debugging
	# rm multiprog*

	# Call the executable (calc_n_a) which determines how many 
	# times each clone should be copied based on the output of 
	# file wDotIntegral.txt .
	# *NOTE* calc_n_a is currently hard-coded to read wDotIntegral.txt .
	# I will need to make some changes to the cloning code to allow
	# for changing the file name, but for now just make sure your 
	# value for integral of the observable is called "wDotIntegral.txt"
	singularity --quiet exec ~/cloning_sandbox.sif /home/cloning/bin/calc_n_a
	wait
	
	# Perform the re-weighing of clone numbers with the iterate.sh script
	# (you probably don't need to modify it)
	sh $root_dir/iterate.sh
	
	wait
	
	# Increment iteration counters
	@ prev_iter_idx = $iter_idx
	@ iter_idx = $iter_idx + 1

	# Remove config.cym and run_clone.sh from each clone directory
	# to keep things tidy 
	find . -name "config.cym" -delete
	find . -name "run_clone.sh" -delete	
	cd ..
end

# Print out time at the end of the run
date +%T
