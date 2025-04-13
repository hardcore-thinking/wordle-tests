#ifndef WORDLEGAME_HPP
#define WORDLEGAME_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <format>
#include <string>
#include <array>

#include <WordGenerator.hpp>
#include <WordComparator.hpp>

constexpr std::string_view const WORDS_PATH = "resources/words.txt";

class WordleGame {
	public:
		WordleGame();
		~WordleGame();

	public:
		void Start();
		void Stop();

	private:
		bool _playing = false;
		bool _won = false;
		std::ifstream _words {};
		size_t _wordsCount = 0;
		std::string _correctWord = "";
		size_t _turn = 0;
		WordGenerator _generator;
		WordComparator _comparator;
};

#endif // !WORDLEGAME_HPP