#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>

using namespace stlab;

int main() {
  auto a = async(default_executor,[]{ return 40; });
  auto b = async(default_executor,[]{ return 2; });
  
  auto answer = when_all(
    default_executor, 
    [](int x, int y) { return x + y; }, 
    a, b);
  
  while (!answer.get_try()) {
  // wait for something else
  }
  std::cout << answer.get_try().value() << '\n';
}