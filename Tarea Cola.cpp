#include <iostream>

template<class T, int N = 10>
struct Cola {
    T* Arr;
    T* head;
    T* tail;
    int nro_Elementos;

    Cola(int n);
    ~Cola();
    bool vacio();
    bool lleno();
    bool push(T elem);
    bool pop(T& elem);
    void print();
};

template<class T, int N>
Cola<T, N>::Cola(int n) {
    nro_Elementos = n;
    Arr = new T[nro_Elementos];
    head = nullptr;
    tail = nullptr;
}

template<class T, int N>
Cola<T, N>::~Cola() {
    delete[] Arr;
}

template<class T, int N>
bool Cola<T, N>::vacio() {
    return !head;
}

template<class T, int N>
bool Cola<T, N>::lleno() {

    if (head > Arr) {
        return tail == head - 1;
    }

    else {
        return tail == Arr + nro_Elementos - 1;
    }
}

template<class T, int N>
bool Cola<T, N>::push(T elem) {
    if (lleno()) {
        return false;
    }

    else {

        if (vacio()) {
            head = Arr;
            tail = Arr;
        }

        else {
            if (head > Arr && tail == Arr + nro_Elementos - 1) {
                tail = Arr;
            }
            
            else { tail++; }
        }


        *tail = elem;
        return true;
    }
}

template<class T, int N>
bool Cola<T, N>::pop(T& elem) {
    if (vacio()) {
        return false;
    }

    else {
        elem = *head;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        }

        else if (head == Arr + nro_Elementos - 1) {
            head = Arr;
        }

        else {
            head++;
        }

    }

    return true;

}

template<class T, int N>
void Cola<T, N>::print() {
    if (vacio()) {
        std::cout << "Cola vacia :)";
    }

    else {
        if (head <= tail) {
            for (T *i = head; i < tail + 1; i++) {
                std::cout << *i << " ";
            }
        }

        else {
            for (T *i = head; i < Arr + nro_Elementos; i++) {
                std::cout << *i << " ";
            }

            for (T* q = Arr; q < tail + 1; q++) {
                std::cout << *q << " ";
            }
        }
    }

    std::cout << std::endl;
}


int main()
{
    int a;
    Cola<int> ola(5);
    ola.push(1);
    ola.push(2);
    ola.push(3);
    ola.push(4);
    ola.push(5);
    ola.print();
    ola.pop(a);
    ola.print();
    ola.push(6);
    ola.print();
    ola.pop(a);
    ola.print();
    ola.pop(a);
    ola.print();
    ola.push(7);
    ola.print();
    

}
