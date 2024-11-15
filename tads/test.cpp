#include "TadEjercicio6.cpp"
using namespace std;
int main() {
    // ColaPrioridadExtendida* c = new ColaPrioridadExtendida(10);
    // c->insertar(1, 2, 3);
    // c->insertar(3, 2, 1);
    // c->insertar(2, 4, 4);
    // c->imprimirEnOrden();

    // Arista* primera = c->desencolar();
    // cout << "Primera arista desencolada: " << primera->origen << " " << primera->destino << " " << primera->peso << endl;
    // c->imprimirEnOrden();
    // c->duplicarPeso(1, 2);
    // cout << "Duplicado el peso de la arista 1 2" << endl;
    // c->imprimirEnOrden();
    // return 0;

    // TEST GRAFO
    // int largoGrafo = 7;
    // GrafoLista* g = new GrafoLista(largoGrafo, false, true);
    // g->agregarArista(1, 2, 100);
    // g->agregarArista(2, 7, 1);
    // g->agregarArista(1, 3, 2);
    // g->agregarArista(3, 4, 3);
    // g->agregarArista(4, 5, 20000);
    // g->agregarArista(5, 7, 10);
    // g->agregarArista(4, 6, 4);
    // g->agregarArista(6, 7, 9);
    // g->agregarCiudad(1, "Montevideo");
    // g->agregarCiudad(2, "Canelones");
    // g->agregarCiudad(3, "Maldonado");
    // g->agregarCiudad(4, "Rocha");
    // g->agregarCiudad(5, "Treinta y Tres");
    // g->agregarCiudad(6, "Durazno");
    // g->agregarCiudad(7, "Tacuarembo");
    // g->imprimir();

    // g->queOrdenEsMejor(1, 5, 2, 7);

    // int largoGrafo = 5;
    // GrafoLista* g = new GrafoLista(largoGrafo, false, true);
    // g->agregarArista(1, 2, 10);
    // g->agregarArista(1, 4, 4);
    // g->agregarArista(2, 5, 2);
    // g->agregarArista(2, 3, 4);
    // g->agregarArista(5, 3, 1);
    // g->agregarArista(4, 5, 2);
    // g->agregarCiudad(1, "Montevideo");
    // g->agregarCiudad(2, "Canelones");
    // g->agregarCiudad(3, "Maldonado");
    // g->agregarCiudad(4, "Rocha");
    // g->agregarCiudad(5, "Treinta y Tres");
    // g->queOrdenEsMejor(1, 4, 2, 3);

    int largoGrafo = 4;
    GrafoLista* g = new GrafoLista(largoGrafo, false, true);
    g->agregarArista(1, 2, 1);
    g->agregarArista(2, 3, 1);
    g->agregarArista(3, 4, 1);
    g->agregarCiudad(1, "Montevideo");
    g->agregarCiudad(2, "Canelones");
    g->agregarCiudad(3, "Maldonado");
    g->agregarCiudad(4, "Rocha");

    g->queOrdenEsMejor(1, 3, 2, 4);


    // ColaPrioridadExtendida *c = new ColaPrioridadExtendida(3);
    // c->insertar(1, 3, 2);
    // c->insertar(3, 2, 1);
    // c->imprimirEnOrden();
    // Arista *primera = c->desencolar();
    // cout << "Primera arista desencolada: " << primera->origen << " " << primera->destino << " " << primera->peso << endl;
    // Arista *segunda = c->desencolar();
    // cout << "Segunda arista desencolada: " << segunda->origen << " " << segunda->destino << " " << segunda->peso << endl;

    // g->imprimir();
    // int** dij = g->dijkstra(1);
    // int* vengo = dij[1];
    // int* costos = dij[0];

    // for (int i = 1; i <= largoGrafo; i++) {
    //     cout << i << " viene de " << vengo[i] << " con costo " << costos[i] << endl;
    // }

    // TEST INSERCION
    // GrafoLista* g = new GrafoLista(3, false, true);
    // g->agregarArista(1, 3, 2);
    // g->agregarArista(2,3,4);
    // g->imprimir();
}