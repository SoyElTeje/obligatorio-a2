#include <cassert>
#include <string>
#include <limits>
#include "tads/TadEjercicio8.cpp"

using namespace std;

int main()
{
    int cantidadCiudades;
    cin >> cantidadCiudades;
    Ciudad * ciudades = new Ciudad[cantidadCiudades];
    for (int i = 0; i < cantidadCiudades; i++) {
        int xCiudad;
        int yCiudad;
        int poblacionCiudad;
        cin >> xCiudad >> yCiudad >> poblacionCiudad;
        ciudades[i].x = xCiudad;
        ciudades[i].y = yCiudad;
        ciudades[i].poblacion = poblacionCiudad;
    }
    DYC* dyc = new DYC(ciudades, cantidadCiudades);
    dyc->solucion();
}