#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <fstream>
#include <cmath>


//Calcualte the distans between two points
double distance(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
	int dx = p1.first - p2.first;
	int dy = p1.second - p2.second;
	return sqrt(pow(dx, 2) + pow(dy, 2));
}


int main() {

	std::ifstream file("C:/Users/julia/Downloads/lab3 (2)/lab3/code/points.txt");

	if (!file.is_open()) {
		std::cerr << "Error";
		return 1;
	}

	std::cout << "The points: \n";


	int x;
	int y;
	char c;
	std::vector<std::pair<int, int>> v;

	while (file >> x >> c >> y) { //read from file
		std::cout << "(" << x << "," << y << ")" << "\n"; //print the point
		v.emplace_back(x, y); //add point to a vector
	}

	//Calculate total distance take each point with innter product
	double d = std::inner_product(std::next(v.begin()), v.end(), v.begin(), 0.0, std::plus<>{}, distance);
	std::cout << "\nDistance traveled = " << d;

	file.close();
}