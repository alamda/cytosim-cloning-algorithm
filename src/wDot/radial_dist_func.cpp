// Calculating the radial distribution function for centers (and potentiall the ends) of filaments
// Starting with just the centers for now
// Will expand to ends later

void read_frame_data()
{
	// read the file with positions of filaments
	// most of reading can be repurposed from parser.cpp ?
}

void initialize_radial_distr_func( int & num_g_r , float & bin_size_g_r , float & simul_box_len , int & num_bins )
{
	// Initialize normalization index for g_r
	num_g_r = 0 ;

	// Calculate the bin size
	bin_size_g_r = simul_box_len / (2*num_bins) ;

	// Initialize vector/array of g_r given number of bins
	// which data structure?
}

void sample_radial_distr_func( int & num_g_r , int & num_particles , int & simul_box_len)
{
	// Sample the position data
	// How many times should the sampling be done?

	// increase the normalization index num_g_r ???
	num_g_r++ ;

	// Iterate over particle pairs

	for (int particle_i = 0 ; particle_i < num_particles - 1 ; ++particle_i)
	{
		for (int particle_j = particle_i + 1 ; particle_j < num_particles ; ++particle_j)
		{
			// Calculate interparticle distance
			// xr = x(i) - x(j)

			// Account for periodic boundary conditions
			// xr = xr - simul_box_len*nint(xr/simul_box_len)
			// ?

			// RMS of the distance
			// r= sqrt(xr^2)

			// Calculate only within half the box length
			if (r < simul_box_len/2)
			{
				// Calculate the bin index to which the current contribution belongs
				// ig = int(r / delg)

				// Contribution of particles i and j to the radial distribution function at index ig
				// g(ig) = g(ig) + 2

			}
		}
	}
}

void calculate_radial_distr_func( int & num_particles)
{
	// do the calculations
	// See p86 of Understanding Molecular Simulation by
	// Frenkel and Smit for algorithm summary




	// Determine g(r)

	for (int idx_hist = 0 ; idx_hist < num_bins ; ++idx_hist)
	{
		// distance
		float r = bin_size_g_r * (idx_hist + 0.5) ;

		// volume between bin i+1 and bin i
		float vol_bin = ((idx_hist + 1)**3 - idx_hist**3) * bin_size_g_r**3 ;

		// number of ideal gas particles in vol_bin
		//float num_ideal = (4/3)*PI*vol_bin*rho ;

		// Normalize g(r)
		// g(idx_hist) = g(idx_hist)/(num_g_r*num_particles*num_ideal)


	}
}

void output_radial_dist_data_file()
{
	// write to data file to be plotted by gnuplot or similar
	// Might be part of the calculation function, idk
}
