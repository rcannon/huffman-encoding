#include "huffman.hh"
#include "bitio.hh"
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

void encode(const char* file)
{
    Huffman huff_enc; 

    ifstream input_file(file); // access input file and ensure readability
    if (!input_file.is_open())
    {
        cerr << "Can't open input file" << file << "\n";
    }

    // create output file
    string name(file);
    ofstream output_file(name + ".comp", ios::binary);

    // initialize other necessary objects
    BitIO bitio(&output_file, nullptr);
    Huffman::bits_t vec_of_bits;
    char symbol;

    // main encoding loop
    while (input_file.get(symbol)) // aka: for each symbol in the input file
    {
        // encode the symbol and output the cooresponding bits to the oputput file
        vec_of_bits = huff_enc.encode(symbol);
        for (auto v : vec_of_bits)
        {
            bitio.output_bit(v);
        }

    }
    // when there are no characters left in the input file
    // encode the end of file symbol so decoder knows when to be done
    vec_of_bits = huff_enc.encode(Huffman::HEOF);
    for (auto v : vec_of_bits)
    {
        bitio.output_bit(v);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cerr << "Need files to encode, pass them as arguments";
    }
    for (int i = 1; i < argc; i++)
    {   
        encode(argv[i]); // encode each given file in turn
    }
    return 0;
}