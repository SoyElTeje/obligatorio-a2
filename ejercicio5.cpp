#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "./tads/Ejercicio5/TadEjercicio5.cpp"

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

// #include <cassert>
// #include <string>
// #include <iostream>
// #include <climits>
// #include "./tads/OT/laGodClase.cpp"

// using namespace std;

// int main()
// {
//     // Ingreso de Misiones
//     int cantidadMisiones;
//     cin >> cantidadMisiones;
//     GrafoMision *grafoMisiones = new GrafoMision(cantidadMisiones);

//     int idMision;
//     string nombreMision;
//     int idCiudad;
//     int dependientes;

//     for (int i = 1; i <= cantidadMisiones; i++)
//     {
//         cin >> idMision;
//         cin >> nombreMision;
//         cin >> idCiudad;
//         grafoMisiones->agregarMision(idMision, nombreMision, idCiudad);

//         cin >> dependientes;
//         while (dependientes != 0)
//         {
//             grafoMisiones->agregarDependientes(idMision, dependientes);
//             cin >> dependientes;
//         }
//     }

//     // Ingreso de Ciudades
//     int cantidadCiudades;
//     cin >> cantidadCiudades;
//     int posInicialIMF;
//     cin >> posInicialIMF;

//     GrafoCiudad *grafoCiudades = new GrafoCiudad(cantidadCiudades);
//     int idCiudadparaCiudades;
//     string nombreCiudad;
//     for (int i = 1; i <= cantidadCiudades; i++)
//     {
//         cin >> idCiudad;
//         cin >> nombreCiudad;
//         grafoCiudades->insertarCiudad(nombreCiudad, idCiudad);
//     }

//     // Conecciones entre ciudades
//     int cantidadConecciones;
//     cin >> cantidadConecciones;
//     int idCiudadOrigen;
//     int idCiudadDestino;
//     int tiempoDesplazamiento;

//     for (int i = 1; i <= cantidadConecciones; i++)
//     {
//         cin >> idCiudadOrigen;
//         cin >> idCiudadDestino;
//         cin >> tiempoDesplazamiento;
//         grafoCiudades->agregarConexionCiudad(idCiudadOrigen, idCiudadDestino, tiempoDesplazamiento);
//     }

//     // Procesar los datos
//     OT *ot = new OT();
//     Lista *ordenTopologico = ot->orden(grafoMisiones, grafoCiudades, posInicialIMF);

//     int tiempoTotal = 0;
//     int posicionIMF = posInicialIMF;

//     cout << "Ciudad inicial: " << grafoCiudades->obtenerNombreCiudad(posicionIMF) << endl;
//     nodoLista *actual = ordenTopologico->getCabeza();

//     while (actual != NULL)
//     {
//         int idMision = actual->idMision;
//         int idCiudadMision = grafoMisiones->getCiudad(idMision);

//         // Obtener detalles de la misión
//         string nombreMision = grafoMisiones->getNombreMision(idMision);
//         string nombreCiudadMision = grafoCiudades->obtenerNombreCiudad(idCiudadMision);
//         int *costos = grafoCiudades->dijkstra(posicionIMF);
//         int tiempoViaje = costos[idCiudadMision];
//         // Imprimir detalles de la misión
//         cout << grafoCiudades->obtenerNombreCiudad(posicionIMF) << " -> "
//              << nombreCiudadMision << " -> Mision: " << nombreMision
//              << " - " << nombreCiudadMision
//              << " - Tiempo de viaje: " << tiempoViaje << endl;
//         // Actualizar tiempo total y posición actual
//         tiempoTotal += tiempoViaje;
//         posicionIMF = idCiudadMision;
//         // Liberar memoria de los costos de Dijkstra
//         delete[] costos;

//         actual = actual->sig;
//     }

//     cout << "Misiones ejecutadas con éxito." << endl;
//     cout << "Tiempo total de viaje: " << tiempoTotal << endl;

//     delete grafoMisiones;
//     delete grafoCiudades;
//     delete ot;

//     return 0;
// }