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

namespace part1 {
	using std::vector, std::string;

	int countXmasInString(const string& str) {
		string copyStr = str;
		int total = 0;

		// first forward copies
		string::size_type n = copyStr.find("XMAS");
		while (n != string::npos) {
			total++;
			copyStr.erase(copyStr.begin(), copyStr.begin() + n + (sizeof("XMAS") - 2));

			n = copyStr.find("XMAS");
		}

		// now backwards copies
		copyStr = str;
		std::reverse(copyStr.begin(), copyStr.end());

		n = copyStr.find("XMAS");
		while (n != string::npos) {
			total++;
			copyStr.erase(copyStr.begin(), copyStr.begin() + n + (sizeof("XMAS") - 2));

			n = copyStr.find("XMAS");
		}

		return total;
	}

	int countHorizontalXmas(const vector<string>& inputLines) {
		int total = 0;

		for (const string& str : inputLines) {
			total += countXmasInString(str);
		}

		return total;
	}

	int countVerticalXmas(const vector<string>& inputLines) {
		int total = 0;

		vector<string> vertLines = common::produceVerticalStrings(inputLines);

		for (const string& str : vertLines) {
			total += countXmasInString(str);
		}

		return total;
	}

	int countDiagonalXmas(const vector<string>& inputLines) {
		int total = 0;

		vector<string> diagLines = common::produceDiagonalStrings(inputLines, static_cast<common::DiagonalDir>(common::DiagonalDir::LeftToRight | common::DiagonalDir::RightToLeft));

		for (const string& str : diagLines) {
			total += countXmasInString(str);
		}

		return total;
	}

	int part1() {
		vector<string> inputLines = common::readLines(PATH);
		int total = 0;

		total += countHorizontalXmas(inputLines);
		total += countDiagonalXmas(inputLines);
		total += countVerticalXmas(inputLines);

		std::cout << "The final result on part 1 is: " << total << std::endl;

		return 0;
	}
}