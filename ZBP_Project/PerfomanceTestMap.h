#ifndef  PERFORMANCE_MAP_H
#define  PERFORMANCE_MAP_H


#include <chrono>
#include <vector>
#include <algorithm>
#include "LLRB.h"
#include "mapLLRB.h"
#include "mapLLRB.h"
#include <unordered_map>
#include <map>
#include <sstream>
#include <fstream>

typedef std::chrono::high_resolution_clock Clock;



class PerfomanceMap
{

	long test_size = 1e6;
	std::stringstream setLLRBss;
	std::stringstream setss;
	std::stringstream unordered_setss;


	void InitializeSets(map<int,int>& Set, mapLLRB<int,int>& mySet, unordered_map<int,int>& Unordered_set)
	{
		vector<std::pair<int,int>> numbers;
		numbers.reserve(test_size);
		for (int i = 0; i < test_size; i++)		//1 milion
		{
			numbers.push_back(make_pair(i,i*10));
		}
		std::random_shuffle(numbers.begin(), numbers.end());

		for (int i = 0; i < test_size; i++)		//1 milion
			mySet.insert(numbers[i]);

		for (int i = 0; i < test_size; i++)		//1 milion
			Set.insert(numbers[i]);

		for (int i = 0; i < test_size; i++)		//1 milion
			Unordered_set.insert(numbers[i]);
	}


	void TestInsertSpeed()
	{
		mapLLRB<int,int> test;
		vector<std::pair<int, int>> numbers;
		numbers.reserve(test_size);
		for (int i = 0; i < test_size; i++)		//1 milion
		{
			numbers.push_back(make_pair(i, i * 10));
		}
		std::random_shuffle(numbers.begin(), numbers.end());


		auto begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test.insert(numbers[i]);
		}

		auto end = Clock::now();
		auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setLLRBss << test_size << "\t" << ms << "\tms\n";


		map<int,int> test2;
		begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test2.insert(numbers[i]);
		}

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setss << test_size << "\t" << ms << "\tms\n";


		unordered_map<int,int> test3;
		begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test3.insert(numbers[i]);
		}

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		unordered_setss << test_size << "\t" << ms << "\tms\n";
	}


	

	void TestClearSpeed()
	{
		mapLLRB<int,int> test;
		map<int,int> test2;
		unordered_map<int,int> test3;

		InitializeSets(test2, test, test3);

		auto begin = Clock::now();

		test.Clear();

		auto end = Clock::now();
		auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setLLRBss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();

		test2.clear();

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();

		test3.clear();

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		unordered_setss << test_size << "\t" << ms << "\tms\n";
	}

	void TestFindSpeed()
	{
		mapLLRB<int,int> test;
		map<int,int> test2;
		unordered_map<int,int> test3;

		InitializeSets(test2, test, test3);

		auto begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test.find(i);
		}

		auto end = Clock::now();
		auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setLLRBss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test2.find(i);
		}

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			auto tmp = test3.find(i);
			*tmp++;
		}
		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		unordered_setss << test_size << "\t" << ms << "\tms\n";
	}

	void TestIterationThroughEveryElementSpeed()
	{
		mapLLRB<int,int> test;
		map<int,int> test2;
		unordered_map<int,int> test3;

		InitializeSets(test2, test, test3);

		auto begin = Clock::now();

		for (auto it = test.begin(); it != test.end(); ++it)		//1 milion
		{
			auto tmp = *it;
		}

		auto end = Clock::now();
		auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setLLRBss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();

		for (auto it = test2.begin(); it != test2.end(); ++it)		//1 milion
		{
			auto tmp = *it;
		}

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();
		int i;
		for (auto it = test3.begin(); it != test3.end(); ++it)		//1 milion
		{
			volatile int tmp = (*it).first;
			i = tmp;
		}

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		unordered_setss << test_size << "\t" << ms << "\tms\n";
	}

	void TestEraseByOneElementSpeed()
	{
		mapLLRB<int,int> test;
		map<int,int> test2;
		unordered_map<int,int> test3;

		InitializeSets(test2, test, test3);

		vector<int> numbers;
		numbers.reserve(test_size);
		for (int i = 0; i < test_size; i++)		//1 milion
		{
			numbers.push_back(i);
		}
		std::random_shuffle(numbers.begin(), numbers.end());

		auto begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test.erase(numbers[i]);
		}

		auto end = Clock::now();
		auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setLLRBss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test2.erase(numbers[i]);
		}

		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		setss << test_size << "\t" << ms << "\tms\n";

		begin = Clock::now();

		for (int i = 0; i < test_size; i++)		//1 milion
		{
			test3.erase(numbers[i]);
		}
		end = Clock::now();
		ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		unordered_setss << test_size << "\t" << ms << "\tms\n";
	}

public:

	void setTestSize(unsigned long testSize)
	{
		test_size = testSize;
	}

	void RunAllTests()
	{
		TestInsertSpeed();
		TestClearSpeed();
		TestFindSpeed();
		TestIterationThroughEveryElementSpeed();
		TestEraseByOneElementSpeed();
	}


	void GetDataForCharts()
	{
		test_size = 100;
		setLLRBss << "Insert:\n";
		unordered_setss << "Insert:\n";
		setss << "Insert:\n";
		for (int i = 0; i < 6; i++, test_size *= 10)
		{
			TestInsertSpeed();
		}

		test_size = 100;
		setLLRBss << "Clear:\n";
		unordered_setss << "Clear:\n";
		setss << "Clear:\n";
		for (int i = 0; i < 6; i++, test_size *= 10)
		{
			TestClearSpeed();
		}


		test_size = 100;
		setLLRBss << "Find:\n";
		unordered_setss << "Find:\n";
		setss << "Find:\n";
		for (int i = 0; i < 6; i++, test_size *= 10)
		{
			TestFindSpeed();
		}

		test_size = 100;
		setLLRBss << "Iteration:\n";
		unordered_setss << "Iteration:\n";
		setss << "Iteration:\n";
		for (int i = 0; i < 6; i++, test_size *= 10)
		{
			TestIterationThroughEveryElementSpeed();
		}

		test_size = 100;
		setLLRBss << "Erase:\n";
		unordered_setss << "Erase:\n";
		setss << "Erase:\n";
		for (int i = 0; i < 6; i++, test_size *= 10)
		{
			TestEraseByOneElementSpeed();
		}
		fstream setL;
		setL.open("mapLLRB.txt", ios_base::app | ios_base::out);
		setL << setLLRBss.str();
		setL.close();

		fstream unset;
		unset.open("unorderedmap.txt", ios_base::app | ios_base::out);
		unset << unordered_setss.str();
		unset.close();

		fstream setS;
		setS.open("map.txt", ios_base::app | ios_base::out);
		setS << setss.str();
		setS.close();
	}

};
#endif // ! PERFORMANCE_SET_H




