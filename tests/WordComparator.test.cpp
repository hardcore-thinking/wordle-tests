#include <snitch/snitch.hpp>

#include <WordComparator.hpp>

// In WordleGame.cpp
std::ifstream validWordsFile("resources/tests/words.test.txt", std::ios_base::beg);
std::ifstream noWordsFile;
std::ifstream invalidvalidWordsFile("resources/tests/random_file_that_doesnt_exist", std::ios_base::beg);
std::string matchingWord = "child";

WordComparator comparator(&validWordsFile, 5);

TEST_CASE("Should throw std::invalid_argument if the std::ifstream pointer is nullptr", "[invalid_iftsream_ptr]") {
	REQUIRE_THROWS_AS(WordComparator(nullptr, 5), std::invalid_argument);
}

TEST_CASE("Should accept if the object is created with a valid file", "[closed_ifstream_ptr_file]") {
	INFO("The file is correctly open");
	REQUIRE(validWordsFile.is_open());
}

TEST_CASE("Should throw std::invalid_argument if the std::ifstream pointer is not open", "[closed_ifstream_ptr_file]") {
	INFO("The file is not open");
	REQUIRE_THROWS_AS(WordComparator(&noWordsFile, 5), std::invalid_argument);
}

TEST_CASE("Should reject words that are not exactly 5 letters long", "[invalid_word_length]") {
	INFO("Testing with 'a'");
	INFO("'a' is not 5 charatcters long");
	REQUIRE_FALSE(comparator.IsAllowed("a"));
}

TEST_CASE("Should accept words that are exactly 5 letters long", "[valid_word_length]") {
	REQUIRE(comparator.IsAllowed("house"));
}

TEST_CASE("Should reject words that are not in the dictionary", "[isnt_in_dictionary]") {
	REQUIRE_FALSE(comparator.IsInList("zzzzz"));
}

TEST_CASE("Should accept words that are in the dictionary", "[is_in_dictionary]") {
	REQUIRE(comparator.IsInList("child"));
}

TEST_CASE("Should reject words that are not alphabetic", "[invalid_word_characters]") {
	INFO("Testing with '123!5'");
	INFO("'123!5' contains non-alphabetic characters");
	REQUIRE_FALSE(comparator.IsAllowed("123!5"));
}

TEST_CASE("Should accept words that match", "[matching_word]") {
	comparator.SetCorrectWord(matchingWord);
	INFO("Testing with 'child'");
	INFO("'child' matches the correct word");
	REQUIRE(comparator.Compare("child") == std::array<LetterMatch, 5>{ LetterMatch::MATCH, LetterMatch::MATCH, LetterMatch::MATCH, LetterMatch::MATCH, LetterMatch::MATCH });
}

TEST_CASE("Should accept words that are misplaced", "[misplaced_word]") {
	comparator.SetCorrectWord(matchingWord);
	INFO("Testing with 'chlid'");
	INFO("'chlid' has 4 letters misplaced");
	REQUIRE(comparator.Compare("chlid") == std::array<LetterMatch, 5>{ LetterMatch::MATCH, LetterMatch::MATCH, LetterMatch::MISPLACED, LetterMatch::MISPLACED, LetterMatch::MATCH });
}

TEST_CASE("Should accept words that are not matching", "[not_matching_word]") {
	comparator.SetCorrectWord(matchingWord);
	INFO("Testing with 'zzzzz'");
	INFO("'zzzzz' has no letters matching");
	REQUIRE(comparator.Compare("zzzzz") == std::array<LetterMatch, 5>{ LetterMatch::NO_MATCH, LetterMatch::NO_MATCH, LetterMatch::NO_MATCH, LetterMatch::NO_MATCH, LetterMatch::NO_MATCH });
}