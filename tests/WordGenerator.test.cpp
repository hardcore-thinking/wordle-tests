#include <array>
#include <algorithm>

#include <snitch/snitch.hpp>

#include <WordGenerator.hpp>

// In WordleGame.cpp
std::ifstream generatorValidWordsFile("resources/tests/words.test.txt");
std::ifstream generatorNoWordsFile;
std::ifstream generatorInvalidWordsFile("resources/tests/random_file_that_doesnt_exist");
std::string generatorMatchingWord = "child";
std::array<std::string, 5> validWords = { "abode", "child", "gooey", "sumac", "twice" };

WordGenerator generator(&generatorValidWordsFile, 5);

TEST_CASE("Should throw std::invalid_argument if the std::ifstream pointer is nullptr", "[generator_invalid_iftsream_ptr]") {
	REQUIRE_THROWS_AS(WordGenerator(nullptr, 5), std::invalid_argument);
}

TEST_CASE("Should accept if the object is created with a valid file", "[generator_closed_ifstream_ptr_file]") {
	INFO("The file is correctly open");
	REQUIRE(generatorValidWordsFile.is_open());
}

TEST_CASE("Should throw std::invalid_argument if the std::ifstream pointer is not open", "[generator_closed_ifstream_ptr_file]") {
	INFO("The file is not open");
	REQUIRE_THROWS_AS(WordGenerator(&generatorNoWordsFile, 5), std::invalid_argument);
}

TEST_CASE("Should generate a valid word from the dictionary", "[generator_valid_word]") {
	std::string generatedWord = generator.Generate();
	INFO("Testing with '", generatedWord, "'");
	REQUIRE(std::find(validWords.begin(), validWords.end(), generatedWord) != validWords.end());
}