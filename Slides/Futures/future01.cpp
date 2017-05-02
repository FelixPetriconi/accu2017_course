#include <future>
#include <iostream>

using namespace std;

int main() {

	auto getTheAnswer = [] {
		this_thread::sleep_for(chrono::milliseconds(815));
    return 42;
	};

  future<int> f2 = async(launch::async, getTheAnswer);
  
  // Do other stuff, getting the answer may take longer
  cout << f2.get() << '\n';        // access the value
}