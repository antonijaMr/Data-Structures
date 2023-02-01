#include "unorderedMap.hpp"

size_t hash(const std::string& s) {
  size_t sum = 5381;
  for (char c : s) {
    sum += (sum << 4) + c;
  }
  return sum;
}

