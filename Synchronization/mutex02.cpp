template <typename K, typename V>
class registry
{
	std::shared_ptr<map<K, V>> 	_data;
	serial_queue 	              _queue;
public:
	void insert(K key, V val) {
		_queue.async([_d = _data, 
									_key = std::move(key), 
									_val = std::move(val)] {
				d->emplace(std::move(key), std::move(val));
		});
	}

	future<V> operator[](K key) {
		return _queue.async([_d = _data, 
									       _key = std::move(key)] {
			return _d->at(key);
		});
	}
};
