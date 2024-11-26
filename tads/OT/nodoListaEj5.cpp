#include <string>
#include <iostream>

struct nodoLista {
    int idMision;
    nodoLista* sig;
};

class Lista {
    private:
    nodoLista* cabeza;

    public:
    Lista () {
        cabeza = NULL;
    }

    ~Lista() {
        while (cabeza) {
            nodoLista* aux = cabeza;
            cabeza = cabeza->sig;
            delete aux;
        }
    }

    void insertar(int idMision) {
        nodoLista* nuevo = new nodoLista;
        nuevo->idMision = idMision;
        nuevo->sig = NULL;

        nodoLista* aux = cabeza;
        nuevo->sig = aux;
        cabeza = nuevo;
    }

    int quitar() {
        if (!cabeza) {
            return -1;
        }

        int id = cabeza->idMision;
        nodoLista* aux = cabeza;
        cabeza = cabeza->sig;
        delete aux;
        return id;
    }

    bool estaVacia() {
        return cabeza == NULL;
    }

    int getIdMision() {
        return cabeza->idMision;
    }

    nodoLista* getCabeza() {
        return cabeza;
    }
};