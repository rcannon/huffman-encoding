#include <climits>
#include <vector>
#include <iostream>

#include "huffman.hh"

// constructor
Huffman::Huffman() : frequency_table_(ALPHABET_SIZE, 0), huffman_tree_(nullptr) {}

// to be called in encode() and decode() methods
// builds a huffman tree given existing frequancy table values
void Huffman::build_huffman() // identical to standard adaptive huffman tree-building
{
    HForest huff_forest;
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    {
        // iterate over each possible symbol and add it to forest, with 0 freq to start
        huff_forest.add_tree(HTree::tree_ptr_t(new HTree(i , frequency_table_[i])));
    }
    while (huff_forest.size() > 1)
    {
        // add nodes with lowest frequency together as children of dummy node, 
        // then place that dummy node in tree and repeat until only one node left
        HTree::tree_ptr_t t1 = huff_forest.pop_top();
        HTree::tree_ptr_t t2 = huff_forest.pop_top();
        huff_forest.add_tree(HTree::tree_ptr_t(new HTree(-1, (t1->get_value() + t2->get_value()), t2, t1)));
    }
    // final node is completed huffman tree
    huffman_tree_ = huff_forest.pop_top(); 
    return;
}


Huffman::bits_t Huffman::encode(int symbol)
{
    build_huffman();

    // we will represent the path as bits, this will be the basis
    //of our encoding
    HTree::path_t path_to_symbol = huffman_tree_->path_to(symbol);

    // create new vecotr of bits
    Huffman::bits_t bits;
    for (auto v : path_to_symbol) // note to self: removed count
    {
        // add 0 bit or 1 bit, corresponding to direction in path to symbol
        bits.push_back(static_cast<bool>(v)); 
    }
    frequency_table_[symbol]++; // update frequency of symbol
    return bits;
}

int Huffman::decode(bool bit)
{
    // if no huff tree exist, then we are starting a new symbol
    if (huffman_tree_ == nullptr) 
    {
        build_huffman();
    }
    // move pointer to tree in direction of tthe symbol, based on value of bit
    huffman_tree_ = huffman_tree_->get_child(static_cast<HTree::Direction>(bit));
    assert(huffman_tree_); // make sure the child is not null

    // if the key is < 0, we are at an intermediate node that doesn't
    // correspond to a symbol
    if (huffman_tree_->get_key() < 0)
    {
        return huffman_tree_->get_key();
    }
    else // otherwise, delete the tree to get ready for next symbol
    {
        int c = huffman_tree_->get_key();
        frequency_table_[c]++;
        huffman_tree_ = nullptr;
        return c;
    }
}




