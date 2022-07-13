#include "utils.h"

uint32_t extract_tag(uint32_t address, const CacheConfig& cache_config) {
  // TODO
  uint32_t num_block_offset_bits = cache_config.get_num_block_offset_bits();
  uint32_t num_index_bits = cache_config.get_num_index_bits();
  uint32_t num_tag_bits = cache_config.get_num_tag_bits();

  if (num_tag_bits > 31) {
    return address;
  } 
  return (address >> (num_block_offset_bits + num_index_bits));
}

uint32_t extract_index(uint32_t address, const CacheConfig& cache_config) {
  // TODO
  uint32_t num_block_offset_bits = cache_config.get_num_block_offset_bits();
  //uint32_t num_index_bits = cache_config.get_num_index_bits();
  uint32_t num_tag_bits = cache_config.get_num_tag_bits();

  if (num_tag_bits > 31) {
    return 0;
  } 
  return (address << num_tag_bits) >> (num_tag_bits + num_block_offset_bits);
}

uint32_t extract_block_offset(uint32_t address, const CacheConfig& cache_config) {
  // TODO
  //uint32_t num_block_offset_bits = cache_config.get_num_block_offset_bits();
  uint32_t num_index_bits = cache_config.get_num_index_bits();
  uint32_t num_tag_bits = cache_config.get_num_tag_bits();

  if (num_tag_bits > 31) {
    return 0;
  } 
  return address << (num_tag_bits + num_index_bits) >> (num_tag_bits + num_index_bits);
}
