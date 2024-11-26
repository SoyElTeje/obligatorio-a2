using namespace std;
#include <string>

bool noRepiteFlorCostados(int **jardin, int tamanioJardin, int fila, int columna, int *restricciones, int flor)
{
    if (columna == 0 && fila == 0)
    {
        return jardin[fila][columna + 1] != flor && jardin[fila + 1][columna] != flor && jardin[fila + 1][columna + 1] != flor;
    }
    else if (columna == 0 && fila < tamanioJardin - 1)
    {
        return jardin[fila][columna + 1] != flor && jardin[fila + 1][columna] != flor && jardin[fila + 1][columna + 1] != flor && jardin[fila - 1][columna] != flor && jardin[fila - 1][columna + 1] != flor;
    }
    else if (columna == 0 && fila == tamanioJardin - 1)
    {
        return jardin[fila][columna + 1] != flor && jardin[fila - 1][columna] != flor && jardin[fila - 1][columna + 1] != flor;
    }
    else if (columna < tamanioJardin - 1 && fila == 0)
    {
        return jardin[fila][columna + 1] != flor && jardin[fila + 1][columna] != flor && jardin[fila + 1][columna + 1] != flor && jardin[fila][columna - 1] != flor && jardin[fila + 1][columna - 1] != flor;
    }
    else if (columna < tamanioJardin - 1 && fila < tamanioJardin - 1)
    {
        return jardin[fila][columna + 1] != flor && jardin[fila + 1][columna] != flor && jardin[fila + 1][columna + 1] != flor && jardin[fila][columna - 1] != flor && jardin[fila + 1][columna - 1] != flor && jardin[fila - 1][columna] != flor && jardin[fila - 1][columna + 1] != flor && jardin[fila - 1][columna - 1] != flor;
    }
    else if (columna < tamanioJardin - 1 && fila == tamanioJardin - 1)
    {
        return jardin[fila][columna + 1] != flor && jardin[fila - 1][columna] != flor && jardin[fila - 1][columna + 1] != flor && jardin[fila][columna - 1] != flor && jardin[fila - 1][columna - 1] != flor;
    }
    else if (columna == tamanioJardin - 1 && fila == 0)
    {
        return jardin[fila][columna - 1] != flor && jardin[fila + 1][columna] != flor && jardin[fila + 1][columna - 1] != flor;
    }
    else if (columna == tamanioJardin - 1 && fila < tamanioJardin - 1)
    {
        return jardin[fila][columna - 1] != flor && jardin[fila + 1][columna] != flor && jardin[fila + 1][columna - 1] != flor && jardin[fila - 1][columna] != flor && jardin[fila - 1][columna - 1] != flor;
    }
    else
    {
        return jardin[fila][columna - 1] != flor && jardin[fila - 1][columna] != flor && jardin[fila - 1][columna - 1] != flor;
    }
}

bool puedoPonerFlor(int **jardin, int tamanioJardin, int fila, int columna, int *restricciones, int flor)
{
    if (restricciones[flor] == -1)
    {
        return noRepiteFlorCostados(jardin, tamanioJardin, fila, columna, restricciones, flor);
    }
    if (restricciones[flor] != fila)
        return false;
}
void cantidadFlores(int colActual, int **jardin, int tamanioJardin, int *restricciones, int &mejorSolucion)
{
    if (colActual == tamanioJardin)
    {
        int solucion = 0;
        for (int i = 0; i < tamanioJardin; i++)
        {
            solucion += jardin[i][restricciones[i]];
        }
        if (solucion < mejorSolucion)
        {
            mejorSolucion = solucion;
        }
    }
    else
    {
        for (int i = 0; i < tamanioJardin; i++)
        {
            restricciones[colActual] = i;
            cantidadFlores(colActual + 1, jardin, tamanioJardin, restricciones, mejorSolucion);
        }
    }
}