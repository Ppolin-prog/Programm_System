# include "pch.h"
# include <gtest/gtest.h>
# include <string>
# include <vector>
# include "sort.h"
# include "check.h"


using namespace std;

TEST(SortTest, RadixSortArray1) {
	vector<int> array1 = {88, 33, 12, 0, 33, 199, 23};
	vector<int> sort_array1;
	vector<int> true_sort_array1 = {0, 12, 23, 33, 33, 88, 199};
	Radix_Sort(array1, sort_array1);
	EXPECT_TRUE(sort_array1 == true_sort_array1);

}

TEST(SortTest, RadixSortArray2) {
	vector<int> sort_array2;
	vector<int> array2 = {38, -33, 32, -12, 99, 3728};
	vector<int> true_sort_array2 = {-33, - 12, 38, 32, 99, 3728};
	Radix_Sort(array2, sort_array2);
	EXPECT_TRUE(sort_array2 == true_sort_array2);

}

TEST(SortTest, RadixSortArray3) {
	vector<int> array3 = {1992, 29, -44, 939, -88, 0, 84, -95};
	vector<int> sort_array3;
	vector<int> true_sort_array3 = {-95, - 88, - 44, 0, 29, 84, 939, 1992};
	Radix_Sort(array3, sort_array3);
	EXPECT_TRUE(sort_array3 == true_sort_array3);

}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	cin.get();
	return RUN_ALL_TESTS();

}