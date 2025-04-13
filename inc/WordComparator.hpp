#ifndef WORDCOMPARATOR_HPP
#define WORDCOMPARATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

enum class LetterMatch {
	NO_MATCH,
	MISPLACED,
	MATCH
};

class WordComparator {
	public:
		WordComparator() = default;
		WordComparator(std::ifstream* words, size_t lines);
		~WordComparator() = default;

	public:
		bool IsAllowed(std::string const& guess) const;
		bool IsInList(std::string const& guess) const;

		std::array<LetterMatch, 5> Compare(std::string const& guess) const;
		void SetCorrectWord(std::string const& word);

	private:
		bool CheckLength(std::string const& guess) const;
		bool CheckCharacters(std::string const& guess) const;

	private:
		std::ifstream* _words = nullptr;
		size_t _lines = 0;
		std::string _correctWord = "";
};

#endif // !WORDCOMPARATOR_HPP