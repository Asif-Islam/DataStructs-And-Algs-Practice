/*
############
# STACK.CPP #
############
*/

#include "iostream"
using namespace std;


/*
Define our basic data structue, templated to hold any type of value
*/
template <typename T>
struct Node {
	T value;
	Node *next;
};

/*
Define our Stack class; Supports pushing and popping from the stack as well
as peaking at the top value of the stack.
*/
template <typename T>
class Stack {
	public:
		Stack();
		~Stack();
		void push(T value);
		T pop();
		T peak();
		void print();
	
	private:
		int size;
		Node<T> *top;
};

/*
Constructor; initialize our size to 0
*/
template<typename T>
Stack<T>::Stack() {
	cout << "Hello" << endl;
	top = NULL;
	size = 0;
}

/*
Deconstructor, loop over our stack and delete each node
*/
template <typename T>
Stack<T>::~Stack() {
	while (top != NULL) {
		Node<T> *temp = top;
		top = top->next;
		delete temp;
	}
}

/*
Push, add a node to the stack, always setting the top variable
of the Stack as the new incoming node
*/
template <typename T>
void Stack<T>::push(T value) {
	if (size == 0) {
		Node<T> *new_top = new Node<T>();
		new_top->value = value;
		top = new_top;
	} else {
		Node<T> *new_top = new Node<T>();
		new_top->value = value;
		new_top->next = top;
		top = new_top;
	}

	size++;
}

/*
Pop, remove the top of the stack and return the node's value
*/
template <typename T>
T Stack<T>::pop() {
	if (size == 0) {
		cout << "Stack is empty!" << endl;
	} else {
		Node<T> *temp = top;
		T result = top->value;
		top = top->next;
		delete temp;
		size--;
		return result;
	}
	
	
}

/*
Peak, return the top value of the stack but do not change the contents of the stack
*/
template <typename T>
T Stack<T>::peak() {
	if (size == 0) {
		cout << "Stack is empty!" << endl;
	} else {
		return *top;
	}
}

/*
Iterate through the stack and print each value
*/
template <typename T>
void Stack<T>::print() {
	Node<T> *it = top;
	while (it != 0) {
		cout << it->value << endl;
		it = it->next;
	}
	cout << "---" << endl;
}

/*
Main! Test out our stack
*/
int main() {
	Stack<int> stack;
	stack.push(1);
	stack.print();
	stack.push(3);
	stack.print();
	stack.push(5);
	stack.print();
	stack.push(7);
	stack.print();
	stack.pop();
	stack.print();
	stack.pop();
	stack.print();
}