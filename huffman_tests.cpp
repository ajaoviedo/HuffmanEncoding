#include <fstream>
#include "catch.hpp"
#include "huffman_encoder.h"

std::string file_as_string(std::string file)
{
    std::ifstream in(file);
    std::string string((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());
    return string;
}

void test_encode_decode(const huffman_encoder &tree, const std::vector<std::string> &files_to_test)
{
    for (std::string file_name : files_to_test)
    {
        std::string encoded_string = tree.encode(file_name);

        bool valid_chars = true;
        for (char c : encoded_string)
        {
            valid_chars &= (c == '0') || (c == '1');
        }
        CHECK(valid_chars);
        CHECK(tree.decode(encoded_string) == file_as_string(file_name));
    }
}

TEST_CASE("Huffman Encoder Iliad")
{
    huffman_encoder tree(frequency_table("texts/iliad_1.txt"));

    std::vector<std::string> files_to_test = {"texts/iliad_1.txt",
                                                "texts/balanced_alphabet.txt",
                                                "texts/litany.txt",
                                                "texts/mississippi.txt",
                                                "texts/single_letter.txt",
                                                "texts/unbalanced_alphabet.txt"};
    test_encode_decode(tree, files_to_test);
}

TEST_CASE("Balanced Tree Code Length")
{
    huffman_encoder tree(frequency_table("texts/balanced_alphabet.txt"));

    std::string encoded_string = tree.encode("texts/balanced_alphabet.txt");
    CHECK(encoded_string.length() == 130);
}

TEST_CASE("Balanced Tree Encode/Decode")
{
    huffman_encoder tree(frequency_table("texts/balanced_alphabet.txt"));

    std::vector<std::string> files_to_test = {"texts/balanced_alphabet.txt",
                                                "texts/unbalanced_alphabet.txt"};
    test_encode_decode(tree, files_to_test);
}

TEST_CASE("Tall Tree Huffman Code Length")
{
    huffman_encoder tree(frequency_table("texts/unbalanced_alphabet.txt"));

    std::string encoded_string = tree.encode("texts/unbalanced_alphabet.txt");
    CHECK(encoded_string.length() == 2035);
}

TEST_CASE("Tall Tree Character Code Lengths")
{
    huffman_encoder tree(frequency_table("texts/unbalanced_alphabet.txt"));

    // for this tree, a and b should have a code length of 9
    // after that, each consecutive letter's code length should
    // decrease by 1 until we get to j, which has a code length of 1
    CHECK(tree.get_character_code('a').length() == 9);
    for (char c = 'b'; c <= 'j'; ++c)
    {
        CHECK(tree.get_character_code(c).length() == 9 - (c - 'b'));
    }
}

TEST_CASE("Tall Tree Encode/Decode")
{
    huffman_encoder tree(frequency_table("texts/unbalanced_alphabet.txt"));

    std::vector<std::string> files_to_test = {"texts/unbalanced_alphabet.txt"};
    test_encode_decode(tree, files_to_test);
}

TEST_CASE("All ASCII Values Code Length")
{
    huffman_encoder tree(frequency_table("texts/all_ascii.txt"));

    std::string encoded_string = tree.encode("texts/all_ascii.txt");
    // every code has a length of 7, except for 1, which has a length of 6
    // so the total length is 126 * 7 + 6 = 888
    CHECK(encoded_string.length() == 888);
}

TEST_CASE("All ASCII Values Encode/Decode")
{
    huffman_encoder tree(frequency_table("texts/all_ascii.txt"));

    std::vector<std::string> files_to_test = {"texts/all_ascii.txt",
                                                "texts/balanced_alphabet.txt",
                                                "texts/iliad_1.txt",
                                                "texts/litany.txt",
                                                "texts/unbalanced_alphabet.txt"};
    test_encode_decode(tree, files_to_test);
}

TEST_CASE("Single Letter Code Length")
{
    huffman_encoder tree(frequency_table("texts/single_letter.txt"));

    std::string encoded_string = tree.encode("texts/single_letter.txt");
    CHECK(encoded_string.length() == 1);
}

TEST_CASE("Single Letter Encode/Decode")
{
    huffman_encoder tree(frequency_table("texts/single_letter.txt"));

    std::vector<std::string> files_to_test = {"texts/single_letter.txt"};
    test_encode_decode(tree, files_to_test);
}

TEST_CASE("Encoding Mississippi Code Length")
{
    huffman_encoder tree(frequency_table("texts/mississippi.txt"));

    std::string encoded_string = tree.encode("texts/mississippi.txt");
    CHECK(encoded_string.length() == 21);
}

TEST_CASE("Encoding Mississippi Encode/Decode")
{
    huffman_encoder tree(frequency_table("texts/mississippi.txt"));

    std::vector<std::string> files_to_test = {"texts/mississippi.txt"};
    test_encode_decode(tree, files_to_test);
}