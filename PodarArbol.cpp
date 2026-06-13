#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <queue>

struct Node {
    int data;
    bool cumple;
    Node* nodes[2];

    Node(int val) {
        data = val;
        cumple = false;
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

    bool find(int val, Node**& p) {
        p = &head;

        while ((*p) && (*p)->data != val) {
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

        std::cout << n->data << " ";
        Inorder(n->nodes[0]);
        Inorder(n->nodes[1]);
    }

    int DevuelveMayor(int a, int b) {
        if (a >= b) { return a; }
        return b;
    }

    int Altura(Node* n) {
        if (!n) { return 0; }
        int l = Altura(n->nodes[0]);
        int r = Altura(n->nodes[1]);

        return DevuelveMayor(l, r) + 1;
    }

    void Dibujame(sf::RenderWindow& window, sf::Font& font, bool a, float x, float y, int value, float antesX = -1, float antesY = -1) {
        std::string mensaje = std::to_string(value);

        if (antesX >= 0) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(antesX, antesY), sf::Color::White),
                sf::Vertex(sf::Vector2f(x, y), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        sf::CircleShape circle(28.f);
        if (a) { circle.setFillColor(sf::Color(200, 130, 180)); }
        else { circle.setFillColor(sf::Color(210, 240, 127)); }

        circle.setOrigin(30.f, 30.f);
        circle.setPosition(x + 18, y + 20);
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(mensaje);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(x, y);

        window.draw(text);
    }

    void dibujarArbol(sf::RenderWindow& window, sf::Font& font, Node* nodo, float x, float y, float espacio = 400.f, float antesX = -1, float antesY = -1) {
        if (!nodo) return;
        Dibujame(window, font, nodo->cumple, x, y, nodo->data, antesX, antesY);

        dibujarArbol(window, font, nodo->nodes[0], x - espacio, y + 120, espacio / 2, x + 18, y + 20);
        dibujarArbol(window, font, nodo->nodes[1], x + espacio, y + 120, espacio / 2, x + 18, y + 20);
    }

    void print(sf::RenderWindow& window, sf::Font& font) {
        podar();
        dibujarArbol(window, font, head, 800, 50);
    }

    void GuardaTodo(std::stack<Node*> &s) {
        std::queue<Node*> q;
        q.push(head);

        while (!q.empty()) {
            if (q.front()->nodes[0]) { q.push(q.front()->nodes[0]); }
            if (q.front()->nodes[1]) { q.push(q.front()->nodes[1]); }

            s.push(q.front());
            q.pop();
        }
    }

    void podar() {
        std::stack<Node*> s;
        GuardaTodo(s);

        while (!s.empty()) {
            int izq = Altura(s.top()->nodes[0]);
            int der = Altura(s.top()->nodes[1]);

            if (izq - der != 0) { 
                std::queue<Node*> q2;
                std::stack<Node*> paraBorrar;

                int i = 0;
                int c = 0;
                if (izq < der) { c = izq; }
                else { c = der; }
                q2.push(s.top()->nodes[izq < der]);

                while (!q2.empty()) {
                    if (i >= pow(2, c)-1) { paraBorrar.push(q2.front()); }
                    
                    if (q2.front()->nodes[0]) { q2.push(q2.front()->nodes[0]); }
                    if (q2.front()->nodes[1]) { q2.push(q2.front()->nodes[1]); }
                    
                    q2.pop();
                    i++;
                }

                while (!paraBorrar.empty()) {
                    remove(paraBorrar.top()->data);
                    paraBorrar.pop();
                }
            }
             s.pop();        
        }
    }


};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 700), "Árbol SFML");
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) return -1;
    
    std::vector<int> Elementos = {12, 8, 18, 5, 11, 17, 4};

    ArbolBinario a;
    
    for (int i = 0; i < Elementos.size(); i++) {
        a.insert(Elementos[i]);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        a.print(window, font);
        window.display();
    }

}

