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
/*char predict_char(const std::vector<int> &positions, std::vector<std::string> &chunks) {
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
}*/

char predict_char(const std::vector<int> &positions, std::vector<std::string> &chunks) {
    // get first position of positions array
    int first_pos = positions.front();

    return chunks[first_pos + 1].back();
}

int main(int argc, char* argv[])
{
    if (argc < 6) {
        cout << "Usage: " << argv[0] << " <filename> <k> <alpha> <fail_threshold> <pause_threshold>" << endl;
        return 1;
    }

    string filename = argv[1];
    int k = std::stoi(argv[2]);
    double alpha = atof(argv[3]);
    int fail_threshold = std::stoi(argv[4]);
    int pause_threshold = std::stoi(argv[5]);
    int hits = 0;
    int fails = 0;
    bool pause_counting = false;
    int pause_count = 0;
    int consecutive_fails = 0;
    double estimated_bits = 0;
    double prob = 0;
    string data = read_file(filename);
    std::map<std::string, std::vector<int>> chunk_positions;
    std::vector<std::string> chunks;

    for (int i = 0; i < data.size() - k; ++i)
    {
        std::string current_chunk = data.substr(i, k);
        chunks.push_back(current_chunk);
        cout << "Current chunk: " << current_chunk << endl;

        if (chunk_positions.find(current_chunk) == chunk_positions.end()) {
            chunk_positions[current_chunk] = std::vector<int>{i};
            continue;
        }

        chunk_positions[current_chunk].push_back(i);

        if (i + k >= data.size())
            break;

        char solution = data[(i+k)-1];
        char prediction = predict_char(chunk_positions[current_chunk], chunks);

        if (pause_counting) {
            pause_count++;

            if (prediction == solution) hits++;

            if (pause_count >= pause_threshold) {
                pause_counting = false;
                pause_count = 0;
            }
        } else {
            if (prediction == solution) {
                hits++;
                consecutive_fails = 0;
            } 
            else {
                fails++;
                consecutive_fails++;

                if (consecutive_fails >= fail_threshold){
                pause_counting = true;
                // remove position that passes threshold
                chunk_positions.erase(chunk_positions.begin());
                }
            }

        }
            prob = (hits + alpha) / (hits + fails + 2 * alpha);
            estimated_bits += -log2(prob);
    }

    double total_symbols = data.size();
    cout << "Hits: " << hits << endl;
    cout << "Fails: " << fails << endl;

    cout << "Estimated total bits: " << estimated_bits << endl;
    cout << "Average bits per symbol: " << estimated_bits / total_symbols << endl;

    return 0;
}