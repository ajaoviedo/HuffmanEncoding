#include "frequency_table.h"
#include <fstream>

using namespace std;

frequency_table::frequency_table(const std::string &file_name) {
	fstream file;
	file.open(file_name);
	if (!file)
		throw runtime_error("Error opening file");
	char inp;
	while (file >> noskipws >> inp)
		M[inp]++;
}

frequency_table::~frequency_table() {
//didn't use dynamic memory
}

int frequency_table::get_frequency(char c) const {
	for (const auto &i : M)
	{
		if (i.first == c)
			return i.second;
	}
	return 0;
}