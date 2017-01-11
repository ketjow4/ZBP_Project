#include <gtest\gtest.h>
#include <mapLLRB.h>


TEST(testConstructorMap, default_constructor_test)
{
	mapLLRB<int,int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(testConstructorMap, default_copy_constructor_test)
{
	auto b = mapLLRB<int, int>();
	ASSERT_EQ(b.size(), 0);
}



TEST(testConstructorMap, initializer_list_constructor_test)
{
	mapLLRB<int, int> a = { {1,1},{ 2,2 },{ 3,3 } };
	ASSERT_EQ(a.size(), 3);
}


TEST(testConstructorMap, initialize_from_copy_test)
{
	auto b = mapLLRB<int, int>();
	b.insert(std::pair<int,int>(1,1));
	mapLLRB<int, int> a(b);
	ASSERT_EQ(a.size(), 1);
}


//---------------------------------------------------------------------------------------------------------------------//
//																													   //
//													 multimap tests													   //
//																													   //
//---------------------------------------------------------------------------------------------------------------------//



TEST(testConstructorMultimultimap, default_constructor_test)
{
	multimapLLRB<int, int> a;
	ASSERT_EQ(a.empty(), true);
}


TEST(testConstructorMultimultimap, default_copy_constructor_test)
{
	auto b = multimapLLRB<int, int>();
	ASSERT_EQ(b.size(), 0);
}



TEST(testConstructorMultimultimap, initializer_list_constructor_test)
{
	multimapLLRB<int, int> a = { { 1,1 },{ 1,1 },{ 2,2 } };
	ASSERT_EQ(a.size(), 3);
}


TEST(testConstructorMultimultimap, initialize_from_copy_test)
{
	auto b = multimapLLRB<int, int>();
	b.insert(std::pair<int, int>(1, 1));
	multimapLLRB<int, int> a(b);
	ASSERT_EQ(a.size(), 1);
}