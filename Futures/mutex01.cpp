#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	vector<int> values;
	mutex v_mutex;

	auto work = [&_mutex = v_mutex, &_values = values]() {
		for (auto i = 0; i < 500; ++i) {
			unique_lock<mutex> lock(_mutex);
			_values.push_back(i);
		}
	};
	std::chrono::time_point<std::chrono::system_clock> start, stop;
  start = std::chrono::system_clock::now();
	auto t1 = thread(work);
	auto t2 = thread(work);
	t2.join();
	t1.join();
	stop = std::chrono::system_clock::now();
    	std::chrono::duration<double> elapsed_seconds = stop-start;
    	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	for (const auto& v : values) { std::cout << v << " "; }
}