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
    struct ciudadAdyacente {
        int pesoLlegada;
        int idMision;
        ciudadAdyacente* sig;
    };

    struct nodoCiudad {
        string nombreCiudad;
        ciudadAdyacente* adyacentes;
    };
    
    int cantCiudades;
    nodoCiudad* vecCiudades;

    void insertarAdy (nodoCiudad* ciudadSalida, int idLlegada, int peso) {
        ciudadAdyacente* nuevoAdyacente = new ciudadAdyacente;
        nuevoAdyacente->idMision = idLlegada;
        nuevoAdyacente->pesoLlegada = peso;
        nuevoAdyacente->sig = NULL;
        

        if (ciudadSalida->adyacentes == NULL) {
            ciudadSalida->adyacentes = nuevoAdyacente;
        } else {
            ciudadAdyacente* aux = ciudadSalida->adyacentes;
            nuevoAdyacente->sig = aux;
            ciudadSalida->adyacentes = nuevoAdyacente;
        }
    }
    

    public:
    Grafo (int cantidadElementos) {
        cantCiudades = cantidadElementos;
        vecCiudades = new nodoCiudad [cantCiudades];
        for (int i = 0; i < cantCiudades; i++) {
            vecCiudades[i].nombreCiudad = "";
            vecCiudades[i].adyacentes = NULL;
        }
    }

    ~Grafo() {
        // TODO
    }

    void insertarCiudad (string nombreCiu, int idCiudad) {
        vecCiudades[idCiudad].nombreCiudad = nombreCiu;
    }

    void agregarConexionCiudad (int idSalida, int idLlegada, int peso) {
        insertarAdy(&vecCiudades[idSalida], idLlegada, peso);
    }

    ciudadAdyacente* ciudadesAdyacentes (int idCiudad) {
        return vecCiudades[idCiudad].adyacentes;
    }
};