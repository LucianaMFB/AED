#include <iostream>

template<class T>
struct ASC {
    bool operator () (T a, T b) { return a < b; }
};

template<class T>
struct DES {
    bool operator () (T a, T b) { return a > b; }
};

template<class T>
struct Node {
    T data;
    Node* next;

    Node(T val) {
        data = val;
        next = 0;
    }
};

template<class T, class O>
struct ListaOrdenada {
    Node<T>* head;
    O Orden;

    ListaOrdenada() {
        head = 0;
    }

    ~ListaOrdenada() {
        Node<T>* temp = head;
        while (temp) {
            temp = temp->next;
            delete head;
            head = temp;
        }
    }

    bool find(T val, Node<T>** &p) {
        p = &head;
        while ((*p) && Orden((*p)->data, val)) {
            p = &(*p)->next;
        }
        return ((*p) && (*p)->data == val);
    }

    bool insert(T val) {
        Node<T>** p;
        if (find(val, p)) { return 0; }

        else {
            Node<T>* t = new Node<T>(val);
            t->next = *p;
            *p = t;
            return 1;
        }
    }

    bool remove(int val) {
        Node<T>** p;
        if (find(val, p)) {
            Node<T>* temp = *p;
            *p = temp->next;
            delete temp;

            return 1;
        }

        else { return 0; }
    }

    void print() {
        Node<T>* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }

        std::cout << std::endl;
    }
};


int main()
{
    ListaOrdenada<char, DES<char>> lista;
    lista.insert('L');
    lista.print();
    lista.insert('U');
    lista.print();
    lista.insert('I');
    lista.print();
    lista.insert('A');
    lista.print();
    lista.insert('C');
    lista.print();

}
