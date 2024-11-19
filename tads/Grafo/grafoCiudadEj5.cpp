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
    int** matrizAdy;
    string* nombreCiudad;
    
    public:
    Grafo (int cantidadElementos) {
        cantElem = cantidadElementos;
        nombreCiudad = new string [cantElem];
        for (int i = 0; i < cantElem; i++) {
            nombreCiudad[i] = "";
        }

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
        delete[] nombreCiudad; 
    }

    void agregarConexionCiudad (int salida, int llegada, int peso, string nombreCiu) {
        matrizAdy[salida][llegada] = peso;
        matrizAdy[llegada][salida] = peso;
        if (nombreCiudad[salida] == "") {
            nombreCiudad[salida] = nombreCiu;
        }
    }

    int pesoCamino (int salida, int llegada) {
        return matrizAdy[salida][llegada];
    }
};