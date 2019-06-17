#include <iostream>
#include "tuple.hpp"
#include <vector>

int main() {
  //init
  my::tuple<int, std::vector<int>, std::string>
      b(10, std::vector<int>(100, 12), " kek ");
  my::tuple<std::string> c(" kek ");
  auto d = my::make_tuple(" kek ", 10, b);
  auto e(" kek ");
  const auto bm(std::move(b));
  auto f = my::make_tuple(100);
  auto g(bm);
  std::cout << g.get<1>()[10] << " " << bm.get<0>() << bm.get<std::string>() << std::endl;
}