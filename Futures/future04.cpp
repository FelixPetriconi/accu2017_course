#include <iostream>
#include <boost/thread/future.hpp>

using namespace std;

int main() {
  auto a = boost::async([]{ return 40; });
  auto b = boost::async([]{ return 2; });
  
  auto answer = boost::when_all(std::move(a), std::move(b)).then( 
    [](auto f) {
      auto t = f.get();
      return get<0>(t).get() + get<1>(t).get();
    });
  
  // wait for the something else
  cout << answer.get() << '\n';
}