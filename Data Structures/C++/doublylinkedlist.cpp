/*
########################
# DOUBLYLINKEDLIST.CPP #
########################
*/

#include "iostream"
using namespace std;

/*
Define our basic data structue, templated to hold any type of value
*/
template <typename T>
struct Node {
	T value;
	Node<T> *next;
	Node<T> *prev;
};

/*
Define our Doubly Linked List; Supports pushing on front and back,
popping from the front, back, or at a specific value and prints both
forward and reverse
*/
template <typename T>
class DoublyLinkedList {
	
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void push_front(T value);
	void push_back(T value);
	T pop_front();
	T pop_back();
	T pop_value(T value);
	int get_size();
	void print();
	void print_reverse();
	
private:
	Node<T> *front;
	Node<T> *back;
	int size;
};

/*
Constructor, initialize pointers to NULL, size to 0
*/
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	front = NULL;
	back = NULL;
	size = 0;
}

/*
Deconsutrctor, iterate trhough list and free each Node's memory
*/
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	while (front != NULL) {
		Node<T> *temp = front;
		front = front->next;
		delete temp;
	}
}

/*
Push a node to the front of the list, reassigning the original front's prev pointer
to the new inserted node
*/
template <typename T>
void DoublyLinkedList<T>::push_front(T value) {
	Node<T> *new_node = new Node<T>();
	new_node->value = value;
	new_node->prev = NULL;
	
	if (size == 0) {
		new_node->next = NULL;
		front = new_node;
		back = new_node;
	} else {
		new_node->next = front;
		front->prev = new_node;
		front = new_node;
	}
	
	size++;
}

/*
Push back a node, reassigning the original back's next pointer to the new
inserted node
*/
template <typename T>
void DoublyLinkedList<T>::push_back(T value) {
	Node<T> *new_node = new Node<T>();
	new_node->value = value;
	new_node->next = NULL;
	
	if (size == 0) {
		new_node->prev = NULL;
		front = new_node;
		back = new_node;
	} else {
		new_node->prev = back;
		back->next = new_node;
		back = new_node;
	}
	
	size++;
}

/*
Remove the front of the list and return the stored value
*/
template <typename T>
T DoublyLinkedList<T>::pop_front() {
	if (size == 0) {
		cout << "List is already empty." << endl;
	} else {
		Node<T> *temp = front;
		T out = temp->value;
		front = front->next;
		if (front != NULL) {			//Always check if the new Node you are pointing to ACTUALLY EXISTS
			front->prev = NULL;
		}
		delete temp;
		size--;
		return out;		
	}
}

/*
Remove the back of the list and return the stored value
*/
template <typename T>
T DoublyLinkedList<T>::pop_back() {
	if (size == 0) {
		cout << "List is already empty." << endl;
	} else {
		Node<T> *temp = back;
		T out = temp->value;
		back = back->prev;
		if (back != NULL) {
			back->next = NULL;
		}
		delete temp;
		size--;
		return out;
	}
}

/*
Remove an element in the list with a given specific value. If the value
does not exist, do nothing
*/
template <typename T>
T DoublyLinkedList<T>::pop_value(T value) {
	if (size == 0) {
		cout << "List is already empty." << endl;
	} else {
		
		if (front->value == value) {
			return pop_front();
		}
		
		if (back->value == value) {
			return pop_back();
		}
		
		Node<T> *it = front->next;
		
		if (it == NULL) {
			cout << "Could not find value: " << value << " In the list." << endl;
		} else {
			while (it->next != NULL) {
				if (it->value == value) {
					it->prev->next = it->next;
					it->next->prev = it->prev;
					delete it;
					size--;
					return value;
				}
				it = it->next;
			}			
		}
	
		cout << "Could not find value: " << value << " In the list." << endl;
		
	}
	

 }

 /*
 Return the size of the linked list
 */
template <typename T>
int DoublyLinkedList<T>::get_size() {
	return size;
}

/*
Print out the list contents in forward order
*/
template <typename T>
void DoublyLinkedList<T>::print() {
	Node<T> *it = front;
	
	while (it != NULL) {
		cout << it->value << " ";
		it = it->next;
	}
	
	cout << "Size of: " << size << endl;
}

/*
Print out the list contents in reverse order
*/
template <typename T>
void DoublyLinkedList<T>::print_reverse() {
	Node<T> *it = back;
	
	while (it != NULL) {
		cout << it->value << " ";
		it = it->prev;
	}
	
	cout << "Size of: " << size << endl;
}

/*
Main! Test out our implementation
*/
int main() {
	DoublyLinkedList<int> list;
	list.push_front(4);
	list.push_front(2);
	list.push_back(10);
	list.push_back(16);
	list.print();
	list.print_reverse();	
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	list.pop_value(8);
	list.pop_value(10);
	list.print();
	list.pop_front();
	list.print();
	list.pop_front();
}