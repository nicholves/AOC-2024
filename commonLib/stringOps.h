#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace common {
	enum DiagonalDir {
		LeftToRight = 1,
		RightToLeft = 2
	};

	std::string readFile(const char* path);

	std::vector<std::string> readLines(const char* path);

	// makes a copy of string to not disturb the input
	std::vector<std::string> stringSplit(std::string str, const std::string& delimiter);

	void removeBlankStringFromStrings(std::vector<std::string>& strings);

	bool isDigit(const char c);

	std::vector<std::string> produceVerticalStrings(const std::vector<std::string>& input);
	std::vector<std::string> produceDiagonalStrings(const std::vector<std::string>& input, DiagonalDir direction);
}