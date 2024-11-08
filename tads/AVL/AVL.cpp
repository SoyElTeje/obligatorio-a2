#include <cassert>
#include <string>
#include <iostream>
using namespace std;

class AVL {
  private:
    struct nodoAVL {
      int id;
      string titulo;
      bool estado; // True = habilitado, False = deshabilitado
      int altura;
      nodoAVL* izq;
      nodoAVL* der;
    };

    nodoAVL* raiz;

    int max(int a, int b) {
      return a > b ? a : b;
    }

    int altura(nodoAVL* nodo) {
      if (!nodo) return 0;

      return 1 + max(altura(nodo->izq), altura(nodo->der));
    }

    int calculoBalance(nodoAVL* nodo) {
      int alturaDer = nodo->der ? nodo->der->altura : 0;
      int alturaIzq = nodo->izq ? nodo->izq->altura : 0;

      int diferencia = alturaIzq - alturaDer;

      /*
      Interpretacion de la diferencia:
        diferencia igual a 0, -1 o 1: el arbol esta balanceado
        diferencia < -1: desbalance hacia la derecha
        diferencia > 1: desbalance hacia la izquierda
      */
      return diferencia;
    }

    nodoAVL* insertarAux(int id, string libroTitulo, nodoAVL* nodo) {
      if (!nodo) {
        nodoAVL* nuevo = new nodoAVL;
        nuevo->titulo = libroTitulo;
        nuevo->estado = true;
        nuevo->der = NULL;
        nuevo->izq = NULL;
        nuevo->altura = 1;
        return nuevo;
      }

      if (nodo->id == id) {
        nodo->titulo = libroTitulo;
        nodo->estado = true;
        return nodo;
      }

      if (nodo->id < id) {
        nodo->der = insertarAux(id, libroTitulo, nodo->der);
      }

      if (nodo->id > id) {
        nodo->izq = insertarAux(id, libroTitulo, nodo->izq);
      }

      nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

      int balance = calculoBalance(nodo);
      bool balanceIzq = balance < -1;
      bool balanceDer = balance > 1;
    }

  public:
    void insertar(int id, string titulo) {
      raiz = insertarAux(id, titulo, raiz);
    }

    void cambiarEstado() {

    }

    int cantLibrosHabilitados() {

    }
};