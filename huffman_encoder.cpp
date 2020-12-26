#include "huffman_encoder.h"
#include <fstream>
#include <vector>
using namespace std;

node* huffman_encoder::getnode(char c, int f, node* l, node* r)
{
	node* n = new node();
	n->symbol = c;
	n->freq = f;
	n->left = l;
	n->right = r;
	return n;
}

void huffman_encoder::encoder(node* n, string str, map<char, string> &list)
{
	if (n == nullptr)
		return;
	if (!n->left && !n->right) //leaf
		HE[n->symbol] = str;
	encoder(n->left, str + "0", list);
	encoder(n->right, str + "1", list);
}

string huffman_encoder::decoder(node* n, string st) const
{
	string o = "";
	node* curr = n;
	for (int i = 0; i < (int)st.size(); i++)
	{
		if (st[i] == '1')
			curr = curr->right;
		else
			curr = curr->left;

		if (!curr->left && !curr->right)
		{
			o += curr->symbol;
			curr = n;
		}
	}
	return o;
}

huffman_encoder::huffman_encoder(const frequency_table &table){
	for (auto a : table.M)
	{
		if (a.second > 0)
			descend.push(getnode(a.first, a.second, nullptr, nullptr));
	}
	if (descend.size() == 1) //single character text
	{
		node* root = descend.top();
		HE[root->symbol] = "1";
	}
	else if(descend.size() > 1) //more than one character text
	{
		while (descend.size() > 1)
		{
			node* l = descend.top();
			descend.pop();
			node* r = descend.top();
			descend.pop();
			int combo = l->freq + r->freq;
			descend.push(getnode('\0', combo, l, r));
		}
		node* root = descend.top();
		encoder(root, "", HE);
	}
}

huffman_encoder::~huffman_encoder(){

}

std::string huffman_encoder::get_character_code(char character) const {
	for (const auto& i : HE)
	{
		if (i.first == character)
			return i.second;
	}
	return "";
}

std::string huffman_encoder::encode(const std::string &file_name) const {
	string str = "";
	string temp = "";
	fstream file;
	file.open(file_name);
	if (!file)
		throw runtime_error("Error opening file");
	char inp;
	while (file >> noskipws >> inp)
	{
		temp = get_character_code(inp);
		if (temp != "")
			str += temp;
		else
			return "";
	}
	return str;
}

std::string huffman_encoder::decode(const std::string &string_to_decode) const {
	string str = string_to_decode;
	string outp = "";
	for (int i = 0; i < (int)str.size(); i++) //contains invalid chars
	{
		if (str[i] != '1' && str[i] != '0')
		{
			return outp;
		}
	}
	if ((int)str.size() == 1) //single character text
	{
		for (auto i : HE)
			outp = i.first;
		return outp;
	}
	node* root = descend.top();
	outp = decoder(root, str);
	return outp;
}