#include <iostream>
#include <cstdlib>
#include <ctime>

struct Node {
	int vidas;
	char letra;
	char* palabra;
	Node* next;
	Node* prev;

	Node(char *_palabra,char* palabra_previa, int tam, char _letra, bool &fuaaaa) {
		palabra = new char[tam+1];
		char* temp = palabra;
		char* p_previo = palabra_previa;
		fuaaaa = true;

		for (char* p = _palabra; *p; p++, temp++, p_previo++) {
			if (*p == *p_previo) {
				*temp = *p;
			}

			else if (*p_previo != '_' && *p == '_') {
				*temp = *p_previo;
			}

			else {
				*temp = *p;
			}

			if (*temp == '_') {
				fuaaaa = false;
			}
		}
		*temp = '\0';

		vidas = 15;
		letra = _letra;
		next = nullptr;
		prev = nullptr;
	}

	~Node() {
		delete[] palabra;
	}

	void print() {
		for (char* temp = palabra; *temp;temp++) {
			std::cout << *temp << " ";
		}
		std::cout << std::endl;
		std::cout << "Letra: " << letra << std::endl;
		std::cout << "Vidas: " << vidas << std::endl;
	}
};

struct Memoria {
	Node* tail;
	int num_elem;

	Memoria() {
		tail = nullptr;
		num_elem = 0;
	}

	~Memoria() {
		while (num_elem != 0) {
			pop();
		}
	};

	bool push(char* _palabra, int tam, char _letra, bool _flag) {
		bool fuaaa;
		if (num_elem == 0) {
			Node* temp = new Node(_palabra, _palabra, tam, _letra, fuaaa);
			tail = temp;
			if (!_flag) {
				tail->vidas = 14;
			}
		}

		else {
			Node* temp = new Node(_palabra, tail->palabra, tam, _letra, fuaaa);
			tail->next = temp;
			temp->prev = tail;
			tail = temp;

			if (!_flag) {
				tail->vidas = tail->prev->vidas - 1;
			}

			else {
				tail->vidas = tail->prev->vidas;
			}
		}

		if (tail->vidas == 0) {
			return false;
		}

		else if (fuaaa == true) {
			std::cout << std::endl;
			std::cout << "GANSTE .)" << std::endl;
			std::cout << std::endl;
			return false;
		}
		num_elem++;
		return true;
		
	}


	void pop() {
		if (num_elem == 0) {
			return;
		}

		if (num_elem == 1) {
			delete tail;
			tail = nullptr;
		}

		else {
			Node* temp = tail->prev;
			tail->prev = nullptr;
			temp->next = nullptr;
			delete tail;
			tail = temp;
		}

		num_elem--;
	}

	void imprimir() {
		if (tail == nullptr) {
			return;
		}

		else {
			tail->print();
			std::cout << std::endl;
		}
	}

};

bool Verificar(char* adivina, char* q, char letra_elegida) {
	bool flag = false;

	for (char* p = adivina; *p; p++, q++) {
		if ((*p == letra_elegida) || (*p + 32 == letra_elegida)) {
			*q = *p;
			flag = flag + true;
		}

		else {
			*q = '_';
			flag = flag + false;
		}

	}

	return flag;
}

int main()
{
	Memoria mem;
	char Diccionario[10][10] = {"PELOTA", "CAMARON", "GUITARRA", "POLLO", "CAMARA", "FLIPANTE", "JUEGO", "OSCURIDAD", "FANTASMA", "GATO"};
	
	srand(time(0));
	int num = rand() % 10;
	char* adivina = Diccionario[num];
	
	int tam = 0;
	for (char* p = adivina; *p; p++) {	tam++; }

	char temp[10] = "";
	char* q = temp;
	bool flag = false;
	char letra_elegida = '-';
	bool flag2 = true;

	while (flag2) {

		std::cout << "Ingrese 0 para regresar" << std::endl;
		std::cout << "Ingrese la letra: ";
		std::cin >> letra_elegida;

		if (letra_elegida == '0') {
			mem.pop();
			mem.imprimir();
			continue;
			
		}

		flag = Verificar(adivina, q, letra_elegida);


		flag2 = mem.push(temp, tam, letra_elegida, flag);
		mem.imprimir();


	}
	
	
	
	return 0;

}

