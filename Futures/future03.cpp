#include <iostream>
#include <boost/thread/future.hpp>

using namespace std;

int main() {
  boost::future<int> answer = boost::async([]{ return 42; });
  
  boost::future<void> done = answer.then( 
    [](boost::future<int> a) { std::cout << a.get() << '\n';} );
  
  // do something else
  done.wait();      // waits until future done is fulfilled
}
