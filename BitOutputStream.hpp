#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

/*
 * Authors: Alex Tsang and Alibek Aidarov
 * Login actsang and aaidarov
 */

/** A class to read bit by bit from the outputstream.
 *  It will be a composition of ofstream
 */


class BitOutputStream {
private:
  char buf;               // one byte buffer of bits
  int nbits;              // how many bits have been read from buf
  std::ostream & out;     // the output stream to use

public:
  /** Initialize a BitOutputStream that will use
    * the given ostream for output.
    */
  BitOutputStream(std::ostream & os) : out(os){
    buf = 0;             // clear buffer
    nbits = 0;           // clear counter 
  }

  /** Send the buffer to the output, and clear it */
  void flush();

  /** Write the least significant bit of the argument to
    * the bit buffer, and increment the bit buffer index.
    * But flush the buffer first, if it is full.
    */
  void writeBit(int i); 


};
#endif //BITOUTPUTSTREAM_HPP