#ifndef TABLA_HASH
#define TABLA_HASH
#include <cassert>
#include <string>
#include <iostream>
using namespace std;


struct Libro {
    int id;
    string titulo;
    bool disponible;
};

class TablaHash
{
private:
    int largo;
    Libro** tabla;
    bool* ocupado;
    int habilitados;
    int deshabilitados;

    int hash1(int clave) {
        const double A = 0.6180339887;
        double hashVal = clave * A;
        hashVal = hashVal - int(hashVal);
        return int(hashVal * largo);
    }

    int hash2(int clave) {
        return 1 + (clave % (largo - 2));
    }

    int siguientePrimo(int n) {
        int primo = n + 1;
        while (true) {
            bool esPrimo = true;
            for (int i = 2; i * i <= primo; i++) {
                if (primo % i == 0) {
                    esPrimo = false;
                    break;
                }
            }
            if (esPrimo) {
                return primo;
            }
            primo++;
        }
    }

    void rehash() {
    int nuevoLargo = siguientePrimo(largo * 2);
    Libro** nuevaTabla = new Libro*[nuevoLargo];
    bool* nuevoOcupado = new bool[nuevoLargo];

    for(int i = 0; i < nuevoLargo; i++) {
        nuevaTabla[i] = NULL;
        nuevoOcupado[i] = false;
    }

    for(int i = 0; i < largo; i++) {
        if(ocupado[i]) {
            int nuevoPos1 = hash1(tabla[i]->id);
            int nuevoPos2 = hash2(tabla[i]->id);
            int intento = 0;
            int nuevoPos = nuevoPos1;
            while (nuevoOcupado[nuevoPos] && intento < nuevoLargo) {
                intento++;
                nuevoPos = (nuevoPos1 + intento * nuevoPos2) % nuevoLargo;
            }
            nuevaTabla[nuevoPos] = tabla[i];
            nuevoOcupado[nuevoPos] = true;
        }
    }
    delete[] tabla;
    delete[] ocupado;

    tabla = nuevaTabla;
    ocupado = nuevoOcupado;
    largo = nuevoLargo;
}

    
    void insertarAux(int id, string titulo) {
        double factorCarga = static_cast<double>(habilitados + deshabilitados) / largo;
        if (factorCarga > 0.7) rehash();
        int pos1 = hash1(id);
        int pos = pos1;
        if (!ocupado[pos]) {
            tabla[pos] = new Libro();
            tabla[pos]->id = id;
            tabla[pos]->titulo = titulo;
            tabla[pos]->disponible = true;
            ocupado[pos] = true;
            habilitados++;
        }
        else {
            if(tabla[pos]->id == id) {
                tabla[pos]->titulo = titulo;
                if (!tabla[pos]->disponible) {
                    tabla[pos]->disponible = true;
                    habilitados++;
                    deshabilitados--;
                }
                return;
            }
            int pos2 = hash2(id);
            int intento = 1;
            while (ocupado[pos] && intento < largo && tabla[pos]->id != id) {
                pos = (pos1 + intento * pos2) % largo;
                intento++;
            }
            if (ocupado[pos]) {
                if (tabla[pos]->id == id) {
                    tabla[pos]->titulo = titulo;
                    if (!tabla[pos]->disponible) {
                        tabla[pos]->disponible = true;
                        habilitados++;
                        deshabilitados--;
                    }
                } else {
                    throw runtime_error("Intento de inserción en tabla llena");
                }
            } else {
                tabla[pos] = new Libro();
                tabla[pos]->id = id;
                tabla[pos]->titulo = titulo;
                tabla[pos]->disponible = true;
                ocupado[pos] = true;
                habilitados++;
            }
        }
    }


    void recuperarAux(int id) {
        bool encontrado = false;
        int pos1 = hash1(id);
        int pos = pos1;
        if(ocupado[pos] && tabla[pos]->id == id) {
            cout << tabla[pos]->titulo  << " " << (tabla[pos]->disponible ? "H" : "D") << endl;
            return;
        }
        int pos2 = hash2(id);
        int intento = 1;
        while (intento < largo) {
            pos = (pos1 + intento * pos2) % largo;
            if (!ocupado[pos]) {
                break;
            }
            if (tabla[pos]->id == id) {
                cout << tabla[pos]->titulo  << " " << (tabla[pos]->disponible ? "H" : "D") << endl;
                encontrado = true;
                break;
            }
            intento++;
        }
        if (!encontrado) cout << "libro_no_encontrado" << endl;
    }


    void cambioEstadoAux(int id) {
        int pos1 = hash1(id);
        int pos = pos1;
        bool encontrado = false;

        if(ocupado[pos] && tabla[pos]->id == id) {
            encontrado = true;
        } else {
            int pos2 = hash2(id);
            int intento = 1;
            while (intento < largo) {
                pos = (pos1 + intento * pos2) % largo;
                if (!ocupado[pos]) {
                    break;
                }
                if (tabla[pos]->id == id) {
                    encontrado = true;
                    break;
                }
                intento++;
            }
        }

        if (encontrado) {
            tabla[pos]->disponible = !tabla[pos]->disponible;
            if (tabla[pos]->disponible) {
                habilitados++;
                deshabilitados--;
            } else {
                habilitados--;
                deshabilitados++;
            }
        } else {
            cout << "libro_no_encontrado" << endl;
        }
    }



public:
    TablaHash(int tamano) {
        largo = this->siguientePrimo(tamano);
        tabla = new Libro*[largo];
        ocupado = new bool[largo];
        habilitados = 0;
        deshabilitados = 0;
        for (int i = 0; i < largo; i++) {
            tabla[i] = nullptr;
            ocupado[i] = false;
        }
    }

    ~TablaHash() {
        for (int i = 0; i < largo; i++) {
            if (tabla[i] != nullptr) {
                delete tabla[i];
            }
        }
        delete[] tabla;
        delete[] ocupado;
    }

    void insertar(int id, string titulo) {
        insertarAux(id, titulo);
    }

    void imprimir() {
        for (int i = 0; i < largo; i++) {
            if (ocupado[i]) {
            }
        }
    }

    void recuperar(int id) {
        recuperarAux(id);
    }

    void informe() {
        cout << to_string(habilitados + deshabilitados) << " " << to_string(habilitados) << " " << to_string(deshabilitados) << endl;
    }

    void cambioEstado(int id) {
        cambioEstadoAux(id);
    }
};

#endif
