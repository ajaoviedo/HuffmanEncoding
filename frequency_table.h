#pragma once
#include <map>

using namespace std;

class frequency_table {
    public:
        frequency_table(const std::string &file_name);
        ~frequency_table();
        int get_frequency(char c) const;
		map<char, int> M;// Something to store the frequency of each character
};