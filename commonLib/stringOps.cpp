#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "stringOps.h"

namespace common {
	std::string readFile(const char* path) {
		std::ifstream file(path);
		std::string text;

		std::string line;
		while (std::getline(file, line)) {
			text += line;
		}

		file.close();

		return text;
	}

	std::vector<std::string> readLines(const char* path) {
		std::ifstream file(path);
		std::vector<std::string> text;

		std::string line;
		while (std::getline(file, line)) {
			text.emplace_back(line);
		}

		file.close();

		return text;
	}

	// makes a copy of string to not disturb the input
	std::vector<std::string> stringSplit(std::string str, const std::string& delimiter) {
		std::vector<std::string> result;
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			result.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		result.push_back(str);

		return result;
	}

	void removeBlankStringFromStrings(std::vector<std::string>& strings) {
		for (int i = 0; i < strings.size(); ++i) {
			if (strings[i].empty()) {
				strings.erase(strings.begin() + i);
				i--;
			}
		}
	}
}