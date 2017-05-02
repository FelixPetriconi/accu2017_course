#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>

int main() {
  auto answer = 
    stlab::async(stlab::default_executor, []{ return 42; } );
  
  stlab::future<void> done = answer.then( 
  	[](int a)                     // pass by value and not by future
    {  
      std::cout << a << '\n'; 
    }); 
  
  while (!done.get_try()) {
    // do something in the meantime
  }
}