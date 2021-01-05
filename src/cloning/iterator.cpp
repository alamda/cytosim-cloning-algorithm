#include "iterator.h"
#include "cloning_params.h"
#include "cytosim_params.h"

// simulate and calculate each clone as a separate process.
// wait for all processes (clones) to finish simulating before moving on
//

void iterate(Clones & clones, Cytosim & cytosim)
{

	// loop over clones (each is a separate process)
	for (int cloneIdx = 0 ; cloneIdx < clones.numClones ; ++cloneIdx )
	{
		// start cytosim simulation for clone - done

		// run wDot calculation on cytosim data - done

		// perform cloning calculations - need to do
	}


}
