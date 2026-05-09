#include <iostream>
#include <stack>
#include <queue>

struct Node {
    int data;
    Node* nodes[2];

    Node(int val) {
        data = val;
        nodes[0] = 0;
        nodes[1] = 0;
    }
};

class ArbolBinario {
    Node* head;
    bool flag;

    public:
    ArbolBinario() {
        head = 0;
        flag = 0;
    }

    bool find(int val, Node** &p) {
        p = &head;

        while ((*p) && (*p)->data != val ) {
            if (val < (*p)->data) { p = &(*p)->nodes[0]; }
            else { p = &(*p)->nodes[1]; }
        }

        return((*p) && (*p)->data == val);
    }

    bool insert(int val) {
        Node** p;

        if (find(val, p)) { return 0; }

        else {
            *p = new Node(val);
            return 1;
        }
    }

    bool remove(int val) {
        Node** p;

        if (!find(val, p)) { return 0; }

        else {

            if ((*p)->nodes[0] && (*p)->nodes[1]) {
                Node** q = buscarRemplazo(p);
                (*p)->data = (*q)->data;
                p = q;

            }

            Node* t = *p;
            *p = (*p)->nodes[(*p)->nodes[0] == 0];
            delete t;
            return 1;
        }
    }

    Node** buscarRemplazo(Node** p) {
        Node** q;
        for (q = &(*p)->nodes[!flag]; (*q)->nodes[flag]; q = &(*q)->nodes[flag]);

        flag = !flag;
        return q;
    }

    void Inorder(Node* n) {
        if (!n) { return; }
        Inorder(n->nodes[0]);
        std::cout << n->data << " ";
        Inorder(n->nodes[1]); 
    }

    void Preorder(Node* n) {
        if (!n) { return; }
        std::cout << n->data << " ";
        Preorder(n->nodes[0]);
        Preorder(n->nodes[1]);
    }

    void Posorder(Node* n) {
        if (!n) { return; }
        Posorder(n->nodes[0]);
        Posorder(n->nodes[1]);
        std::cout << n->data << " ";
    }

    void Reverse(Node* n) {
        if (!n) { return; }
        Reverse(n->nodes[1]);
        std::cout << n->data << " ";
        Reverse(n->nodes[0]);
    }

    void stack_Inorder(Node* n) {
        std::stack<std::pair<int, Node*>> s;

        s.push(std::make_pair(0, n));

        while (!s.empty()) {
            switch (s.top().first) {
                case 0:
                    if (!s.top().second) {
                        s.pop();
                        break;
                    }

                    s.top().first = 1;
                    s.push(std::make_pair(0, (s.top().second)->nodes[0]));
                    break;

                case 1:
                    s.top().first = 2;
                    break;

                case 2:
                    std::cout << (s.top().second)->data << " ";
                    s.top().first = 3;
                    s.push(std::make_pair(0, (s.top().second)->nodes[1]));
                    break;

                case 3:
                    s.pop();
                    break;
            }
        }
    }

    void stack_Reverse(Node* n) {
        std::stack<std::pair<int, Node*>> s;

        s.push(std::make_pair(0, n));

        while (!s.empty()) {
            switch (s.top().first) {
                case 0:
                    if (!s.top().second) {
                        s.pop();
                        break;
                    }

                    s.top().first = 1;
                    s.push(std::make_pair(0, s.top().second->nodes[1]));
                    break;

                case 1:
                    s.top().first = 2;
                    break;

                case 2:
                    std::cout << s.top().second->data << " ";
                    s.top().first = 3;
                    s.push(std::make_pair(0, s.top().second->nodes[0]));
                    break;
                case 3:
                    s.pop();
                    break;
            }
        }
    }

    void stack_Preorder(Node* n) {
        std::stack<std::pair<int, Node*>> s;

        s.push(std::make_pair(0,n));

        while (!s.empty()) {
            switch (s.top().first) {
                case 0:
                    if (!s.top().second) {
                        s.pop();
                        break;
                    }

                    std::cout << s.top().second->data << " ";
                    s.top().first = 1;
                    s.push(std::make_pair(0, (s.top().second)->nodes[0]));

                    break;

                case 1:
                    s.top().first = 2;
                    s.push(std::make_pair(0, s.top().second->nodes[1]));
                    break;

                case 2:
                    s.pop();
                    break;
            }
        }
    }

    void stack_Levels(Node* n) {
        std::queue<Node*> q;

        q.push(n);
        while (!q.empty()) {

            if (!q.front()) {
                q.pop();
                break;
            }

            std::cout << q.front()->data << " ";
            if ((q.front())->nodes[0]) { q.push((q.front())->nodes[0]); }

            if ((q.front())->nodes[1]) { q.push((q.front())->nodes[1]); }

            q.pop();
            
        }
    }

