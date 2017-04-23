#include <stlab/channel.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
#include <cstdlib>

using namespace stlab;

int main() {
  sender<int> sendA, sendB;
  receiver<int> receiverA, receiverB;
  std::tie(sendA, receiverA) = channel<int>(default_executor);
  std::tie(sendB, receiverB) = channel<int>(default_executor);

  auto printer = [](int x, int y) {
    printf("Process %d %d\n", x, y);
  };

  auto printProcess = join(default_executor, printer,
                           receiverA, receiverB);

  receiverA.set_ready();
  receiverB.set_ready();

  sendA(1); sendA(2);
  sendB(3); sendA(4);
  sendB(5); sendB(6);

  int end; std::cin >> end;
}