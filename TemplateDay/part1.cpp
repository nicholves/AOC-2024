#include <iostream>
#include <string>
#include <algorithm>

#include "stringOps.h"

#define INPUT 0

#if INPUT == 0
	#define PATH "sample.txt"
#else
	#define PATH "puzzle.txt"
#endif

namespace part1 {
	using std::vector, std::string;

	int part1() {
		vector<string> input = common::readLines(PATH);

		//std::cout << "The final result on part 1 is: " << computeSumDistances(leftList, rightList) << std::endl;

		return 0;
	}
}