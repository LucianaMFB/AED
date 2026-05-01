#include <iostream>

int Precedencia(char val) {
    if (val == '+' || val == '-') { return 1; }
    else if (val == '*' || val == '/') { return 2; }
    return -1;
}

bool OperadorPreguntaSuperPreguntosa(char val) {
    return((val == '+') || (val == '-') || (val == '*') || (val == '/') || (val == '(') || (val == ')'));
}

int Opera(char car, int a, int b) {
    if (car == '+') {
        return (a + b);
    }

    else if (car == '-') {
        return (a - b);
    }

    else if (car == '*') {
        return a * b;
    }

    else if (car == '/') {
        return a /b ;
    }
}

template <class T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T val) {
        data = val;
        next = 0;
        prev = 0;
    }
};

template <class T>
struct LinkedList {
    Node<T>* tail;
    Node<T>* head;
    int num_elem;

    LinkedList() {
        tail = 0;
        head = 0;
        num_elem = 0;
    }

    ~LinkedList() {
        Node<T>* temp = head;
        while (head) {
            head = temp->next;
            delete temp;
            temp = head;
        }

        tail = 0;
        head = 0;
    }

    void push_front(T val) {
        Node<T>* t = new Node(val);

        if (!head) {
            head = t;
            tail = t;
        }

        else {
            t->next = head;
            head->prev = t;
            head = t;
        }

        num_elem++;
    }

    void push_back(T val) {
        Node<T>* t = new Node(val);
        if (!head) {
            head = t;
            tail = t;
        }

        else {
            t->prev = tail;
            tail->next = t;
            tail = t;
        }
        num_elem++;
        return;
    }

    void pop_front(T &val) {
        val = head->data;
        if (head == tail) {
            delete head;
            head = 0;
            tail = 0;
        }
        else {

            head = head->next;
            delete head->prev;
            head->prev = 0;
        }

        num_elem--;
        return;
    }

    void pop_back(T &val) {
        val = tail->data;
        if (head == tail) {
            delete tail;
            head = 0;
            tail = 0;
        }
        else {

            tail = tail->prev;
            delete tail->next;
            tail->next = 0;
        }
        num_elem--;
        return;
    }

    void print() {
        Node<T>* temp = tail;
        if (!temp) { return; }
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }

        std::cout << std::endl;
    }

    
};

int main()
{
    char Operacion[12] = "3+4*2/(1-5)";
    LinkedList<char> Stack;
    LinkedList<char> Result;
    LinkedList<int> Solve;
    char basurachar;
    int basuraint;

    char* p = Operacion;
    while (*p != '\0') {
        if (!OperadorPreguntaSuperPreguntosa(*p)) { Result.push_front(*p);}
        else if (*p == '(') { Stack.push_front(*p); }

        else if (*p == ')') {
            while (Stack.head->data != '(') {
                Result.push_front(Stack.head->data);
                Stack.pop_front(basurachar);
            }
            Stack.pop_front(basurachar);
        }

        else {
            if ((Stack.head)&&(Precedencia(*p) <= Precedencia((Stack.head->data)))) {
                Result.push_front(Stack.head->data);
                Stack.pop_front(basurachar);
                Stack.push_front(*p);
            }
            else { Stack.push_front(*p); }
        }

        std::cout << "Result: ";
        Result.print();
        std::cout << "Stack: ";
        Stack.print();
        std::cout << std::endl;
        p++;
    }

    while (Stack.head) {
        Result.push_front(Stack.head->data);
        Stack.pop_front(basurachar);
    }

    std::cout << "Super Resultado: ";
    Result.print();
    std::cout << std::endl;
    
    if (Result.num_elem > 2) {
        while (Result.tail) {

            if (OperadorPreguntaSuperPreguntosa(Result.tail->data)) {
                int b = Solve.tail->data;
                int a = Solve.tail->prev->data;
                Solve.pop_back(basuraint);
                Solve.pop_back(basuraint);

                Solve.push_back(Opera(Result.tail->data,a,b));
            } 
            else {
                Solve.push_back(Result.tail->data - 48);
            }
            Result.pop_back(basurachar);
        }
    }

    std::cout << "Super Resultado Super Resuelto: ";
    Solve.print();

}

