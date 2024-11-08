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

    nodoAVL* rotacionHoraria(nodoAVL* B) {
      nodoAVL* A = B->izq;
      nodoAVL* T2 = A->der;
      A->der = B;
      B->izq = T2;

      A->altura = altura(A);
      B->altura = altura(B);

      return A;
    }

    nodoAVL* rotacionAntihoraria(nodoAVL* A) {
      nodoAVL* B = A->der;
      nodoAVL* T2 = B->izq;
      B->izq = A;
      A->der = T2;

      A->altura = altura(A);
      B->altura = altura(B);

      return B;
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
      bool desbalanceIzq = balance < -1;
      bool desbalanceDer = balance > 1;

      if (desbalanceIzq) {
        // Caso izq - izq
        if (nodo->izq->id > id) {
          return rotacionHoraria(nodo);
        } else { // Caso izq der
          nodo->izq = rotacionAntihoraria(nodo->izq);
          return rotacionHoraria(nodo);
        }
      }
      if (desbalanceDer) {
        // Caso der - der
        if (nodo->der->id < id) {
          return rotacionHoraria(nodo);
        } else { // Caso der - izq
          nodo->der = rotacionHoraria(nodo->der);
          return rotacionAntihoraria(nodo);
        }
      }
      
      // En caso de no haber rotacion
      return nodo;
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