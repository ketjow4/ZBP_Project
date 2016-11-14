#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



#include "LLRB.h"



int main()
{
	LLRB<int> tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(8);
	tree.insert(9);

	std::cout << tree << "\n\n\n\n\n\n";

	tree.erase(1);
	tree.erase(2);
	tree.erase(3);
	tree.erase(4);
	tree.erase(5);

	std::cout << tree;

	tree.erase(6);
	tree.erase(7);
	tree.erase(8);
	tree.erase(9);

	std::cout << tree;

	_CrtDumpMemoryLeaks();

	return 0;
}