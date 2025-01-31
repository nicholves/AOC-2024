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

	bool isDigit(const char c) {
		return c >= '0' && c <= '9';
	}

	std::vector<std::string> produceVerticalStrings(const std::vector<std::string>& input) {
		std::vector<std::string> output;

		for (int i = 0; i < input[0].size(); ++i) {
			std::string vertLine;

			for (const std::string& str : input) {
				vertLine += str[i];
			}

			output.push_back(vertLine);
		}

		return output;
	}

	std::vector<std::string> produceDiagonalStrings(const std::vector<std::string>& input, DiagonalDir direction) {
		std::vector<std::string> output;

		if (direction & DiagonalDir::LeftToRight) {
			// count down the vertical
			for (int i = 0; i < input.size(); ++i) {
				std::string str;

				int j = i; // j is the row we are pulling from. J decrements each loop
				int k = 0; // k is the collumn we are pulling from. K increments each loop
				while (j >= 0 && k < input[0].size()) {
					str += input[j--][k++];
				}

				output.push_back(str);
			}

			// we reached the bottom now go accross
			for (int i = 1; i < input[0].size(); ++i) {
				std::string str;

				int j = input.size() - 1; // j is the row we are pulling from. J decrements each loop
				int k = i; // k is the collumn we are pulling from. K increments each loop

				while (j >= 0 && k <= input[0].size()) {
					str += input[j--][k++];
				}

				output.push_back(str);
			}
		}

		if (direction & DiagonalDir::RightToLeft) {
			// count down the vertical
			for (int i = 0; i < input.size(); ++i) {
				std::string str;

				int j = i; // j is the row we are pulling from. J decrements each loop
				int k = input[0].size() - 1; // k is the collumn we are pulling from. K decrements each loop
				while (j >= 0 && k >= 0) {
					str += input[j--][k--];
				}

				output.push_back(str);
			}

			// we reached the bottom now go accross
			for (int i = input[0].size() - 2; i >= 0; --i) {
				std::string str;

				int j = input.size() - 1; // j is the row we are pulling from. J decrements each loop
				int k = i; // k is the collumn we are pulling from. K decrements each loop

				while (j >= 0 && k >= 0) {
					str += input[j--][k--];
				}

				output.push_back(str);
			}
		}

		return output;
	}
}