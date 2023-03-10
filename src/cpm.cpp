#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::reverse;
using std::string;

// read content of file and store it in a string
string read_file(string filename)
{
    string content;
    ifstream input(filename);
    if (input)
    {
        input.seekg(0, ios::end);
        content.resize(input.tellg());
        input.seekg(0, ios::beg);
        input.read(&content[0], content.size());
        input.close();
    }
    return content;
}

int main()
{
    // cout << "Hello, World!\n";
    int k = 5; // k is the sliding window
    string content = read_file("test.txt"); // get file content
    std::map<std::string, std::vector<int>> hash_map; // create hashmap to store K strings and its positions
    for (int i = 0; i < content.size() - k + 1; ++i)
    {
        std::string substring = content.substr(i, k);
        if (hash_map.find(substring) != hash_map.end())
        {
            hash_map[substring].push_back(i);
            if (i + k < content.size())
            {
                char next_char = content[i + k];
                cout << substring << " (previous positions: ";
                for (int pos : hash_map[substring]) {
                    if (pos != i) {
                        cout << pos << ", ";
                    }
                }
                cout << i << ") " << "Next char: " << next_char << endl;
            }
        }
        else
        {
            cout << substring << endl;
            hash_map[substring] = std::vector<int>{i}; // add K-string to hashmap
        }
    }
    return 0;
}
