#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
protected:
	template <typename J>
	class Node {
	public:
		Node(const J& data, Node<J>* prev, Node<J>* next) {
			this->data = data;
			this->prev = prev;
			this->next = next;
		}

		Node<J>* prev;
		Node<J>* next;
		J data;
	};
public:
	// Behaviors
	void printForward() const {
		Node<T>* current = head;
		Node<T>* next = nullptr;

		while (current != nullptr) {
			next = current->next;
            std::cout << current->data << std::endl;

			current = next;
		}
	}

	void printReverse() const {
        Node<T>* current = tail;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            prev = current->prev;
            std::cout << current->data << std::endl;

            current = prev;
        }
    }

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
        return count;
    }

	Node<T>* getHead() {
        return head;
    }

	const Node<T>* getHead() const {
        return head;
    }

	Node<T>* getTail() {
        return tail;
    }

	const Node<T>* getTail() const {
        return tail;
    }

	// Insertion
	void addHead(const T& data) {
        Node<T>* newNode = new Node<T>(data, nullptr, head);

        if (head != nullptr) {
            head->prev = newNode;
        }

        head = newNode;

        if (tail == nullptr) {
            tail = newNode;
        }

        count++;
    }

	void addTail(const T& data) {
        Node<T>* newNode = new Node<T>(data, tail, nullptr);

        if (tail != nullptr) {
            tail->next = newNode;
        }

        tail = newNode;

        if (head == nullptr) {
            head = newNode;
        }

        count++;
    }

	// Removal
	bool removeHead() {
        if (head == nullptr) {
            return false;
        }

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count = 0;
            return true;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }

        count--;
        return true;
    }

	bool removeTail() {
        if (tail == nullptr) {
            return false;
        }

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count = 0;
            return true;
        }

        if (tail->prev == nullptr) {
            delete tail;
            tail = nullptr;
        } else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }

        count--;
        return true;
    }

	void clear() {
        if (head == nullptr && tail == nullptr) {
            return;
        }

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        Node<T>* current = head;
        Node<T>* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        count = 0;
    }

	// Operators
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}

        clear();

        count = 0;
		const Node<T>* currNode = rhs.getHead();
		while (currNode != nullptr) {
			addTail(currNode->data);
			currNode = currNode->next;
		}

		return *this;
	}

	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        clear();

        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
        return *this;
    }

	// Construction/Destruction
	LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

	LinkedList(const LinkedList<T>& list) {
        count = 0;
		const Node<T>* currNode = list.getHead();
		while (currNode != nullptr) {
			addTail(currNode->data);
			currNode = currNode->next;
		}
	}

	LinkedList(LinkedList<T>&& other) noexcept {
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

	~LinkedList() {
        clear();
    }

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};
