#include <stlab/future.hpp>
#include <stlab/serial_queue.hpp>
#include <stlab/default_executor.hpp>
#include <chrono>
#include <vector>
#include <iostream>
using namespace stlab;
using namespace std;
int main() {
	vector<int> values;
	const int Size = 500;
	auto my_serial_queue = serial_queue<detail::default_executor_type>(default_executor);
	auto executor = my_serial_queue.executor();

	auto work = [&]{	
		for (auto i = 0; i < Size; ++i) {
			executor([&values, i]{ values.push_back(i); });
		}
	};

	std::chrono::time_point<std::chrono::system_clock> start, stop;
  start = std::chrono::system_clock::now();

	auto f1 = async(default_executor, work).then([]{ return 0; });
	auto f2 = async(default_executor, work).then([]{ return 0; });

	auto ready = when_all(default_executor, [&](int, int){
			stop = std::chrono::system_clock::now();
    	std::chrono::duration<double> elapsed_seconds = stop-start;
    	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
				for (const auto& v : values) { 
					std::cout << v << " "; 
				}
			}, f1, f2);

	int end; std::cin >> end;
}