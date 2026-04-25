#include <iostream>

struct Node {
    char data;
    Node* next;
    Node* prev;

    Node(char val) {
        data = val;
        next = 0;
        prev = 0;
    }
};

struct LinkedList {
    Node* tail;
    Node* head;

    LinkedList() {
        tail = 0;
        head = 0;
    }

    ~LinkedList() {
        Node* temp = head;
        while (head) {
            head = temp->next;
            delete temp;
            temp = head;
        }

        tail = 0;
        head = 0;
    }

    void push_front(char val) {
        Node* t = new Node(val);

        if (!head) {
            head = t;
            tail = t;
        }

        else {
            t->next = head;
            head->prev = t;
            head = t;
        }
    }

    void push_back(char val) {
        Node* t = new Node(val);
        if (!head) {
            head = t;
            tail = t;
        }

        else {
            t->prev = tail;
            tail->next = t;
            tail = t;
        }
        return;
    }

    void pop_front(char &val) {
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
        return;
    }

    void pop_back(char &val) {
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
        return;
    }

    void print() {
        Node* temp = tail;
        if (!temp) { return; }
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }

        std::cout << std::endl;
    }
};

int Precedencia(char val) {
    if (val == '+' || val == '-') { return 1; }
    else if (val == '*' || val == '/') { return 2;}
    return -1;
}

bool OperadorPreguntaSuperPreguntosaPorqueSiYYaMeQuieroDormirPorfaFunciona(char val) {
    return((val == '+') || (val == '-') || (val == '*') || (val == '/') || (val == '(') || (val == ')'));
}

int main()
{
    char Operacion[30] = "(A+(B*C-(D/E*F)*G)*H)";
    LinkedList Stack;
    LinkedList Result;
    char a;

    char* p = Operacion;
    while (*p != '\0') {
        if (!OperadorPreguntaSuperPreguntosaPorqueSiYYaMeQuieroDormirPorfaFunciona(*p)) { Result.push_front(*p);}
        else if (*p == '(') { Stack.push_front(*p); }

        else if (*p == ')') {
            while (Stack.head->data != '(') {
                Result.push_front(Stack.head->data);
                Stack.pop_front(a);
            }
            Stack.pop_front(a);
        }

        else {
            if ((Stack.head)&&(Precedencia(*p) <= Precedencia((Stack.head->data)))) {
                Result.push_front(Stack.head->data);
                Stack.pop_front(a);
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
        Stack.pop_front(a);
    }

    Result.print();


}

