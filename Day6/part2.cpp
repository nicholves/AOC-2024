#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <thread>

#include "stringOps.h"

#define INPUT 1

#if INPUT == 0
	#define PATH "sample.txt"
#else
	#define PATH "puzzle.txt"
#endif

namespace part2 {
	using std::vector, std::string, std::pair, std::unordered_set;

	struct pair_hash {
		inline std::size_t operator()(const std::pair<int, int>& v) const {
			return v.first * 31 + v.second;
		}
	};

	enum facingDirection {
		Up = 1,
		Right = 2,
		Down = 4,
		Left = 8
	};

	void runSimulation(pair<size_t, size_t> guardPos, unordered_set<pair<int, int>, pair_hash> blockers, const size_t width, const size_t height, vector<pair<int, int>> aditionalBlockerLoc, vector<bool>* resultVec) {
		
		int* const visited = new int[width * height];

		pair<size_t, size_t> guardPosOrig = guardPos;

		for (const pair<int, int>& blocker : aditionalBlockerLoc) {
			// reset the run
			facingDirection dir = facingDirection::Up;
			memset(visited, 0, width * height * sizeof(int));
			guardPos = guardPosOrig;


			unordered_set<pair<int, int>, pair_hash> blockerCopy = blockers;
			blockerCopy.insert(blocker);

			while (true) {
				bool shouldBreak = false;
				const int y = guardPos.first;
				const int x = guardPos.second;

				if (visited[y * width + x] & static_cast<int>(dir)) {
					resultVec->push_back(true);
					break;
				}

				visited[y * width + x] = visited[y * width + x] | dir;

				switch (dir)
				{
				case part2::facingDirection::Up:
					if (y - 1 < 0) {
						resultVec->push_back(false);
						shouldBreak = true;
						break;
					}

					if (blockerCopy.find(pair<int, int>(y - 1, x)) != blockerCopy.end()) {
						dir = facingDirection::Right;
					}
					else {
						guardPos.first--;
					}
					break;
				case part2::facingDirection::Right:
					if (x + 1 >= width) {
						resultVec->push_back(false);
						shouldBreak = true;
						break;
					}
					if (blockerCopy.find(pair<int, int>(y, x + 1)) != blockerCopy.end()) {
						dir = facingDirection::Down;
					}
					else {
						guardPos.second++;
					}
					break;
				case part2::facingDirection::Down:
					if (y + 1 >= height) {
						resultVec->push_back(false);
						shouldBreak = true;
						break;
					}

					if (blockerCopy.find(pair<int, int>(y + 1, x)) != blockerCopy.end()) {
						dir = facingDirection::Left;
					}
					else {
						guardPos.first++;
					}
					break;
				case part2::facingDirection::Left:
					if (x - 1 < 0) {
						resultVec->push_back(false);
						shouldBreak = true;
						break;
					}

					if (blockerCopy.find(pair<int, int>(y, x - 1)) != blockerCopy.end()) {
						dir = facingDirection::Up;
					}
					else {
						guardPos.second--;
					}
					break;
				default:
					resultVec->push_back(false);
					break;
				}

				if (shouldBreak)
					break;
			}
		}

		delete[] visited;
	}

	int part2() {
		vector<string> input = common::readLines(PATH);

		const size_t width = input[0].length();
		const size_t height = input.size();

		unordered_set<pair<int, int>, pair_hash> blockers;
		pair<size_t, size_t> guardPos;

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (input[i][j] == '#')
					blockers.emplace(i, j);

				if (input[i][j] == '^') {
					guardPos = pair<size_t, size_t>(i, j);
				}
			}
		}

		
		const auto processor_count = std::thread::hardware_concurrency() - 2;
		vector<std::thread> threads;
		vector<vector<bool>> resultVectors;
		size_t depth = 0;
		size_t workPerThread = (width * height) / processor_count;

		for (int i = 0; i < processor_count; ++i) {
			resultVectors.emplace_back(); // build the correct amount of output vectors
		}

		for (int i = 0; i < processor_count; ++i) {
			vector<pair<int, int>> assignedWork;

			if (i == processor_count - 1) {
				for (; depth < width * height; ++depth) {
					assignedWork.emplace_back(depth / width, depth % width);
				}
			}
			else {
				for (int j = 0; j < workPerThread; ++j) {
					assignedWork.emplace_back(depth / width, depth % width);
;					depth++;
				}
			}

			threads.push_back(std::thread(runSimulation, guardPos, blockers, width, height, assignedWork, &resultVectors[i]));
		}

		for (auto& t : threads) {
			t.join();  // Ensure the main thread waits for each worker thread to finish
		}

		
		int total = 0;
			
		for (const vector<bool>& resultSet : resultVectors) {
			for (const bool result : resultSet) {
				if (result)
					total++;
			}
		}

		// run in realease for best results
		std::cout << "The final result on part 2 is: " << total << std::endl;

		return 0;
	}
}