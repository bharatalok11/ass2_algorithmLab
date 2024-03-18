#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Node structure for the Huffman tree
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char d) : data(d), left(nullptr), right(nullptr) {}
};

// Function to build the Huffman tree from the provided codes
Node* buildHuffmanTree(const unordered_map<char, string>& codes) {
    Node* root = new Node('\0'); // Dummy root node
    for (const auto& pair : codes) {
        Node* current = root;
        const string& code = pair.second;
        for (char bit : code) {
            if (bit == '0') {
                if (current->left == nullptr)
                    current->left = new Node('\0');
                current = current->left;
            } else {
                if (current->right == nullptr)
                    current->right = new Node('\0');
                current = current->right;
            }
        }
        current->data = pair.first;
    }
    return root;
}

// Function to perform instantaneous decoding of the input stream
string instantaneousDecode(Node* root, const string& encodedData) {
    Node* current = root;
    string decodedData;
    for (char bit : encodedData) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->data != '\0') {
            decodedData += current->data;
            current = root; // Reset to the root for the next character
        }
    }
    return decodedData;
}

int main() {
    // Sample Huffman codes
    unordered_map<char, string> huffmanCodes = {
        {'a', "00"},
        {'b', "01"},
        {'c', "10"},
        {'d', "11"}
    };

    // Build the Huffman tree
    Node* root = buildHuffmanTree(huffmanCodes);

    // Sample encoded data
    string encodedData = "001011101100";

    // Decode the encoded data using instantaneous decoding
    string decodedData = instantaneousDecode(root, encodedData);

    // Print the decoded data
    cout << "Decoded Data: " << decodedData << endl;

    return 0;
}
