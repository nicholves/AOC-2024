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

namespace part2 {
	using std::vector, std::string;

	int part2() {
		vector<string> input = common::readLines(PATH);

		//std::cout << "The final rersult on part 2 is: " << computeSumSimilarity(leftList, rightList) << std::endl;

		return 0;
	}

}