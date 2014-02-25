#include "BitOutputStream.hpp"

/*
 * Authors: Alex Tsang and Alibek Aidarov
 * Login actsang and aaidarov
 */

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to
  * the bit buffer, and increment the bit buffer index.
  * But flush the buffer first, if it is full.
  */
void BitOutputStream::writeBit(int i) {
  // Is the bit buffer full? Then flush it
  if(nbits == 8) {
    flush();
  } 

  // Write the least significant bit of i into the buffer
  // at the current index
  buf = (i << (7-nbits)) | buf;      

  // Increment the index
  nbits++;
}

