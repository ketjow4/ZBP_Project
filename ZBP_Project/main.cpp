#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "LLRB.h"
#include "setLLRB.h"
#include "mapLLRB.h"

#include <set>
#include <functional>


#include <map>


int main()
{

	mapLLRB<int, int> a = { { 1,1} };
	auto ret = a.find(1);

	

	_CrtDumpMemoryLeaks();
	

	

	return 0;
}
