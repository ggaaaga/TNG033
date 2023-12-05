/*****************************************
 * Lab 3: exercise 2                      *
 * Anagrams table                         *
 ******************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility> 
#include <fstream>
#include <cassert>
#include <algorithm>

int main() {
	std::string name = "uppgift2_kort.txt";
	//std::cout << "text file: ";
	//std::cin >> name;

	std::ifstream file{ "../code/" + name };

	if (!file) {
		std::cout << "Could not open input file!!\n";
		return 0;
	}

	int counter{ 0 };
	std::vector<std::string> words;

	//Read lines
	std::copy(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(), std::back_inserter(words)); //Bryter vid whitespaces

	std::sort(words.begin(),words.end());
	counter = words.size();
	words.erase(std::unique(words.begin(), words.end()), words.end());

	std::vector<std::string> subjects;

	//Create subjects
	std::transform(words.begin(), words.end(), std::back_inserter(subjects),
		[](std::string word) {
			std::sort(word.begin(), word.end());
			return word;
		});

	//Find anagrams
	std::map<std::string, std::vector<std::string>> anagrams;

	std::transform(subjects.begin(), subjects.end(), words.begin(), std::inserter(anagrams, anagrams.end()),
		[&](const std::string& subject, const std::string& word) { //Lambda expression 
			auto it = anagrams.find(subject);
			if (it != anagrams.end()) { //Om den hittar, pusback ordet vid den subject
				it->second.push_back(word);
			}
			else {
				anagrams[subject] = std::vector<std::string>{ word };
			}

			return std::make_pair(subject, std::vector<std::string>{});

		});

	//Output
	std::cout << "Number of words = " << counter;
	std::cout << "\n\n-- ANAGRAMS --\n";

	std::for_each(anagrams.begin(), anagrams.end(),
		[&](const auto& p) {
			if (p.second.size() >= 2) {
				std::copy(p.second.begin(), p.second.end(), std::ostream_iterator<std::string>(std::cout, " "));
				std::cout << " --> " << p.second.size() << " words.\n";
			}
		});
}