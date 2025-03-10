/*****************************************
 * Lab 3: exercise 1                      *
 ******************************************/

 /*
AE EM 102
AN PS 190
EM BD 23
CK EM 15
FF CK 17
AE CK 9
PS FF 50
DH FF 35
DH EM 65
PS AN 75
FF CK 18
AE EM 91
JP FF 203
-1 -1 -1
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cmath>


int main() {
	int price = 0; //store the amount of money being transferred
	std::string payer; //store the name of the payer
	std::string receiver; //store the name of the reciver

	std::map<std::string, int> group; //track balance of each person, key are the names values are their balance

	while (std::cin >> payer >> receiver >> price) { //reads input
		if (price < 0) break; //stop loop if price negative
		group[payer] += price; //match the key name and add their price
		group[receiver] -= price; //match the key name and take their money
	}

	//converts map to vector name and balance
	std::vector<std::pair< std::string, int>> V(group.begin(), group.end());
	
	//Sort in descending order of balance
	std::sort(V.begin(), V.end(), [](const auto& a, const auto& b)-> bool {return a.second > b.second; });


	std::cout << "name   Balance\n";

	//Format and print the names and balance
	std::ostream_iterator<std::string> out{ std::cout,"\n" };
	std::transform(V.begin(), V.end(), out, [](const auto& a) {return a.first + "     " + std::to_string(a.second); });

	//Calcualtes totaly amounts of loans
	int loan = std::accumulate(V.begin(), V.end(), 0, [](int acc, const std::pair<std::string, int>& p) {
		return p.second > 0 ? acc + p.second : acc;
		});

	//Calcualtes total debt
	int debt = std::accumulate(V.begin(), V.end(), 0, [](int accc, const std::pair<std::string, int>& pp) {
		return pp.second < 0 ? accc + pp.second : accc;
		});

	debt = abs(debt);
	
	std::cout << "Mean loan amount: " << std::to_string(loan / 4) << std::endl;
	std::cout << "Mean debt amount: " << std::to_string(debt / 5) << std::endl;


}
