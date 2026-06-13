#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
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

    void Hojitas() {
        std::stack<std::pair<int, Node*>> s;
        if (head) {
            s.push(std::make_pair(0, head));
        }

        while (!s.empty()) {
            switch (s.top().first) {
            case 0:
                if ((!s.top().second->nodes[0]) || (!s.top().second->nodes[1])) {
                    s.top().first = 2;

                    if (s.top().second->nodes[0]){
                        s.push(std::make_pair(0, s.top().second->nodes[0]));
                    }
                }

                else {
                    s.top().first = 4;
                    s.push(std::make_pair(0, s.top().second->nodes[0]));
                }
                break;

            case 2:
                s.top().first = 4;
                s.top().second->cumple = true;
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

    void Lado_Izquierdo() {
        Node* p = head;
        while (p->nodes[0]) {
            p->cumple = true;
            p = p->nodes[0];
        }
    }

    void Lado_Derecha(){
        std::stack<std::pair<int, Node*>> izqu;
        izqu.push(std::make_pair(0, head->nodes[1]));

        while (!izqu.empty()) {
            switch (izqu.top().first) {
            case 0:

                if (!izqu.top().second->nodes[1]) {
                    izqu.pop();
                    break;
                }
                izqu.top().first = 1;
                izqu.push(std::make_pair(0, izqu.top().second->nodes[1]));
                break;

            case 1:
                izqu.top().second->cumple = 1;
                izqu.pop();
                break;
            }
        }
    }

    void perimeter() {
        Lado_Izquierdo();
        Hojitas();
        Lado_Derecha();
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
        if(a) { circle.setFillColor(sf::Color(200, 130, 180)); }
        else { circle.setFillColor(sf::Color(163, 192, 207)); }

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
        dibujarArbol(window, font, head, 800, 50);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 700), "Árbol SFML");
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) return -1;
    
    std::vector<int> Elementos = { 50,30,70,20,40,60,80,15,25,35,45,55,65,75,90,12,22,38,42,48,52,62,68,78,85,95 };

    ArbolBinario a;

    for (int i = 0; i < Elementos.size(); i++) {
        a.insert(Elementos[i]);
    }

    
    a.perimeter();


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
