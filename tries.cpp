#include <iostream>
#include <cstring> // For memset

using namespace std;

// Class for TrieNode
class TrieNode {
public:
    TrieNode* children[26]; // Array to store child nodes (26 lowercase letters)
    bool isEndOfWord;       // Indicates the end of a word

    // Constructor to initialize a new node
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
    }
};

// Class for Trie
class Trie {
private:
    TrieNode* root;

public:
    // Constructor to initialize the Trie
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(const string& word) {
        TrieNode* current = root;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (current->children[index] == NULL) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool search(const string& word) {
        TrieNode* current = root;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (current->children[index] == NULL) {
                return false;
            }
            current = current->children[index];
        }
        return current != NULL && current->isEndOfWord;
    }

    // Helper function for deletion
    bool deleteHelper(TrieNode* node, const string& word, int depth) {
        if (node == NULL) {
            return false;
        }

        // If last character of the word is being processed
        if (depth == word.length()) {
            // Mark current node as not end of word
            if (node->isEndOfWord) {
                node->isEndOfWord = false;
            }

            // If the node has no children, it can be deleted
            for (int i = 0; i < 26; i++) {
                if (node->children[i] != NULL) {
                    return false;
                }
            }
            delete node;
            return true;
        }

        // Recursive call for the child node corresponding to the current character
        int index = word[depth] - 'a';
        if (deleteHelper(node->children[index], word, depth + 1)) {
            node->children[index] = NULL;

            // Check if this node can also be deleted
            if (!node->isEndOfWord) {
                for (int i = 0; i < 26; i++) {
                    if (node->children[i] != NULL) {
                        return false;
                    }
                }
                delete node;
                return true;
            }
        }
        return false;
    }

    // Delete a word from the Trie
    void deleteWord(const string& word) {
        deleteHelper(root, word, 0);
    }
};

int main() {
    Trie trie;

    // Insert words into the Trie
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("grape");

    // Search for words in the Trie
    cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "Search 'grape': " << (trie.search("grape") ? "Found" : "Not Found") << endl;
    cout << "Search 'orange': " << (trie.search("orange") ? "Found" : "Not Found") << endl;

    // Delete a word and search again
    trie.deleteWord("apple");
    cout << "After deleting 'apple', search 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl;

    return 0;
}
