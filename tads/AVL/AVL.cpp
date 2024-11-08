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