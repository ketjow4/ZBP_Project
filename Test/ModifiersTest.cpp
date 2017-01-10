#include <gtest\gtest.h>
#include <setLLRB.h>

TEST(insertTestSet, can_insert_one_element_by_value)
{
	setLLRB<int> a;
	auto pairib = a.insert(1);
	ASSERT_EQ(pairib.second, true);
	ASSERT_EQ(*(pairib.first), 1);
}


TEST(eraseTestSet, can_erase_one_element_by_value)
{
	setLLRB<int> a;
	a.insert(1);
	ASSERT_EQ(a.erase(1) , 1);
}


TEST(swapTestSet, swap_not_empty_sets)
{
	setLLRB<int> a = {1,2,3};
	setLLRB<int> b = { 4,5,6 };
	a.swap(b);
	ASSERT_EQ(*(a.begin()), 4);
	ASSERT_EQ(*(b.begin()), 1);
}

TEST(clearTestSet, clear_empty_set)
{
	setLLRB<int> a;
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}

TEST(clearTestSet, clear_set_with_one_element)
{
	setLLRB<int> a = {1};
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}

TEST(clearTestSet, clear_set_with_many_elements)
{
	setLLRB<int> a = { 1,2,3,4,5 };
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}


TEST(emplaceTestSet, emplace_single_element_in_set)
{
	setLLRB<int> a;
	auto pairib = a.emplace(1);
	ASSERT_EQ(pairib.second, true);
	ASSERT_EQ(*(pairib.first), 1);
}


TEST(emplaceTestSet, emplace_many_elements_in_set)
{
	setLLRB<int> a;
	for(int i = 0; i < 10; i++)
	{ 
		auto pairib = a.emplace(i);
		ASSERT_EQ(pairib.second, true);
		ASSERT_EQ(*(pairib.first), i);
	}
	ASSERT_EQ(a.size(), 10);
}