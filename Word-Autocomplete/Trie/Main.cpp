#include "Trie.h"

int main() {
	TrieNode* Dict = getNewNode();
	insert(Dict, "hello");
	insert(Dict, "he");
	insert(Dict, "heol");
	insert(Dict, "hell");
	insert(Dict, "hi");
	insert(Dict, "world");
	string input;
	cout << "Enter the start of the word: ";
	cin >> input;
	for (int i = 0; i < input.length(); i++) {
		input[i] = tolower(input[i]); //lowering the case of the entire string
	}	
	vector<string> res = findWords(Dict, input);
	if (res.empty())
		cout << "There are no matches in the dictionary with such a set of letters";
	else {
		cout << "Possible list of words that are in the dictionary: ";
		for (int i = 0; i < res.size(); ++i) {
			cout << res[i] << " ";
		}
	}
	Dict = remove(Dict, "hello");
	Dict = remove(Dict, "he");
	Dict = remove(Dict, "heol");
	Dict = remove(Dict, "hell");
	Dict = remove(Dict, "hi");
	Dict = remove(Dict, "world");
	delete[] Dict;
	return 0;
}