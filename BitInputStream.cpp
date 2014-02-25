#include "BitInputStream.hpp" 

/*
 * Authors: Alex Tsang and Ali Aaidorav
 * Login actsang and aaidarov
 */

/** A class to read bit by bit from the inputstream.
 *  It will be a composition of ifstream
 */


/** Fill the buffer from the input */
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

/** Read the next bit from the bit buffer.
  * Fill the buffer from the input stream first if needed.
  * Return 1 if the bit read is 1;
  * Return 0 if the bit read is 0.
  */
int BitInputStream::readBit() {
  // If all bits in the buffer are read, fill the buffer first
  if(nbits == 8) {
    fill();
  } 

  // Get the bit at the apprioriate location in the bit
  // buffer, and return the appropriate int
  int i = (buf >> (7-nbits)) & 1; 

  // Increment the index
  nbits++;
  return i;
}