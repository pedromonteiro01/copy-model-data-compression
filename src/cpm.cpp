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
    int k = 5; // k is the sliding window
    string content = read_file("chry.txt"); // get file content
    std::map<std::string, int> hash_map; // create hashmap to store K strings
    for (int i = 0; i < content.size() - k + 1; ++i)
    {
        std::string substring = content.substr(i, k);
        auto it = hash_map.find(substring);
        if (it == hash_map.end())
        {
            cout << substring << endl; // if it is not in the hashmap, print it
            hash_map[substring] = i; // add to hashmap
        }
        else
        {
            cout << substring << " (first appeared at position " << it->second << ")" << endl;
        }
    }
    return 0;
}
