#ifndef PERFORMANCE_MULTISET_H
#define PERFORMANCE_MULTISET_H


#include <chrono>
#include <vector>
#include <algorithm>
#include "LLRB.h"
#include "setLLRB.h"
#include "mapLLRB.h"
#include <unordered_set>
#include <set>
#include <sstream>
#include <fstream>

typedef std::chrono::high_resolution_clock Clock;


class PerformanceMultiSet
{
	long test_size = 100000;
	std::stringstream setLLRB;
	std::stringstream set;
	std::stringstream unordered_set;

void InitializeSets(multiset<int>& Set, multisetLLRB<int>& mySet, unordered_multiset<int>& Unordered_set)
{
	vector<int> numbers;
	numbers.reserve(test_size);
	for (int i = 0; i < test_size; i++)		
	{
		numbers.push_back(i % (test_size/10));
	}
	std::random_shuffle(numbers.begin(), numbers.end());

	for (int i = 0; i < test_size; i++)		
		mySet.insert(numbers[i]);

	for (int i = 0; i < test_size; i++)		
		Set.insert(numbers[i]);

	for (int i = 0; i < test_size; i++)		
		Unordered_set.insert(numbers[i]);
}

void TestInsertSpeed()
{
	multisetLLRB<int> test;
	vector<int> numbers;
	numbers.reserve(test_size);
	for (int i = 0; i < test_size; i++)		
	{
		numbers.push_back(i % (test_size / 10));
	}
	std::random_shuffle(numbers.begin(), numbers.end());


	auto begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test.insert(numbers[i]);
	}

	auto end = Clock::now();
	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	setLLRB << test_size << "\t" << ms << "\tms\n";


	multiset<int> test2;
	begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test2.insert(numbers[i]);
	}

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	set << test_size << "\t" << ms << "\tms\n";


	unordered_multiset<int> test3;
	begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test3.insert(numbers[i]);
	}

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	unordered_set << test_size << "\t" << ms << "\tms\n";



}

void TestClearSpeed()
{
	multisetLLRB<int> test;
	multiset<int> test2;
	unordered_multiset<int> test3;

	InitializeSets(test2, test, test3);

	auto begin = Clock::now();

	test.Clear();

	auto end = Clock::now();
	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	setLLRB << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();

	test2.clear();

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	set << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();

	test3.clear();

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	unordered_set << test_size << "\t" << ms << "\tms\n";
}

void TestFindSpeed()
{
	multisetLLRB<int> test;
	multiset<int> test2;
	unordered_multiset<int> test3;

	InitializeSets(test2, test, test3);

	auto begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test.find(i);
	}

	auto end = Clock::now();
	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	setLLRB << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test2.find(i);
	}

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	set << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		auto tmp = test3.find(i);
		*tmp++;
	}
	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	unordered_set << test_size << "\t" << ms << "\tms\n";
}

void TestIterationThroughEveryElementSpeed()
{
	multisetLLRB<int> test;
	multiset<int> test2;
	unordered_multiset<int> test3;

	InitializeSets(test2, test, test3);

	auto begin = Clock::now();

	for (auto it = test.begin(); it != test.end(); ++it)		
	{
		auto tmp = *it;
	}

	auto end = Clock::now();
	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	setLLRB << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();

	for (auto it = test2.begin(); it != test2.end(); ++it)	
	{
		auto tmp = *it;
	}

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	set << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();
	int i;
	for (auto it = test3.begin(); it != test3.end(); ++it)		
	{
		volatile int tmp = *it;
		i = tmp;
	}

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	unordered_set << test_size << "\t" << ms << "\tms\n";
}

void TestEraseByOneElementSpeed()
{
	multisetLLRB<int> test;
	multiset<int> test2;
	unordered_multiset<int> test3;

	InitializeSets(test2, test, test3);

	vector<int> numbers;
	numbers.reserve(test_size);
	for (int i = 0; i < test_size; i++)		
	{
		numbers.push_back(i % 2);
	}
	std::random_shuffle(numbers.begin(), numbers.end());

	auto begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test.erase(numbers[i]);
	}


	auto end = Clock::now();
	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	setLLRB << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test2.erase(numbers[i]);
	}

	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	set << test_size << "\t" << ms << "\tms\n";

	begin = Clock::now();

	for (int i = 0; i < test_size; i++)		
	{
		test3.erase(numbers[i]);
	}
	end = Clock::now();
	ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	unordered_set << test_size <<"\t" << ms << "\tms\n";
}

public:

void setTestSize(unsigned long testSize )
{
	test_size = testSize;
}

void RunAllTests()
{
	TestInsertSpeed();
	TestClearSpeed();
	TestFindSpeed();
	TestIterationThroughEveryElementSpeed();
	//TestEraseByOneElementSpeed(); //Don't run this
}

void GetDataForCharts()
{
	test_size = 100;
	setLLRB << "Insert:\n";
	unordered_set << "Insert:\n";
	set << "Insert:\n";
	for (int i = 0; i < 6; i++, test_size *= 10)
	{
		TestInsertSpeed();
	}

	test_size = 100;
	setLLRB << "Clear:\n";
	unordered_set << "Clear:\n";
	set << "Clear:\n";
	for (int i = 0; i < 6; i++, test_size *= 10)
	{
		TestClearSpeed();
	}


	test_size = 100;
	setLLRB << "Find:\n";
	unordered_set << "Find:\n";
	set << "Find:\n";
	for (int i = 0; i < 6; i++, test_size *= 10)
	{
		TestFindSpeed();
	}

	test_size = 100;
	setLLRB << "Iteration:\n";
	unordered_set << "Iteration:\n";
	set << "Iteration:\n";
	for (int i = 0; i < 6; i++, test_size *= 10)
	{
		TestIterationThroughEveryElementSpeed();
	}
	fstream setL;
	setL.open("multisetLLRB.txt", ios_base::app | ios_base::out);
	setL << setLLRB.str();
	setL.close();

	fstream unset;
	unset.open("unordered.txt", ios_base::app | ios_base::out);
	unset << unordered_set.str();
	unset.close();

	fstream setS;
	setS.open("multiset.txt", ios_base::app | ios_base::out);
	setS << set.str();
	setS.close();
}


};
#endif

