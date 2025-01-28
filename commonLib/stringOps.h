#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace common {
	std::string readFile(const char* path);

	std::vector<std::string> readLines(const char* path);

	// makes a copy of string to not disturb the input
	std::vector<std::string> stringSplit(std::string str, const std::string& delimiter);

	void removeBlankStringFromStrings(std::vector<std::string>& strings);
}