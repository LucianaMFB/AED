#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stack>
#include <queue>

struct Node {
    int data;
    int grade;
    Node* nodes[2];

    Node(int val) {
        data = val;
        grade = 0;
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

    void Dibujame(sf::RenderWindow& window, sf::Font& font, float x, float y, int value, int grado, float antesX = -1, float antesY = -1) {
        std::string mensaje = std::to_string(value);

        if (antesX >= 0) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(antesX, antesY), sf::Color(100, 100, 100)),
                sf::Vertex(sf::Vector2f(x, y), sf::Color(100, 100, 100))
            };
            window.draw(line, 2, sf::Lines);
        }

        sf::CircleShape circle(28.f);
        circle.setFillColor(sf::Color(255, 262 - (grado+grado)*30, 0));

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
        Dibujame(window, font, x, y, nodo->data,nodo->grade, antesX, antesY);

        dibujarArbol(window, font, nodo->nodes[0], x - espacio, y + 120, espacio / 2, x + 18, y + 20);
        dibujarArbol(window, font, nodo->nodes[1], x + espacio, y + 120, espacio / 2, x + 18, y + 20);
    }

    void print(sf::RenderWindow& window, sf::Font& font) { dibujarArbol(window, font, head, 800, 50); }

    bool GuardaCamino(int val, std::stack<Node*> &mem) {
        Node* p = head;

        while ((p) && (p->data != val)) {
            mem.push(p);
            p = p->nodes[p->data < val];
        }

        if (p) { mem.push(p); return 1; }
        else { return 0; }
    }

    void Quemame(int val) {
        std::stack<Node*> mem;
        if (!GuardaCamino(val, mem)) { std::cout << "No data"; return; }

        else {
            int contadorsuperserio = 1;
            std::queue<Node*> q;

            q.push(mem.top());
            q.front()->grade = 1;

            while (!q.empty()) {
                contadorsuperserio++;
                if ((q.front()->nodes[0]) && (q.front()->nodes[0]->grade < 1)) {
                    q.front()->nodes[0]->grade = q.front()->grade+1;
                    q.push(q.front()->nodes[0]);
                }

                if ((q.front()->nodes[1]) && (q.front()->nodes[1]->grade < 1)) {
                    q.front()->nodes[1]->grade = q.front()->grade + 1;
                    q.push(q.front()->nodes[1]);
                }

                if (!mem.empty() && (q.front() == mem.top())) {
                    mem.pop();
                    if (!mem.empty()) {
                        mem.top()->grade = q.front()->grade + 1;
                        q.push(mem.top());
                    }
                }

                //std::cout << q.front()->data << " Grade: " << q.front()->grade << std::endl;
                q.pop();
            }

        }

    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 700), "Árbol SFML");
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) return -1;

    std::vector<int> Elementos = { 40, 30, 60, 50, 80, 45, 55, 75, 90 };

    ArbolBinario a;

    for (int i = 0; i < Elementos.size(); i++) {
        a.insert(Elementos[i]);
    }

    a.Quemame(80);

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
