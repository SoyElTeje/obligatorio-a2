#include <iostream>
#include "definiciones.cpp"
using namespace std;

class GrafoMatriz
{
private:
	int **matriz;
	int cantidadV;
	bool dirigido;
	bool ponderado;

public:
	GrafoMatriz(int cantV, bool esDirigido, bool esPonderado)
	{
		matriz = new int *[cantV + 1];
		for (int i = 1; i <= cantV; i++)
		{
			matriz[i] = new int[cantV + 1]();
			for (int j = 1; j <= cantV; j++)
			{
				matriz[i][j] = INT_MIN;
			}
		}
		cantidadV = cantV;
		dirigido = esDirigido;
		ponderado = esPonderado;
	}

	~GrafoMatriz()
	{
		for (int i = 0; i <= cantidadV; i++)
		{
			delete[] matriz[i];
		}
		delete[] matriz;
	}

	void agregarArista(int origen, int destino, int peso = 1)
	{
		matriz[origen][destino] = peso;
		if (!dirigido)
		{
			matriz[destino][origen] = peso;
		}
	}

	void imprimir()
	{

		cout << endl << "Matriz de adyacencia:" << endl;
		for (int i = 1; i <= cantidadV; i++)
		{
			cout << i << ": ";
			Arista *actual = adyacentes(i);
			while (actual->sig != NULL)
			{
				cout << actual->destino << " ";
				if (ponderado)
				{
					cout << "(" << actual->peso << ") ";
				}
				if (actual->sig->sig)
				{
					cout << "-> ";
				}
				actual = actual->sig;
			}
			cout << endl;
		}
	}

	Arista *adyacentes(int adyacentesA)
	{
		Arista *adyacentes = NULL;
		for (int i = 1; i <= cantidadV; i++)
		{
			if (matriz[adyacentesA][i] != INT_MIN)
			{
				Arista *nuevaArista = new Arista();
				nuevaArista->destino = i;
				nuevaArista->peso = matriz[adyacentesA][i];
				nuevaArista->sig = adyacentes;
				adyacentes = nuevaArista;
			}
		}
		return adyacentes;
	}

	int cantidadVertices()
	{
		return cantidadV;
	}
};