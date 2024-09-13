#include <iostream>
#include "tads/HashEjercicio2.cpp"

int main() {
    TablaHash tabla(100);
    tabla.insertar("asd", "Libro 1");
    tabla.insertar("dsa", "Libro 2");
    tabla.imprimir();
    cout << tabla.recuperar("asd") << endl;
    cout << tabla.recuperar("dsa") << endl;
    cout << tabla.recuperar("qwe") << endl;

    cout << tabla.informe() << endl;

    cout << tabla.cambioEstado("asd") << endl;
    cout << tabla.informe() << endl;
    cout << tabla.cambioEstado("asd") << endl;
    cout << tabla.informe() << endl;
    cout << tabla.cambioEstado("epicooo") << endl;
    return 0;
}