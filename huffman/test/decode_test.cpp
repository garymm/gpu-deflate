#include "huffman/huffman.hpp"

#include <boost/ut.hpp>

#include <array>
#include <cstddef>

auto main() -> int
{
  using ::boost::ut::expect;
  using ::boost::ut::test;

  namespace huffman = ::gpu_deflate::huffman;

  // encoded data from dahuffman readme.rst, but in hex.
  constexpr std::array<std::byte, 6> bytes = {
      std::byte{0x86},
      std::byte{0x7c},
      std::byte{0x25},
      std::byte{0x13},
      std::byte{0x69},
      std::byte{0x40}};
  return EXIT_SUCCESS;
}
