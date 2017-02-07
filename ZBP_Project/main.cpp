#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "LLRB.h"
#include "setLLRB.h"
#include "mapLLRB.h"

#include <set>
#include <functional>


#include <map>


#include "PerformanceTest.h"
#include "PerformanceTestMultiSet.h"
#include "PerfomanceTestMap.h"

typedef std::chrono::high_resolution_clock Clock;

int main()
{
	//PerformanceMultiSet pms;
	//pms.GetDataForCharts();
	//PerfomanceSet ps;
	//ps.GetDataForCharts();
	PerfomanceMap pm;
	pm.GetDataForCharts();

	_CrtDumpMemoryLeaks();


	return 0;
}
