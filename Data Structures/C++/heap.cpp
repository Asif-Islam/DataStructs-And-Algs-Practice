/*
HEAP.CPP

This is an implementation of the Heap (priority queue) data structure.

*/


#include "iostream"

using namespace std;
/*
Define our basic data structue, templated to hold any type of value
*/
template <typename T>
struct Node {
	int key;
	T value;
};

/*
Define our Heap class, notably containing an array of Nodes, a bool determining if 
extract max or extract min, and a size
*/
template <typename T>
class Heap {
	
	public:
		Node<T> *heap_array;
		bool extract_min;
		int size;
		Heap<T>(bool extract_min);
		~Heap<T>();
		void Insert(Node<T> node);
		void Print();
		Node<T> Extract();
	
	private:
		void Resize_Array();
		void BubbleUp(int index);
		void BubbleDown(int index);
		int max_size;
	
};

/*
Heap Constructor: Accept a boolean that determines whether our heap performs
minimum or maximum extraction
*/
template <typename T>
Heap<T>::Heap(bool extract_min) {
	this->extract_min = extract_min;
	heap_array = new Node<T>[2];
	if (!heap_array) {
		cout << "Insufficient memory" << endl;
		return;
	}
	size = 0;
	max_size = 2;
}

/*
Heap Deconstructor: Ensure we delete our heap array when our heap goes out of scope
or is deleted
*/
template <typename T>
Heap<T>::~Heap() {
	delete [] heap_array;
}

/*
Restore the heap property for a leaf; I.e., ensure that the node's parent has a smaller
value than it's own, and that it's children have a larger value
*/
template <typename T>
void Heap<T>::BubbleUp(int pos) {
	int parent_pos = (pos - 1) / 2;
	if (pos != 0 && (heap_array[parent_pos].key > heap_array[pos].key)) {
		Node<T> temp = heap_array[parent_pos];
		heap_array[parent_pos] = heap_array[pos];
		heap_array[pos] = temp;
		BubbleUp(parent_pos);
	}
}

/*
Restore the heap property for the root; I.e., ensure that the node's parent has a smaller
value than it's own, and that it's children have a larger value
*/
template <typename T>
void Heap<T>::BubbleDown(int pos) {
	int child1_pos = 2 * pos + 1;
	int child2_pos = 2 * pos + 2;
	int minIndex = pos;

	if (child1_pos >= size) {
		return;
	}

	if (heap_array[child1_pos].key < heap_array[minIndex].key) {
		minIndex = child1_pos;
	} else if ((child2_pos < size) && (heap_array[child2_pos].key < heap_array[minIndex].key)) {
		minIndex = child2_pos;
	}

	if (minIndex != pos) {
		Node<T> temp = heap_array[minIndex];
		heap_array[minIndex] = heap_array[pos];
		heap_array[pos] = temp;
		BubbleDown(minIndex);		
	}

}

/*
Insert a node into the heap, Bubbling up to restore the heap property
*/
template <typename T>
void Heap<T>::Insert(Node<T> node) {
	//Resize if we've reached the maximum of our array
	if (size == max_size) {
		Resize_Array();
	}

	/*
		If we're extracting maximum, then flip the key values as they enter; The technical maximum
		will have the most negative value now, and will be the root of our heap
	*/
	if (!extract_min) {
		node.key *= -1;
	}

	int pos = size;
	heap_array[pos] = node;
	size++;

	if (pos == 0) { 
		return;
	}

	int parent_pos = (pos - 1) / 2;
	BubbleUp(pos);
}

/*
	Print out the keys of the heap in order
*/
template <typename T>
void Heap<T>::Print() {
	for (int i = 0; i < size; i++) {
		cout << heap_array[i].key << endl;
	}
	cout << "---" << endl;
}

/*
Extract the root of the heap; then take the farthest leaf, append it as the root,
and Bubble Down to restore the heap property
*/
template <typename T>
Node<T> Heap<T>::Extract() {
	
	if (size == 0) {
		cout << "Cannot extract a node; The heap is null" << endl;
	}

	Node<T> outNode = heap_array[0];
	if (size == 1) {
		Node<T> *p = &heap_array[0];
		p = NULL;
		size--;
		return outNode;
	}

	heap_array[0] = heap_array[size - 1];
	
	Node<T> *p = &heap_array[size - 1];
	p = NULL;
	size--;
	BubbleDown(0);
	return outNode;
}

/*
When our heap's array has reached it's maximum, allocate memory for an array double the size;
Copy the values of the current heap array into the new array and delete the old array
*/
template <typename T>
void Heap<T>::Resize_Array() {
	max_size *= 2;
	Node<T> *new_array = new Node<T>[max_size];
	
	if (!new_array) {
		cout << "Insufficient memory" << endl;
	}
	
	for (int i = 0; i < size; i++) {
		new_array[i] = heap_array[i];
	}
	
	Node<T> *temp = heap_array;
	heap_array = new_array;
	delete [] temp;
}

/*
Main! Test out our heap
*/
int main() {
	Heap<char> heap(true);
	for (int i = 6; i > 0; i--) {
		Node<char> s;
		s.key = i;
		s.value = 'a';
		heap.Insert(s);
		heap.Print();
	}
	cout << heap.Extract().key << endl;

}