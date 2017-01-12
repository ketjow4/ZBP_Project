#include <gtest\gtest.h>
#include <mapLLRB.h>

TEST(atTestMap, at_function_returns_value)
{
	mapLLRB<int, int> a = { {1,1} };
	ASSERT_EQ(a.at(1), 1);
}

TEST(atTestMap, at_function_throws_error_when_no_value)
{
	mapLLRB<int, int> a;
	ASSERT_ANY_THROW(a.at(1));
}

TEST(atTestMap, at_function_returns_reference_that_can_be_modified)
{
	mapLLRB<int, int> a = { { 1,1 } };
	a.at(1) = 2;
	ASSERT_EQ(a.at(1), 2);
}


TEST(findTestMap, find_on_empty_map)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.find(1), a.end());
}


TEST(findTestMap, find_on_one_element_map)
{
	mapLLRB<int,int> a;
	a.insert({1,2});
	auto it = a.find(1);
	ASSERT_EQ((*it).first, 1);
	ASSERT_EQ((*it).second, 2);
}


TEST(findTestMap, find_on_many_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };
	ASSERT_EQ((*(a.find(8))).second, 8);
	ASSERT_EQ((*(a.find(3))).second, 3);
	ASSERT_EQ((*(a.find(1))).second, 1);
	ASSERT_EQ((*(a.find(10))).second, 10);

}

TEST(findTestMap, find_non_existing_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };
	ASSERT_EQ((a.find(11)), a.end());
	ASSERT_EQ((a.find(0)), a.end());
	ASSERT_EQ((a.find(-5)), a.end());
}


TEST(findTestMap, find_max_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };;
	ASSERT_EQ((a.findMax(a._Myhead()))->data.first, 10);
}


TEST(findTestMap, find_min_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };;
	ASSERT_EQ((a.findMin(a._Myhead()))->data.first, 1);
}

TEST(lowerBoundTestMap, lower_bound_on_empty_map)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.lower_bound(1), a.end());
}


TEST(lowerBoundTestMap, lower_bound_on_non_empty_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };;
	auto it = a.lower_bound(2);
	ASSERT_EQ((*(it)).second, 2);
	it = a.lower_bound(1);
	ASSERT_EQ((*(it)).second, 1);
}


TEST(lowerBoundTestMap, lower_bound_on_non_existing_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };;
	auto it = a.lower_bound(11);
	ASSERT_EQ((it), a.end());
}

TEST(upperBoundTestMap, upper_bound_on_empty_map)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.upper_bound(1), a.end());
}


TEST(upperBoundTestMap, upper_bound_on_non_existing_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };;
	auto it = a.upper_bound(0);
	ASSERT_EQ((*(it)).second, 1);
}

TEST(upperBoundTestMap, upper_bound_on_non_empty_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };
	auto it = a.upper_bound(2);
	ASSERT_EQ((*(it)).second, 3);

	it = a.upper_bound(10);
	ASSERT_EQ((it), a.end());
}


TEST(equalRangeTestMap, equal_range_on_non_empty_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };

	auto ii = a.equal_range(2);
	ASSERT_EQ((*ii.first).first, 2);
	ASSERT_EQ((*ii.second).first, 3);
	ASSERT_EQ(std::distance(ii.first, ii.second), 1);
}

TEST(equalRangeTestMap, equal_range_on_non_existing_smaller_than_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };

	auto ii = a.equal_range(0);
	ASSERT_EQ((*ii.first).first, 1);
	ASSERT_EQ((*ii.second).first, 1);
}

TEST(equalRangeTestMap, equal_range_on_non_existing_bigger_than_element_map)
{
	mapLLRB<int,int> a = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 } };

	auto ii = a.equal_range(11);
	ASSERT_EQ(ii.first, a.end());
	ASSERT_EQ(ii.second, a.end());
}


//---------------------------------------------------------------------------------------------------------------------//
//																													   //
//													 multimap tests													   //
//																													   //
//---------------------------------------------------------------------------------------------------------------------//



TEST(findTestMultimultimap, find_on_empty_multimap)
{
	multimapLLRB<int, int> a;
	ASSERT_EQ(a.find(1), a.end());
}


TEST(findTestMultimultimap, find_on_one_element_multimap)
{
	multimapLLRB<int, int> a;
	a.insert({ 1,2 });
	auto it = a.find(1);
	ASSERT_EQ((*it).first, 1);
	ASSERT_EQ((*it).second, 2);
}


TEST(findTestMultimultimap, find_on_many_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	ASSERT_EQ((*(a.find(8))).second, 9);
	ASSERT_EQ((*(a.find(4))).second, 4);
	ASSERT_EQ((*(a.find(1))).second, 1);
	ASSERT_EQ((*(a.find(10))).second, 10);

}

TEST(findTestMultimultimap, find_non_existing_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	ASSERT_EQ((a.find(11)), a.end());
	ASSERT_EQ((a.find(0)), a.end());
	ASSERT_EQ((a.find(-5)), a.end());
}


TEST(findTestMultimultimap, find_max_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	ASSERT_EQ((a.findMax(a._Myhead()))->data.first, 10);
}


TEST(findTestMultimultimap, find_min_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	ASSERT_EQ((a.findMin(a._Myhead()))->data.first, 1);
}

TEST(lowerBoundTestMultimultimap, lower_bound_on_empty_multimap)
{
	multimapLLRB<int, int> a;
	ASSERT_EQ(a.lower_bound(1), a.end());
}


TEST(lowerBoundTestMultimultimap, lower_bound_on_non_empty_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	auto it = a.lower_bound(2);
	ASSERT_EQ((*(it)).second, 2);
	it = a.lower_bound(1);
	ASSERT_EQ((*(it)).second, 1);
}


TEST(lowerBoundTestMultimultimap, lower_bound_on_non_existing_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	auto it = a.lower_bound(11);
	ASSERT_EQ((it), a.end());
}

TEST(upperBoundTestMultimultimap, upper_bound_on_empty_multimap)
{
	multimapLLRB<int, int> a;
	ASSERT_EQ(a.upper_bound(1), a.end());
}


TEST(upperBoundTestMultimultimap, upper_bound_on_non_existing_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	auto it = a.upper_bound(0);
	ASSERT_EQ((*(it)).second, 1);
}

TEST(upperBoundTestMultimultimap, upper_bound_on_non_empty_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };
	auto it = a.upper_bound(2);
	ASSERT_EQ((*(it)).second, 3);

	it = a.upper_bound(10);
	ASSERT_EQ((it), a.end());
}


TEST(equalRangeTestMultimultimap, equal_range_on_non_empty_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };

	auto ii = a.equal_range(1);
	ASSERT_EQ((*ii.first).first, 1);
	ASSERT_EQ((*ii.second).first, 4);
	ASSERT_EQ(std::distance(ii.first, ii.second), 3);
}

TEST(equalRangeTestMultimultimap, equal_range_on_non_existing_smaller_than_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };

	auto ii = a.equal_range(0);
	ASSERT_EQ((*ii.first).first, 1);
	ASSERT_EQ((*ii.second).first, 1);
}

TEST(equalRangeTestMultimultimap, equal_range_on_non_existing_bigger_than_element_multimap)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,2 },{ 1,3 },{ 4,4 },{ 4,5 },{ 7,6 },{ 7,7 },{ 8,8 },{ 8,9 },{ 10,10 } };

	auto ii = a.equal_range(11);
	ASSERT_EQ(ii.first, a.end());
	ASSERT_EQ(ii.second, a.end());
}