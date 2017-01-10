#include <gtest\gtest.h>
#include <setLLRB.h>

TEST(testConstructorSet, default_constructor_test)
{
	setLLRB<int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(testConstructorSet, default_copy_constructor_test)
{
	auto b = setLLRB<int>();
	ASSERT_EQ(b.size(),0);
}



TEST(testConstructorSet, initializer_list_constructor_test)
{
	setLLRB<int> a = {1,2,3};
	ASSERT_EQ(a.size(), 3);
}


TEST(testConstructorSet, initialize_from_copy_test)
{
	auto b = setLLRB<int>();
	b.insert(1);
	setLLRB<int> a(b);
	ASSERT_EQ(a.size(),1);
}



//---------------------------------------------------------------------------------------------------------------------//
//																													   //
//													 multiset tests													   //
//																													   //
//---------------------------------------------------------------------------------------------------------------------//




TEST(testConstructormultiset, default_constructor_test)
{
	multisetLLRB<int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(testConstructormultiset, default_copy_constructor_test)
{
	auto b = multisetLLRB<int>();
	ASSERT_EQ(b.size(), 0);
}



TEST(testConstructormultiset, initializer_list_constructor_test)
{
	multisetLLRB<int> a = { 1,2,2 };
	ASSERT_EQ(a.size(), 3);
}


TEST(testConstructormultiset, initialize_from_copy_test)
{
	auto b = multisetLLRB<int>();
	b.insert(1);
	multisetLLRB<int> a(b);
	ASSERT_EQ(a.size(), 1);
}