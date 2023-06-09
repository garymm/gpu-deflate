#include "huffman/huffman.hpp"

#include <boost/ut.hpp>

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

auto main() -> int
{
  using ::boost::ut::aborts;
  using ::boost::ut::expect;
  using ::boost::ut::test;

  namespace huffman = ::gpu_deflate::huffman;
  using namespace huffman::literals;

  test("code table constructible from code-symbol mapping") = [] {
    const auto t = huffman::table<char>{
        huffman::table_contents,
        {{00000_c, '\4'},
         {00001_c, 'x'},
         {0001_c, 'q'},
         {001_c, 'n'},
         {01_c, 'i'},
         {1_c, 'e'}}};

    auto ss = std::stringstream{};
    ss << t;

    constexpr auto table =
        "Bits\tCode\tValue\tSymbol\n"
        "1\t1\t1\t`e`\n"
        "2\t01\t1\t`i`\n"
        "3\t001\t1\t`n`\n"
        "4\t0001\t1\t`q`\n"
        "5\t00000\t0\t`\4`\n"
        "5\t00001\t1\t`x`\n";

    expect(table == ss.str()) << ss.str();
  };

  test("code table constructible from code-symbol mapping from different "
       "ranges") = [] {
    // `t1` deduces a C-array for the range
    const auto t1 =  // clang-format off
      huffman::table<char>{
        huffman::table_contents,
        {{00000_c, '\4'},
         {00001_c, 'x'},
         {0001_c,  'q'},
         {001_c,   'n'},
         {01_c,    'i'},
         {1_c,     'e'}}
      };
    // clang-format on

    const auto t2 =  // clang-format off
      huffman::table<char>{
        huffman::table_contents,
        std::vector{
            std::tuple{00000_c, '\4'},
                      {00001_c, 'x'},
                      {0001_c,  'q'},
                      {001_c,   'n'},
                      {01_c,    'i'},
                      {1_c,     'e'}}
      };
    // clang-format on

    expect(std::ranges::equal(t1, t2));
  };

  test("code table constructible from code-symbol mapping with deduction "
       "guides") = [] {
    const auto t1 =  // clang-format off
      huffman::table{
        huffman::table_contents,
        {std::pair{00000_c, '\4'},
                  {00001_c, 'x'},
                  {0001_c,  'q'},
                  {001_c,   'n'},
                  {01_c,    'i'},
                  {1_c,     'e'}}
      };
    // clang-format on

    const auto t2 =  // clang-format off
      huffman::table{
        huffman::table_contents,
        std::vector{
            std::tuple{00000_c, '\4'},
                      {00001_c, 'x'},
                      {0001_c,  'q'},
                      {001_c,   'n'},
                      {01_c,    'i'},
                      {1_c,     'e'}}
      };
      // clang-format off

    expect(std::ranges::equal(t1, t2));
  };

  test("code table constexpr constructible from code-symbol") = [] {
    static constexpr auto t1 = // clang-format off
      huffman::table{
        huffman::table_contents,
        {std::pair{00000_c, '\4'},
                  {00001_c, 'x'},
                  {0001_c,  'q'},
                  {001_c,   'n'},
                  {01_c,    'i'},
                  {1_c,     'e'}}
      };
    // clang-format on

    static constexpr auto t2 =  // clang-format off
        huffman::table<char, 6>{
          huffman::table_contents,
          {{00000_c, '\4'},
           {00001_c, 'x'},
           {0001_c,  'q'},
           {001_c,   'n'},
           {01_c,    'i'},
           {1_c,     'e'}}
        };
    // clang-format on

    expect(std::ranges::equal(t1, t2));
  };

  test("code table aborts on duplicate codes") = [] {
    expect(aborts([] {  // clang-format off
      huffman::table{
          huffman::table_contents,
          {std::pair{00000_c, '\4'},
                    {00001_c, 'x'},
                    {0001_c,  'q'},
                    {0001_c,  'g'},
                    {001_c,   'n'},
                    {01_c,    'i'},
                    {1_c,     'e'}}};
      // clang-format on
    }));
  };

  test("code table aborts on duplicate symbols") = [] {
    expect(aborts([] {  // clang-format off
      huffman::table{
          huffman::table_contents,
          {std::pair{00000_c, '\4'},
                    {00001_c, 'x'},
                    {0001_c,  'q'},
                    {0000_c,  'q'},
                    {001_c,   'n'},
                    {01_c,    'i'},
                    {1_c,     'e'}}};
      // clang-format on
    }));
  };
}
