#include <iostream>
#include "tads/HashEjercicio2.cpp"

int main() {
    TablaHash tabla(100);
    tabla.insertar(1, "Libro 1");
    tabla.insertar(2, "Libro 2");
    tabla.imprimir();
    tabla.recuperar(1);
    tabla.recuperar(2);
    tabla.recuperar(3);

    cout << tabla.informe() << endl;

    tabla.cambioEstado(1);
    tabla.informe();
    tabla.cambioEstado(1);
    tabla.informe();
    tabla.cambioEstado(3);
    return 0;
}