using namespace std;
#include <string>
#include <iostream>

bool noRepiteFlorCostados(int **jardin, int tamanioJardin, int fila, int columna, int flor)
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
    if (restricciones[flor] != fila && restricciones[flor] != -1)
    {
        return false;
    }
    return noRepiteFlorCostados(jardin, tamanioJardin, fila, columna, flor);
}

bool esPosicionValida(int fila, int columna, int tamanioJardin)
{
    return fila >= 0 && fila < tamanioJardin && columna >= 0 && columna < tamanioJardin;
}

bool esSolucion(int **jardin, int tamanioJardin, int filaActual, int columnaActual)
{
    return filaActual == tamanioJardin;
}

void procesarSolucion(int totalFlores, int &mejorSolucion)
{
    if (totalFlores > mejorSolucion)
    {
        mejorSolucion = totalFlores;
    }
}

void cantidadFlores(int colActual, int filaActual, int **jardin, int tamanioJardin, int *restricciones, int totalFlores, int colocadasActual, int &mejorSolucion)
{
    int floresRestantesAColocar = tamanioJardin * tamanioJardin - (filaActual > 0 ? filaActual - 1 : 0) * (tamanioJardin)-colActual;
    if (colocadasActual + floresRestantesAColocar <= mejorSolucion)
    {
        return;
    }
    if (colActual == tamanioJardin)
    {
        colActual = 0;
        filaActual++;
    }
    if (esSolucion(jardin, tamanioJardin, filaActual, colActual))
    {
        procesarSolucion(colocadasActual, mejorSolucion);
        return;
    }

    for (int flor = 1; flor <= totalFlores; flor++)
    {
        if (puedoPonerFlor(jardin, tamanioJardin, filaActual, colActual, restricciones, flor))
        {
            jardin[filaActual][colActual] = flor;
            colocadasActual++;
            cantidadFlores(colActual + 1, filaActual, jardin, tamanioJardin, restricciones, totalFlores, colocadasActual, mejorSolucion);
            colocadasActual--;
            jardin[filaActual][colActual] = 0;
        }
    }
    cantidadFlores(colActual + 1, filaActual, jardin, tamanioJardin, restricciones, totalFlores, colocadasActual, mejorSolucion);
}

int **inicializarJardin(int tamanioJardin)
{
    int **jardin = new int *[tamanioJardin];
    for (int i = 0; i < tamanioJardin; i++)
    {
        jardin[i] = new int[tamanioJardin];
        for (int j = 0; j < tamanioJardin; j++)
        {
            jardin[i][j] = 0;
        }
    }
    return jardin;
}
