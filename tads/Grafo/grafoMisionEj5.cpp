#include <string>
#include <iostream>
using namespace std;

/* 
Grafo ponderado:
Para las misiones se usa peso 1 para establecer las dependencias
Para las ciudades se usa como peso las distancias
*/
class Grafo {
    private:
    struct misionDependiente {
        int idMision;
        misionDependiente* sig;
    };
    struct nodoMision {
        string nombreMision;
        int idCiudad;
        misionDependiente* misionesDependientes;
    };

    int cantMisiones;
    nodoMision* vecMisiones;
    
    public:
    Grafo (int cantidadElementos) {
        cantMisiones = cantidadElementos;
        vecMisiones = new nodoMision[cantMisiones];
        for (int i = 0; i < cantMisiones; i++) {
            vecMisiones[i].idCiudad = 0;
            vecMisiones[i].misionesDependientes = NULL;
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
        misionDependiente* nueva = new misionDependiente;
        nueva->idMision = idDependiente;
        nueva->sig = NULL;

        if (vecMisiones[idMision].misionesDependientes == NULL) {
            vecMisiones[idMision].misionesDependientes = nueva;
        } else {
            misionDependiente* aux = vecMisiones[idMision].misionesDependientes;
            nueva->sig = aux;
            vecMisiones[idMision].misionesDependientes = nueva;
        }
    }
};