    int max(int l, int r) {
        if (l >= r) { return l; }
        return r;
    }

    int heigh(Node* n) {
        if (!n) { return 0; }

        int l = heigh(n->nodes[0]);
        int r = heigh(n->nodes[1]);


        return max(l, r) + 1;

    }

    int stack_Heigh(Node* n) {
        std::stack<std::tuple<int, int, int, Node*>> s;

        s.push(std::make_tuple(0, 0, 0, n));

        while (!s.empty()) {
            switch (std::get<0>(s.top())) {
                case 0:
                    if (!std::get<3>(s.top())) {
                        s.pop();
                        break;
                    }

                    std::get<0>(s.top()) = 1;
                    s.push(std::make_tuple(0, 0, 0, std::get<3>(s.top())->nodes[0]));
                    break;

                case 1:
                    std::get<0>(s.top()) = 2;
                    s.push(std::make_tuple(0, 0, 0, std::get<3>(s.top())->nodes[1]));
                    break;

                case 2:
                    int l = max(std::get<1>(s.top()), std::get<2>(s.top())) + 1;
                    s.pop();
                    
                    if (!s.empty()) {
                        if (std::get<0>(s.top()) == 1) {
                            std::get<1>(s.top()) = l;
                        }

                        else if (std::get<0>(s.top()) == 2) {
                            std::get<2>(s.top()) = l;
                        }
                    }

                    else {
                        return l;
                    }
                    break;  
            }
        }

        return 0;
    }

    int queue_Heigh(Node* n) {
        std::queue<std::pair<int, Node*>> q;
        int altura = 0;

        q.push(std::make_pair(1, n));

        while (!q.empty()) {
            if (!q.front().second) {
                q.pop();
                return 0;
            }

            if (q.front().second->nodes[0]) {
                q.push(std::make_pair(q.front().first + 1, q.front().second->nodes[0]));
            }

            if (q.front().second->nodes[1]) {
                q.push(std::make_pair(q.front().first + 1, q.front().second->nodes[1]));
            }

            altura = q.front().first;

            q.pop();
            
        }

        return altura;
    }

    void Un_lado(Node* n) {
        if (!n) { return; }
        Un_lado(n->nodes[0]);
        std::cout << n->data << " ";
    }

    int N_elem(Node* n) {
        if (!n) { return 0; }
        int l = N_elem(n->nodes[0]);
        int r = N_elem(n->nodes[1]);

        return l + r + 1;
    }

    int Sum(Node* n) {
        if (!n || n == head->nodes[1]) { return 0; }

        int l = Sum(n->nodes[0]);
        int r = Sum(n->nodes[1]);

        std::cout << l << std::endl;
        std::cout << r << std::endl;
        std::cout << n->data << std::endl;

        return l + r + n->data;
    }

    void MaxMin(Node* n, int min, int max) {
        
        if (!n) { return; }

        if (n->data > min) { MaxMin(n->nodes[0], min, max); }

        if (n->data > min && n->data < max) { std::cout << n->data << " "; }

        if (n->data < max) { MaxMin(n->nodes[1], min, max); }

        return ;
    }

    void MaxMin_AlexMood(int min, int max) {
        std::stack<std::pair<Node*, int>> s;
        s.push(std::make_pair(head, 0));

        while (!s.empty()) 
        {
            switch (s.top().second) 
            {
                case 0:
                    if (!s.top().first) {
                        s.pop();
                        break;
                    }

                    if (s.top().first->data > min && s.top().first->data < max) {
                        s.top().second = 1;
                        s.push(std::make_pair(s.top().first->nodes[0], 0));
                    }

                    else {
                        s.top().second = 4;
                    }
                    break;

                case 1:
                    std::cout << s.top().first->data << " ";
                    s.top().second = 2;
                    break;

                case 2:
                    s.top().second = 3;
                    s.push(std::make_pair(s.top().first->nodes[1], 0));
                    break;

                case 3:
                    s.pop();
                    break;

                case 4:
                    s.top().second = 3;
                    if (s.top().first->data <= min) {
                        s.push(std::make_pair(s.top().first->nodes[1], 0));
                    }

                    if (s.top().first->data > max) {
                        s.push(std::make_pair(s.top().first->nodes[0], 0));
                    }
                    break;
            }
        }
        return;
    }

