#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = 0;
    }
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() {
        head = 0;
    }

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void printForward() {
        Node* current = head;
        std::cout << "Lista: ";
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* find(Node* p, Node*& antes_p, int val) {
        antes_p = nullptr;

        while (p && p->data != val) {
            antes_p = p;
            p = p->next;
        }

        return p;
    }

    void swapNodes(int x, int y) {
        // Implementar
        // 1. Buscar los nodos con valores x e y
        // 2. Si alguno no existe, no hacer nada
        // 3. Si son el mismo nodo, no hacer nada
        // 4. Intercambiar las posiciones modificando solo punteros
        // 5. Actualizar head si es necesario
        // 6. Tener cuidado con el caso de nodos adyacentes
        
        Node* antes_nx;
        Node* nx = find(head, antes_nx, x);

        Node* antes_ny;
        Node* ny = find(head, antes_ny, y);
        
        if (!nx || !ny) { std::cout << "No hay" << std::endl; return; }

        else if (nx == ny) { std::cout << "Son el mismo" << std::endl;return; }

        else {

            if (nx->next == ny) {
                if (antes_nx) {
                    antes_nx->next = ny;
                }

                else { head = ny; }

                nx->next = ny->next;
                ny->next = nx;

            }

            else if (ny->next == nx) {
                if (antes_ny) {
                    antes_ny->next = nx;
                }

                else { head = nx; }

                ny->next = nx->next;
                nx->next = ny;
            }

            else {
                if (antes_nx) {
                    antes_nx->next = ny;
                }

                else { head = ny; }

                if (antes_ny) {
                    antes_ny->next = nx;
                }

                else { head = nx; }

                Node* t = nx->next;
                nx->next = ny->next;
                ny->next = t;
            }
        }
    }

    void deleteNode(int val) {
        Node* antes_e;
        Node* elim = find(head, antes_e, val);

        if (!elim) { std::cout << "No hay" << std::endl; return; }

        if (antes_e) { antes_e->next = elim->next; }
        else { head = elim->next; }

        delete elim;
    }

    void Reverse(Node* n, Node* antes_n) {
        Node* previo = nullptr;
        Node* p = n;
        Node* siguiente = nullptr;

        while (p) {
            siguiente = p->next;
            p->next = previo;
            previo = p;
            p = siguiente;
        }

        antes_n->next = previo;
    }

    int Tamano() {
        Node* n = head;
        int tam = 0;
        while (n) {
            n = n->next;
            tam++;
        }

        return tam;
    }

    bool Palindromo() {

        Node* p = head;
        Node* q = head;
        Node* antes_q = head;
        int tam = Tamano();
        int tammedio = tam/2;

        while (tammedio > 0) {
            antes_q = q;
            q = q->next;
            tammedio--;
        }


        if (tam % 2 != 0) { 
            antes_q = q;
            q = q->next; }

        Reverse(q, antes_q);

        q = antes_q->next;

        while (q && (p->data == q->data)) {
            p = p->next;
            q = q->next;
            
        }

        std::cout << !q << std::endl;

        return(!q);
    }
};

int main() {

    SinglyLinkedList lista;

    // Crear lista: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70
    lista.push_back(10);
    lista.push_back(30);
    lista.push_back(20);
    lista.push_back(20);
    lista.push_back(30);
    lista.push_back(10);

    std::cout << "LISTA ORIGINAL" << std::endl;
    lista.printForward();
    std::cout << std::endl;
    lista.Palindromo();
    lista.printForward();
    std::cout << std::endl;

    
    
    return 0;
}
