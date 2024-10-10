#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TadEjercicio4.cpp"

using namespace std;

int main()
{
    int cantidadPedidos;
    int cantidadOperaciones;
    cin >> cantidadPedidos;
    cin >> cantidadOperaciones;
    cout << cantidadOperaciones;
    ColaPrioridad* cp = new ColaPrioridad(cantidadPedidos);
    string entrada;
    for(int i = 0; i < cantidadOperaciones; i++) {
        cin >> entrada;
        cout << entrada;
        if (entrada == "I") {
            int id;
            int prioridad;
            bool paraLlevar;
            string items;
            cin >> id >> prioridad >> paraLlevar >> items;
            cout << id << endl;
            cout << prioridad << endl;
            cout << paraLlevar << endl;
            cout << items << endl;
            cp->insertar(new Pedido{id, prioridad, paraLlevar, items});
        }
        else if (entrada == "E") {
            cout << "Entregando pedido" << endl;
            cp->entregarPedido();
        }
        else if (entrada == "C") {
            int id;
            cin >> id;
            cp->hacerParaLlevar(id);
        }
        
    }
    return 0;
}