#include <cassert>
#include <string>
#include <iostream>
#include "tads/Ejercicio2/HashEjercicio2.cpp"

int main()
{
    int cantidadElementos;
    cin >> cantidadElementos;
    TablaHash tabla(cantidadElementos);
    string entrada = "";
    for (int i = 0; i < cantidadElementos; i++) {
        cin >> entrada;
        if(entrada == "ADD") {
            int id;
            string titulo;
            cin >> id;
            cin >> titulo;
            tabla.insertar(id, titulo);
        }
        else if (entrada == "FIND") {
            int id;
            cin >> id;
            tabla.recuperar(id);
        }
        else if (entrada == "TOGGLE") {
            int id;
            cin >> id;
            tabla.cambioEstado(id);
        }
        else if (entrada == "COUNT") {
            tabla.informe();
        }
    }
    return 0;
}