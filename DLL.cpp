#include <iostream>
#include <assert.h>

struct Node {
	int data;
	Node* prev;
	Node* next;

	Node(int val) {
		data = val;
		prev = nullptr;
		next = nullptr;
	}
};

struct DLinkedList {
	Node* head;
	Node* tail;
	int n_Elem;

	DLinkedList();
	~DLinkedList();
	int& operator[](int indice);
	void push_front(int val);
	void pop_front();
	void push_back(int val);
	void pop_back();
	void print();
	//Insertar y sacar elemento en cualquier posición
	//Ordenar
};

DLinkedList::DLinkedList() {
	head = nullptr;
	tail = nullptr;
	n_Elem = 0;
}

DLinkedList::~DLinkedList() {
	Node* temp = head;
	while (temp != nullptr) {
		temp = head->next;
		delete head;
		head = temp;
	}
}

int& DLinkedList::operator[](int indice) {
	//assert(i < n_Elem);
	Node* temp = head;
	for (int i = 0; i < indice; i++, temp = temp ->next) {}
	return temp->data;
}

void DLinkedList::push_front(int val) {
	Node* elem = new Node(val);
	if (head == nullptr) {
		head = elem;
		tail = elem;
	}

	else {
		head->prev = elem;
		elem->next = head;
		head = elem;
	}
	n_Elem++;
	
}

void DLinkedList::pop_front() {
	if (head == tail) {
		delete head;
		head, tail = nullptr;
	}

	else {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
	n_Elem--;
}

void DLinkedList::push_back(int val) {
	Node* elem = new Node(val);
	if (n_Elem == 0) {
		head = elem;
		tail = elem;
	}

	else {
		tail->next = elem;
		elem->prev = tail;
		tail = elem;
	}

	n_Elem++;
	return;
}

void DLinkedList::pop_back() {
	//asssert(n_Elem >0);
	
	if (head == tail) {
		delete head;
		head, tail = nullptr;
	}

	else {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}

	n_Elem--;
	return;
}

void DLinkedList::print() {
	std::cout << n_Elem << std::endl;
	for (Node* temp = head; temp != nullptr; temp = temp->next) {
		std::cout << temp->data << " -> ";
	}
	std::cout << std::endl;
}

int main()
{
	DLinkedList o;
	o.push_back(9);
	o.push_front(6);
	o.push_back(3);
	o.push_back(2);
	o[0] = 13;
	o.print();
}

