#include <stlab/channel.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
#include <cstdlib>
using namespace stlab;
int main() {
	sender<int> send;       
	receiver<int> receiver; 
	std::tie(send, receiver) = channel<int>(default_executor);

	auto printerA = [](int x){ printf("Process A %d\n", x); };
	auto printerB =	[](int x){ printf("Process B %d\n", x); };

	auto printer_processA = receiver | printerA;
	auto printer_processB = receiver | printerB;

	receiver.set_ready();          // no more processes will be attached
																 // process may start to work
	send(1); send(2); send(3);
	int end; std::cin >> end;
}