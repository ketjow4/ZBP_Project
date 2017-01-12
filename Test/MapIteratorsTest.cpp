#include <gtest\gtest.h>
#include <mapLLRB.h>


TEST(iteratorTestMap, empyt_map_iterators)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.begin(), a.end());
}


TEST(iteratorTestMap, not_empyt_map_iterators)
{
	mapLLRB<int,int> a = { { 1 ,1},{ 2 ,1 },{ 3 ,1 },{ 4 ,1 } };
	ASSERT_NE(a.begin(), a.end());
	ASSERT_EQ((*(a.begin())).first, 1);
	ASSERT_EQ((*(--a.end())).first, 4);
}


TEST(iteratorTestMap, postincrement_map_iterators)
{
	mapLLRB<int,int> a = { { 1 ,1 },{ 2 ,1 },{ 3 ,1 },{ 4 ,1 } };
	auto it = a.begin();
	ASSERT_EQ((*(it++)).first, 1);
	ASSERT_EQ((*(it)).first, 2);
}

TEST(iteratorTestMap, preincrement_map_iterators)
{
	mapLLRB<int,int> a = { { 1 ,1 },{ 2 ,1 },{ 3 ,1 },{ 4 ,1 } };
	auto it = a.begin();
	ASSERT_EQ((*(++it)).first, 2);
}

TEST(iteratorTestMap, postdecrement_map_iterators)
{
	mapLLRB<int,int> a = { { 1 ,1 },{ 2 ,1 },{ 3 ,1 },{ 4 ,1 } };
	auto it = a.end();
	ASSERT_EQ((it--).ptr_, nullptr);
	ASSERT_EQ((*(it)).first, 4);
	ASSERT_EQ((*(it)).second, 1);
}

TEST(iteratorTestMap, predecrement_map_iterators)
{
	mapLLRB<int,int> a = { { 1 ,1 },{ 2 ,1 },{ 3 ,1 },{ 4 ,1 } };
	auto it = a.end();
	ASSERT_EQ((*(--it)).first, 4);
}


TEST(iteratorTestMap, loop_through_map_iterators)
{
	mapLLRB<int,int> a = { { 1 ,1 },{ 2 ,1 },{ 3 ,1 },{ 4 ,1 } };
	int i = 1;
	for (auto it = a.begin(); it != a.end(); ++it, i++)
	{
		ASSERT_EQ((*it).first, i);
		ASSERT_EQ((*it).second, 1);
	}
}


TEST(iteratorTestMap, loop_through_map_reverse_iterators)
{
	mapLLRB<int,int> a = { { 1 ,1 },{ 2 ,1 },{ 3 ,1 },{ 4 ,1 } };
	int i = 4;
	for (auto it = a.rbegin(); it != a.rend(); ++it, i--)
	{
		ASSERT_EQ((*it).first, i);
		ASSERT_EQ((*it).second, 1);
	}
}