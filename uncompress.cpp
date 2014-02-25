#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include <iostream>
#include <fstream>
#include <vector>

/*
 * Authors: Alex Tsang and Alibek Aidarov
 * Login actsang and aaidarov
 */

using namespace std;

int main(int argc, char** argv) {
  if(argc != 3) {
    cout << "Usage Error: ./compress [Infile] [Outfile]" << endl;
    return 1;
  }
  // Open input and output streams 
  ifstream in;
  ofstream out;
  in.open(argv[1],ios::binary);   // Open input stream
  out.open(argv[2]); // Open output stream as format 
  BitInputStream inStream = BitInputStream(in);
  int n;
  int ch;
  int freq;
  int counts = 0;
  // Count frequencies of chars
  vector<int> freqs = vector<int>(256, 0); // Create a vector for ascii values
  while(true) {
    in >> n; // read the next integer from the ifstream (character)
    ch = n;
    if(!in.good() || ch == -1) { //256 is end of file header
      break; // failure or eof or done reading
    }
    in >> n; // read the next integer from the ifstream (freq)
    freq = n;
    counts = counts + freq; 
    freqs[ch] = freq;
  }
  // Recreating the huffman tree
  HCTree* tree = new HCTree();
  tree->build(freqs);

  // Decode the bits until all frequencies of chars are accounted for
  int counter = 0;
  while(counter != counts) {
    if(!in.good()) {
      break; // failure or eof
    }
    char binary = (char)tree->decode(inStream);
    out << binary;
    counter++;
  }
  out.close();
  in.close();
}