#include <iostream>
#include <string>
#include <windows.h>

struct Libro {
    int calificacion;
    float precio;
    std::string nombre;
    std::string autor;
    Libro* next;

    Libro(int cal, float prec, std::string nom, std::string at) {
        next = 0;
        calificacion = cal;
        precio = prec;
        nombre = nom;
        autor = at;
    }
};

template<class T>
struct ASC {
    bool operator () (T a, T b) { return (a < b); }
};

template<class T>
struct DES {
    bool operator () (T a, T b) { return (a > b); }
};

template<class O1, class O2>
struct OrdenCalificacion {
    O1 orden1;
    O2 orden2;

    bool operator()(Libro* a, Libro* b) {
        if (a->calificacion != b->calificacion)
            return orden1(a->calificacion, b->calificacion);

        return orden2(a->nombre, b->nombre);
    }
};

template<class O1, class O2>
struct OrdenPrecio {
    O1 orden1;
    O2 orden2;

    bool operator()(Libro* a, Libro* b) {
        if (a->precio != b->precio)
            return orden1(a->precio, b->precio);

        return orden2(a->nombre, b->nombre);
    }
};

template<class O1, class O2>
struct OrdenAutor {
    O1 orden1;
    O2 ordenderespaldopararespaldaroki;

    bool operator()(Libro* a, Libro* b) {
        if (a->autor != b->autor)
            return orden1(a->autor, b->autor);

        return ordenderespaldopararespaldaroki(a->nombre, b->nombre);
    }
};

template<class O1>
struct OrdenNombre {
    O1 orden1;

    bool operator()(Libro* a, Libro* b) {
        return orden1(a->nombre, b->nombre);
    }
};


template<class C>
struct Biblioteca {
    Libro* head;
    C compara;

    Biblioteca(): head(0), compara(){}

    ~Biblioteca() {
        Libro* temp = head;
        while (temp) {
            Libro* next = temp->next;
            delete temp;
            temp = next;
        }
    }


    bool find(Libro* val, Libro** &p) {
        p = &head;
        while ((*p) && (compara(*p, val))) {
            p = &(*p)->next;
        }

        return((*p) && !(compara(*p, val) || (compara(val, *p))));
    }

    bool insert(Libro* val) {
        Libro** p;

        if (find(val, p)) { return 0; }
        else {
            val->next = *p;
            *p = val;

            return 1;
        }
    }

    void remove(Libro* val) {
        Libro** p;

        if (find(val, p)) {
            Libro* t = *p;
            *p = t->next;
            delete t;
        }
    }


    void print() {
        Libro *l = head;
        while (l) {
            int i = l->calificacion;
            std::cout << "Calificacion: ";
            while (i != 0) {
                std::cout << "★ ";
                i--;
            }
            std::cout<<std::endl;
            std::cout << "Precio: S/" << l->precio << std::endl;
            std::cout << "Nombre: " << l->nombre << std::endl;
            std::cout << "Autor: " << l->autor << std::endl;
            std::cout << "-------------------------------------" << std::endl;

            l = l->next;
        }
    }
};

int main()
{
    SetConsoleOutputCP(65001);
    Biblioteca<OrdenNombre<DES<std::string>>> b;
    std::cout << "******************* BIBLIOTECA POR NOMBRE *******************" << std::endl;
    std::cout << std::endl;
    b.insert(new Libro(5, 56.5, "LA ILIADA", "HOMERO"));
    b.insert(new Libro(1, 62, "LA ODISEA", "HOMERO"));
    b.insert(new Libro(3, 54.5, "ORGULLO Y PREJUICIO", "JANE AUSTEN"));
    b.insert(new Libro(5, 20.99, "CUMBRES BORRASCOSAS", "EMILY BRONTE"));
    b.insert(new Libro(1, 20.99, "DE PROFUNDIS", "OSCAR WILDE"));
    b.insert(new Libro(5, 20.99, "EL FANTASMA DE CANTERVILLE", "OSCAR WILDE"));
    b.insert(new Libro(3, 76.3, "EL PERRO DE LOS BASKERVILLE", "ARTHUR CONAN DOYLE"));
    b.insert(new Libro(2, 28.9, "MUERTE EN LA VICARIA", "AGATHA CHRISTIE"));
    b.insert(new Libro(4, 33, "LA MUERTE VISITA AL DENTISTA", "AGATHA CHRISTIE"));
    b.insert(new Libro(5, 39.9, "LAS MIL Y UNA NOCHES", "ANONIMO"));
    b.remove(new Libro(0, 0, "ORGULLO Y PREJUICIO", "-"));
    b.print();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "******************* BIBLIOTECA POR CALIFICACION *******************" << std::endl;
    std::cout << std::endl;


    Biblioteca<OrdenCalificacion<DES<int>, DES<std::string>>> a;
    a.insert(new Libro(5, 56.5, "LA ILIADA", "HOMERO"));
    a.insert(new Libro(1, 62, "LA ODISEA", "HOMERO"));
    a.insert(new Libro(3, 54.5, "ORGULLO Y PREJUICIO", "JANE AUSTEN"));
    a.insert(new Libro(5, 20.99, "CUMBRES BORRASCOSAS", "EMILY BRONTE"));
    a.insert(new Libro(1, 20.99, "DE PROFUNDIS", "OSCAR WILDE"));
    a.insert(new Libro(5, 20.99, "EL FANTASMA DE CANTERVILLE", "OSCAR WILDE"));
    a.insert(new Libro(3, 76.3, "EL PERRO DE LOS BASKERVILLE", "ARTHUR CONAN DOYLE"));
    a.insert(new Libro(2, 28.9, "MUERTE EN LA VICARIA", "AGATHA CHRISTIE"));
    a.insert(new Libro(4, 33, "LA MUERTE VISITA AL DENTISTA", "AGATHA CHRISTIE"));
    a.insert(new Libro(5, 39.9, "LAS MIL Y UNA NOCHES", "ANONIMO"));
    a.print();

    return 0;
}

