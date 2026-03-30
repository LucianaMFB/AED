#include <iostream>

struct Vector {
    int* Arr;
    int* p;
    int num_Elem;

    Vector(int n) {
        num_Elem = n;
        Arr = new int[n];
        p = nullptr;

    }

    ~Vector() {
        delete[] Arr;
        p = nullptr;
    }

    bool vacio() {
        return !p;
    }

    bool lleno() {
        return p == Arr + num_Elem - 1;
    }

    int& operator [](int indice) {
        if (!(vacio()) && (indice >= 0) && (indice < num_Elem)) {
            return *(Arr + indice);
        }
    }

    bool push_front(int val) {
        if (vacio()) {
            p = Arr;
        }

        else {

            if (lleno()) {
                expandir();
            }
            int* q = p;
            while (q != Arr - 1) {
                *(q + 1) = *q;
                q--;
            }
            p++;
        }

        *Arr = val;
        return true;
        
    }

    bool pop_front(int& val) {
        if (vacio()) {
            return false;
        }
        else {
            val = *Arr;
            int* q = Arr;
            while (q < p) {
                *q = *(q + 1);
                q++;
            }

            p--;
            return true;
        }
    }

    bool push_back(int val) {
        if (vacio()) {
            p = Arr;
        }

        else {
            if (lleno()) {
                expandir();
            }
            p++;
        }
        *p = val;
        return true;
        
    }

    bool pop_back(int& val) {
        if (vacio()) {
            return false;
        }

        else {
            val = *p;
            p--;
            return true;
        }
    }

    void print() {
        if (vacio()) { return; }
        for (int* i = Arr; i <= p; i++) {
            std::cout << *i << " ";
        }
        std::cout << std::endl;
    }

    bool expandir() {
        if (lleno()) {
            num_Elem = num_Elem * 2;
            int* nuevo = new int[num_Elem];

            int* q = nuevo;
            for (int* i = Arr; i < p + 1; ++i, ++q) {
                *q = *i;
            }

            delete[] Arr;
            Arr = nuevo;
            p = Arr + (num_Elem / 2) - 1;
            return true;
        }

        else {
            return false;
        }
    }
};

int main()
{
    int a;
    Vector v(5);
    v.push_back(1);
    v.push_front(0);
    v.push_back(2);
    v.push_front(15);
    v.push_front(3);
    std::cout << v.push_back(4) << std::endl;
    std::cout << v.lleno() << std::endl;
    std::cout << v[5] << std::endl;
    v.print();
}
