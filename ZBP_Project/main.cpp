#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "LLRB.h"
#include "setLLRB.h"

#include <set>
#include <functional>


int main()
{
	setLLRB<int, greater<int>> tree, bar;

	std::set<int> a;

	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(5);
	a.insert(6);
	a.insert(7);
	a.insert(8);
	a.insert(9);

	/*for (auto its = a.begin(); its != a.end(); ++its)
	{
		cout << *its << " ";
	}
	cout << "\n";

	for (auto its = --a.end(); its != a.begin(); --its)
	{
		cout << *its << " ";
	}*/

	auto b = a.begin();
	for (int i = 0; i < 7; i++)
	{
		std::cout << *b << '\n';
		b++;
	}
	a.insert(10);
	std::cout << *b << "\n";	//shoudl be 8

	a.insert(11);

	std::cout << *++b << "\n";	//should be 9

	a.erase(8);

	std::cout << *b << "\n";	//shoudl be 9


	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(8);
	tree.insert(9);

	/*std::cout << "\nLLRB_iterator \n";
	
	for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\n";
	for (auto it = --tree.end(); it != tree.begin(); --it)
	{
		std::cout << *it << ' ';
	}*/

	auto it = tree.begin();
	for (int i = 0; i < 7; i++)
		it++;






	//std::insert_iterator<LLRB<int, greater<int>>> insert_it(tree, it);

	//bar.insert(100);

	//std::copy(bar.begin(), bar.end(), insert_it);


	tree.insert(10);

	auto r = tree.rbegin();
	for (auto rit = tree.rbegin(); rit != tree.rend(); rit++)
		cout << *rit << " ";

	cout << "\n";

	for (auto rit = tree.crbegin(); rit != tree.crend(); rit++)
		cout << *rit << " ";

	//std::cout << tree << "\n\n\n\n\n\n";

	std::cout << *it << "\n";	//shoudl be 8

	tree.insert(11);

	std::cout << *++it << "\n";	//should be 9

	std::cout << tree << "\n\n\n\n\n\n";

	tree.erase(8);

	std::cout << *it << "\n";	//shoudl be 9

	std::cout << tree << "\n\n\n\n\n\n";

	//tree.erase(8);
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