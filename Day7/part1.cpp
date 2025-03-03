#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

#include "stringOps.h"

#define INPUT 1

#if INPUT == 0
	#define PATH "sample.txt"
#else
	#define PATH "puzzle.txt"
#endif

namespace part1 {
	using std::vector, std::string;

	enum class Operation {
		MULTIPLY,
		ADD
	};

	struct Equation {
		uint64_t testValue;
		vector<uint64_t> operands;
	};

	vector<Equation> parseOperands(const vector<string>& input) {
		vector<Equation> result;

		for (const string& str : input) {
			uint64_t testValue;
			vector<uint64_t> operands;
			Equation eq;

			const vector<string> arr = common::stringSplit(str, ":");
			assert(arr.size() == 2);
			testValue = _atoi64(arr[0].c_str());

			vector<string> operandsStrs = common::stringSplit(arr[1], " ");
			operandsStrs.erase(operandsStrs.begin()); // clear the blank space
			for (const string& num : operandsStrs) {
				operands.push_back(_atoi64(num.c_str()));
			}

			eq.testValue = testValue;
			eq.operands = operands;

			result.push_back(eq);
		}

		return result;
	}

	bool validateOpSet(uint64_t testValue, const vector<uint64_t>& operands, const vector<Operation>& operations) {
		uint64_t total = operands[0];

		for (size_t i = 0; i < operands.size() - 1; ++i) {
			if (operations[i] == Operation::ADD) {
				total += operands[i + 1];
			}
			else {
				total *= operands[i + 1];
			}
		}

		return total == testValue;
	}


	bool validateEquation(const Equation& eq) {
		size_t numOperands = eq.operands.size();

		assert(numOperands > 1);

		int total = 0;
		for (int i = 0; i < pow(2, numOperands - 1); ++i) {
			vector<Operation> opsList;

			for (int j = 0; j < numOperands - 1; ++j) {
				bool flag = total & (1 << j);

				opsList.push_back(flag ? Operation::MULTIPLY : Operation::ADD);
			}

			if (validateOpSet(eq.testValue, eq.operands, opsList)) {
				return true;
			}

			total++;
		}

		return false;
	}

	vector<uint64_t> selectValidEquations(const vector<Equation>& equations) {
		vector<uint64_t> result;

		for (const Equation& eq : equations) {
			if (validateEquation(eq)) {
				result.push_back(eq.testValue);
			}
		}

		return result;
	}

	int part1() {
		vector<string> input = common::readLines(PATH);

		vector<Equation> equations = parseOperands(input);

		vector<uint64_t> validEquations = selectValidEquations(equations);

		uint64_t result = 0;

		for (const uint64_t& valid : validEquations) {
			result += valid;
		}

		std::cout << "The final result on part 1 is: " << result << std::endl;

		return 0;
	}
}