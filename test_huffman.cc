/*
 * test_huffman: test the Huffman class
 */

#include "huffman.hh"
#include <iostream>
#include <cassert>
#include <climits>

//////////////////////////////////////////////////////////////////////////////
// Ensure the encoder actually modifies the coding' length as expected
void test_encode()
{
  Huffman huff;

  auto bits = huff.encode('a');
  assert(bits.size() > CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() > CHAR_BIT);
  
  bits = huff.encode('a');
  assert(bits.size() < CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() < CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() == huff.encode('a').size());

  bits = huff.encode('b');
  bits = huff.encode('b');
  bits = huff.encode('b');
  assert(bits.size() < huff.encode('a').size());
}

//////////////////////////////////////////////////////////////////////////////
// A utility function that takes a collection of bits and a Huffman tree, and
// figures out which symbol these bits encode.
int decode_symbol(Huffman& huff, const Huffman::bits_t& bits)
{
  int symbol = -1;

  for (auto b : bits) {
    symbol = huff.decode(b);
  }
  assert(symbol >= 0);
  return symbol;
}

//////////////////////////////////////////////////////////////////////////////
// Ensure decoding returns the same symbol that was encoded, in different
// scenarios.
void test_decode()
{
  Huffman encoder, decoder;

  auto bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode('b');
  assert(decode_symbol(decoder, bits) == 'b');
  bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode(Huffman::HEOF);
  assert(decode_symbol(decoder, bits) == Huffman::HEOF);
}

void more1() // encoding end_of_file and 0 -- multiple times
{
  Huffman encoder, decoder;

  auto bits = encoder.encode(256);
  assert(decode_symbol(decoder, bits) == 256);

  bits = encoder.encode(0);
  assert(decode_symbol(decoder, bits) == 0);

  bits = encoder.encode(256);
  assert(decode_symbol(decoder, bits) == 256);

  bits = encoder.encode(0);
  assert(decode_symbol(decoder, bits) == 0);

  bits = encoder.encode(256);
  assert(decode_symbol(decoder, bits) == 256);

  bits = encoder.encode(0);
  assert(decode_symbol(decoder, bits) == 0);

  bits = encoder.encode(0);
  assert(decode_symbol(decoder, bits) == 0);
}

void more2() // test all ascii chars
{
  Huffman::bits_t bits;
  Huffman encoder, decoder;
  for (int i = 0; i < 257; i++)
  {
    bits = encoder.encode(i);
    assert(decode_symbol(decoder, bits) == i);
  }
}

void more3() // this came in handy for encoder part
{
  Huffman huff;
  huff.encode('h');
  huff.encode(Huffman::HEOF);
}


//////////////////////////////////////////////////////////////////////////////
int main()
{
  test_encode();
  test_decode();
  more1();
  more2();
  more3();
  std::cout << "yay!" << "\n";
  return 0;
}

