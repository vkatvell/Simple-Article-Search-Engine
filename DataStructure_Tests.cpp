

/**
 * This file contains some simple tests.
 *
 * DO NOT add the #define CATCH_CONFIG_RUNNER to this file.
 * It is already in catch_setup.cpp
 *
 * Note that you can have more than one cpp file with tests in them.
 * For example, you could have a test file for your DSString and a
 * separate one for your DSVector.
 */

#include <iostream>

// for converting string to wstring then back to string
#include <codecvt>
#include "olestem/stemming/english_stem.h"
#include <string>

#include "catch.hpp"
#include "DSVector.h"


TEST_CASE("DSVector of Integers", "[DSVec_Int]"){

    /**
     * Things that are at the top of a test case but not inside a section are re-declared before the running of
     * each section.
     */
    DSVector<int> empty_vector;
    DSVector<int> test_vector;
    test_vector.pushBack(10);
    test_vector.pushBack(20);

    SECTION("Testing Empty Vector") {
        REQUIRE(empty_vector.getSize() == 0);
        REQUIRE(test_vector.getSize() != 0);
    }

    SECTION("Testing 10 at first pos and 20 at second") {
        REQUIRE(test_vector[0] == 10);
        REQUIRE(test_vector[1] == 20);
    }

    SECTION("Testing that after pushing back a new element, it is in pos 3") {
        test_vector.pushBack(30);
        CHECK(test_vector[2] == 30);
    }

}

TEST_CASE("Stemming library", "[Stemming strings]") {

    SECTION("Testing stemming library") {
        // word to be stemmed needs to be converted to wstring
        std::wstring word(L"tempting");

        std::wcout << L"Original text:\t" << word.c_str() << std::endl;

        stemming::english_stem<> Stem;

        Stem(word);

        std::wcout << L"Stemmed text:\t" << word.c_str() << std::endl;

        std::wstring comp(L"tempt");

        CHECK(comp == word);

    }

    SECTION("Testing stemming library with string class instead of wstring") {

        std::string sourceText = "tempting";

        // converting string to wstr
        std::wstring wstr(sourceText.begin(), sourceText.end());

        std::wcout << L"Original text:\t" << wstr.c_str() << std::endl;

        stemming::english_stem<> Stem;

        // stemming the wstring
        Stem(wstr);

        std::wcout << L"Stemmed text:\t" << wstr.c_str() << std::endl;

        // comparison string
        std::string comp("tempt");

        // converting the wstring back into a string using a wstring_convert from the codecvt library
        std::string str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);

        CHECK(str == comp);
    }

}