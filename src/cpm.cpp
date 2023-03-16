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
    string data;
    ifstream input(filename);
    if (input)
    {
        input.seekg(0, ios::end);
        data.resize(input.tellg());
        input.seekg(0, ios::beg);
        input.read(&data[0], data.size());
        input.close();
    }
    return data;
}

// Returns the key with greatest int value in a map
char get_map_max_value(std::map<char, int> mymap) {
    char retval = '\0';
    int max_count = 0;
    
    for (const auto& c : mymap) {
        if (c.second > max_count) {
            max_count = c.second;
            retval = c.first;
        }
    }

    return retval;
}

// Function to get the most frequent next character
char predict_char(const std::vector<int> &positions, std::vector<std::string> &chunks) {
    // Step 0: Initialize a counter for each symbol
    std::map<char, int> char_counter;

    for (const auto& pos : positions)
    {
        // validate if a next chunk exists
        if (pos+1 >= chunks.size())
            continue;

        // Get last char of the next chunk
        char next_char = chunks[pos + 1].back();

        // Increment counter for that char
        char_counter[next_char]++;
    }

    // Find and return the most frequent symbol
    char most_frequent_char = get_map_max_value(char_counter);

    return most_frequent_char;
}

int main()
{
    int k = 5; // k is the sliding window
    int hits = 0; // hits
    int fails = 0; // fails
    string data = read_file("test.txt"); // get file data
    std::map<std::string, std::vector<int>> chunk_positions; // create hashmap to store K strings and its positions
    std::vector<std::string> chunks; // create vector to store the chunks

    for (int i = 0; i < data.size() - k; ++i)
    {
        std::string current_chunk = data.substr(i, k);
        chunks.push_back(current_chunk);
        
        // if current_chunk not in hashmap then add to hashmap and go to next iteration
        if (chunk_positions.find(current_chunk) == chunk_positions.end())  {
            chunk_positions[current_chunk] = std::vector<int>{i}; // add K-string to hashmap
            continue;
        }

        // add the chunk's current position to the hashmap
        chunk_positions[current_chunk].push_back(i);
        
        // if EOF reached then break
        if (i + k >= data.size())
            break;

        // get the solution (last char of next chunk)
        char solution = data[(i+k)-1];

        // make a prediction for the last char of the next chunk
        char prediction = predict_char(chunk_positions[current_chunk], chunks);

        // update results
        prediction == solution ? hits++ : fails++;
    }

    cout << "Hits: " << hits << endl;
    cout << "Fails: " << fails << endl;
    return 0;
}
