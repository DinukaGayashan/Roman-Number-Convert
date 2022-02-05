/********************************************************************
Course		:	CO2210 Programming Quest
Quest No	:	02
Title		:	Roman Number Converter
Author		:	Kasthuriarachchi K.A.D.G.
Index No	:	19/ENG/053
Date		:	14-09-2021
********************************************************************/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*---------------------------------------------------------------------------------
Function            :	get_input
Description         :	getting input from the text file "Roman_numbers.txt"
Input Parameters    :	-
Return              :	string vector of numbers in the text file
---------------------------------------------------------------------------------*/
vector<string> get_input()
{
	//initializing vector to get inputs
	vector<string> nums;
	
	//initializing the text file to take inputs
	ifstream roman_numbers;
	roman_numbers.open("Roman_numbers.txt");
	
	//taking all the numbers to the vector 
	string num;
	while (roman_numbers >> num)
		nums.push_back(num);

	return nums;
}

/*---------------------------------------------------------------------------------
Function            :	roman_initialize
Description         :	initial checking of the number and replacing all possible
						characters with capital letters
Input Parameters    :	&num - reference of the Roman number string
Return              :	boolean value to inicate whether it contains convertable 
						values or not
---------------------------------------------------------------------------------*/
bool roman_initialize(string &num)
{
	//checking every character in a number
	for (int i = 0; i < num.size(); i++)
	{
		//if the character is a Roman making it capital
		if (num[i] == 'i' || num[i] == 'I')
			num[i] = 'I';
		else if (num[i] == 'v' || num[i] == 'V')
			num[i] = 'V';
		else if (num[i] == 'x' || num[i] == 'X')
			num[i] = 'X';
		else if (num[i] == 'l' || num[i] == 'L')
			num[i] = 'L';
		else if (num[i] == 'c' || num[i] == 'C')
			num[i] = 'C';
		//return false if any character is not a roman character
		else
			return false;
	}
	//return true if all characters are fine
	return true;
}

/*---------------------------------------------------------------------------------
Function            :	hindhuarabic_to_roman
Description         :	converting a Hindhu-Arabic number to Roman number 
Input Parameters    :	num - Hindhu-Arabic number
Return              :	Roman number string
---------------------------------------------------------------------------------*/
string hindhuarabic_to_roman(int num)
{
	//initializing string to Roman number
	string roman = "";

	//loop while the number is in the convertable range
	while (num > 0 && num <= 100)
	{
		//initializing variables to find Roman number
		int val = 0;
		string symbol = "";

		//assigning variables according to the number left to convert
		if (num / 100 > 0)
		{
			val = 100;
			symbol = "C";
		}
		else if (num / 90 > 0)
		{
			val = 90;
			symbol = "XC";
		}
		else if (num / 50 > 0)
		{
			val = 50;
			symbol = "L";
		}
		else if (num / 40 > 0)
		{
			val = 40;
			symbol = "XL";
		}
		else if (num / 10 > 0)
		{
			val = 10;
			symbol = "X";
		}
		else if (num / 9 > 0)
		{
			val = 9;
			symbol = "IX";
		}
		else if (num / 5 > 0)
		{
			val = 5;
			symbol = "V";
		}
		else if (num / 4 > 0)
		{
			val = 4;
			symbol = "IV";
		}
		else if (num / 1 > 0)
		{
			val = 1;
			symbol = "I";
		}

		//appending symbols according to the value
		for (int i = 0; i < num / val; i++)
			roman += symbol;

		//reassigning number by subtracting the value of added symbols
		num %= val;
	}
	return roman;
}

/*---------------------------------------------------------------------------------
Function            :	roman_to_hindhuarabic
Description         :	converting a Roman number to Hindhu-Arabic number
Input Parameters    :	num - Roman number
Return              :	Hindhu-Arabic number
---------------------------------------------------------------------------------*/
int roman_to_hindhuarabic(string num)
{
	//initializing variables to assign Hindhu-Arabic number values
	vector<int> individual_values;
	int value = 0;

	//looping through every character
	for (int i = 0; i < num.size(); i++)
	{
		//assigning corresponding value to the vector
		if (num[i] == 'I')
			individual_values.push_back(1);
		else if (num[i] == 'V')
			individual_values.push_back(5);
		else if (num[i] == 'X')
			individual_values.push_back(10);
		else if (num[i] == 'L')
			individual_values.push_back(50);
		else if (num[i] == 'C')
			individual_values.push_back(100);
	}
	
	//calculating the value by looping till the second last element
	for (int i = 0; i < individual_values.size() - 1; i++)
	{
		//if the right side value has higher presidence, subtract value
		if (individual_values[i + 1] > individual_values[i])
			value -= individual_values[i];
		//if the right side value has lower presidence, add value
		else
			value += individual_values[i];
	}
	//always add the last value
	value += individual_values[individual_values.size() - 1];
	
	return value;
}

int main()
{
	//making two vectors to take the input and a copy to print
	vector<string> input_nums = get_input();
	vector<string> input_nums_copy = input_nums;

	//looping through all the items in the vector
	for (int i = 0; i < input_nums.size(); i++)
	{
		//variable to initial check the Roman number
		bool initialized = roman_initialize(input_nums[i]);
		
		//printing the Roman number in the text file
		cout << input_nums_copy[i] << " = ";

		//checking whether the Roman number is correct
		if (initialized)
		{
			//assigning value with the converted number to Hindhu-Arabic
			int value = roman_to_hindhuarabic(input_nums[i]);

			/*
			to check a number that can correctly be converted
			to Hindhu-Arabic, following method is used

			checking whether the initial Roman number is equal to the
			Roman number obtained by converting back Hindhu-Arabic number

			ex:
				checking XIX
					XIX = 19
					19 = XIX
					thus, convertion is correct

				checking IXX
					IXX = 19
					19 = XIX
					thus, convertion is wrong
			*/
			if (input_nums[i] == hindhuarabic_to_roman(value))
				cout << value << endl;

			//printing error if convertion cannot be done
			else
				cerr << "error" << endl;
		}
		//printing error if number is incorrect
		else
			cerr << "error" << endl;
	}

	return 0;
}