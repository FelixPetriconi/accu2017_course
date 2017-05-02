
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <stlab/channel.hpp>
#include <stlab/default_executor.hpp>

using namespace stlab;
using namespace std;

struct unpack
{
  std::string _data;
  process_state_scheduled _state = await_forever;
  string::const_iterator _it;

  void await(std::string s) {
      if (s.size() != 80)
          return;

    _data = std::move(s);
    _state = yield_immediate;
    _it = _data.begin();
  }

  auto state() const { return _state; }

  auto yield() {
    auto result = *_it;
    ++_it;
    if (_it == _data.end())
      _state = await_forever;
    return result;
  }
};

struct filter
{
  process_state_scheduled _state;
  char _c;

  void await(char c) {
    if (c == 10 || c == 13 )
      return;

    _c = c;
    _state = yield_immediate;
  }

  auto state() const { return _state; }

  auto yield() {
    _state = await_forever;
    return _c;
  }
};


struct pack
{
  char _data[125];
  process_state_scheduled _state;
  int _i;

  pack()
    : _state(await_forever)
    , _i(0)
  {}

  void await(string::value_type c) {
    _data[_i] = c;
    ++_i;
    if (_i == 125)
      _state = yield_immediate;
  }

  auto state() const { return _state; }

  auto yield() {
    _i = 0;
    _state = await_forever;
    return string(_data, 125);
  }
};

int main() {
  sender<string> send;
  receiver<string> receiver;
  std::tie(send, receiver) = channel<string>(default_executor);

  auto unpack_pack = receiver | 
      unpack{} |
      filter{} |
      pack{} | 
      [](string s) { 
      printf("%s\n", s.c_str()); };

  receiver.set_ready();

  char buffer[80];

  fstream fileStream("text.txt", ios_base::in);
  if (!fileStream.is_open()) {
    std::cout << "Failed to open text.txt\n";
    return -1;
  }
  while (!fileStream.eof()) {
    fileStream.get(buffer, 80);
    send(string(buffer, 80));
  }

  while (true) {
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
}