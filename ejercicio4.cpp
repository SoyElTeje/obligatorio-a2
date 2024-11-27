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
    ColaPrioridad *cp = new ColaPrioridad(cantidadPedidos);
    string entrada;
    for (int i = 0; i < cantidadOperaciones; i++)
    {
        cin >> entrada;
        if (entrada == "I")
        {
            int id;
            int prioridad;
            string paraLlevar;
            string items;
            cin >> id >> prioridad >> paraLlevar >> items;
            cp->insertar(new Pedido{id, prioridad, paraLlevar == "true", items});
        }
        else if (entrada == "E")
        {
            int id;
            cin >> id;
            cp->entregarPedido(id);
        }
        else if (entrada == "C")
        {
            int id;
            cin >> id;
            cp->hacerParaLlevar(id);
        }
    }
    cp->imprimirLosQueFaltan();
    return 0;
}