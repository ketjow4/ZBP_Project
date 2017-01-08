#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "LLRB.h"
#include "setLLRB.h"
#include "mapLLRB.h"

#include <set>
#include <functional>


#include <map>

//TODO 
//-difference between multiset<pair<int,int> and multimap<int,int>  this is the same for me now 

int main()
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	a.Clear();
	

	_CrtDumpMemoryLeaks();
	

	

	return 0;
}
