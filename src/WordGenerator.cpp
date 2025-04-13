#include <WordGenerator.hpp>

WordGenerator::WordGenerator(std::ifstream* words, size_t lines) {
	// needs a valid words ifstream pointer
	if (words == nullptr) {
		throw std::invalid_argument("The words file cannot be null");
	}

	// but also an opened file in this ifstream
	if (!words->is_open()) {
		throw std::invalid_argument("The words file is not open");
	}
	
	_words = words;
	_lines = lines;
}

size_t WordGenerator::GenerateFileIndex() const {
	// getting an index between zero and the number of lines in the list
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dist(0, _lines - 1);
	return dist(gen);
}

std::string WordGenerator::Generate() {
	size_t index = GenerateFileIndex();
	
	// looping through the list to get the word at the given random index
	_words->clear();
	_words->seekg(std::ios_base::beg);
	for (size_t i = 0; i < index; ++i) {
		_words->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	std::string word = "";
	*_words >> word;

	//std::clog << "[INFO] Generated word: " << word << std::endl;

	return word;
}
