/*
############# 
# QUEUE.CPP #
#############
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
};

/*
Define our Queue class, with supported peaking of the front and back
of the queue
*/
template <typename T>
class Queue {

public:
	Queue();
	~Queue();
	void push(T value);
	int get_size();
	T pop();
	T get_front();
	T get_back();
	void print();

private:
	Node<T> *front;
	Node<T> *back;
	int size;
	
};

/*
Consutructor, initialize our size and NULL our pointers
*/
template <typename T>
Queue<T>::Queue() {
	front = NULL;
	back = NULL;
	size = 0;
}

/*
Deconstructor, loop through the queue and delete each node
*/
template <typename T>
Queue<T>::~Queue() {
	Node<T> *it = front;
	
	while (it != NULL) {
		Node<T> *temp = it;
		it = it->next;
		delete temp;
	}
}

/*
Push a value into the queue; if the queue was originally empty,
set the front and back to the new node, otherwise only change the 
back pointer to point to the newly introduced node
*/
template <typename T>
void Queue<T>::push(T value) {
	
	Node<T> *new_node = new Node<T>();
	
	if (!new_node) {
		cout << "Insufficient memory." << endl;
		return;
	}
	
	new_node->value = value;
	new_node->next = NULL;
	
	if (size == 0) {
		front = new_node;
		back = new_node;
	} else {
		back->next = new_node;
		back = new_node;
	}
	
	size++;
}

/*
Remove the top element of the queue and return the value stored.
If there was only one node, then also set back = NULL
*/
template <typename T>
T Queue<T>::pop() {
	
	if (size == 0) {
		cout << "Queue is alredy empty." << endl;
	} else {
		Node<T> *temp = front;
		T out = front->value;
		front = front->next;
		delete temp;
		
		if (size == 1) {
			back = NULL;
		}
		
		size--;
		return out;		
	}
}

/*
Return the current size of the queue
*/
template <typename T>
int Queue<T>::get_size() {
	return size;
}

/*
Return the front value in the queue
*/
template <typename T>
T Queue<T>::get_front() {
	if (size == 0) {
		cout << "Queue is empty." << endl;
	} else {
		return front->value;		
	}

}

/*
Return the last value of the queue
*/
template <typename T>
T Queue<T>::get_back() {
	if (size == 0) {
		cout << "Queue is empty." << endl;
	} else {
		return back->value;		
	}

}

template <typename T>
void Queue<T>::print() {
	Node<T> *it = front;
	
	while (it != NULL) {
		cout << it->value << " ";
		it = it->next;
	}
	cout << endl;
}

/*
Main! Test out the queue
*/
int main() {
	Queue<int> queue;
	queue.push(2);
	queue.print();
	cout << queue.get_front() << endl;
	cout << queue.get_back() << endl;
	queue.push(5);
	queue.push(1);
	cout << "SIZE: " << queue.get_size() << endl;
	queue.print();
	queue.pop();
	cout << "SIZE: " << queue.get_size() << endl;
	queue.print();
	cout << queue.get_front() << endl;
	
}