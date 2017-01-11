#include <gtest\gtest.h>
#include <mapLLRB.h>

TEST(atTestMap, at_function_returns_value)
{
	mapLLRB<int, int> a = { {1,1} };
	ASSERT_EQ(a.at(1), 1);
}

TEST(atTestMap, at_function_throws_error_when_no_value)
{
	mapLLRB<int, int> a;
	ASSERT_ANY_THROW(a.at(1));
}