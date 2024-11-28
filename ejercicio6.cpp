#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Ejercicio6/TadEjercicio6.cpp"

using namespace std;

int main()
{
    int cantidadCiudades;
    cin >> cantidadCiudades;
    GrafoLista* g = new GrafoLista(cantidadCiudades, false, true);
    for (int i = 1; i <= cantidadCiudades; i++) {
        int indiceCiudad;
        string ciudad;
        cin >> indiceCiudad >> ciudad;
        // cout << "Indice ciudad: " << indiceCiudad << " Ciudad: " << ciudad << endl;
        g->agregarCiudad(indiceCiudad, ciudad);
    }

    int origenMision, entidadMision, equipoMision, extraccionMision;
    cin >> origenMision >> entidadMision >> equipoMision >> extraccionMision;
    // cout << "Origen: " << origen << " Entidad: " << entidad << " Equipo: " << equipo << " Extraccion: " << extraccion << endl;
    int cantidadConexiones;
    cin >> cantidadConexiones;
    for (int i = 0; i < cantidadConexiones; i++) {
        int origen, destino, peso;
        cin >> origen >> destino >> peso;
        // cout << "Origen: " << origen << " Destino: " << destino << " Peso: " << peso << endl;
        g->agregarArista(origen, destino, peso);
    }
    g->queOrdenEsMejor(origenMision, entidadMision, equipoMision, extraccionMision);
}