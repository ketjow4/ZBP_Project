
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

	std::cout << tree;


	return 0;
}