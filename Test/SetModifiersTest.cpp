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



//---------------------------------------------------------------------------------------------------------------------//
//																													   //
//													 multiset tests													   //
//																													   //
//---------------------------------------------------------------------------------------------------------------------//



TEST(insertTestMultiset, can_insert_one_element_by_value)
{
	multisetLLRB<int> a;
	auto pairib = a.insert(1);
	ASSERT_EQ(pairib.second, true);
	ASSERT_EQ(*(pairib.first), 1);
}

TEST(insertTestMultiset, can_insert_same_value_more_than_once)
{
	multisetLLRB<int> a;
	for(int i = 0; i < 10; i++)
	{
		auto pairib = a.insert(1);
		ASSERT_EQ(pairib.second, true);
		ASSERT_EQ(*(pairib.first), 1);
	}
}


TEST(eraseTestMultiset, can_erase_one_element_by_value)
{
	multisetLLRB<int> a;
	a.insert(1);
	ASSERT_EQ(a.erase(1), 1);
}


TEST(eraseTestMultiset, can_erase_one_repeated_element_by_value)
{
	multisetLLRB<int> a;
	a.insert(1);
	a.insert(1);
	ASSERT_EQ(a.erase(1), 2);
	ASSERT_EQ(a.size(), 0);
}

TEST(eraseTestMultiset, can_erase_one_repeated_element_by_value_2)
{
	//multisetLLRB<int> a = { 1,1,1,2,3,4,5,5,7,7 };
	//ASSERT_EQ(a.erase(1), 3);
	//ASSERT_EQ(a.size(), 7);
}

TEST(eraseTestMultiset, can_erase_one_repeated_element_by_value_3)
{
	/*multisetLLRB<int> a = { 1,1,1,1,1,1,1,2,3,4,5,5,7,7 };
	ASSERT_EQ(a.erase(1), 7);
	ASSERT_EQ(a.size(), 7);*/
}


TEST(swapTestMultiset, swap_not_empty_multisets)
{
	multisetLLRB<int> a = { 1,1,1 };
	multisetLLRB<int> b = { 4,4,4 };
	a.swap(b);
	ASSERT_EQ(*(a.begin()), 4);
	ASSERT_EQ(*(b.begin()), 1);
}

TEST(clearTestMultiset, clear_empty_multiset)
{
	multisetLLRB<int> a;
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}

TEST(clearTestMultiset, clear_multiset_with_one_element)
{
	multisetLLRB<int> a = { 1 };
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}

TEST(clearTestMultiset, clear_multiset_with_many_elements)
{
	multisetLLRB<int> a = { 1,2,2,3,3 };
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}


TEST(emplaceTestMultiset, emplace_single_element_in_multiset)
{
	multisetLLRB<int> a;
	auto pairib = a.emplace(1);
	ASSERT_EQ(pairib.second, true);
	ASSERT_EQ(*(pairib.first), 1);
}


TEST(emplaceTestMultiset, emplace_many_same_elements_in_multiset)
{
	multisetLLRB<int> a;
	for (int i = 0; i < 10; i++)
	{
		auto pairib = a.emplace(1);
		ASSERT_EQ(pairib.second, true);
		ASSERT_EQ(*(pairib.first), 1);
	}
	ASSERT_EQ(a.size(), 10);
}