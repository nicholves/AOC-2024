namespace part1{
	int part1();
}

namespace part2 {
	int part2();
}

int main() {
	part1::part1();

	// run in release for the best results
	part2::part2();

	return 0;
}