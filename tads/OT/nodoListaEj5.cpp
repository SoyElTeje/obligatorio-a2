#include <string>
#include <iostream>
#include "../Grafo/grafoMisionEj5.cpp"

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

    int getIdMision() {
        return cabeza->idMision;
    }

    void decrementarDependencias(int idActual, Grafo* grafo) {
        nodoLista* aux = grafo->nodosDependientes(idActual);
        while (aux) {
            grafo->decrementarGrado(aux->idMision);
        }
    }
    
};