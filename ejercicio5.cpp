#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "./tads/TadEjercicio5.cpp"

using namespace std;

int main()
{
    int cantidadMisiones;
    cin >> cantidadMisiones;
    GrafoOT *dep = new GrafoOT(cantidadMisiones);
    int *mapeoCiudadAMisiones = new int[cantidadMisiones + 1]();
    string *nombresMisiones = new string[cantidadMisiones + 1]();
    for (int i = 0; i < cantidadMisiones; i++)
    {
        int idMision;
        cin >> idMision;
        string nombreMision;
        cin >> nombreMision;
        nombresMisiones[idMision] = nombreMision;
        int idCiudad;
        cin >> idCiudad;
        int dependencia;
        cin >> dependencia;
        mapeoCiudadAMisiones[idMision] = idCiudad;
        while (dependencia != 0)
        {
            dep->agregarDependencia(dependencia, idMision);
            cin >> dependencia;
        }
    }
    int cantidadCiudades;
    cin >> cantidadCiudades;
    GrafoLista *grafoCiudades = new GrafoLista(cantidadCiudades, false, true);
    int origen;
    cin >> origen;
    string *nombresCiudades = new string[cantidadCiudades + 1]();
    for (int i = 0; i < cantidadCiudades; i++)
    {
        int idCiudad;
        cin >> idCiudad;
        string nombreCiudad;
        cin >> nombreCiudad;
        nombresCiudades[idCiudad] = nombreCiudad;
    }
    int cantidadConexiones;
    cin >> cantidadConexiones;
    for (int i = 0; i < cantidadConexiones; i++)
    {
        int origen;
        cin >> origen;
        int destino;
        cin >> destino;
        int tiempo;
        cin >> tiempo;
        grafoCiudades->agregarArista(origen, destino, tiempo);
    }

    Misiones *misiones = new Misiones(grafoCiudades, dep, mapeoCiudadAMisiones);
    misiones->setMapeoCiudades(nombresCiudades);
    misiones->setNombresMisiones(nombresMisiones);
    misiones->imprimirOrdenIdeal(origen);
}