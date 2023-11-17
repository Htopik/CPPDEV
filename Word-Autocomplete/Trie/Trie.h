#pragma once
#include <iostream>
#include <vector>
using namespace std;
const int ALPHABET_SIZE = 26;
struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
};

TrieNode* getNewNode();
void insert(TrieNode*, string);
bool search(TrieNode*, string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, string, int depth = 0);
vector<string> findWords(TrieNode*, string);

