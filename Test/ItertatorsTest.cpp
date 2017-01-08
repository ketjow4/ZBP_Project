#include <gtest\gtest.h>
#include <setLLRB.h>


TEST(iteratorTestSet, empyt_set_iterators)
{
	setLLRB<int> a;
	ASSERT_EQ(a.begin(), a.end());
}


TEST(iteratorTestSet, not_empyt_set_iterators)
{
	setLLRB<int> a = { 1,2,3,4 };
	ASSERT_NE(a.begin(), a.end());
	ASSERT_EQ(*(a.begin()), 1);
	ASSERT_EQ(*(--a.end()), 4);
}


TEST(iteratorTestSet, postincrement_set_iterators)
{
	setLLRB<int> a = { 1,2,3,4 };
	auto it = a.begin();
	ASSERT_EQ(*(it++), 1);
	ASSERT_EQ(*(it), 2);
}

TEST(iteratorTestSet, preincrement_set_iterators)
{
	setLLRB<int> a = { 1,2,3,4 };
	auto it = a.begin();
	ASSERT_EQ(*(++it), 2);
}

TEST(iteratorTestSet, postdecrement_set_iterators)
{
	setLLRB<int> a = { 1,2,3,4 };
	auto it = a.end();
	ASSERT_EQ((it--).ptr_, nullptr);
	ASSERT_EQ(*(it), 4);
}

TEST(iteratorTestSet, predecrement_set_iterators)
{
	setLLRB<int> a = { 1,2,3,4 };
	auto it = a.end();
	ASSERT_EQ(*(--it), 4);
}


TEST(iteratorTestSet, loop_through_set_iterators)
{
	setLLRB<int> a = { 0,1,2,3,4,5,6,7,8 };
	int i = 0;
	for (auto it = a.begin(); it != a.end(); ++it, i++)
		ASSERT_EQ(*it,i);
}


TEST(iteratorTestSet, loop_through_set_reverse_iterators)
{
	setLLRB<int> a = { 0,1,2,3,4,5,6,7,8 };
	int i = 8;
	for (auto it = a.rbegin(); it != a.rend(); ++it, i--)
		ASSERT_EQ(*it, i);
}

//Need to enable "Enable C++ Exceptions" to "Yes With SEH Exceptions" in project properities to work
TEST(iteratorTestSet, reference_iterator_on_empty_set)
{
	setLLRB<int> a;
	ASSERT_ANY_THROW(auto it = *(a.begin()));
}

//Need to enable "Enable C++ Exceptions" to "Yes With SEH Exceptions" in project properities to work
TEST(iteratorTestSet, reference_end_iterator_on_set)
{
	setLLRB<int> a = {1,2,3,4};
	ASSERT_ANY_THROW(auto it = *(a.end()));
}

