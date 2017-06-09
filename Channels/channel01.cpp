#include <stlab/channel.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
int main() {
	stlab::sender<int> send;       // sending part of the channel
	stlab::receiver<int> receiver; // receiving part of the channel
	std::tie(send, receiver) =     // combining both to a channel
		stlab::channel<int>(stlab::default_executor);

	auto printer = 
		[](int x){ std::cout << x << '\n'; };	// stateless process

	auto printer_process = 
		receiver | printer; 				 // attaching process to the receiving
																 // part
	receiver.set_ready();          // no more processes will be attached
																 // process starts to work
	send(1); send(2); send(3);     // start sending into the channel

	int end; std::cin >> end;      // simply wait to end application
}