#ifndef WORDGENERATOR_HPP
#define WORDGENERATOR_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <limits>

class WordGenerator {
	public:
		WordGenerator() = default;
		WordGenerator(std::ifstream* words, size_t files);
		~WordGenerator() = default;

	public:
		std::string Generate();

	private:
		size_t GenerateFileIndex() const;

	private:
		std::ifstream* _words = nullptr;
		size_t _lines = 0;
	};

#endif // !WORDGENERATOR_HPP