# Huffman Encoding

Convert text files into Huffman-coded binaries.

## Huffman

The central program for this assignment is the Huffman class. This class stores a Huffman tree that it computes, as well as a frequency table for all of the ascii symbols that it has seen in the file so far. I chose to store the huffman tree as a shared pointer to a const tree for easy clean up and assurance that no changes would be made. I chose to the the frequency table as an array of integers, as recommended. 

The Huffman class contains two public methods, encode() and decode(). It is intended that each instance of a huffman tree serves does exacly on of these. the encode() function returns a vector of bits for a given symbol (int). The vecotr of bits represents the path to the node with that symbol current huffman tree. The decode() method does the opposite, it takes a bit as input and returns the symbol that is reach by going left (0) or right (1) from the current node in the tree. 

## BitIO

The BitIO class is what allows us to read and write from and to files. The two variable members that are assigned by the user are an ostream object and an istream object, although no bitio object should have both assigned. One needs to be sure to pass nullptr as an argument in place of the stream object you do not intend to use with that object. 

The bitio class has two public methods, output_bit() and input_bit(). The output_bit() method takes a biot as input and sends it to the ostream defined when the object was created. The input_bit() method read a single bit through the istream and outputs it to the caller.

## Encoder and Decoder

The encoder.cc and eecoder.cc tie the whole project together. they both use the Huffman and BitIO classes to compress an ascii text file into binary or decopress a binary file into plain text. The files that one desires to encode or decode are passed as arguments when calling the main function from the command line. Any number of arguments can be passed, and each will get encoded/decoded in turn. An example of running the encoder on three files: in the terminal and within the directory with the encoding program and the three files, type

$ ./encoder file1.txt file2.txt file3.txt

Using the decoder is similar.


Part 4 - Table of Results

  File Name      | Size Before compression  | Size After Compression | Decomp and Raw Match (y/n) 

hitchhikers.txt  | 1461 bytes               | 1007 bytes             | Yes 

README_hw7.txt   | 1587 bytes               | 1067 bytes             | Yes

README_hw6.txt   | 2302 bytes               | 1451 bytes             | Yes

README_hw5.txt   | 2070 bytes               | 1549 bytes             | Yes

tale_of_two_cities-full.txt | 786,023 bytes | 445,718 bytes          | Yes :)



