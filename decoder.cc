#include "huffman.hh"
#include "bitio.hh"
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

void decode(const char* file)
{
    // open the file passed as an argument for reading 
    ifstream input_file(file, ios::binary);
    if (!input_file.is_open())
    {
        cerr << "Can't open input file " <<  file << "\n";
    }

    // create an output file of desired name
    string name(file);
    ofstream output_file(name + ".plaintext");

    // initialiaze necessary objects
    Huffman huff_dec;
    BitIO bitio(nullptr, &input_file);
    int symbol = -1;
    
    // main decoding loop
    while (true) 
    {
        while (symbol < 0) // aka: while we are not at a valid ascii char in huff tree
        {
            symbol = huff_dec.decode(bitio.input_bit()); // get next bit from stream
        }
        if (symbol == Huffman::HEOF) 
        {
            break; // if we are at end of file, we want to break
        } 
        else 
        {
            output_file.put(symbol); // place valid ascii symbol in output file
            symbol = -1; // reset symbol in order to get next one
        }
    }  
}

int main(int argc, char** argv)
{
    if (argc < 2) 
    {
        cerr << "Need something to decode, no argument files given";
    }
    for (int i = 1; i < argc; i++)
    {   
        decode(argv[i]); // decode each file given as argument
    }
    return 0;
}

