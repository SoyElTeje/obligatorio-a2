#include <iostream>
#include "tads/TadEjercicio10.cpp"

using namespace std;

int main()
{
    int tamanioJardin;
    cin >> tamanioJardin;
    int numTiposFlores;
    cin >> numTiposFlores;

    // Inicializar restricciones con tamaño adecuado e índices desde 1
    int *restricciones = new int[numTiposFlores + 1];
    for (int i = 1; i <= numTiposFlores; i++)
    {
        restricciones[i] = -1; // Inicializar sin restricciones
    }
    for (int i = 1; i <= numTiposFlores; i++)
    {
        string nombreFlor;
        int restriccion;
        cin >> nombreFlor >> restriccion;
        restricciones[i] = restriccion;
    }

    int maximasFlores = 0;
    int **jardin = inicializarJardin(tamanioJardin);

    cantidadFlores(0, 0, jardin, tamanioJardin, restricciones, numTiposFlores, 0, maximasFlores);
    cout << maximasFlores << endl;

    // Liberar memoria
    for (int i = 0; i < tamanioJardin; i++)
    {
        delete[] jardin[i];
    }
    delete[] jardin;
    delete[] restricciones;

    return 0;
}
