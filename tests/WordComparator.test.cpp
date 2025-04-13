#include <snitch/snitch.hpp>

#include <WordComparator.hpp>

// In WordleGame.cpp
std::ifstream validWordsFile("resources/tests/words.test.txt", std::ios_base::beg);
std::ifstream noWordsFile;
std::ifstream invalidvalidWordsFile("resources/tests/random_file_that_doesnt_exist", std::ios_base::beg);

WordComparator comparator(&validWordsFile, 5);

TEST_CASE("Should throw std::invalid_argument if the std::ifstream pointer is nullptr", "[invalid_iftsream_ptr]") {
	REQUIRE_THROWS_AS(WordComparator(nullptr, 5), std::invalid_argument);
}

TEST_CASE("Should accept if the object is created with a valid file", "[closed_ifstream_ptr_file]") {
	INFO("The file is correctly open");
	REQUIRE(validWordsFile.is_open());
}

TEST_CASE("Should reject words that are not exactly 5 letters long") {
	INFO("Testing with 'a'");
	INFO("'a' is not 5 charatcters long");
	REQUIRE_FALSE(comparator.IsAllowed("a"));
}

TEST_CASE("Should accept words that are exactly 5 letters long") {
	REQUIRE(comparator.IsAllowed("house"));
}

TEST_CASE("Should reject words that are not in the dictionary") {
	REQUIRE_FALSE(comparator.IsInList("zzzzz"));
}

TEST_CASE("Should accept words that are in the dictionary") {
	REQUIRE(comparator.IsInList("child"));
}