#include <string>
#include <iostream>
#include "../Grafo/grafoMisionEj5.cpp"
#include "nodoListaEj5.cpp"
using namespace std;

class OT {
    private:
    Lista* ordenTopologico;

    public:
    OT() {
       ordenTopologico = new Lista;
    }

    void orden(Grafo* grafo) {
        Lista* noEntrada = grafo->noEntrantes();
        
        while (noEntrada) {
            int noEntradaActual = noEntrada->quitar();
            ordenTopologico->insertar(noEntradaActual);
            noEntrada->decrementarDependencias(noEntradaActual, grafo);
        }
    }
};