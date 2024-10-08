#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int cantidadElementos;
    cin >> cantidadElementos;
    TablaHash tabla(cantidadElementos);
    string entrada = "";
    while(cin >> entrada) {
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
            cout << tabla.recuperar(id) << endl;
        }
        else if (entrada == "TOGGLE") {
            int id;
            cin >> id;
            tabla.cambioEstado(id);
        }
    }
    return 0;
}
