#include <map>
#include <future>
#include <mutex>
#include <string>
#include <iostream>
using namespace std;
template <typename K, typename V>
class registry
{
	map<K, V> _data;
	mutex 	  _guard;
public:
	void insert(const K& key, const V& value) {
		unique_lock<mutex> lock(_guard);
		_data.insert(
			make_pair("What is the answer?", 42)
		);
	}

	V operator[](const K& key) {
		unique_lock<mutex> lock(_guard);
		return _data[key];
	}
};

int main() {
	registry<string, int> my_registry;
	auto work = [&] {	my_registry.insert("What is the answer?", 42); };
  auto f1 = async(launch::async, work);
  auto f2 = async(launch::async, work);
  f1.get(); f2.get();
  cout << "What is the answer? " << my_registry["What is the answer?"] << '\n';
}