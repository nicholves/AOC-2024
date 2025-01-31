#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

#include "stringOps.h"

#define INPUT 1

#if INPUT == 0
	#define PATH "sample.txt"
#else
	#define PATH "puzzle.txt"
#endif

namespace part1 {
	using std::vector, std::string, std::pair, std::unordered_set;

	struct pair_hash {
		inline std::size_t operator()(const std::pair<int, int>& v) const {
			return v.first * 31 + v.second;
		}
	};

	enum class facingDirection {
		Up,
		Right,
		Down,
		Left
	};

	void runSimulation(pair<int, int> guardPos, const unordered_set<pair<int, int>, pair_hash>& blockers, const size_t width, const size_t height, bool* visited) {
		facingDirection dir = facingDirection::Up;

		while (true) {
			const size_t y = guardPos.first;
			const size_t x = guardPos.second;

			visited[y * width + x] = true;

			switch (dir)
			{
			case part1::facingDirection::Up:
				if (y - 1 < 0)
					return;

				if (blockers.find(pair<int, int>(y - 1, x)) != blockers.end()) {
					dir = facingDirection::Right;
				} else {
					guardPos.first--;
				}
				break;
			case part1::facingDirection::Right:
				if (x + 1 >= width)
					return;

				if (blockers.find(pair<int, int>(y, x + 1)) != blockers.end()) {
					dir = facingDirection::Down;
				}
				else {
					guardPos.second++;
				}
				break;
			case part1::facingDirection::Down:
				if (y + 1 >= height)
					return;

				if (blockers.find(pair<int, int>(y + 1, x)) != blockers.end()) {
					dir = facingDirection::Left;
				}
				else {
					guardPos.first++;
				}
				break;
			case part1::facingDirection::Left:
				if (x - 1 < 0)
					return;

				if (blockers.find(pair<int, int>(y, x - 1)) != blockers.end()) {
					dir = facingDirection::Up;
				}
				else {
					guardPos.second--;
				}
				break;
			default:
				break;
			}
		}
	}

	int part1() {
		vector<string> input = common::readLines(PATH);

		size_t width = input[0].length();
		size_t height = input.size();

		bool* visited = new bool[width * height];
		memset(visited, false, width * height);

		unordered_set<pair<int, int>, pair_hash> blockers;
		pair<int, int> guardPos;

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (input[i][j] == '#')
					blockers.emplace(i, j);

				if (input[i][j] == '^') {
					guardPos = pair<int, int>(i, j);
				}
			}
		}

		runSimulation(guardPos, blockers, width, height, visited);

		int total = 0;
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (visited[i * width + j])
					total++;
			}
		}


		std::cout << "The final result on part 1 is: " << total << std::endl;

		delete[] visited;

		return 0;
	}
}