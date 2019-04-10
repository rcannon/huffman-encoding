/*
 * A simple class to perform stream I/O on individual bits.
 * Before reading any bits, ensure your input stream still has valid inputs.
 */
#include <iostream>

class BitIO {
 public:
  // Construct with one of either an input stream or output (the other null)
  BitIO(std::ostream* os, std::istream* is);

  // Flushes out any remaining output bits and trailing zeros, if any:
  ~BitIO();

  BitIO(const BitIO&) = default;
  BitIO(BitIO&&) = default;
  BitIO& operator=(const BitIO&) = default;
  BitIO& operator=(BitIO&&) = default;

  // Output a single bit (buffered)
  void output_bit(bool bit);

  // Read a single bit (or trailing zero)
  bool input_bit();

 private:
  int bit_index_; // tells us which bit we are currently pointing at in buffer
  char buffer_; // tempoarily stores bits for ouptput to file or returning to caller
  char mask_; // used to access a specific bit in the buffer
  std::ostream* os_; // the out-stream object
  std::istream* is_; // the in-stream object
};
