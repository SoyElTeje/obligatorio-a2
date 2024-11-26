#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TadEjercicio10.cpp"

using namespace std;

int main()
{
    int tamanioJardin;
    cin >> tamanioJardin;
    int totalFlores;
    cin >> totalFlores;
    int *restricciones = new int[totalFlores + 1];
    for (int i = 1; i <= totalFlores; i++)
    {
        cin >> restricciones[i];
    }
    int maximasFlores = 0;
    int **jardin = inicializarJardin(tamanioJardin);
    cantidadFlores(0, 0, jardin, tamanioJardin, restricciones, totalFlores, 0, maximasFlores);
    cout << maximasFlores << endl;
    return 0;
}