#include <future>
#include <iostream>
#include <exception>

using namespace std;

int main() {
	auto getTheAnswer = [] {
		throw runtime_error("Bad things happened: Vogons appeared!");
    return 42;
	};

  future<int> f2 = async(launch::async, getTheAnswer);
  
  // Do other stuff, getting the answer may take longer
  try {
    cout << f2.get() << '\n';  // try accessing the value
                               // rethrows the stored exception
  }
  catch (const runtime_error& ex) {
    cout << ex.what() << '\n';
  }
}