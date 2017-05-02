#include <stlab/channel.hpp>
#include <stlab/default_executor.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace stlab;
using namespace std;
int main() {
  sender<int> sendInt;
  receiver<int> receiveInt;
  std::tie(sendInt, receiveInt) = channel<int>(default_executor);

  sender<string> sendString;
  receiver<string> receiveString;
  std::tie(sendString, receiveString) = channel<string>(default_executor);

  sender<double> sendDouble;
  receiver<double> receiveDouble;
  std::tie(sendDouble, receiveDouble) = channel<double>(default_executor);


  auto combiner = [](int x, string y, double z){
    stringstream s;
    s << x << " " << y << " " << z;
    return s.str();
  };

  auto printer = [] (string s) {
    printf("%s\n",s.c_str());
  };

  auto storer = [](const string& s) {
    fstream fileStream("test.txt", ios_base::app);
    fileStream << s << '\n';
  };

  auto joinedProcess = join(default_executor, combiner,
                            receiveInt, receiveString, receiveDouble);

  receiveInt.set_ready();
  receiveString.set_ready();
  receiveDouble.set_ready();

  auto printingProcess = joinedProcess | printer;
  auto storingProcess = joinedProcess | storer;

  joinedProcess.set_ready();
  printingProcess.set_ready();
  storingProcess.set_ready();

  sendInt(1); sendInt(2);
  sendString("One"); sendString("Two");
  sendDouble(1.0); sendDouble(2.0);

  int end; std::cin >> end;
}