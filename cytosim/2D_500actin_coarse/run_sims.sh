#!/bin/sh

for config_file in ./*.cym; do
	dir="${config_file%.*}"
	mkdir "${dir}"
	cd ${dir}
	cp ../${config_file} ../cytosim.sbatch ../sim .
	sbatch cytosim.sbatch
	cd ..
done

mkdir config_files
mv config*.cym config_files
