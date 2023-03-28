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
        input.seekg(0, ios::end); // go to the end of the file
        data.resize(input.tellg()); // resize the string to fit the file size
        input.seekg(0, ios::beg); // go back to the beginning of the file
        input.read(&data[0], data.size()); // read the file content into the string
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

    return retval; // return the key with the highest count
}

// Predicts the next character based on the previous k characters
char predict_char(const std::vector<int> &positions, std::vector<std::string> &chunks) {

    // get the first position of the positions array
    int first_pos = positions.front();

    // return the last character of the chunk immediately following the first position
    return chunks[first_pos + 1].back();
}

int main(int argc, char* argv[])
{
    if (argc < 5) {
        cout << "Usage: " << argv[0] << " <filename> <k> <alpha> <fail_threshold>" << endl;
        return 1;
    }

    // Parse command-line arguments
    string filename = argv[1];
    int k = std::stoi(argv[2]);
    double alpha = atof(argv[3]);
    int fail_threshold = std::stoi(argv[4]);

    int hits = 0;
    int fails = 0;
    bool pause_counting = false; // flag to pause counting hits and fails
    int pause_count = 0; // number of chunks to pause for
    int consecutive_fails = 0;
    double estimated_bits = 0; // estimated total number of bits
    double prob = 0; // probability of correct prediction
    string data = read_file(filename);

    std::map<std::string, std::vector<int>> chunk_positions; // map of chunk strings to their positions in the file
    std::vector<std::string> chunks; // vector of chunks of length k

    for (int i = 0; i < data.size() - k; ++i)
    {
        // extract k length chunk from the file and add it to the vector of chunks
        std::string current_chunk = data.substr(i, k);
        chunks.push_back(current_chunk);

        // if the current chunk is not in the map add it to the map
        if (chunk_positions.find(current_chunk) == chunk_positions.end()) {
            chunk_positions[current_chunk] = std::vector<int>{i};
            continue;
        }

        // add the position of the current chunk to the map
        chunk_positions[current_chunk].push_back(i);

        // if this is the last chunk, break out of the loop
        if (i + k >= data.size())
            break;

        // get the actual next character and the predicted next character
        char solution = data[(i+k)-1];
        char prediction = predict_char(chunk_positions[current_chunk], chunks);

        if (pause_counting) {
            pause_count++;

            if (prediction == solution)
                hits++;

        } else { // if not in pause mode
            if (prediction == solution) {
                hits++;
                consecutive_fails = 0;
            } else {
                fails++;
                consecutive_fails++;

                if (consecutive_fails >= fail_threshold){
                    pause_counting = true;
                    chunk_positions.erase(chunk_positions.begin()); // remove the oldest chunk from the map
                }
            }

        }

        // calculate the probability of a correct prediction and update the estimated total number of bits
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
