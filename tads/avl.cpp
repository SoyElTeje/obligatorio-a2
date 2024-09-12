#include <iostream>
using namespace std;

class AVL {
	private:
	struct NodoAVL {
		int dato;
		NodoAVL *izq, *der;
		int altura;
		NodoAVL(int d) : dato(d), izq(NULL), der(NULL), altura(1) {}
	};

	NodoAVL *raiz;

	int max(int a, int b) {
		return a > b ? a : b;
	}

	// Funcion para acceder a la altura del nodo, si el nodo es nulo, la altura es 0
	int altura(NodoAVL *n) {
		if (!n) return 0;
		return n->altura;
	}

	// Funcion para calcular el balance del nodo
	int balance(NodoAVL *n) {
		if (!n) return 0;
		return altura(n->izq) - altura(n->der);
	}

	NodoAVL* rotacionHoraria(NodoAVL *A) {
		NodoAVL *B = A->izq;
		NodoAVL *T2 = B->der;
		B->der = A;
		A->izq = T2;
		A->altura = 1 + max(altura(A->izq), altura(A->der));
		B->altura = 1 + max(altura(B->izq), altura(B->der));
		return B;
	}

	NodoAVL* rotacionAntiHoraria(NodoAVL* B) {
		NodoAVL *A = B->der;
		NodoAVL *T2 = A->izq;
		A->izq = B;
		B->der = T2;
		B->altura = 1 + max(altura(B->izq), altura(B->der));
		A->altura = 1 + max(altura(A->izq), altura(A->der));
		return A;
	}

	NodoAVL * insertarAux(NodoAVL *nodo, int dato) {
		cout << "Insertando " << dato << " en insertarAux" << endl;
		if(!nodo) return new NodoAVL(dato);
		if(dato < nodo->dato) 
			nodo->izq = insertarAux(nodo->izq, dato);
		else if(dato > nodo->dato)
			nodo->der = insertarAux(nodo->der, dato);
		else
			return nodo;
		
		// A la vuelta de la recursión, actualizo la altura del nodo en el que estoy
		nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

		// Verifico si el nodo está desbalanceado
		int balanceo = balance(nodo);

		bool desbalanceoIzq = balanceo > 1;
		bool desbalanceoDer = balanceo < -1;

		// Caso izquierda izquierda
		if(desbalanceoIzq && dato < nodo->izq->dato) {
			return rotacionHoraria(nodo);
		}

		// Caso derecha derecha
		if(desbalanceoDer && dato > nodo->der->dato) {
			return rotacionAntiHoraria(nodo);
		}

		// Caso izquierda derecha
		if(desbalanceoIzq && dato > nodo->izq->dato) {
			nodo->izq = rotacionAntiHoraria(nodo->izq);
			return rotacionHoraria(nodo);
		}

		// Caso derecha izquierda
		if(desbalanceoDer && dato < nodo->der->dato) {
			nodo->der = rotacionHoraria(nodo->der);
			return rotacionAntiHoraria(nodo);
		}

		return nodo;
	}

	void inOrdenAux(NodoAVL *nodo) {
		if(!nodo) return;
		inOrdenAux(nodo->izq);
		cout << nodo->dato << " ";
		inOrdenAux(nodo->der);
	}

	public:
	void insertar(int dato) {
		cout << "Insertando " << dato << endl;
		raiz = insertarAux(raiz, dato);
	}

	void inOrder() {
		cout << "InOrder: ";
		inOrdenAux(raiz);
	}
};