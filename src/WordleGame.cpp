#include <WordleGame.hpp>

WordleGame::WordleGame() {
	// opening word list
	_words.open(WORDS_PATH.data());
	if (!_words.is_open()) {
		throw std::runtime_error("[ERROR] Failed to open words file");
	}
	std::clog << "[INFO] Opened words file at " << WORDS_PATH << std::endl;

	_words.seekg(std::ios_base::beg);

	// counting words in the file
	std::string word = "";
	while (std::getline(_words, word)) {
		++_wordsCount;
	}

	std::clog << "[INFO] Loaded " << _wordsCount << " words" << std::endl;

	// creating word processors
	_generator = WordGenerator(&_words, _wordsCount);
	std::clog << "[INFO] Word generator ready" << std::endl;
	
	_comparator = WordComparator(&_words, _wordsCount);
	std::clog << "[INFO] Word comparator ready" << std::endl;

	std::cout << std::endl;
}

WordleGame::~WordleGame() {
	_words.close();

	std::clog << "[INFO] Closed words file at " << WORDS_PATH << std::endl;
}

void WordleGame::Start() {
	_playing = true;
	_won = false;
	while (_playing) {
		// taking a random word in the list
		_correctWord = _generator.Generate();
		_comparator.SetCorrectWord(_correctWord);

		// looping for the 6 attempts
		std::cout << "You have 6 attempts" << std::endl;
		_turn = 0;
		_won = false;
		while (_turn < 6) {
			std::string guess;

			// user input and invalid inputs handling
			std::cout << "[Attempt " << _turn + 1 << "] >>> ";
			std::cin >> guess;
			while (!_comparator.IsAllowed(guess)) {
				std::cout << "Please enter a valid string containing only 5 letters (a-z)" << std::endl;
				std::cout << ">>> ";
				std::cin >> guess;
			}

			if (!_comparator.IsInList(guess)) {
				std::cout << "The word is not in the list" << std::endl;
				continue;
			}

			// getting letters match status
			std::array<LetterMatch, 5> matches = _comparator.Compare(guess);

			// displaying status to the user
			for (auto& match : matches) {
				switch (match) {
					case LetterMatch::NO_MATCH:
						std::cout << "N";
						break;

					case LetterMatch::MISPLACED:
						std::cout << "M";
						break;

					case LetterMatch::MATCH:
						std::cout << "Y";
						break;
				}
			}

			std::cout << std::endl;

			// checking if all letters match
			if (std::all_of(matches.begin(), matches.end(), [](LetterMatch match) { return match == LetterMatch::MATCH; })) {
				_won = true;
				std::cout << std::endl;
				std::cout << "Congratulations! You found the word!" << std::endl;
				std::cout << std::endl;
				break;
			}

			// next turn
			_turn++;
		}

		if (!_won) {
			std::cout << std::endl;
			std::cout << "You lose! The word was: " << _correctWord << std::endl;
		}

		_playing = false;
	}
}

void WordleGame::Stop() {
	_playing = false;
}