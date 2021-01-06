/* Using the values calculated in analyze_clones.cpp,
 * create and populate directories on the next iteration
 * of the cloning algorithm
 *
 * calls cytosim's frametool executable
 */

#include "cloning_params.h"

#include <cstdio>		/*printf */
#include <math.h>		/* log10, floor */
#include <sys/stat.h>	/* mkdir */
#include <filesystem>
namespace fs = std::filesystem ;

void create_empty_directories(CloningParams & cloningParams)
{
	/* Directory naming convention: cN_iM
	 * N: clone number, M: iteration number
	 * zero padding for each depends on length of clonse.numClones and cloningParams.numIters
	 */

	// Index to count clones and iterations
	int idxClone ;

	// Calculate the zero padding required for clone idx and iter idx
	int nZerosClone = static_cast<int>( floor(log10(cloningParams.numClones)) ) + 1;
	int nZerosIter = static_cast<int>( floor(log10(cloningParams.numIters)) ) + 1 ;

	// Declare the buffer large enough to accommodate each directory name
	char dirNameBuff [1 + 				// leading c character
					  nZerosClone + 	// clone index
					  1 + 				// underscore
					  1 + 				// leading i character
					  nZerosIter		// iteration index
					  ] ;

	for (idxClone = 0 ; idxClone < cloningParams.numClones; ++idxClone)
	{
		// Fill the directory name buffer
		// sprintf actually returns an int specifying the length
		// of the string in the buffer (not used here)
		int dirNameLen =
			sprintf(dirNameBuff, "c%0*i_i%0*i",
					nZerosClone, idxClone, nZerosIter, cloningParams.idxIter) ;

		// Create the directory with correct name
		// https://codeyarns.com/tech/2014-08-07-how-to-create-directory-using-c-on-linux.html
		const int dirErr =
			mkdir(dirNameBuff, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		// Check if there are any errors in creating the directory
		if (-1 == dirErr)
		{
			printf("Error creating directories! Check that directories don't already exist.\n");
			exit(1);
		}

		// copy the config.cym file into directory
		// https://stackoverflow.com/a/48871008
		fs::path configFile = "config.cym";
		auto targetDir = std::string(dirNameBuff) / configFile.filename();

		fs::copy_file(configFile, targetDir, fs::copy_options::overwrite_existing);

	} // exit the for loop creating the directories
}

void generate_data_files()
{
// needs to know which clones are duplicated so as to not generate data files
// for clones which will be deleted

// will call Cytosim's frametool executable
// frametool objects.cmo last > objects.cmi
}

void copy_simulation_files()
{
// needs to know which clones are duplicated and how many times
}
