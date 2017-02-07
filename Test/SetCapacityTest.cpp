#include <gtest\gtest.h>
#include <setLLRB.h>



TEST(capacityTestSet, is_set_empty)
{
	setLLRB<int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestSet, is_set_not_empty)
{
	setLLRB<int> a = {1,2,3};
	ASSERT_EQ(a.empty(), false);
}


TEST(capacityTestSet, is_set_empty_changing)
{
	setLLRB<int> a;
	ASSERT_EQ(a.empty(), true);
	a.insert(1);
	ASSERT_EQ(a.empty(), false);
	a.erase(1);
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestSet, is_set_size_zero_when_no_elements)
{
	setLLRB<int> a;
	ASSERT_EQ(a.size(), 0);
}

TEST(capacityTestSet, is_set_size_growing)
{
	setLLRB<int> a = { 1,2,3 };
	ASSERT_EQ(a.size(), 3);
	a.insert(4);
	ASSERT_EQ(a.size(), 4);
}

TEST(capacityTestSet, is_set_size_shrinking)
{
	setLLRB<int> a = { 1,2,3 };
	ASSERT_EQ(a.size(), 3);
	a.erase(3);
	ASSERT_EQ(a.size(), 2);
}

//---------------------------------------------------------------------------------------------------------------------//
//																													   //
//													 multiset tests													   //
//																													   //
//---------------------------------------------------------------------------------------------------------------------//

TEST(capacityTestmultiset, is_multiset_empty)
{
	multisetLLRB<int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestmultiset, is_multiset_not_empty)
{
	multisetLLRB<int> a = { 1,2,2 };
	ASSERT_EQ(a.empty(), false);
}


TEST(capacityTestmultiset, is_multiset_empty_changing)
{
	multisetLLRB<int> a;
	ASSERT_EQ(a.empty(), true);
	a.insert(1);
	ASSERT_EQ(a.empty(), false);
	a.erase(1);
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestmultiset, is_multiset_size_zero_when_no_elements)
{
	multisetLLRB<int> a;
	ASSERT_EQ(a.size(), 0);
}

TEST(capacityTestmultiset, is_multiset_size_growing)
{
	multisetLLRB<int> a = { 1,2,3 };
	ASSERT_EQ(a.size(), 3);
	a.insert(4);
	ASSERT_EQ(a.size(), 4);
}

TEST(capacityTestmultiset, is_multiset_size_shrinking)
{
	/*multisetLLRB<int> a = { 1,2,3 };
	ASSERT_EQ(a.size(), 3);
	a.erase(3);
	ASSERT_EQ(a.size(), 2);*/
}