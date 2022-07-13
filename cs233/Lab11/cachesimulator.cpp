#include "cachesimulator.h"
#include <bits/stdc++.h>

Cache::Block* CacheSimulator::find_block(uint32_t address) const {
  /**
   * TODO
   *
   * 1. Use `_cache->get_blocks_in_set` to get all the blocks that could
   *    possibly have `address` cached.
   * 2. Loop through all these blocks to see if any one of them actually has
   *    `address` cached (i.e. the block is valid and the tags match).
   * 3. If you find the block, increment `_hits` and return a pointer to the
   *    block. Otherwise, return NULL.
   */
  const CacheConfig& configuration = _cache->get_config();
  vector<Cache::Block*> blocks = _cache->get_blocks_in_set(extract_index(address, configuration));
  uint32_t tag = extract_tag(address, configuration);
  for (Cache::Block* i : blocks) {
    if (i->get_tag() == tag && i->is_valid()) {
      _hits++;
      return i;
    }
  }
  return NULL;
}

Cache::Block* CacheSimulator::bring_block_into_cache(uint32_t address) const {
  /**
   * TODO
   *
   * 1. Use `_cache->get_blocks_in_set` to get all the blocks that could
   *    cache `address`.
   * 2. Loop through all these blocks to find an invalid `block`. If found,
   *    skip to step 4.
   * 3. Loop through all these blocks to find the least recently used `block`.
   *    If the block is dirty, write it back to memory.
   * 4. Update the `block`'s tag. Read data into it from memory. Mark it as
   *    valid. Mark it as clean. Return a pointer to the `block`.
   */
  const CacheConfig& configuration = _cache->get_config();
  uint32_t lru = INT_MAX;
  vector<Cache::Block*> blocks = _cache->get_blocks_in_set(extract_index(address, configuration));
  uint32_t tag = extract_tag(address, configuration);
  Cache::Block* block;
  for (Cache::Block* i : blocks) {
    if (!i->is_valid()) {
      i->mark_as_clean();
      i->mark_as_valid();
      i->set_tag(tag);
      i->read_data_from_memory(_memory);
      return i;
    }
    if (i->get_last_used_time() < lru) {
      lru = i->get_last_used_time();
      block = i;
    }
  }
  if (block->is_dirty()) {
    block->write_data_to_memory(_memory);
  }
  block->mark_as_clean();
  block->mark_as_valid();
  block->set_tag(tag);
  block->read_data_from_memory(_memory);
  return block;
}

uint32_t CacheSimulator::read_access(uint32_t address) const {
  /**
   * TODO
   *
   * 1. Use `find_block` to find the `block` caching `address`.
   * 2. If not found, use `bring_block_into_cache` cache `address` in `block`.
   * 3. Update the `last_used_time` for the `block`.
   * 4. Use `read_word_at_offset` to return the data at `address`.
   */
  Cache::Block* block = find_block(address);
  if (block == NULL) {
    block = bring_block_into_cache(address);
  }
  block->set_last_used_time(_use_clock.get_count()); 
  ++_use_clock;
  const CacheConfig& configuration = _cache->get_config();
  return block->read_word_at_offset(extract_block_offset(address, configuration));
}

void CacheSimulator::write_access(uint32_t address, uint32_t word) const {
  /**
   * TODO
   *
   * 1. Use `find_block` to find the `block` caching `address`.
   * 2. If not found
   *    a. If the policy is write allocate, use `bring_block_into_cache`.
   *    a. Otherwise, directly write the `word` to `address` in the memory
   *       using `_memory->write_word` and return.
   * 3. Update the `last_used_time` for the `block`.
   * 4. Use `write_word_at_offset` to to write `word` to `address`.
   * 5. a. If the policy is write back, mark `block` as dirty.
   *    b. Otherwise, write `word` to `address` in memory.
   */
  Cache::Block* block = find_block(address);
  if (block == NULL) {
    if (_policy.is_write_allocate()) {
      block = bring_block_into_cache(address);
    } else {
      _memory->write_word(address, word); 
      return;
    }
  }
  block->set_last_used_time(_use_clock.get_count()); 
  ++_use_clock;
  const CacheConfig& configuration = _cache->get_config();
  block->write_word_at_offset(word, extract_block_offset(address, configuration));
  if (_policy.is_write_back()) {
    block->mark_as_dirty();
  } else {
    block->write_data_to_memory(_memory);
  }
  
    
}
