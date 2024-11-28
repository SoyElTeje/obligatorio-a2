#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Ejercicio1/AVL.cpp"

using namespace std;

int main()
{
    int cantidadElementos;
    cin >> cantidadElementos;
    AVL arbol;
    string entrada;

    for (int i = 0; i < cantidadElementos; i++) {
        cin >> entrada;
        if(entrada == "ADD") {
            int id;
            string titulo;
            cin >> id;
            cin >> titulo;
            arbol.insertar(id, titulo);
        }
        if(entrada == "FIND") {
            int id;
            cin >> id;
            arbol.buscar(id);
        }
        if(entrada == "TOGGLE") {
            int id;
            cin >> id;
            arbol.cambiarEstado(id);
        }
        if(entrada == "COUNT") {
            arbol.cantLibrosHabilitados();
        }
    }
    return 0;
}