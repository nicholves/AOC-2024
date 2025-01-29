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
	using std::vector, std::string, std::pair;

	bool chopToMulOperation(string& str) {
		string::size_type n = str.find("mul(");

		if (n == string::npos) {
			return false;
		}

		str.erase(str.begin(), str.begin() + n);

		return true;
	}

	pair<int, int>* extractMul(string& str) {
		while (true) { 
			loop:
			if (!chopToMulOperation(str)) {
				return nullptr;
			}

			str.erase(str.begin(), str.begin() + sizeof("mul"));
			// up to three digits
			string firstDigit = "";
			int i;
			for (i = 0; i < 3; ++i) {
				if (common::isDigit(str[0])) {
					firstDigit += str[0];
					str.erase(str.begin());
					continue;
				}

				if (str[0] == ',') {
					if (i == 0)
						goto loop;

					break;
				}
			}

			// remove the ,
			if (str[0] != ',') {
				goto loop;
			}

			str.erase(str.begin());

			string secondDigit = "";
			for (i = 0; i < 3; ++i) {
				if (common::isDigit(str[0])) {
					secondDigit += str[0];
					str.erase(str.begin());
					continue;
				}

				if (str[0] == ')') {
					if (i == 0)
						goto loop;

					break;
				}
			}

			// remove the ,
			if (str[0] != ')') {
				goto loop;
			}

			str.erase(str.begin());

			return new pair<int, int>(atoi(firstDigit.c_str()), atoi(secondDigit.c_str()));
		}

		return nullptr;
	}

	int part1() {
		string input = common::readFile(PATH);

		vector<pair<int, int>*> mulOps;

		pair<int, int>* mulOp = extractMul(input);

		while (mulOp != nullptr) {
			mulOps.push_back(mulOp);

			mulOp = extractMul(input);
		}

		int total = 0;

		for (pair<int, int>* mulOp : mulOps) {
			total += mulOp->first * mulOp->second;

			delete mulOp;
		}


		std::cout << "The final result on part 1 is: " << total << std::endl;

		return 0;
	}
}