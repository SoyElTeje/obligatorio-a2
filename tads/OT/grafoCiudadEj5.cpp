#include <string>
#include <iostream>
#include "./heapEj5.cpp"

#include <climits>
using namespace std;

class GrafoCiudad {
    private:
    struct ciudadAdyacente {
        int idMision;
        int peso; // Peso de ir de la ciudad a este adyacente
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
        nuevoAdyacente->peso = peso;
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
    GrafoCiudad (int cantidadElementos) {
        cantCiudades = cantidadElementos;
        vecCiudades = new nodoCiudad [cantCiudades];
        for (int i = 0; i < cantCiudades; i++) {
            vecCiudades[i].nombreCiudad = "";
            vecCiudades[i].adyacentes = NULL;
        }
    }

    ~GrafoCiudad () {
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

    string obtenerNombreCiudad(int posIMF) {
        return vecCiudades[posIMF].nombreCiudad;
    }

    int* dijkstra(int posIMF) {
        bool* visitados = new bool [cantCiudades + 1];
        int* costos = new int [cantCiudades + 1];
        int* vengoDe = new int [cantCiudades + 1]; // No es necesario pero lo dejo por si hay que implementar algo en la defensa

        for (int i = 0; i < cantCiudades + 1; i++) {
            visitados[i] = false;
            costos[i] = INT_MAX;
            vengoDe[i] = -1;
        }
        
        costos[posIMF] = 0;

        Heap* cp = new Heap(cantCiudades);
        cp->insertar(posIMF, 0);

        while (!cp->estaVacio()) {
            nodoHeap v = cp->minimo();
            visitados[v.idNodo] = true;

            ciudadAdyacente* adyacente = vecCiudades[v.idNodo].adyacentes;
            while (adyacente != NULL) {
                int w = adyacente->idMision;
                int peso = adyacente->peso;

                if (!visitados[w] && costos[w] > costos[v.idNodo] + peso) {
                    costos[w] = costos[v.idNodo] + peso;
                    vengoDe[w] = v.idNodo;
                    cp->insertar(w, costos[w]);
                }

                adyacente = adyacente->sig;
            }
        }

        delete[] visitados;
        delete[] vengoDe;
        delete cp;

        return costos;
    }
};