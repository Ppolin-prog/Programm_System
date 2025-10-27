#pragma once
# include <iostream>
# include <vector>
using namespace std;

int Number_Length(int number);
int Max_Length(vector<int>& original);
void Sort_Funktion(vector<int>& array, int position = 0, int max_len = -1);
void Radix_Sort(vector<int>& original, vector<int>& sorted);