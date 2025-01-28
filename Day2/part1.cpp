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

	vector<int> reportIntoNumList(const string& report) {
		vector<string> nums = common::stringSplit(report, " ");
		
		vector<int> results;

		for (const string& num : nums) {
			results.emplace_back(atoi(num.c_str()));
		}

		return results;
	}

	bool allStable(const vector<int>& nums) {
		bool incrementing;

		if (nums.size() < 2 || nums[0] == nums[1]) {
			return false;
		}

		incrementing = (nums[1] - nums[0]) > 0;

		for (int i = 0; i < nums.size() - 1; ++i) {
			if (incrementing) {
				if ((nums[i + 1] - nums[i]) <= 0)
					return false;
			}

			else {
				if ((nums[i + 1] - nums[i]) >= 0)
					return false;
			}

			if (abs(nums[i + 1] - nums[i]) < 1 || abs(nums[i + 1] - nums[i]) > 3)
				return false;
		}

		return true;
	}

	bool safeReport(const string& report) {
		vector<int> reportValues = reportIntoNumList(report);

		return allStable(reportValues);
	}

	int part1() {
		vector<string> reports = common::readLines(PATH);

		int count = 0;

		for (int i = 0; i < reports.size(); ++i) {
			if (safeReport(reports[i]))
				count++;
		}

		std::cout << "The final result on part 1 is: " << count << std::endl;

		return 0;
	}
}