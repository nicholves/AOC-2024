#include <iostream>
#include <string>
#include <algorithm>

#include "stringOps.h"

#define INPUT 1

#if INPUT == 0
	#define PATH "sample.txt"
#else
	#define PATH "puzzle.txt"
#endif

namespace part2 {
	using std::vector, std::string, std::pair;

	typedef vector<pair<vector<pair<int, int>>, string>> stringWCoords;

	vector<pair<int, int>> findMasInString(const pair<vector<pair<int, int>>, string>& stringAndCoords) {
		string copyStr = stringAndCoords.second;
		vector<pair<int, int>> output;

		// first forward copies
		string::size_type n = copyStr.find("MAS");
		size_t depth = 0;
		while (n != string::npos) {
			copyStr.erase(copyStr.begin(), copyStr.begin() + n + (sizeof("MAS") - 1));
			output.emplace_back(stringAndCoords.first[depth + n + 1]);
			depth += n + sizeof("MAS") - 1;

			n = copyStr.find("MAS");
		}

		// now backwards copies
		copyStr = stringAndCoords.second;
		depth = 0;

		n = copyStr.find("SAM");
		while (n != string::npos) {
			copyStr.erase(copyStr.begin(), copyStr.begin() + n + (sizeof("SAM") - 1));
			output.emplace_back(stringAndCoords.first[depth + n + 1]);
			depth += n + sizeof("SAM") - 1;

			n = copyStr.find("SAM");
		}


		return output;
	}

	stringWCoords produceDiagonalStringsWithCoords(const std::vector<std::string>& input, common::DiagonalDir direction) {
		stringWCoords output;

		if (direction & common::DiagonalDir::LeftToRight) {
			// count down the vertical
			for (int i = 0; i < input.size(); ++i) {
				std::string str;
				vector<pair<int, int>> coords;

				int j = i; // j is the row we are pulling from. J decrements each loop
				int k = 0; // k is the collumn we are pulling from. K increments each loop
				while (j >= 0 && k < input[0].size()) {
					str += input[j--][k++];
					coords.emplace_back(j + 1, k - 1);
				}

				output.emplace_back(coords, str);
			}

			// we reached the bottom now go accross
			for (int i = 1; i < input[0].size(); ++i) {
				std::string str;
				vector<pair<int, int>> coords;

				int j = input.size() - 1; // j is the row we are pulling from. J decrements each loop
				int k = i; // k is the collumn we are pulling from. K increments each loop

				while (j >= 0 && k <= input[0].size()) {
					str += input[j--][k++];
					coords.emplace_back(j + 1, k - 1);
				}

				output.emplace_back(coords, str);
			}
		}

		if (direction & common::DiagonalDir::RightToLeft) {
			// count down the vertical
			for (int i = 0; i < input.size(); ++i) {
				std::string str;
				vector<pair<int, int>> coords;

				int j = i; // j is the row we are pulling from. J decrements each loop
				int k = input[0].size() - 1; // k is the collumn we are pulling from. K decrements each loop
				while (j >= 0 && k >= 0) {
					str += input[j--][k--];
					coords.emplace_back(j + 1, k + 1);
				}

				output.emplace_back(coords, str);
			}

			// we reached the bottom now go accross
			for (int i = input[0].size() - 2; i >= 0; --i) {
				std::string str;
				vector<pair<int, int>> coords;

				int j = input.size() - 1; // j is the row we are pulling from. J decrements each loop
				int k = i; // k is the collumn we are pulling from. K decrements each loop

				while (j >= 0 && k >= 0) {
					str += input[j--][k--];
					coords.emplace_back(j + 1 , k + 1);
				}

				output.emplace_back(coords, str);
			}
		}

		return output;
	}

	int part2() {
		vector<string> input = common::readLines(PATH);

		stringWCoords leftToRight = produceDiagonalStringsWithCoords(input, common::DiagonalDir::LeftToRight);
		stringWCoords rightToLeft = produceDiagonalStringsWithCoords(input, common::DiagonalDir::RightToLeft);

		vector<pair<int, int>> leftToRightSam;
		vector<pair<int, int>> rightToLeftSam;

		for (const auto& line : leftToRight) {
			auto temp = findMasInString(line);
			leftToRightSam.insert(leftToRightSam.end(), temp.begin(), temp.end());
		}

		for (const auto& line : rightToLeft) {
			auto temp = findMasInString(line);
			rightToLeftSam.insert(rightToLeftSam.end(), temp.begin(), temp.end());
		}

		int total = 0;
		for (const auto& pair : leftToRightSam) {
			if (std::find(rightToLeftSam.begin(), rightToLeftSam.end(), pair) != rightToLeftSam.end()) {
				total++;
			}
		}


		std::cout << "The final rersult on part 2 is: " << total << std::endl;

		return 0;
	}

}