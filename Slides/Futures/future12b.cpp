#include <stlab/future.hpp>
#include <iostream>
#include <exception>
using namespace std;
int main() {
	auto getTheAnswer = [] {
    throw exception("Bad thing happened: Vogons appeared");
    cout << "I have got the answer\n";
    return 42;
  };

  auto handleTheAnswer = [](int v) { 
    if (!v) cout << "No answer\n"; return v; 
  };

  auto f = stlab::async(stlab::default_scheduler(), getTheAnswer)
    .recover([](stlab::future<int> result) {
      if (result.error()) {
        cout << "Listen to Vogon poetry!\n";
        return 0;
      }
      return result.get_try().value();
  }).then(handleTheAnswer);

  while (!f.get_try()) {   // try accessing the value
                           // no rethrow
                           // Do other stuff, getting the answer may take longer
  }
  cout << f.get_try().value() << '\n';
}