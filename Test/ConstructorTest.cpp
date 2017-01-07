#include <gtest\gtest.h>
#include <setLLRB.h>

TEST(testConstructorSet, default_constructor_test)
{
	setLLRB<int> a;
	ASSERT_EQ(nullptr, nullptr);
}


TEST(testConstructorSet, default_copy_constructor_test)
{
	auto b = setLLRB<int>();
	ASSERT_EQ(b.size(),0);
}



TEST(testConstructorSet, initializer_list_constructor_test)
{
	/*setLLRB<int> a = {1,2,3};
	ASSERT_EQ(a.size(), 3);*/
}


TEST(testConstructorSet, initialize_from_copy_test)
{
	//auto b = setLLRB<int>();
	//b.insert(1);
	//setLLRB<int> a(b);
	//ASSERT_EQ(a.size(),1);
}



