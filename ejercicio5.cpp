#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "./tads/OT/grafoMisionEj5.cpp"
#include "./tads/OT/grafoCiudadEj5.cpp"
#include "./tads/OT/ordenTopologicoEj5.cpp"
#include "./tads/OT/nodoListaEj5.cpp"

using namespace std;

int main()
{
    // Ingreso de Misiones
    int cantidadMisiones;
    cin >> cantidadMisiones;
    GrafoMision* grafoMisiones = new GrafoMision(cantidadMisiones);

    int idMision;
    string nombreMision;
    int idCiudad;
    int dependientes;

    for (int i = 0; i < cantidadMisiones; i++) {
        cin >> idMision;
        cin >> nombreMision;
        cin >> idCiudad;
        grafoMisiones->agregarMision(idMision, nombreMision, idCiudad, NULL);

        cin >> dependientes;
        while (dependientes != 0) {
            grafoMisiones->agregarDependientes(idMision, dependientes);
            cin >> dependientes;
        }
    }

    // Ingreso de Ciudades
    int cantidadCiudades;
    cin >> cantidadCiudades;
    int posInicialIMF;
    cin >> posInicialIMF;

    GrafoCiudad* grafoCiudades = new GrafoCiudad(cantidadCiudades);
    int idCiudadparaCiudades;
    string nombreCiudad;
    for (int i = 0; i < idCiudadparaCiudades; i++) {
        cin >> idCiudad;
        cin >> nombreCiudad;
    }


    // Conecciones entre ciudades
    int cantidadConecciones;
    cin >> cantidadConecciones;
    int idCiudadOrigen;
    int idCiudadDestino;
    int tiempoDesplazamiento;

    for (int i = 0; i < cantidadConecciones; i++) {
        cin >> idCiudadOrigen;
        cin >> idCiudadDestino;
        cin >> tiempoDesplazamiento;
        grafoCiudades->agregarConexionCiudad(idCiudadOrigen, idCiudadDestino, tiempoDesplazamiento);
    }

    // Procesar los datos
    OT* ot = new OT();
    Lista* ordenTopologico = ot->orden(grafoMisiones, grafoCiudades, posInicialIMF);

    int tiempoTotal = 0;
    int posicionIMF = posInicialIMF;

    cout << "Ciudad inicial: " << grafoCiudades->obtenerNombreCiudad(posicionIMF) << endl;
    nodoLista* actual = ordenTopologico->getCabeza();

    while (actual != NULL) {
        int idMision = actual->idMision;
        int idCiudadMision = grafoMisiones->getCiudad(idMision);

        string nombreMision = grafoMisiones->getNombreMision(idMision);
        cout << "Mision: " << nombreMision << " - Ciudad: " << grafoCiudades->obtenerNombreCiudad(idCiudadMision) << endl;

        actual = actual->sig;
    }

    cout << "Misiones ejecutadas con éxito." << endl;
    cout << "Tiempo total de viaje: " << tiempoTotal << endl;

    return 0;
}