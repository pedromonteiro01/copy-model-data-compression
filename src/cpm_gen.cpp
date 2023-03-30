#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime> 
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::reverse;
using std::string;

// Read the content of a file and store it in a string
string read_file(string filename)
{
    string data;
    ifstream input(filename);
    if (input)
    {
        input.seekg(0, ios::end);          // Move the file pointer to the end of the file
        data.resize(input.tellg());        // Resize the string to the size of the file
        input.seekg(0, ios::beg);          // Move the file pointer back to the beginning of the file
        input.read(&data[0], data.size()); // Read the file content into the string
        input.close();                     // Close the file
    }
    return data;
}

// For each chunk of text, add the counters of characters to a map 
void load_map(int k ,string &data, std::map<std::string, std::map<char, int>> &char_counting, std::vector<std::string> &chunks){

    // Iterate through the data, creating k-length chunks
    for (int i = 0; i < data.size() - k; ++i)
    {
        // Extract a k-length chunk from the data
        std::string current_chunk = data.substr(i, k);

        // Add the current chunk to the chunks vector
        chunks.push_back(current_chunk);

        // Get the character immediately following the current chunk
        char next_char = data[(i+k)];

        // If the current chunk is not yet in the char_counting map,
        // add it with the next character count initialized to 1
        if (char_counting.find(current_chunk) == char_counting.end()) {
            char_counting[current_chunk][next_char] = 1;
            continue;
        }

        // If the current chunk is already in the char_counting map,
        // increment the count for the next character
        char_counting[current_chunk][next_char] += 1;

    }
}

// Generates the next character based on the character probabilities in the given map
std::string get_next_char(std::map<char, int> char_count){

    std::string text = "";

    // Calculate the total count of characters
    int total = 0;
    for (const auto& char_map : char_count){
        total += char_map.second;
    }

    // Generate a random float between 0 and 1
    double random_float = static_cast<double>(std::rand()) / RAND_MAX;
    double cumulative_probability = 0.0;

    // Iterate through the character map, accumulating probabilities
    for (const auto& char_map : char_count){
        cumulative_probability += static_cast<double>(char_map.second) / total;
        // If the random float is less than or equal to the cumulative probability, return the current character
        if (random_float <= cumulative_probability){
            text = std::string(1, char_map.first);
            return text;
        }
    }

    // This should never be reached, but it's here to avoid compiler warnings
    return text;
}

// Generates text based on the character probabilities in the given map, for a specified length, starting with the last chunk from the text
std::string generate_text(std::map<std::string, std::map<char, int>> char_counting, int text_length, const std::string& starting_text)
{
    std::string text = starting_text;

    // While the generated text length is less than the desired length
    while (text.length() < text_length){
        // Get the current chunk from the end of the generated text
        std::string current_chunk = text.substr(text.length() - starting_text.length(), starting_text.length());

        if (char_counting.find(current_chunk) == char_counting.end()){
            break;
        }
        // Generate and append the next character to the text
        text += get_next_char(char_counting[current_chunk]);
    }

    return text;
}

double calculate_entropy(const std::map<std::string, std::map<char, int>>& char_counting) {
    double entropy = 0.0;
    int num_chunks = 0;

    for (const auto& chunk_map : char_counting) {
        int total_chars = 0;
        for (const auto& char_map : chunk_map.second) {
            total_chars += char_map.second;
        }

        for (const auto& char_map : chunk_map.second) {
            double probability = static_cast<double>(char_map.second) / total_chars;
            entropy += probability * std::log2(probability);
        }

        num_chunks++;
    }

    // Calculate average entropy
    entropy = -entropy / num_chunks;

    return entropy;
}

int main(int argc, char* argv[])
{
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <filename> <k> <text_length>" << endl;
        return 1;
    }

    string filename = argv[1];
    int k = std::stoi(argv[2]);
    int text_length = std::stoi(argv[3]);
    string data = read_file(filename);
    std::map<std::string, std::map<char, int>> char_counting;
    std::vector<std::string> chunks;

    load_map(k, data, char_counting, chunks);

    // Calculate and print the entropy
    double entropy = calculate_entropy(char_counting);
    cout << "Entropy for k = " << k << ": " << entropy << endl;

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Starting text of the text to be generated (last chunk of the text that was read)
    std::string starting_text = chunks.back();
    std::string gen_text = generate_text(char_counting, text_length, starting_text);

    cout << gen_text << endl;

    return 0;
}