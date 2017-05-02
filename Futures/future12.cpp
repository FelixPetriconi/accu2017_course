#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
#include <exception>

int main() { 
  auto getTheAnswer = [] {
    throw std::runtime_error("Bad thing happened: Vogons appeared!");
    return 42;
  };
  auto f = stlab::async(stlab::default_executor, getTheAnswer);

  try {
    while (!f.get_try()) { // try accessing the value
                           // may rethrow a stored exception
      // Do other stuff, getting the answer may take longer
    }

    std::cout << f.get_try().value() << '\n';
  }
  catch (const std::runtime_error& ex) {
    std::cout << ex.what() << '\n';
  }
}