#include "stats.h"

/**
 * Use this function to compute the final statistics of the simulation
 *
 * @param stats The struct used for book keeping.
 *
 * Refer the "stats.h" file in the simulator-src
 */
void compute_stats(stats_t *stats)
{
	/********* TODO ************/
	stats->accesses = stats->reads + stats->writes;
  double tlbmissrate = 1.0*stats->translation_faults/stats->accesses;
	double pagetablemr = 1.0*stats->page_faults/stats->translation_faults;

	double pagetablewbr = 1.0*(stats->writes_to_disk)/stats->translation_faults;
	stats->reads_from_disk = stats->page_faults;

	double pagetableaat = 1.0*(stats->MEMORY_READ_TIME
										+ (pagetablemr * stats->DISK_READ_TIME)
										+ (pagetablewbr * stats->DISK_WRITE_TIME));

	stats->AAT = 1.0*(stats->TLB_READ_TIME + (tlbmissrate * pagetableaat)
										+ stats->MEMORY_READ_TIME);
	// Use the passed in struct to make sure all the stats are computed

	// Think of how many times the tlb, memory and disk are accessed when you have
	// 1) A translation fault
	// 2) A page fault - Disk is read here at least once
	// 3) A dirty page is evicted - Disk is written to here
	// 4) For every access regardless of translation fault and page fault
}
