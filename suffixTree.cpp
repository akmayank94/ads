#include <iostream>
#include <map>
#include <string>
using namespace std;

// Node structure for the suffix tree
struct SuffixTreeNode {
    map<char, SuffixTreeNode*> children; // Children nodes
    bool isEndOfWord;                   // Marks the end of a suffix

    SuffixTreeNode() : isEndOfWord(false) {}
};

// Suffix Tree class
class SuffixTree {
private:
    SuffixTreeNode* root;

public:
    // Constructor
    SuffixTree() {
        root = new SuffixTreeNode();
    }

    // Destructor to free memory
    ~SuffixTree() {
        deleteTree(root);
    }

    // Function to insert a string into the suffix tree
    void insert(const string& text) {
        for (size_t i = 0; i < text.size(); ++i) {
            SuffixTreeNode* current = root;
            for (size_t j = i; j < text.size(); ++j) {
                char c = text[j];
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new SuffixTreeNode();
                }
                current = current->children[c];
            }
            current->isEndOfWord = true; // Mark the end of the suffix
        }
    }

    // Function to search for a substring in the suffix tree
    bool search(const string& pattern) {
        SuffixTreeNode* current = root;
        for (size_t i = 0; i < pattern.size(); ++i) {
            char c = pattern[i];
            if (current->children.find(c) == current->children.end()) {
                return false; // Character not found
            }
            current = current->children[c];
        }
        return true; // Pattern found
    }

private:
    // Recursive function to delete the tree
    void deleteTree(SuffixTreeNode* node) {
        map<char, SuffixTreeNode*>::iterator it;
        for (it = node->children.begin(); it != node->children.end(); ++it) {
            deleteTree(it->second);
        }
        delete node;
    }
};

// Main function to demonstrate the suffix tree
int main() {
    SuffixTree tree;

    // Input text from the user
    string text;
    cout << "Enter the text: ";
    cin >> text;
    tree.insert(text);

    cout << "Text: " << text << endl;

    // Input pattern to search
    string pattern;
    cout << "Enter a pattern to search: ";
    cin >> pattern;

    // Search for the pattern and display result
    cout << "Searching for '" << pattern << "': "
         << (tree.search(pattern) ? "Found" : "Not Found") << endl;

    return 0;
}
