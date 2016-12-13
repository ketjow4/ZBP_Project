
#include <gtest\gtest.h>
#include <LLRB.h>

TEST(testConstructor, default_constructor_test)
{
	LLRB<int> a;
	ASSERT_EQ(nullptr, nullptr);
}