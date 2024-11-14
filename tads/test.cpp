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
    GrafoLista* g = new GrafoLista(3, false, true);
    g->agregarArista(1, 3, 2);
    g->agregarArista(3, 2, 1);
    g->imprimir();
    int** dij = g->dijkstra(1);
    int* vengo = dij[1];
    int* costos = dij[0];

    for (int i = 1; i <= 3; i++) {
        cout << i << " viene de " << vengo[i] << " con costo " << costos[i] << endl;
    }

    // TEST INSERCION
    // GrafoLista* g = new GrafoLista(3, false, true);
    // g->agregarArista(1, 3, 2);
    // g->agregarArista(2,3,4);
    // g->imprimir();
}