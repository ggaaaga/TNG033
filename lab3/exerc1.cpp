/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm>

 /*******************************
  * 1. Declarations              *
  ********************************/

  // A function to test the tables created by the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
	const std::string& file_name, int n);

bool checkChar(char s) {

	std::string chars = ".,!?:\"();";

	return chars.find(s) != std::string::npos; //std::string::npos = slutet av strängen
}

bool sortByFreq (const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) {

	if (p1.second == p2.second) {

		return p1.first < p2.first;
	}

	return p1.second > p2.second;
}

/*******************************
 * 2. Main function             *
 *******************************/

int main() {
	std::string name = "uppgift1.txt";
	//std::cout << "text file: ";
	//std::cin >> name;

	std::ifstream in_File{ "../code/" + name };

	if (!in_File) {
		std::cout << "Could not open input file!!\n";
		return 0;
	}

	std::map<std::string, int> table;
	int counter{ 0 };  

	std::string word;
	while (in_File >> word)
	{
		//Lowercase. 
		std::transform(word.begin(), word.end(), word.begin(), tolower);

		//Remove symbols. Erase-remove idiom
		word.erase(
			std::remove_if(word.begin(), word.end(), checkChar),
			word.end());

		//Adds word to table. If word appears more than once the integer is incremented
		table[word]++;

		++counter;
	}

	//Vector freq
	std::vector<std::pair<std::string, int>> freq;

	//Copy table elements into freq
	std::copy(table.begin(), table.end(), std::back_inserter(freq));

	//Sort by frequency
	std::sort(freq.begin(), freq.end(), sortByFreq);

	/* ************** Testing **************** */
	test(table, freq, name, counter);
}

/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
	const std::string& file_name, int n)
{

	std::ifstream file{ "../code/out_" + file_name };

	// Test if stream is in good state
	assert(bool(file) == true);

	std::map<std::string, int> result1;
	std::string word;
	int counter{ 0 };
	int total{ 0 };

	// load expected frequency table sorted alphabetically
	while (file >> word >> counter && counter > 0) {
		result1[word] = counter;
		total += counter;
	}

	/*
	* uppgift1_kort: 69 words
	* uppgift1.txt: 1063 words
	*/

	assert(total == n);  // test if total number of words is correct
	assert(t == result1);

	std::vector<std::pair<std::string, int>> result2;

	// load expected frequency table sorted by frequence
	while (file >> word >> counter) {
		result2.push_back(std::pair{ word, counter });
	}

	assert(v == result2);

	std::cout << "\nPassed all tests successfully!!\n";
}
