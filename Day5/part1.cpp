#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>

#include "stringOps.h"

#define INPUT 1

#if INPUT == 0
	#define PATH "sample.txt"
#else
	#define PATH "puzzle.txt"
#endif

namespace part1 {
	using std::vector, std::string, std::map, std::set;

	map<int, set<int>> rules;

	map<int, set<int>> buildRules(const vector<string>& lines) {
		map<int, set<int>> rules;

		for (const string& line : lines) {
			auto numsList = common::stringSplit(line, "|");

			int firstNum = atoi(numsList[0].c_str());
			int secondNum = atoi(numsList[1].c_str());

			rules[secondNum].insert(firstNum);
		}

		return rules;
	}

	bool validateLine(const string& line) {
		vector<string> numsS = common::stringSplit(line, ",");
		// turn it into a list of numbers
		vector<int> nums;

		for (const auto& strNum : numsS) {
			nums.push_back(atoi(strNum.c_str()));
		}

		set<int> existingNums;

		// build the set of letters that exist in the string
		for (int num : nums) {
			existingNums.insert(num);
		}


		// validate iteratively
		set<int> seenSoFar;
		
		for (int num : nums) {
			if (rules.find(num) != rules.end()) {
				// if the number has a rule then all the numbers in the value of the rule must be in the seenSoFarSet
				for (const int& requirement : rules[num]) {
					if (seenSoFar.find(requirement) == seenSoFar.end() && existingNums.find(requirement) != existingNums.end())
						return false;
				}
			}

			seenSoFar.insert(num);
		}

		return true;
	}
	
	int part1() {
		vector<string> input = common::readLines(PATH);

		vector<string> rulesLines;
		vector<string> updateLines;

		for (int i = 0; i < input.size(); ++i) {
			if (input[i].empty()) {
				rulesLines.insert(rulesLines.begin(), input.begin(), input.begin() + i);
				updateLines.insert(updateLines.begin(), input.begin() + i + 1, input.end());

				break;
			}
		}

		rules = buildRules(rulesLines);

		vector<string> validLines;

		std::copy_if(updateLines.begin(), updateLines.end(), std::back_inserter(validLines), validateLine);

		int result = 0;

		for (const string& line : validLines) {
			vector<string> numsS = common::stringSplit(line, ",");
			// turn it into a list of numbers
			vector<int> nums;

			for (const auto& strNum : numsS) {
				nums.push_back(atoi(strNum.c_str()));
			}

			result += nums[nums.size() / 2];
		}

		std::cout << "The final result on part 1 is: " << result << std::endl;

		return 0;
	}
}