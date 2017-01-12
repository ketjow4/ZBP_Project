#include <gtest\gtest.h>
#include <mapLLRB.h>


TEST(capacityTestMap, is_map_empty)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestMap, is_map_not_empty)
{
	mapLLRB<int, int> a = { {1,1},{ 2,2 },{ 3,3 } };
	ASSERT_EQ(a.empty(), false);
}


TEST(capacityTestMap, is_map_empty_changing)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.empty(), true);
	a.insert({1,1});
	ASSERT_EQ(a.empty(), false);
	a.erase(1);
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestMap, is_map_size_zero_when_no_elements)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.size(), 0);
}

TEST(capacityTestMap, is_map_size_growing)
{
	mapLLRB<int, int> a = { { 1,1 }, { 2,2 }, { 3,3 } };
	ASSERT_EQ(a.size(), 3);
	a.insert({ 4 ,4});
	ASSERT_EQ(a.size(), 4);
}

TEST(capacityTestMap, is_map_size_shrinking)
{
	mapLLRB<int, int> a = { { 1,1 }, { 2,2 }, { 3,3 } };
	ASSERT_EQ(a.size(), 3);
	a.erase(3);
	ASSERT_EQ(a.size(), 2);
}


//---------------------------------------------------------------------------------------------------------------------//
//																													   //
//													 multimap tests													   //
//																													   //
//---------------------------------------------------------------------------------------------------------------------//



TEST(capacityTestMultimap, is_multimap_empty)
{
	multimapLLRB<int, int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestMap, is_multimap_not_empty)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,1 },{ 3,3 } };
	ASSERT_EQ(a.empty(), false);
}


TEST(capacityTestMap, is_multimap_empty_changing)
{
	multimapLLRB<int, int> a;
	ASSERT_EQ(a.empty(), true);
	a.insert({ 1,1 });
	ASSERT_EQ(a.empty(), false);
	a.erase(1);
	ASSERT_EQ(a.empty(), true);
}


TEST(capacityTestMap, is_multimap_size_zero_when_no_elements)
{
	multimapLLRB<int, int> a;
	ASSERT_EQ(a.size(), 0);
}

TEST(capacityTestMap, is_multimap_size_growing)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,1 },{ 3,3 } };
	ASSERT_EQ(a.size(), 3);
	a.insert({ 4 ,4 });
	ASSERT_EQ(a.size(), 4);
}

TEST(capacityTestMap, is_multimap_size_shrinking)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,1 },{ 3,3 } };
	ASSERT_EQ(a.size(), 3);
	a.erase(3);
	ASSERT_EQ(a.size(), 2);
}


TEST(capacityTestMultimap, can_count_elements_with_same_key_multimap)
{
	multimapLLRB<int, int> a = { { 1, 1 }, { 1,1 }, { 3,3 } };
	ASSERT_EQ(a.count(1) , 2);
}