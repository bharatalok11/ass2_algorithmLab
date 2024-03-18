#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }

    Node(int frequency, Node* left, Node* right) {
        data = '\0';
        this->frequency = frequency;
        this->left = left;
        this->right = right;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

unordered_map<char, string> codes;

void generateCodes(Node* root, string code) {
    if (root == nullptr) {
        return;
    }
    if (root->data != '\0') {
        codes[root->data] = code;
    }
    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

string encode(string text) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    unordered_map<char, int> freq;

    for (char c : text) {
        freq[c]++;
    }

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->frequency + right->frequency;
        pq.push(new Node(sum, left, right));
    }

    Node* root = pq.top();
    generateCodes(root, "");
    string encoded = "";

    for (char c : text) {
        encoded += codes[c];
    }

    delete root;
    return encoded;
}

double calculateCompressionRatio(const string& original, const string& compressed) {
    return (double)original.size() / compressed.size();
}

int main() {
    // Read the first document
    ifstream file1("document1.txt");
    if (!file1.is_open()) {
        cerr << "Error: Unable to open document1.txt" << endl;
        return 1;
    }

    string text1((istreambuf_iterator<char>(file1)), istreambuf_iterator<char>());
    string encoded1 = encode(text1);

    // Calculate compression ratio for document1
    double compressionRatio1 = calculateCompressionRatio(text1, encoded1);

    cout << "Compression ratio for document1: " << compressionRatio1 << endl;

    // Read the second document
    ifstream file2("document2.txt");
    if (!file2.is_open()) {
        cerr << "Error: Unable to open document2.txt" << endl;
        return 1;
    }

    string text2((istreambuf_iterator<char>(file2)), istreambuf_iterator<char>());
    string encoded2 = encode(text2);

    // Calculate compression ratio for document2
    double compressionRatio2 = calculateCompressionRatio(text2, encoded2);

    cout << "Compression ratio for document2: " << compressionRatio2 << endl;

    // Compare compression ratios
    if (compressionRatio1 < compressionRatio2) {
        cout << "Huffman coding provides better compression for document1 compared to document2." << endl;
    } else if (compressionRatio1 > compressionRatio2) {
        cout << "Huffman coding provides better compression for document2 compared to document1." << endl;
    } else {
        cout << "Both documents achieve similar compression ratios using Huffman coding." << endl;
    }

    return 0;
}
