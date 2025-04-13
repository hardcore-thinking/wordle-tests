#include <iostream>
#include <cstdlib>

#include <WordleGame.hpp>

int main() {
	try {
		WordleGame game;

		game.Start();
	}

	catch (std::runtime_error const& e) {
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}