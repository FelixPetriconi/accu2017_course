#include <stlab/channel.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
using namespace stlab;

struct adder
{
	int _sum = 0;
	process_state_scheduled _state = await_forever;

	void await(int x) {
		_sum += x;
		if (x == 0) {
			_state = yield_immediate;
		}
	}

	int yield() {
		int result = _sum;
		_sum = 0;
		_state = await_forever;
		return result;
	}

	auto state() const { return _state; }
};

int main() {
	sender<int> send;       
	receiver<int> receiver; 
	std::tie(send, receiver) = channel<int>(default_executor);

	auto calculator = receiver | adder{} | 
		[](int x) { std::cout << x << '\n'; };
		
	receiver.set_ready();

	while (true) {
		int x;
		std::cin >> x;
		send(x);
	}
}