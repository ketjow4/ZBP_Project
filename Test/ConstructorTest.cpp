
#include <gtest\gtest.h>
#include <setLLRB.h>

TEST(testConstructorSet, default_constructor_test)
{
	setLLRB<int> a;
	ASSERT_EQ(nullptr, nullptr);
}


TEST(testConstructorSet, initializer_list_constructor_test)
{
	setLLRB<int> a;
	ASSERT_EQ(1, 2);
}


TEST(testConstructorSet, initialize_from_copy_test)
{
	setLLRB<int> a;
	ASSERT_EQ(1, 2);
}

TEST(testConstructorSet, initialize_from_const_copy_test)
{
	setLLRB<int> a;
	ASSERT_EQ(1, 2);
}

TEST(testConstructorSet, initialize_from_input_iterators_test)
{
	setLLRB<int> a;
	ASSERT_EQ(1, 2);
}
