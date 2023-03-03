#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using std::cout; using std::endl;
using std::string; using std::reverse;
using std::ifstream;
using std::ios;

// read content of file and store it in a string
string read_file(string filename) {
    string content;
    ifstream input(filename);
    if (input) {
        input.seekg(0, ios::end);
        content.resize(input.tellg());
        input.seekg(0, ios::beg);
        input.read(&content[0], content.size());
        input.close();
    }
    return content;
}

int main() {
    //cout << "Hello, World!\n";
    string content = read_file("chry.txt");
    for (int i = 0; i < content.size(); i++) {
        cout << content[i];
    }
    cout << endl;
    return 0;
}
