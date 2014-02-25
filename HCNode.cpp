#include "HCNode.hpp"

/*
 * Authors: Alex Tsang and Alibek Aidarov
 * Login actsang and aaidarov
 */

/** Compare this HCNode and other for priority ordering.
  * Smaller count means higher priority.
  * Use node symbol for deterministic tiebreaking
  */
bool HCNode::operator<(HCNode const & other) {
  // if counts are different, just compare counts
  if(count != other.count) return count > other.count;
  // counts are equal. use symbol value to break tie.
  // (for this to work, internal HCNodes must have symb set.)
  return symbol < other.symbol;
}