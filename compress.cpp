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
  in.open(argv[1]);   // Open input stream
  out.open(argv[2],ios::binary);  // to force 1 byte per char
  BitOutputStream outStream = BitOutputStream(out);
  int n;
  // Count frequencies of chars
  vector<int> freqs = vector<int>(256, 0); // Create a vector for ascii values
  while(true) {
    n = (int)in.get(); // read the next integer from the ifstream
    if(!in.good()) {
      break; // failure or eof
    }
    freqs[n]++; 
  }

  // Creating header for reconstruction of tree in decompress
  int freq;
  for(int ch=0; ch<256; ch++) {
    if(freqs[ch]!=0) {
      freq = freqs[ch];
      out << ch << " ";
      out << freq << " ";
    }
  }
  out << -1; //end of file header

  // Error checking for error other than eof
  if(!in.eof()) {
    cerr << "There was a problem with your InFile" << endl;
    return 1;
  }


  // Close input stream and build huffman tree
  in.close();
  HCTree* tree = new HCTree();
  tree->build(freqs);
  // Reopen input stream and encode into ouput stream
  in.clear();
  in.open(argv[1]);
  while(true) {
    n = (int)in.get(); // read the next integer from the ifstream
    if(!in.good()) {
      break; // failure or eof
    }
    tree->encode(n,outStream);
  }
  // Force last flush and close streams;
  outStream.flush();
  in.close();
  out.close();
}