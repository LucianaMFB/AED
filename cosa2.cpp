#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

struct LinkedList {
    Node* head;

    LinkedList();
    ~LinkedList();
    bool vacio();
    Node& operator[](int indice);
    bool push_front(int val);
    bool pop_front(Node& elem);
    bool push_back(int val);
    bool pop_back(Node& elem);
    void print();
};

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

bool LinkedList::vacio() {
    return(!head);
}

Node& LinkedList::operator[](int indice) {
    Node* p = head;

    for (int i = 0; i < indice; i++) {
        p = p->next;
    }
    return *p;
}

bool LinkedList::push_front(int val) {
    Node* elem = new Node(val);
    if (vacio()) {
        elem->next = nullptr;
    }

    else {
        elem->next = head;
    }

    head = elem;
    return true;
}

bool LinkedList::pop_front(Node& elem) {
    return true;
}

bool LinkedList::push_back(int val) {
    Node* elem = new Node(val);
    if (vacio()) {
        head = elem;
    }

    else {
        Node* i = head;
        for (; i->next != nullptr; i = i->next) {}
        i->next = elem;
    }

    return true;
}

bool LinkedList::pop_back(Node& elem) {
    return true;
}

void LinkedList::print() {
    for (Node* temp = head; temp != nullptr; temp = temp->next) {
        std::cout << temp->data << " ";
    }
    std::cout << std::endl;
}

int main()
{
    LinkedList l;
    l.push_back(2);
    l.push_front(3);
    l.print();
}


