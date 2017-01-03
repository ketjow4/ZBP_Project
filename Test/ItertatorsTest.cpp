#include <gtest\gtest.h>
#include <setLLRB.h>


TEST(iteratorTestSet, empyt_set_iterators)
{
	setLLRB<int> a;
	ASSERT_EQ(a.begin(), a.end());
}