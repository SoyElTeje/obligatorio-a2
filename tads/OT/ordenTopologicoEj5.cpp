#include <string>
#include <iostream>
#include "./nodoListaEj5.cpp"
#include "./grafoCiudadEj5.cpp"
#include "./grafoMisionEj5.cpp"
#include "./heapEj5.cpp"

using namespace std;

class OT {
    private:
    Lista* ordenTopologico;

    public:
    OT() {
       ordenTopologico = new Lista;
    }

    Lista* orden(GrafoMision* grafoMisiones, GrafoCiudad* grafoCiudades, int posicionIMF) {
        int* costos = grafoCiudades->dijkstra(posicionIMF);
        Heap* misionesSinDependencias = grafoMisiones->noEntrantes(costos);

        while (!misionesSinDependencias->estaVacio()) {
            nodoHeap misionActual = misionesSinDependencias->minimo();
            int idMision = misionActual.idNodo;
            int idCiudadMision = grafoMisiones->getCiudad(idMision);
            
            ordenTopologico->insertar(idMision);

            posicionIMF = idCiudadMision;

            Lista* dependientes = grafoMisiones->nodosDependientes(idMision);
            
            while (!dependientes->estaVacia()) {
                int misionDependiente = dependientes->quitar();
                grafoMisiones->decrementarGrado(misionDependiente);
                if (grafoMisiones->gradoEntrada(misionDependiente) == 0) {
                    int costoViaje = costos[grafoMisiones->getCiudad(misionDependiente)];
                    misionesSinDependencias->insertar(misionDependiente, costoViaje);
                }
            }
        }
        delete[] costos;
        delete misionesSinDependencias;
        return ordenTopologico;
    }

    nodoLista* obtenerCabeza() {
        return ordenTopologico->getCabeza();
    }
};