#!/bin/bash

# genealogy.txt is the file output by calc_n_a 
input="genealogy.txt"

# Get the total number of clones by counting the lines in geneaolgy.txt
N_clones=$(wc -l $input | awk '{print $1}' )

clone_count=0

# Remove unnecessary restart files from iter directory.
# Each clone directory contains it's own restart file - 
# those restart files are not deleted in this step.
[ -s objects.cmi ] && rm objects.cmi

# Read genealogy.txt
while read -r line
do
	clone_id=$(echo $line | awk '{print $1}' )
	copy_num=$(echo $line | awk '{print $2}' )

	# Copy clone$clone_id restart files $copy_num number of times
	# to the iteration directory, with the name $clone_count.cmi
	for ((i=0; i<$copy_num ; i++ ))
	do
		# MODIFY
		cp $clone_id/objects.cmi ${clone_count}.cmi
		# END MODIFY

		(( clone_count+=1))

	done
	
done < $input
