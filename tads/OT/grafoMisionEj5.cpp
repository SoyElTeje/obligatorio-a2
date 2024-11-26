#include <string>
#include <iostream>
#include "./nodoListaEj5.cpp"
#include "./heapEj5.cpp"

using namespace std;

class GrafoMision {
    private:
    struct nodoMision {
        string nombreMision;
        int gradoEntrada;
        int idCiudad;
        Lista* misionesDependientes;
    };

    int cantMisiones;
    nodoMision* vecMisiones;
    
    public:
    GrafoMision (int cantidadElementos) {
        cantMisiones = cantidadElementos;
        vecMisiones = new nodoMision[cantMisiones];
        for (int i = 0; i < cantMisiones; i++) {
            vecMisiones[i].idCiudad = 0;
            vecMisiones[i].misionesDependientes = new Lista();
            vecMisiones[i].nombreMision = "";
        }
    }

    ~GrafoMision() {
        for (int i = 0; i < cantMisiones; i++) {
            delete vecMisiones[i].misionesDependientes;
        }
        delete[] vecMisiones;
    }


    void agregarMision (int idMision, string nombreMision, int idCiudad, int* dependientes) {
        vecMisiones[idMision].nombreMision = nombreMision;
        vecMisiones[idMision].idCiudad = idCiudad;

        int i = 0;
        while (dependientes[i] != 0) {
            agregarDependientes(idMision, dependientes[i]);
            i++;
        }
    }

    void agregarDependientes (int idMision, int idDependiente) {
        vecMisiones[idMision].misionesDependientes->insertar(idDependiente);
        vecMisiones[idDependiente].gradoEntrada++;
    }

    Heap* noEntrantes(int* costos) {
        Heap* grados = new Heap(cantMisiones);
        for (int i = 0; i < cantMisiones; i++) {
            if (vecMisiones[i].gradoEntrada == 0) {
                int costoViaje = costos[vecMisiones[i].idCiudad];
                grados->insertar(i, costoViaje);
            }
        }
        delete[] costos;
        return grados;
    }

    Lista* nodosDependientes(int idMision) {
        return vecMisiones[idMision].misionesDependientes;
    }

    void decrementarGrado(int idMision) {
        vecMisiones[idMision].gradoEntrada--;
    }

    int getCiudad(int idMision) {
        return vecMisiones[idMision].idCiudad;
    }

    int gradoEntrada(int idMision) {
        return vecMisiones[idMision].gradoEntrada;
    }

    string getNombreMision (int idMision) {
        return vecMisiones[idMision].nombreMision;
    }
};