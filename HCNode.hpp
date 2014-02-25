#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

/*
 * Authors: Alex Tsang and Alibek Aidarov
 * Login actsang and aaidarov
 */

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {
  friend bool comp(HCNode* one, HCNode* other);

public:
  int count;              // Count/frequency of symbols in subtree
  byte symbol;   // byte in the file we're keeping track of
  HCNode* child0;         // pointer to '0' child
  HCNode* child1;         // pointer to '1' child
  HCNode* parent;         // pointer to parent
  bool isChild0;          // true if this is "0" child of its parent

  //HCNode constructor 
  HCNode(int count,
	 byte symbol,
	 HCNode* child0 = 0,
	 HCNode* child1 = 0,
	 HCNode* parent = 0,
         bool isChild0 = false)
    : count(count), symbol(symbol), child0(child0), child1(child1), 
      parent(parent), isChild0(isChild0) { }

  // HCNode destructor
  ~HCNode() {
    delete child1;
    delete child0;
    parent = 0;
    count = 0;
    symbol = 0;
    child0 = 0;
    child1 = 0;
    isChild0 = false;
  }

  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool operator<(const HCNode& other);  
};

/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak)); // shut the linker up
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" << n.count << "," << (int) (n.symbol) << "]";
    return stm;
}
// Comparator function
bool comp(HCNode* one, HCNode* other);


#endif // HCNODE_HPP