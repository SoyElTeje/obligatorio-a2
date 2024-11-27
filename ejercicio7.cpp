#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Greedy/GreedyEj7.cpp"

using namespace std;

int main()
{

    int cantidadCanciones;
    cin >> cantidadCanciones;

    int* canciones = new int [cantidadCanciones];
    for (int i = 0; i < cantidadCanciones; i++) {
        cin >> canciones[i];
    }

    int cantidadEdtudiantes;
    cin >> cantidadEdtudiantes;

    GreedyCanciones* procesarCanciones = new GreedyCanciones(cantidadCanciones, cantidadEdtudiantes, canciones);
    procesarCanciones->calcularResultado();

    return 0;
}