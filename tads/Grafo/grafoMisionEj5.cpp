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
    struct nodoMision {
        string nombreMision;
        int ciudadMision;
        int peso;
    };

    int cantElem;
    nodoMision** matrizAdy;
    
    public:
    Grafo (int cantidadElementos) {
        cantElem = cantidadElementos;
        matrizAdy = new nodoMision * [cantElem];
        for (int i = 0; i < cantidadElementos; i++) {
            matrizAdy[i] = new nodoMision[cantidadElementos];
            for (int j = 0; j < cantidadElementos; j++) {
                matrizAdy[i][j].ciudadMision = 0;
                matrizAdy[i][j].peso = 0;
                matrizAdy[i][j].nombreMision = "";
            }
        }
    }

    ~Grafo() {
        for (int i = 0; i < cantElem; i++) {
            delete[] matrizAdy[i];
        }
        delete[] matrizAdy;
    }

    void agregarMision (int salida, int llegada, int idCiudad, int peso, string nombreMision) {
        matrizAdy[salida][llegada].peso = peso;
        matrizAdy[llegada][salida].peso = peso;
        matrizAdy[salida][llegada].ciudadMision = idCiudad;
        matrizAdy[llegada][salida].ciudadMision = idCiudad;
        matrizAdy[salida][llegada].nombreMision = nombreMision;
        matrizAdy[llegada][salida].nombreMision = nombreMision;
        
    }

    int pesoCamino (int salida, int llegada) {
        return matrizAdy[salida][llegada].peso;
    }
};