/*
 * list.h
 *
 *  Created on: Jul 3, 2017
 *      Author: tannous
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include "Exceptions.h"

using namespace mtm;
using namespace ListExceptions;

template<class T>
class List {

	class Node {
		T data;
		Node* next;
		Node* prev;
	public:
		friend class List;
		Node(const T& data_t) : data(data_t), next(nullptr), prev(nullptr) {} // C'tor
		Node(const Node& node) : data(node.data), next(node.next), prev(node.prev) {} // CC
		Node& operator=(const Node& node) {
			if (this == &node) {
				return *this;
			}
			data = node.data;
			next = node.next;
			prev = node.prev;
			return *this;
		}
		~Node() {};

		T& getData() {
			return data;
		}

		const T& getData() const {
			return data;
		}

	};

	static void swap(Node* i ,Node* j) {
		T temp = i->data;
		i->data = j->data;
		j->data = temp;
	}

	Node* first;
	int size;
public:

	class Iterator {
		Node* current;
		const List<T>* list;
	public:
		friend class List;
		Iterator(const List<T>* list, Node* node) : current(node), list(list) {}; // C'tor
		Iterator(const Iterator& iter) : current(iter.current), list(iter.list) {}; // CC
		~Iterator() {};

		Iterator& operator++() {           // ++x
			if (current == nullptr) {
				return *this;
			}
			current = current->next;
			return *this;
		}

		Iterator operator++(int) {         // x++
			if (current == nullptr) {
				return *this;
			}
			Iterator ret = *this;
			current = current->next;
			return ret;
		}

		Iterator& operator--() {           // --x
			if (current == list->first) {
				return *this;
			}
			if (*this == list->end()) {
				current = list->tail().current;
				return *this;
			}
			current = current->prev;
			return *this;
		}

		Iterator operator--(int) {         // x--
			if (current == list->first) {
				return *this;
			}
			if (*this == list->end()) {
				current = list->tail().current;
				return *this;
			}
			Iterator ret = *this;
			current = current->prev;
			return ret;
		}

		T& operator*() {
			if (current == nullptr) {
				throw ElementNotFound();
			}
			return current->data;
		}

		bool operator==(const Iterator& iter) {
			return ((current == iter.current) && (list == iter.list));
		}

		bool operator!=(const Iterator& iter) {
			return !(*this == iter);
		}

		Iterator& operator=(const Iterator& iter) {
			if (this == &iter) {
				return *this;
			}
			current = iter.current;
			list = iter.list;
			return *this;
		}

	};

	List() : first(nullptr), size(0) {}; // C'tor

	List<T>(const List<T>& list) : first(list.first), size(0) {
		for (Iterator iter = begin(); iter != end(); ++iter) {
			insert(*iter, end());
		}
	}

	~List<T>() {
		Iterator iter = begin();
		int count = size;
		for (int i = 0; i < count; i++) {
			remove(iter);
			iter = begin();
		}
	}

	List<T>& operator=(const List<T>& list) {
		if (this == &list) {
			return *this;
		}
		int count = size;
		Iterator iter = begin();
		for (int i = 0; i < count; i++) {
			remove(iter);
			iter = begin();
		}
		for (Iterator it = list.begin(); it != list.end(); ++it) {
			insert(*it,end());
		}
		return *this;
	}

	Iterator begin() const {
		Iterator iter(this, first);
		return iter;
	}

	Iterator end() const {
		Iterator iter = begin();
		while (iter.current) {
			++iter;
		}
		return iter;
	}

	Iterator tail() const {
		Iterator tail_iter = begin();
		for (Iterator iter = begin(); iter.current != nullptr; ++iter) {
			tail_iter = iter;
		}
		return tail_iter;
	}

	void insert(const T& data, Iterator iterator) {
		if (this != iterator.list) {
			throw ElementNotFound();
		}
		Iterator first_iter = begin();
		Node* node = new Node(data);
		if (size == 0) {
			first = node;
			iterator.current = first;
			iterator.current->next = nullptr;
			iterator.current->prev = nullptr; //
			size++;
			return;
		}
		node->next = iterator.current;
		if (first_iter == iterator) {
			iterator.current->prev = node;
			node->prev = nullptr; //
			first = node;
			size++;
			return;
		}
		if (iterator == end()) {
			Iterator iter = tail();
			Node* save_node = iter.current;
			node->prev = save_node;
			save_node->next = node;
			size++;
			return;
		} else {
			iterator--;
			Node* save_node = iterator.current;
			node->prev = save_node;
			save_node->next = node;
			Node* next_node = node->next;
			next_node->prev = node;
			size++;
			return;
		}
	}

	void insert(const T& data) {
		insert(data, end());
	}

	void remove(Iterator iterator) {
		if (size == 0 || iterator.list != this || iterator.current == nullptr) {
			throw ElementNotFound();
		}
		Node* node = iterator.current;
		if (size == 1) {
			delete node;
			first = nullptr;
			size--;
			return;
		}
		if (iterator == tail()) {
			iterator--;
			Node* prev = iterator.current;
			prev->next = nullptr;
			delete node;
			size--;
			return;
		}
		if (iterator == begin()) {
			iterator++;
			iterator.current->prev = nullptr; //
			first = iterator.current;
			delete node;
			size--;
			return;
		} else {
			iterator++;
			Node* node_next = iterator.current;
			iterator--;
			iterator--;
			Node* node_prev = iterator.current;
			node_prev->next = node_next;
			node_next->prev = node_prev;
			delete node;
			size--;
			return;
		}
	}

	template<class Predicate>
	Iterator find(const Predicate& predicate) {
		for (Iterator iter = begin(); iter != end(); ++iter) {
			if (predicate(*iter)) {
				return iter;
			}
		}
		return end();
	}

	template<class Compare>
	void sort(const Compare& compare) {
		if (size <= 1) {
			return;
		}
		for (Iterator i = begin(); i != end(); ++i) {
			for (Iterator j = i; j != end(); ++j) {
				if (i != j) {
					if (!compare(*i, *j)) {
						swap(i.current, j.current);
					}
				}
			}
		}
	}

	int getSize() const {
		return size;
	}

	bool operator==(const List<T>& list) {
		if (getSize() != list.getSize()) {
			return false;
		}
		for (int i = 0; i < getSize(); i++) {
			Iterator this_iter = begin();
			Iterator iter = list.begin();
			if (*this_iter != *iter) {
				return false;
			}
			iter++;
			this_iter++;
		}
		return true;
	}

	bool operator!=(const List<T>& list) {
		return !(*this == list);
	}

};

#endif /* LIST_H_ */
