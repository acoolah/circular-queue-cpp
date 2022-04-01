#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class CircularQueue {
private:
	std::vector<T> _container;
	int _head = -1;
	int _tail = -1;
	T _trash = NULL;

protected:
	bool IsFull() {
		return (_head == _tail + 1) || (_head == 0 && _tail == _container.size() - 1);
	}

	bool IsEmpty() {
		return _head == _tail;
	}

public:
	CircularQueue(int bufferSize = 10, T trashValue = NULL) {
		if (bufferSize > 0) {
			_trash = trashValue;
			_container = std::vector<T>(bufferSize, _trash);
		}
		else {
			throw(std::invalid_argument("Invalid buffer size."));
		}
	}

	std::vector<T> GetQueueValues() {
		std::vector<T>_queue(_container);
		return _queue;
	}

	T GetTrashValue() const {
		return _trash;
	}

	T Push(T item) {
		if (!IsFull()) {
			if (_head == -1) _head = 0;

			_tail = (_tail + 1) % _container.size();
			_container[_tail] = item;

			return item;
		}

		return _trash;
	}

	T Pop() {
		T _buffer;

		if (!IsEmpty()) {
			_buffer = _container[_head];
			_container[_head] = _trash;

			if (_head == _tail) {
				_head = -1;
				_tail = -1;
			}
			else {
				_head = (_head + 1) % _container.size();
			}

			return _buffer;
		}

		return _trash;
	}

	void ClearQueue() {
		std::fill(_container.begin(), _container.end(), _trash);
	}

	int Capacity() {
		return _container.size();
	}

	int CountOfNotEmpty() {
		std::vector<std::vector<T>::const_iterator> _matches;
		for (auto i = _container.begin(); i != _container.end(); ++i) {
			if (*i != _trash) {
				_matches.push_back(i);
			}
		}

		return _matches.size();
	}

	T Next() const {
		return _container[_head];
	}

	T Last() const {
		return _container[_tail];
	}
};