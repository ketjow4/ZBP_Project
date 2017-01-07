#include <gtest\gtest.h>
#include <setLLRB.h>


TEST(iteratorTestSet, empyt_set_iterators)
{
	setLLRB<int> a;
	ASSERT_EQ(a.begin(), a.end());
}


TEST(iteratorTestSet, not_empyt_set_iterators)
{
	/*setLLRB<int> a = { 1,2,3,4 };
	ASSERT_NE(a.begin(), a.end());*/
}