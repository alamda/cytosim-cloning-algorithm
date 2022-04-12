# These are the simulation instructions for a single clone
# MODIFY
singularity --quiet exec ~/cytosim_sandbox.sif /home/cytosim/bin/sim2
wait
singularity --quiet exec ~/cytosim_sandbox.sif /home/cytosim/bin/report2 couple:link > link.txt
wait
# *NOTE* you will need to write your own code for calculating the integral
# of your observable, which needs to be output to a file named
# wDotIntegral.txt .
singularity --quiet exec ~/cloning_sandbox.sif /home/cloning/bin/calculate
wait
singularity --quiet exec ~/cytosim_sandbox.sif /home/cytosim/bin/frametool objects.cmo last > objects.cmi
wait
find . -name "*.cmo" -delete
find . -name "link.txt" -delete
# END MODIFY
