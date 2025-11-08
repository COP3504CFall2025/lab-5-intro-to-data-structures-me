#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
protected:
	template <typename J>
	class Node {
	public:
		Node(const J& data, Node<J>* previous, Node<J>* next) {
			datum = new J(data);
			this->previous = previous;
			this->next = next;
		}

		~Node() {
			delete datum;
		}

		Node<J>* previous;
		Node<J>* next;
		J* datum;
	};
public:
	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};
