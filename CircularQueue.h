#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class CircularQueue {
public:
	/*
	* Конструктор класса
	* @param {int} bufferSize - максимальный размер буфера (размера) очереди.
	* Выделяет память под определенное количество элементов. Не может быть изменено после создания экземпляра класса
	* @param {T} trashValue - значение, используемое в качетсве пустоты. Не может быть изменено после создания экземпляра класса
	*/
	CircularQueue(int bufferSize, T trashValue) {
		if (bufferSize > 0) {
			m_trash = trashValue;
			m_container = std::vector<T>(bufferSize, m_trash);
		}
		else {
			throw(std::invalid_argument("Invalid buffer size."));
		}
	}

	/*
	* Метод получения копии значений элементов очереди
	*/
	std::vector<T> getQueueValues() const {
		std::vector<T>_queue(m_container);
		return _queue;
	}

	/*
	* Метод получения значения, установленного в качестве пустоты
	*/
	T getTrashValue() const {
		return m_trash;
	}

	/*
	* Метод, выполняющий ввод нового элемента в очередь
	*/
	T push(T item) const {
		if (!isFull()) {
			if (m_head == -1) m_head = 0;

			m_tail = (m_tail + 1) % m_container.size();
			m_container[m_tail] = item;

			return item;
		}

		return m_trash;
	}

	/*
	* Метод получения элемента из очереди
	*/
	T pop() const {
		T tmp;

		if (!isEmpty()) {
			tmp = m_container[m_head];
			m_container[m_head] = m_trash;

			if (m_head == m_tail) {
				m_head = -1;
				m_tail = -1;
			}
			else {
				m_head = (m_head + 1) % m_container.size();
			}

			return tmp;
		}

		return m_trash;
	}

	/*
	* Метод очищения очереди. Заполняет очередь значением пустоты
	*/
	void clearQueue() {
		std::fill(m_container.begin(), m_container.end(), m_trash);
	}

	/*
	* Метод получения максимального количества элементов очереди
	*/
	int capacity() const {
		return m_container.size();
	}

	/*
	* Метод получения количества задействованных элементов
	*/
	int countOfNotEmpty() const {
		std::vector<std::vector<T>::const_iterator> _matches;
		for (auto i = m_container.begin(); i != m_container.end(); ++i) {
			if (*i != m_trash) {
				_matches.push_back(i);
			}
		}

		return _matches.size();
	}

	/*
	* Метод получения значения первого элемента
	*/
	T getFrontValue() const {
		return m_container[m_head];
	}

	/*
	* Метод получения значения последнего элемента
	*/
	T getBackValue() const {
		return m_container[m_tail];
	}

	/*
	* Метод проверки заполнения очереди. True если заполнено
	*/
	bool isFull() const {
		return (m_head == m_tail + 1) || (m_head == 0 && m_tail == m_container.size() - 1);
	}

	/*
	* Метод проверки заполнения очереди. True если пусто
	*/
	bool isEmpty() const {
		return m_head == m_tail;
	}

private:
	std::vector<T> m_container;
	int m_head = -1;
	int m_tail = -1;
	T m_trash;
};
