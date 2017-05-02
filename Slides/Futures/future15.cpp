#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
#include <exception>
int main() {
	auto getTheAnswer = [] {
    throw std::runtime_error("Bad thing happened: Vogons appeared");
    std::cout << "I have got the answer\n"; return 42;
  };
  auto handleTheAnswer = [](int v) { 
    if (v == 0) std::cout << "We have a problem!\n"; 
    else std::cout << "The answer is " << v << '\n';
  };

  auto f = stlab::async(stlab::default_executor, getTheAnswer)
    .recover([](stlab::future<int> result) {
      if (result.error()) {
        std::cout << "Listen to Vogon poetry!\n"; 
        return 0;
      }
      return result.get_try().value();
  }).then(handleTheAnswer);

  while (!f.get_try());
}