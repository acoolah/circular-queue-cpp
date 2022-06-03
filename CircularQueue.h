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
	void printValues() const {
		std::vector<T>::const_iterator iter = m_container.cbegin();
		for (iter; iter != m_container.cend(); ++iter) {
			sdt::cout << *iter << std::endl;
		}
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
	T pushBack(T item) {
		if (!full()) {
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
	T take() {
		T tmp;

		if (!empty()) {
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
	void clear() {
		std::fill(m_container.begin(), m_container.end(), m_trash);
	}

	/*
	* Метод получения максимального количества элементов очереди
	*/
	int size() const {
		return m_container.size();
	}

	/*
	* Метод получения количества задействованных элементов
	*/
	int capacity() const {
		std::vector<std::vector<T>::const_iterator> _matches;
		for (auto i = m_container.begin(); i != m_container.end(); ++i) {
			if (*i != m_trash) {
				_matches.push_back(i);
			}
		}

		return _matches.size();
	}

	/*
	* Метод проверки заполнения очереди. True если заполнено
	*/
	bool full() const {
		return (m_head == m_tail + 1) || (m_head == 0 && m_tail == m_container.size() - 1);
	}

	/*
	* Метод проверки заполнения очереди. True если пусто
	*/
	bool empty() const {
		return (m_head == m_tail) && (m_head == -1 && m_tail == -1);
	}

private:
	std::vector<T> m_container;
	int m_head = -1;
	int m_tail = -1;
	T m_trash;
};
