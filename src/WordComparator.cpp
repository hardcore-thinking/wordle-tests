#include <WordComparator.hpp>

WordComparator::WordComparator(std::ifstream* words, size_t lines) {
	if (words == nullptr) {
		throw std::invalid_argument("The words file cannot be null");
	}

	if (!words->is_open()) {
		throw std::invalid_argument("The words file is not open");
	}

	_words = words;
	_lines = lines;
}

bool WordComparator::IsAllowed(std::string const& guess) const {
	return CheckLength(guess) && CheckCharacters(guess);
}

std::array<LetterMatch, 5> WordComparator::Compare(std::string const& guess) const {
	// matches with only NO_MATCH at the beginning
	std::array<LetterMatch, 5> matches;
	matches.fill(LetterMatch::NO_MATCH);

	// looping through the guess to find matches
	for (size_t i = 0; i < 5; ++i) {
		if (guess[i] == _correctWord[i]) {
			matches[i] = LetterMatch::MATCH;
		}

		else if (std::find(_correctWord.begin(), _correctWord.end(), guess[i]) != _correctWord.end()) {
			matches[i] = LetterMatch::MISPLACED;
		}

		else {
			matches[i] = LetterMatch::NO_MATCH;
		}
	}

	return matches;
}

void WordComparator::SetCorrectWord(std::string const& word) {
	_correctWord = word;
}

bool WordComparator::CheckLength(std::string const& guess) const {
	return guess.size() == 5;
}

bool WordComparator::CheckCharacters(std::string const& guess) const {
	// checking if all characters are alphabetic (case-insensitive)
	return std::all_of(guess.begin(), guess.end(), [&](char c) { return std::isalpha(std::tolower(c)); });
}

bool WordComparator::IsInList(std::string const& guess) const {
	// checking if the word is in the list
	_words->clear();
	_words->seekg(std::ios_base::beg);

	std::string word;
	while (*_words >> word) {
		if (word == guess) {
			return true;
		}
	}
	
	return false;
}
