#include <string>
#include <iostream>
#include "../OT/nodoListaEj5.cpp"
using namespace std;

/* 
Grafo ponderado:
Para las misiones se usa peso 1 para establecer las dependencias
Para las ciudades se usa como peso las distancias
*/
class Grafo {
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
    Grafo (int cantidadElementos) {
        cantMisiones = cantidadElementos;
        vecMisiones = new nodoMision[cantMisiones];
        for (int i = 0; i < cantMisiones; i++) {
            vecMisiones[i].idCiudad = 0;
            vecMisiones[i].misionesDependientes = Lista();
            vecMisiones[i].nombreMision = "";
        }
    }

    ~Grafo() {
        // TODO
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

    Lista* noEntrantes() {
        Lista* grados = new Lista;

        for (int i = 0; i < cantMisiones; i++) {
            if (vecMisiones[i].gradoEntrada == 0) {
                grados->insertar(i);
            }
        }
        return grados;
    }

    Lista* nodosDependientes(int idMision) {
        return vecMisiones[idMision].misionesDependientes;
    }

    void decrementarGrado(int idMision) {
        vecMisiones[idMision].gradoEntrada--;
    }
};