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

namespace part2 {
	using std::vector, std::string;

	enum class Operation {
		MULTIPLY,
		ADD,
		CONCAT
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

	void doConcat(uint64_t& src, const uint64_t toConcat) {
		src = _atoi64((std::to_string(src) + std::to_string(toConcat)).c_str());
	}

	bool validateOpSet(uint64_t testValue, const vector<uint64_t>& operands, const vector<Operation>& operations) {
		uint64_t total = operands[0];

		for (size_t i = 0; i < operands.size() - 1; ++i) {
			switch (operations[i])
			{
			case Operation::MULTIPLY:
				total *= operands[i + 1];
				break;
			case Operation::ADD:
				total += operands[i + 1];
				break;
			case Operation::CONCAT:
				doConcat(total, operands[i + 1]);
				break;
			default:
				assert(0 && "unreachable");
				break;
			}
		}

		return total == testValue;
	}

	// Helper function to generate all permutations of operations
	void generatePermutations(const std::vector<Operation>& operations, size_t numOperations,
		vector<Operation>& currentCombination,
		vector<vector<Operation>>& result) {
		if (currentCombination.size() == numOperations) {
			result.push_back(currentCombination);
			return;
		}

		for (const auto& op : operations) {
			currentCombination.push_back(op);
			generatePermutations(operations, numOperations, currentCombination, result);
			currentCombination.pop_back();
		}
	}

	vector<vector<Operation>> computePermutationsOfOperations(const size_t numOperations) {
		// Define the set of operations
		vector<Operation> operations = { Operation::MULTIPLY, Operation::ADD, Operation::CONCAT };
		vector<vector<Operation>> result;
		vector<Operation> currentCombination;

		// Generate the permutations
		generatePermutations(operations, numOperations, currentCombination, result);

		return result;
	}


	bool validateEquation(const Equation& eq) {
		size_t numOperands = eq.operands.size();

		assert(numOperands > 1);

		vector<vector<Operation>> permutations = computePermutationsOfOperations(numOperands - 1);

		for (const vector<Operation>& opsList : permutations) {
			if (validateOpSet(eq.testValue, eq.operands, opsList)) {
				return true;
			}
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

	int part2() {
		vector<string> input = common::readLines(PATH);

		vector<Equation> equations = parseOperands(input);

		vector<uint64_t> validEquations = selectValidEquations(equations);

		uint64_t result = 0;

		for (const uint64_t& valid : validEquations) {
			result += valid;
		}

		std::cout << "The final result on part 2 is: " << result << std::endl;

		return 0;
	}

}