#include "simplecache.h"
#include <iostream>

int SimpleCache::find(int index, int tag, int block_offset) {
  // read handout for implementation details
  std::vector< SimpleCacheBlock > & blocks = _cache.at(index);
  for (SimpleCacheBlock & i : blocks) {
    if (i.valid() && i.tag() == tag) { // should check validity of block_offset?
      return i.get_byte(block_offset);
    }
  }

  return 0xdeadbeef;
}

void SimpleCache::insert(int index, int tag, char data[]) {
  // read handout for implementation details
  // keep in mind what happens when you assign (see "C++ Rule of Three")
  std::vector< SimpleCacheBlock > & blocks = _cache.at(index);
  for (SimpleCacheBlock & i : blocks) {
    if (!i.valid()) {
      i.replace(tag, data);
      return;
    }
  }
  blocks[0].replace(tag, data);
  return;
}
