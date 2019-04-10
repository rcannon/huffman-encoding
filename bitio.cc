/*
 * A simple class to perform stream I/O on individual bits.
 * Before reading any bits, ensure your input stream still has valid inputs.
 */
#include "bitio.hh"
#include <iostream>
#include <cassert>

  // Construct with one of either an input stream or output (the other null)
BitIO::BitIO(std::ostream* os, std::istream* is)
: bit_index_(0), buffer_(0), mask_(0), os_(os), is_(is)
{
  assert((!os) || (!is));
}

  // Flushes out any remaining output bits and trailing zeros, if any:
BitIO::~BitIO()
{
// if bit-index != 0 and we are doing output, we need to fill out buffer 
// with 0's and output to stream before destruction
  if ((bit_index_ != 0) && os_)
  {
    os_->put(buffer_);
    buffer_ = 0;
    bit_index_ = 0;
  }
  return;
}


  // Output a single bit (buffered)
void BitIO::output_bit(bool bit)
{
  assert(os_);
  assert(bit_index_ < 8);

  // if the given bit is true, we need to place a 1 in the 
  // next spot in the buffer
  // by default, next bit is 0
  if (bit == true)
  {
    mask_ = 1 << bit_index_;
    buffer_ = buffer_ | mask_;
  }
  bit_index_++;

  // if the buffer is full, output it as a character to the stream
  // and clear the buffer and reset the bit_index
  if (bit_index_ == 8)
  {
    os_->put(buffer_);
    bit_index_ = 0;
    buffer_ = 0;
  }
}



  // Read a single bit (or trailing zero)
bool BitIO::input_bit()
{
  assert(is_);

  // if buffer is empty, get the next
  // symbol from the stream
  if (bit_index_ == 0)
  {
    is_->get(buffer_);
  }
  mask_ = 1 << (bit_index_);
  
  bit_index_ = bit_index_ + 1;

  // if the index is now past the number of spots in the 
  // buffer, reset it to 0 to refill buffer on next call
  if (bit_index_ == 8)
  {
    bit_index_ = 0;
  }

  // use mask to access desired bit
  mask_ = mask_ & buffer_;

  //return according to whether desired bit was 1 or 0
  if (mask_ != 0) return true;
  else return false;
}

