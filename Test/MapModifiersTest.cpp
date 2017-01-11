#include <gtest\gtest.h>
#include <mapLLRB.h>


TEST(insertTestMap, can_insert_one_element_by_value)
{
	mapLLRB<int,int> a;
	auto pairib = a.insert( std::pair<int,int>(1,1) );
	ASSERT_EQ(pairib.second, true);
	ASSERT_EQ((*(pairib.first)).first, 1);
}

TEST(insertTestMap, cannot_insert_one_element_many_times)
{
	mapLLRB<int, int> a;
	auto pairib = a.insert(std::pair<int, int>(1, 1));
	ASSERT_EQ(pairib.second, true);
	ASSERT_EQ((*(pairib.first)).first, 1);
	pairib = a.insert(std::pair<int, int>(1, 1));
	ASSERT_EQ(pairib.second, false);
	ASSERT_EQ((*(pairib.first)).first, 1);
}


TEST(eraseTestMap, can_erase_one_element_by_value)
{
	mapLLRB<int,int> a;
	a.insert(std::pair<int, int>(1, 1));
	ASSERT_EQ(a.erase(1), 1);
}


TEST(swapTestMap, swap_not_empty_maps)
{
	mapLLRB<int, int> a = { {1,1},{ 2,2 },{ 3,3 } };
	mapLLRB<int,int> b = { { 4,4 },{ 5,5 },{ 6,6 } };
	a.swap(b);
	ASSERT_EQ((*(a.begin())).first, 4);
	ASSERT_EQ((*(b.begin())).first, 1);
}

TEST(clearTestMap, clear_empty_map)
{
	mapLLRB<int,int> a;
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}

TEST(clearTestMap, clear_map_with_one_element)
{
	mapLLRB<int, int> a = { {1,1} };
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}

TEST(clearTestMap, clear_map_with_many_elements)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 } };
	a.Clear();
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.empty(), true);
}


TEST(emplaceTestMap, emplace_single_element_in_map)
{
	mapLLRB<int,int> a;
	auto pairib = a.emplace(1,1);
	ASSERT_EQ(pairib.second, true);
	ASSERT_EQ((*(pairib.first)).first, 1);
}


TEST(emplaceTestMap, emplace_many_elements_in_map)
{
	mapLLRB<int,int> a;
	for (int i = 0; i < 10; i++)
	{
		auto pairib = a.emplace(i,i);
		ASSERT_EQ(pairib.second, true);
		ASSERT_EQ((*(pairib.first)).first, i);
		ASSERT_EQ((*(pairib.first)).second, i);
	}
	ASSERT_EQ(a.size(), 10);
}

TEST(operatorTestMap, can_insert_one_element_with_operator)
{
	mapLLRB<int, int> a;
	a[1] = 2;
	ASSERT_EQ(a[1], 2);
}

TEST(operatorTestMap, can_modify_element_with_operator)
{
	mapLLRB<int, int> a = { {1,1} };
	a[1] = 5;
	ASSERT_EQ(a[1], 5);
}