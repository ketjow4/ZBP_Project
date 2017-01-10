#include <gtest\gtest.h>
#include <setLLRB.h>



TEST(findTestSet, find_on_empty_set)
{
	setLLRB<int> a;
	ASSERT_EQ(a.find(1), a.end());
}


TEST(findTestSet, find_on_one_element_set)
{
	setLLRB<int> a;
	a.insert(1);
	ASSERT_EQ(*(a.find(1)), 1);
}


TEST(findTestSet, find_on_many_element_set)
{
	setLLRB<int> a = {1,2,3,4,5,6,7,8,9,10};
	ASSERT_EQ(*(a.find(8)), 8);
	ASSERT_EQ(*(a.find(3)), 3);
	ASSERT_EQ(*(a.find(1)), 1);
	ASSERT_EQ(*(a.find(10)), 10);

}

TEST(findTestSet, find_non_existing_element_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	ASSERT_EQ((a.find(11)), a.end());
	ASSERT_EQ((a.find(0)), a.end());
	ASSERT_EQ((a.find(-5)), a.end());
}


TEST(findTestSet, find_max_element_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	ASSERT_EQ((a.findMax(a._Myhead()))->data, 10);
}


TEST(findTestSet, find_min_element_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	ASSERT_EQ((a.findMin(a._Myhead()))->data, 1);
}

TEST(lowerBoundTestSet, lower_bound_on_empty_set)
{
	setLLRB<int> a;
	ASSERT_EQ(a.lower_bound(1), a.end());
}


TEST(lowerBoundTestSet, lower_bound_on_non_empty_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	auto it = a.lower_bound(2);
	ASSERT_EQ(*(it), 2);
	it = a.lower_bound(1);
	ASSERT_EQ(*(it), 1);
}


TEST(lowerBoundTestSet, lower_bound_on_non_existing_element_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	auto it = a.lower_bound(11);
	ASSERT_EQ((it), a.end());
}

TEST(upperBoundTestSet, upper_bound_on_empty_set)
{
	setLLRB<int> a;
	ASSERT_EQ(a.upper_bound(1), a.end());
}


TEST(upperBoundTestSet, upper_bound_on_non_existing_element_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	auto it = a.upper_bound(0);
	ASSERT_EQ(*(it), 1);
}

TEST(upperBoundTestSet, upper_bound_on_non_empty_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	auto it = a.upper_bound(2);
	ASSERT_EQ(*(it), 3);

	it = a.upper_bound(10);
	ASSERT_EQ((it), a.end());
}


TEST(equalRangeTestSet, equal_range_on_non_empty_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	
	auto ii = a.equal_range(2);
	ASSERT_EQ(*ii.first, 2);
	ASSERT_EQ(*ii.second, 3);
	ASSERT_EQ(std::distance(ii.first, ii.second), 1);
}

TEST(equalRangeTestSet, equal_range_on_non_existing_smaller_than_element_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };

	auto ii = a.equal_range(0);
	ASSERT_EQ(*ii.first, 1);
	ASSERT_EQ(*ii.second, 1);
}

TEST(equalRangeTestSet, equal_range_on_non_existing_bigger_than_element_set)
{
	setLLRB<int> a = { 1,2,3,4,5,6,7,8,9,10 };

	auto ii = a.equal_range(11);
	ASSERT_EQ(ii.first, a.end());
	ASSERT_EQ(ii.second, a.end());
}