    void Hojitas() {
        std::stack<std::pair<int, Node*>> s;
        if (head) {
            s.push(std::make_pair(0, head));
        }

        while (!s.empty()) {
            switch (s.top().first) {
                case 0:
                    if (!s.top().second->nodes[0]) {
                        s.top().first = 1;
                    }

                    else {
                        s.top().first = 4;
                        s.push(std::make_pair(0, s.top().second->nodes[0]));
                    }
                    break;

                case 1:
                    if (!s.top().second->nodes[1]) {
                        s.top().first = 2;
                    }

                    else {
                        s.top().first = 3;
                        s.push(std::make_pair(0, s.top().second->nodes[1]));
                    }
                    break;

                case 2:
                    s.top().first = 3;
                    std::cout << s.top().second->data << " ";
                    break;

                case 3:
                    s.pop();
                    break;

                case 4:
                    s.top().first = 3;
                    if (s.top().second->nodes[1]) {
                        s.push(std::make_pair(0, s.top().second->nodes[1]));
                    }
                    
                    break;
            }
        }

        return;
    }

    void Montana() {
        std::stack<std::pair<int, Node*>> s;
        s.push(std::make_pair(0, head));

        while (!s.empty()) {
            switch (s.top().first) {
                case 0:
                    if (!s.top().second) {
                        s.pop();
                        break;
                    }
                    if (s.top().second == head) {
                        s.top().first = 2;
                    }

                    else {
                        s.top().first = 1;
                    }

                    s.push(std::make_pair(0, s.top().second->nodes[0]));
                    break;

                case 1:
                    s.top().first = 3;
                    std::cout << s.top().second->data << " ";
                    break;

                case 2:
                    if (!s.top().second) {
                        s.pop();
                        break;
                    }

                    s.top().first = 3;
                    std::cout << s.top().second->data << " ";

                    s.push(std::make_pair(2, s.top().second->nodes[1]));
                    break;

                case 3:
                    s.pop();
                    break;

            }


        }
    }

    void PrintN_level(int nivel) {
        nivel = pow(2, nivel) - 1;
        std::queue<Node*> q;
        q.push(head);
        while (!q.empty() && nivel > 0) {
            if (!q.front()) {
                q.pop();
            }

            else {
                q.push(q.front()->nodes[0]);
                q.push(q.front()->nodes[1]);
                q.pop();
            }

            nivel--;
        }

        while (!q.empty()) {
            if (q.front()) {
                std::cout << q.front()->data << " ";
            }
            q.pop();
        }
    }

    int SumN_level(int nivel) {
        nivel = pow(2, nivel) - 1;
        std::queue<Node*> q;
        q.push(head);
        int sum = 0;

        while (!q.empty() && nivel > 0) {
            if (!q.front()) {
                q.pop();
            }

            else {
                q.push(q.front()->nodes[0]);
                q.push(q.front()->nodes[1]);
                q.pop();
            }

            nivel--;
        }

        while (!q.empty()) {
            if (q.front()) {
                sum = sum + q.front()->data;
            }
            q.pop();
        }

        std::cout << sum << std::endl;
        return sum;
    }

    int N_elem_stack() {
        std::stack<std::pair<int, Node*>> s;
        s.push(std::make_pair(0, head));
        int n = 0;

        while (!s.empty()) {
            switch (s.top().first) {
                case 0:
                    if (!s.top().second) {
                        s.pop();
                        break;
                    }

                    s.top().first = 1;
                    s.push(std::make_pair(0, s.top().second->nodes[0]));
                    break;

                case 1:
                    s.top().first = 2;
                    s.push(std::make_pair(0, s.top().second->nodes[1]));
                    break;

                case 2:
                    n = n + 1;
                    s.top().first = 3;
                    break;

                case 3:
                    s.pop();
                    break;
            }
        }

        std::cout << n << std::endl;
        return n;
    }

    int Suma_elem_stack() {
        std::stack<std::pair<int, Node*>> s;
        s.push(std::make_pair(0, head));
        int n = 0;

        while (!s.empty()) {
            switch (s.top().first) {
            case 0:
                if (!s.top().second) {
                    s.pop();
                    break;
                }

                s.top().first = 1;
                s.push(std::make_pair(0, s.top().second->nodes[0]));
                break;

            case 1:
                s.top().first = 2;
                s.push(std::make_pair(0, s.top().second->nodes[1]));
                break;

            case 2:
                n = n + s.top().second->data;
                s.top().first = 3;
                break;

            case 3:
                s.pop();
                break;
            }
        }

        std::cout << n << std::endl;
        return n;
    }

    void print() {
        Suma_elem_stack();
    }

};



int main()
{
    ArbolBinario a;
    a.insert(42);
    a.insert(33);
    a.insert(12);
    a.insert(10);
    a.insert(61);
    a.insert(70);
    a.insert(55);
    a.insert(36);
    a.insert(39);
    a.insert(68);
    a.insert(13);


    a.print();
}

