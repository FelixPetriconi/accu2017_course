#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>

using namespace stlab;

int main() {
  auto answer = async(default_executor,[]{ return 42; });

  auto dent = answer.then([](int a) {
    std::cout << "Tell the answer " << a << " Arthur Dent\n"; 
  });
  
  auto marvin = answer.then([](int a) { 
    std::cout << "May the answer " << a << " shear up Marvin\n"; 
  });  
  
  while (!dent.get_try() && !marvin.get_try()) {
  // wait for  something else
  }
}