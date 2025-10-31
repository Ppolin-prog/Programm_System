#pragma once
# include <iostream>
# include <vector>
# include "check.h"
using namespace std;

void Show_Values(vector<int>& values);
int Get_Length_Array();
void Self_Input(vector<int>& values);
void Random_Input(vector<int>& values);
void Random_Range_Input(vector<int>& values);
void Work_With_Data(vector<int>& original_array, vector<int>& sorted_array);
void Primary_Part(void (*Choice_Function)(vector<int>& values), vector<int>& original_array, vector<int>& sorted_array);
void Choice_Save_Into_File(vector<int>& sorted_array);
void Implement_Sort();