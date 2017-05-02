#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
using namespace std;
int main() {
  auto getTheAnswer = [] {
    this_thread::sleep_for(chrono::milliseconds(815));
    return 42;
  };
  stlab::future<int> f = 
    stlab::async(
      stlab::default_executor,// default_executor
                              // uses platfrom thread pool on Win/OSX
                              // uses stlab thread pool on other OS
      getTheAnswer
    );

  while (!f.get_try()) {      // does not block
    // Do other stuff, getting the answer may take longer :-)
  }

  cout << f.get_try().value() << '\n'; // access the value
                           // throws exception .value() if not ready
}
