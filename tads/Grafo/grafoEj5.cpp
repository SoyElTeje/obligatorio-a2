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
    int cantElem;
    int **matrizAdy;
    
    public:
    Grafo (int cantidadElementos) {
        cantElem = cantidadElementos;
        matrizAdy = new int * [cantElem];
        for (int i = 0; i < cantidadElementos; i++) {
            matrizAdy[i] = new int[cantidadElementos];
            for (int j = 0; j < cantidadElementos; j++) {
                matrizAdy[i][j] = 0;
            }
        }
    }

    ~Grafo() {
        for (int i = 0; i < cantElem; i++) {
            delete[] matrizAdy[i];
        }
        delete[] matrizAdy;
    }

    void agregarNodo (int salida, int llegada, int peso) {
        matrizAdy[salida][llegada] = peso;
        matrizAdy[llegada][salida] = peso;
    }

    int pesoCamino (int salida, int llegada) {
        return matrizAdy[salida][llegada];
    }
};