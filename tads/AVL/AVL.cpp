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

    int cantidadLibros = 0;
    int cantidadHab = 0;
    int cantidadDes = 0;

    nodoAVL* raiz;

    int max(int a, int b) {
      return a > b ? a : b;
    }

    int altura(nodoAVL* nodo) {
      return nodo ? nodo->altura : 0;
    }

    int calculoBalance(nodoAVL* nodo) {
      if (!nodo) {
        return 0;
      }

      return (altura(nodo->izq) - altura(nodo->der));
    }

    nodoAVL* rotacionHoraria(nodoAVL* B) {
      nodoAVL* A = B->izq;
      nodoAVL* T2 = A->der;
      A->der = B;
      B->izq = T2;

      B->altura = 1 + max(altura(B->izq), altura(B->der));
      A->altura = 1 + max(altura(A->izq), altura(A->der));

      return A;
    }

    nodoAVL* rotacionAntihoraria(nodoAVL* A) {
      nodoAVL* B = A->der;
      nodoAVL* T2 = B->izq;
      B->izq = A;
      A->der = T2;

      A->altura = 1 + max(altura(A->izq), altura(A->der));
      B->altura = 1 + max(altura(B->izq), altura(B->der));

      return B;
    }

    nodoAVL* insertarAux(int id, string libroTitulo, nodoAVL* nodo) {
      if (!nodo) {
        nodoAVL* nuevo = new nodoAVL;
        nuevo->id = id;
        nuevo->titulo = libroTitulo;
        nuevo->estado = true;
        nuevo->der = NULL;
        nuevo->izq = NULL;
        nuevo->altura = 1;
        cantidadLibros++;
        cantidadHab++;
        return nuevo;
      }

      if (id < nodo->id) {
        nodo->izq = insertarAux(id, libroTitulo, nodo->izq);
      } else if (id > nodo->id) {
        nodo->der = insertarAux(id, libroTitulo, nodo->der);
      } else {
          if (!nodo->estado) {
            nodo->estado = true;
            cantidadHab++;
            cantidadDes--;
          }
          nodo->titulo = libroTitulo;
          return nodo;
      }

      nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

      int balance = calculoBalance(nodo);

      if (balance > 1 && id < nodo->izq->id) {
        // Caso Izquierda-Izquierda
        return rotacionHoraria(nodo);
      }
      if (balance > 1 && id > nodo->izq->id) {
        // Caso Izquierda-Derecha
        nodo->izq = rotacionAntihoraria(nodo->izq);
        return rotacionHoraria(nodo);
      }
      if (balance < -1 && id > nodo->der->id) {
        // Caso Derecha-Derecha
        return rotacionAntihoraria(nodo);
      }
      if (balance < -1 && id < nodo->der->id) {
        // Caso Derecha-Izquierda
        nodo->der = rotacionHoraria(nodo->der);
        return rotacionAntihoraria(nodo);
      }
      
      // En caso de no haber rotacion
      return nodo;
    }

    void buscarAux(int id, nodoAVL* nodo) {
      if (!nodo) {
        cout << "libro_no_encontrado" << endl;
        return;
      }

      if (nodo->id == id) {
        if (nodo->estado) {
          cout << nodo->titulo << " H" << endl;
        } else {
          cout << nodo->titulo << " D" << endl;
        }
        return;
      }

      if (id < nodo->id) {
        buscarAux(id, nodo->izq);
      } else {
        buscarAux(id, nodo->der);
      }
    }

    void cambiarAux(int id, nodoAVL* nodo) {
      if (!nodo) {
        cout << "libro_no_encontrado" << endl;
        return;
      }

      if (nodo->id == id) {
        if (nodo->estado) {
          cantidadDes++;
          cantidadHab--;
          nodo->estado = false;
        } else {
          cantidadDes--;
          cantidadHab++;
          nodo->estado = true;
        }
        return;
      }

      if (id < nodo->id) {
        cambiarAux(id, nodo->izq);
      } else {
        cambiarAux(id, nodo->der);
      }
    }

  public:
    AVL() {
      raiz = NULL;
    }

    void insertar(int id, string titulo) {
      raiz = insertarAux(id, titulo, raiz);
    }


    void buscar(int id) {
      return buscarAux(id, raiz);
    }

    void cambiarEstado(int id) {
      cambiarAux(id, raiz);
    }

    void cantLibrosHabilitados() {
      cout << cantidadLibros << " " << cantidadHab << " " << cantidadDes << endl;
    }
};