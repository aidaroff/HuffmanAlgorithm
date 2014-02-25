#include "HCTree.hpp"
#include <algorithm>
#include <vector>
#include <queue>
#include <list>

/*
 * Authors: Alex Tsang and Alibek Aidarov
 * Login actsang and aaidarov
 */

using namespace std;

void HCTree::build(const vector<int>& freqs) {
  // Create forest of HCNodes with priority queue; 
  // highest priority means lowest freq.
  priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> forest;
  // Go through all ascii characters and add those with freq > 0 to forest
  for(int i=0; i<256; i++) {
    if(freqs[i]>0) {
      HCNode* node = new HCNode(freqs[i], i);
      forest.push(node);
    }
  }

  // If only 1 character create a root and link it to the single node
  if(forest.size() == 1) {
    HCNode* top = forest.top();
    forest.pop();
    HCNode* root = new HCNode(-1, -1);
    root->child1 = top;
    top->parent = root;
    forest.push(root);
    // Set pointers from leaves vector to point at leaves
    leaves[top->symbol] = top;
    // Set root to be root of huffman tree
    this->root = root;
  }

  // Combining lowest freq. nodes until one node remains
  while(forest.size()>1) {
    // Pop off top 2 HCNode and attach them to a single root
    HCNode* top1 = forest.top();
    forest.pop();
    HCNode* top2 = forest.top();
    forest.pop();
    int freq = top1->count + top2->count;
    // Create the root with added frequencies and push it back to forest
    HCNode* root = new HCNode(freq, -1);
    root->child1 = top1;
    root->child0 = top2;
    top2->parent = root;
    top1->parent = root;
    top2->isChild0 = true;
    forest.push(root);
    // Set pointers from leaves vector to point at leaves
    leaves[top1->symbol] = top1;
    leaves[top2->symbol] = top2;
    // Set root to be root of huffman tree
    this->root = root;
  }
}


void HCTree::encode(byte symbol, BitOutputStream& out) const{
  HCNode* leaf = leaves[symbol];
  list<int> mylist;
  // Store the bit path of symbol from leaf to root
  while(leaf != this->root) {
    if(leaf->isChild0) {
      mylist.push_back(0);
    }
    else {
      mylist.push_back(1);
    }
    leaf = leaf->parent;
  }
  // Reverse the bit path so it now goes from root to leaf
  mylist.reverse();
  // Go through list and write bits into bitoutputstream
  int i;
  while(mylist.size() != 0) {
    i = mylist.front();
    if(i==0) {
      out.writeBit(0);
    }
    else if(i==1) {
      out.writeBit(1);
    }
    mylist.pop_front();
  }
}

//Decode the read in bits: If bit is 1 go to child1 if 0 go to child0 until a leaf is reached
int HCTree::decode(BitInputStream& in) const {
  HCNode* node = this->root;
  while(node->child0 != 0 || node->child1 != 0) {
    int i = in.readBit();
    if(i==1) {
      node = node->child1;
    }
    else if (i==0) {
      node = node->child0;
    }
    else {
      return -1;
    }
  }
  return node->symbol;
}