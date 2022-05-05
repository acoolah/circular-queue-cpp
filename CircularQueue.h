#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class CircularQueue {
public:
	/*
	* ����������� ������
	* @param {int} bufferSize - ������������ ������ ������ (�������) �������.
	* �������� ������ ��� ������������ ���������� ���������. �� ����� ���� �������� ����� �������� ���������� ������
	* @param {T} trashValue - ��������, ������������ � �������� �������. �� ����� ���� �������� ����� �������� ���������� ������
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
	* ����� ��������� ����� �������� ��������� �������
	*/
	std::vector<T> getQueueValues() const {
		std::vector<T>_queue(m_container);
		return _queue;
	}

	/*
	* ����� ��������� ��������, �������������� � �������� �������
	*/
	T getTrashValue() const {
		return m_trash;
	}

	/*
	* �����, ����������� ���� ������ �������� � �������
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
	* ����� ��������� �������� �� �������
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
	* ����� �������� �������. ��������� ������� ��������� �������
	*/
	void clearQueue() {
		std::fill(m_container.begin(), m_container.end(), m_trash);
	}

	/*
	* ����� ��������� ������������� ���������� ��������� �������
	*/
	int capacity() const {
		return m_container.size();
	}

	/*
	* ����� ��������� ���������� ��������������� ���������
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
	* ����� ��������� �������� ������� ��������
	*/
	T getFrontValue() const {
		return m_container[m_head];
	}

	/*
	* ����� ��������� �������� ���������� ��������
	*/
	T getBackValue() const {
		return m_container[m_tail];
	}

	/*
	* ����� �������� ���������� �������. True ���� ���������
	*/
	bool isFull() const {
		return (m_head == m_tail + 1) || (m_head == 0 && m_tail == m_container.size() - 1);
	}

	/*
	* ����� �������� ���������� �������. True ���� �����
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
