
/**************************
 * Lab 3: exercise 3      *
 **************************/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <fstream>
#include <cmath>
#include <set>


std::string sorted(const std::string& word) {
	std::string sort = word;//copy of the input
	std::sort(sort.begin(), sort.end()); //Sort the word 
	return sort; //return sorted version
}


int main() {

	std::ifstream input("C:/Users/julia/Downloads/lab3 (2)/lab3/code/uppgift3_kort.txt");
	std::ofstream output("C:/Users/julia/Downloads/lab3 (2)/lab3/code/uppgift3_kort_out.txt");

	if (!input.is_open()) {
		std::cerr << "Error input";
		return 1;
	}

	if (!output.is_open()) {
		std::cerr << "Error output";
		return 1;
	}

	//Key is the sorted version, set of all the words that match the key
	std::map<std::string, std::set<std::string>> group;

	//read word from file
	std::string word;
	while (input >> word) {
		std::string sort = sorted(word); //sorted version of word
		group[sort].insert(word); //Add hte word to the set of its sorted key
	}

	input.close();


	//write anagrams to output
	for (const auto& x : group) { //Iterates through group 
		if(x.second.size() > 1){ //check if size of set greater than 1
		output << "Anagram group (" << x.second.size() << " words): ";
		
		//copies all the elemetns in a range of teh std::set, iterator write out each element
		std::copy(x.second.begin(), x.second.end(), std::ostream_iterator<std::string>(output, " "));
		output << std::endl;
		}
	}


	output.close();

	std::cout << "Anargrams have been written"; 
	return 0;
}
