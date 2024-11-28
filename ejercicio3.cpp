#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Ejercicio3/heapEjercicio3.cpp"

using namespace std;

int main()
{
    int cantidadElementos;
    cin >> cantidadElementos;
    Heap heap(cantidadElementos);

    for (int i = 0; i < cantidadElementos; i++) {
        int id;
        int precio;
        cin >> id;
        cin >> precio;
        heap.agregarElemento(id, precio);
    }
    int k;
    cin >> k;
    heap.mostrtarKelementos(k);

    return 0;
}