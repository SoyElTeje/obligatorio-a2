#include <string>
#include <iostream>
using namespace std;

class Heap {
    private:
    struct nodoHeap {
        int id;
        int precio;
    };

    int largo;
    nodoHeap* vec;
    int ultimaPos;


    void agregarElementoAux(int id, int precio) {
        vec[ultimaPos].id = id;
        vec[ultimaPos].precio = precio;

        int i = ultimaPos;
        while (i > 1 && precio < vec[i/2].precio) {
            nodoHeap aux = vec[i];
            vec[i] = vec[i/2];
            vec[i/2] = aux;
            i = i / 2;
        }
    }

    public:
    Heap(int k) {
        largo = k;
        vec = new nodoHeap [largo + 1];
        ultimaPos = 0;
    }

    void agregarElemento(int id, int precio){
        agregarElementoAux(id, precio);
    };

    void mostrtarKelementos(int k) {
        for (int i = 0; i < k && i < largo + 1; i++) {
            cout << vec[i].id << endl;
        }
    };
};