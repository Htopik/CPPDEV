#include "Trie.h"


TrieNode* getNewNode()
{
	struct TrieNode* pNode = new TrieNode;
	pNode->isEndOfWord = false;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

void insert(TrieNode* root, string key)
{
	TrieNode* node = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index]) {
			node->children[index] = getNewNode();
		}
		node = node->children[index];
	}
	node->isEndOfWord = true;
}
bool search(struct TrieNode* root, string key)
{
	TrieNode* node = root;
	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
			return false;

		node = node->children[index];
	}

	return (node != nullptr && node->isEndOfWord);
}

bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}

TrieNode* remove(TrieNode* root, string key, int depth)
{
	if (!root)
		return nullptr;
	if (depth == key.size()) {
		if (root->isEndOfWord)
			root->isEndOfWord = false;
		if (isEmpty(root)) {
			delete[] (root);
			root = nullptr;
		}

		return root;
	}
	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete[] (root);
		root = nullptr;
	}
	return root;
}
void traverse(std::string prefix, TrieNode* node, vector<string>& v)
{
	if (node->isEndOfWord)
	{
		v.push_back(prefix);
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (node->children[i])
		{
			traverse(prefix + (char)('a' + i), node->children[i], v);
		}
	}
}

vector<string> findWords(TrieNode* root, string input) {
	vector<string> res;
	if (!root) return res;
	TrieNode* node = root;

	for (int i = 0; i < input.length(); i++) //going down the tree knowing the given letters
	{
		int index = input[i] - 'a';
		if (!node->children[index])
			return res;
		node = node->children[index];
	}
	if (node == nullptr)
		return res;
	traverse(input, node, res);
	return res;
}

