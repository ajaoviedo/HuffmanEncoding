#pragma once
#include "frequency_table.h"
#include <queue>
#include <map>

using namespace std;

struct node
{
	char symbol;
	int freq;
	node* left, * right = nullptr;
};

struct Compare
{
	bool operator()(node* left, node* right)
	{
		return left->freq > right->freq;
	}
};

class huffman_encoder {
public:
		map<char, string> HE;
		node* getnode(char, int, node*, node*);
		void encoder(node*, string, map<char, string>&);
		string decoder(node*, string) const;
		priority_queue<node*, vector<node*>, Compare> descend;
        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();

        std::string get_character_code(char c) const;
        std::string encode(const std::string &file_name) const;
		std::string decode(const std::string& string_to_decode)const;
};
