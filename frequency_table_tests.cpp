#include <fstream>
#include "catch.hpp"
#include "frequency_table.h"

const int alphabet_size = 128;

TEST_CASE("Iliad")
{
    frequency_table table("texts/iliad_1.txt");
    int expected_freqs[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 106, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5806, 1, 116, 0, 0, 0, 0, 11, 2, 2, 0, 0, 495, 49, 208, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 49, 0, 0, 0, 16, 0, 143, 15, 27, 9, 5, 8, 9, 19, 95, 35, 5, 9, 17, 11, 28, 24, 0, 0, 24, 64, 4, 3, 27, 0, 13, 0, 0, 0, 0, 0, 0, 0, 1768, 327, 382, 1019, 2946, 567, 470, 1840, 1299, 15, 142, 971, 620, 1488, 1949, 350, 18, 1413, 1559, 1916, 708, 247, 552, 11, 567, 15, 0, 0, 0, 0, 0};
    for(int i = 0; i < alphabet_size; ++i) {
        CHECK(table.get_frequency(static_cast<char>(i)) == expected_freqs[i]);
    }
}

TEST_CASE("Balanced Tree")
{
    frequency_table table("texts/balanced_alphabet.txt");
    for(int i = 0; i < 26; ++i) {
        CHECK(table.get_frequency('a'+i) == 1);
    }
}

TEST_CASE("Tall Tree")
{
    frequency_table table("texts/unbalanced_alphabet.txt");
    for(int i = 0; i < 10; ++i) {
        CHECK(table.get_frequency('a'+i) == (1 << i));
    }
}

TEST_CASE("All ASCII Values")
{
    frequency_table table("texts/all_ascii.txt");
    for(int i = 0; i < alphabet_size; ++i) {
        if(i != 26) {
            CHECK(table.get_frequency(static_cast<char>(i)) == 1);
        }
    }
}

TEST_CASE("Single Letter")
{
    frequency_table table("texts/single_letter.txt");
    CHECK(table.get_frequency('x') == 1);
}

TEST_CASE("Mississippi")
{
    frequency_table table("texts/mississippi.txt");
    CHECK(table.get_frequency('m') == 1);
    CHECK(table.get_frequency('i') == 4);
    CHECK(table.get_frequency('s') == 4);
    CHECK(table.get_frequency('p') == 2);
}

TEST_CASE("Litany")
{
    frequency_table table("texts/litany.txt");
    int expected_freqs[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 3, 1, 4, 32, 4, 5, 15, 20, 0, 1, 17, 7, 16, 11, 4, 0, 16, 11, 27, 3, 1, 6, 0, 3, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < alphabet_size; ++i) {
        CHECK(table.get_frequency(static_cast<char>(i)) == expected_freqs[i]);
    }    
}

TEST_CASE("Throws when files doesn't exist") {
    try {
        frequency_table table("texts/uh_oh_does_not_exist.txt");
        CHECK(false);
    } catch(std::runtime_error) {
        CHECK(true);
    }
}