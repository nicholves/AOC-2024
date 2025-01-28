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

	using std::pair, std::vector, std::string;

	pair<vector<int>, vector<int>> makeLists(const vector<string>& list) {
		vector<int> leftList;
		vector<int> rightList;

		for (const string& line : list) {
			vector<string> elements = common::stringSplit(line, " ");

			common::removeBlankStringFromStrings(elements);

			leftList.emplace_back(atoi(elements[0].c_str()));
			rightList.emplace_back(atoi(elements[1].c_str()));
		}

		return pair<vector<int>, vector<int>>(leftList, rightList);
	}

	int computeSumDistances(const vector<int>& leftList, const vector<int>& rightList) {
		int total = 0;

		for (int i = 0; i < leftList.size(); ++i) {
			total += abs(leftList[i] - rightList[i]);
		}

		return total;
	}

	int part1() {
		vector<string> input = common::readLines(PATH);

		pair<vector<int>, vector<int>> lists = makeLists(input);

		vector<int>& leftList = lists.first;
		vector<int>& rightList = lists.second;

		std::sort(leftList.begin(), leftList.end());
		std::sort(rightList.begin(), rightList.end());

		std::cout << "The final result on part 1 is: " << computeSumDistances(leftList, rightList) << std::endl;

		return 0;
	}
}