/* Iterate over directories and read wDotINtegral.txt values
 * Calculate s_a for each clone (need to store previous value)
 * Calculate sum of s_a for all clones
 *
 * Start new iteration
 * Calculate n_a for each clone
 */
#include "cloning_calculations.h"



void calc_exponential()
{
// takes wDotIntegral.txt as input
// extracts time stamp and integral value
// needs to know biasing parameter h from the cloning configuration file
}

void calc_s_a()
{
// needs to know exponential value from clone's previous iteration
// s_a = calc_exp_now/calc_exp_previous
}

void sum_s_a()
{
// sum of s_a values for all clones in the iteration
}

void calc_n_a()
{
// needs to know N_c (total number of clones) from cloning config file
// generate random number between 0 and 1
// needs to STORE the calculated values of n_a
}
