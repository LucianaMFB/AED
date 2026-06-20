#include <iostream>
#include<vector>

template<class T>
class SparseMatrix;
template<class T>
struct obj;

template <class T>
struct Node {
    T data;
    int x;
    int y;
    Node<T>* right;
    Node<T>* botom;

    Node(T val, int x_, int y_) {
        data = val;
        x = x_;
        y = y_;
        
        right = 0;
        botom = 0;
    }
};

template <class T>
class SparseMatrix {
public:
    int tam_Columnas;
    int tam_Filas;

    Node<T>** fila;
    Node<T>** columna;

    SparseMatrix(int fil, int col) {
        tam_Filas = fil;
        tam_Columnas = col;
        fila = new Node<T> * [tam_Filas];
        columna = new Node<T> * [tam_Columnas];
        

        for (int i = 0; i < tam_Filas; i++) {
            fila[i] = nullptr;
        }

        for (int i = 0; i < tam_Columnas; i++) {
            columna[i] = nullptr;
        }
    }

    bool find_Botom(int fil, int col, Node<T>** &p) {
        p = &columna[col];
        for (;(*p) && (*p)->x < fil; p = &((*p)->botom));

        return ((*p) && ((*p)->x == fil) && ((*p)->y == col));
    }

    bool find_Rigth(int fil, int col, Node<T>**& p) {
        p = &fila[fil];
        for (;(*p) && (*p)-> y < col; p = &((*p)->right));

        return ((*p) && ((*p)->x == fil) && ((*p)->y == col));
    }


    void set(T val, int fil, int col) {
        if (fil >= tam_Filas || col >= tam_Columnas) { return; }

        Node<T>** p;
        Node<T>** q;
        
        bool fb = find_Botom(fil, col, p);
        bool fr = find_Rigth(fil, col, q);

        if (fb && fr) {
            if (val != 0) {
                (*p)->data = val;
            }

            else {
                Node<T>* t = *p;
                *p = t->botom;
                *q = t->right;
                delete t;
            }
        }

        else {
            Node<T>* t = new Node<T>(val, fil, col);
            t->botom = *p;
            *p = t;
            t->right = *q;
            *q = t;
        }
    }

    T get(int fil, int col) {
        if (fil >= tam_Filas || col >= tam_Columnas) { return 0; }

        Node<T>** p;
        Node<T>** q;

        bool fb = find_Botom(fil, col, p);
        bool fr = find_Rigth(fil, col, q);

        if (!(fb && fr)) { return 0; }

        else {
            return (*p)->data;
        }
    }

    void print() {
        for (int i = 0; i < tam_Filas; i++) {
            for (int j = 0; j < tam_Columnas; j++) {
                std::cout <<  get(i, j) << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    obj<T> operator()(int fil, int col);
    
};

template <class T>
struct obj {
    SparseMatrix<T>* s;
    int x;
    int y;

    obj(SparseMatrix<T>* s_=nullptr): s(s_) {}

    obj<T> operator=(T v) {
        s->set(v, x, y);
        return *this;
    }

    obj<T> operator=(obj<T>& otro) {
        s->set(otro.s->get(otro.x, otro.y), x, y);
        return *this;
    }

    operator T() {
        return s->get(x, y);
    }
};

template <class T>
obj<T> SparseMatrix<T>::operator()(int fil, int col) {
    obj<T> ox(this);
    ox.x = fil;
    ox.y = col;
    return ox;
}

void Resolver(SparseMatrix<double> &Mresolver) {
    for (int a = 0; a < Mresolver.tam_Filas-1; a++) {
        for (int i = a+1; i < Mresolver.tam_Filas; i++) {
            if (Mresolver(a, a) == 0) { std::cout << "Nao nao" << std::endl; return; }

            double inter = (double)Mresolver(i, a) / Mresolver(a, a);
            for (int j = a; j < Mresolver.tam_Columnas; j++) {
                int l = Mresolver(i, j);
                int u = Mresolver(a, j);

                Mresolver.set(l - inter * u, i, j);
            }
        }
    }
}


void ResolverSistema(SparseMatrix<double>& Gauss) {
    int n = Gauss.tam_Filas;

    std::vector<double> solucion(n);

    for(int i = n - 1; i >= 0; i--) {
        double suma = 0;
        for (int j = i + 1; j < n; j++) {
            suma += Gauss(i, j) * solucion[j];
        } 
        if (Gauss(i, i) == 0) { std::cout << "Nao nao" <<std::endl; return; }
        solucion[i] =(Gauss(i, Gauss.tam_Columnas - 1) - suma) / Gauss(i, i);
    }

    for (int l = 0; l < n; l++) {
        std::cout << solucion[l] << " ";
    }
    std::cout << std::endl;

    return;
}

int main()
{
    SparseMatrix<double> m(3, 4);
    m(0, 0) = 2;
    m(0, 1) = -3;
    m(0, 2) = -5;
    m(0, 3) = 1;

    m(1, 0) = 3;
    m(1, 1) = -1;
    m(1, 2) = -2;
    m(1, 3) = 3;

    m(2, 0) = 1;
    m(2, 1) = 2;
    m(2, 2) = 4;
    m(2, 3) = 1;

    m.print();

    Resolver(m);

    m.print();
    ResolverSistema(m);

    return 0;
}

