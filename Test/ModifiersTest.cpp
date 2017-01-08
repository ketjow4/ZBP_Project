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


TEST(swapTestSet, TODO)
{
	setLLRB<int> a;
	ASSERT_EQ(2, 1);
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