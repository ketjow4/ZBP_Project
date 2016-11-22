#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "LLRB.h"

#include <set>

int main()
{
	LLRB<int> tree;

	std::set<int> a;

	a.insert(1);
	auto b = a.begin();
	//*b = 2;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(8);
	tree.insert(9);


	node<int>* min = tree.findMin(tree.root);
	std::cout << min->data << endl;
	std::cout << tree.next(min)->data << endl;
	std::cout << tree.next(tree.root)->data << endl;

	std::cout << tree << "\n\n\n\n\n\n";

	tree.erase(8);
	std::cout << tree << "\n\n\n\n\n\n";
	tree.erase(2);
	std::cout << tree << "\n\n\n\n\n\n";
	tree.erase(3);
	std::cout << tree << "\n\n\n\n\n\n";
	tree.erase(4);
	std::cout << tree << "\n\n\n\n\n\n";
	tree.erase(5);

	std::cout << tree << "\n\n\n\n\n\n";

	tree.erase(6);
	std::cout << tree << "\n\n\n\n\n\n";
	tree.erase(7);
	std::cout << tree << "\n\n\n\n\n\n";
	tree.erase(9);
	std::cout << tree << "\n\n\n\n\n\n";
	tree.erase(1);
	std::cout << tree << "\n\n\n\n\n\n";
	std::cout << tree;

	_CrtDumpMemoryLeaks();

	return 0;
}