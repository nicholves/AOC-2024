#include <iostream>
#include <string>
#include <algorithm>

#include "stringOps.h"

#define INPUT 2

#if INPUT == 0
	#define PATH "sample.txt"
#endif
#if INPUT == 1
	#define PATH "sample2.txt"
#endif
#if INPUT == 2
	#define PATH "puzzle.txt"
#endif

namespace part2 {
	using std::vector, std::string, std::pair;


	bool chopToDoOperation(string& str);

	bool chopToMulOperation(string& str) {
		string::size_type n = str.find("mul(");
		string::size_type toDont = str.find("don't()");

		if (n == string::npos) {
			return false;
		}
		if (n < toDont) {
			str.erase(str.begin(), str.begin() + n);
			return true;
		}
		
		if (chopToDoOperation(str)) {
			return chopToMulOperation(str);
		}

		return false;
	}

	bool chopToDoOperation(string& str) {
		string::size_type n = str.find("do()");

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

	int part2() {
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


		std::cout << "The final result on part 2 is: " << total << std::endl;

		return 0;
	}

}