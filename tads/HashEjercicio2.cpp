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
        return clave % largo;
    }

    int hash2(int clave) {
        return (clave + 1) % largo;
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

        for(int i = 0; i < nuevoLargo; i++) {
            if(ocupado[i]) {
                int nuevoPos = hash1(tabla[i]->id);
                if(!nuevoOcupado[nuevoPos]) {
                    nuevaTabla[nuevoPos] = tabla[i];
                    nuevoOcupado[nuevoPos] = true;
                }
                else {
                    int nuevoPos2 = hash2(tabla[i]->id);
                    int intento = 0;
                    while (nuevoOcupado[nuevoPos] && intento < nuevoLargo) {
                        nuevoPos = (nuevoPos + intento * nuevoPos2) % nuevoLargo;
                        intento++;
                    }
                    nuevaTabla[nuevoPos] = tabla[i];
                    nuevoOcupado[i] = true;
                }
            }
        }
        delete[] tabla;
        delete[] ocupado;

        tabla = nuevaTabla;
        ocupado = nuevoOcupado;
        largo = nuevoLargo;
    }
    
    void insertarAux(int id, string titulo) {
        int factorCarga = (habilitados + deshabilitados) / largo;
        if (factorCarga > 0.7) rehash();
        int pos = hash1(id);
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
                tabla[pos]->disponible = true;
                return;
            }
            int pos2 = hash2(id);
            int intento = 0;
            while (ocupado[pos] && intento < largo) {
                pos = (pos + intento * pos2) % largo;
                intento++;
            }
            if (ocupado[pos]) {
                if (tabla[pos]->id == id) {
                    tabla[pos]->titulo = titulo;
                    tabla[pos]->disponible = true;
                } else {
                    throw runtime_error("Intento de inserción en tabla llena");
                }
            } else {
                tabla[pos] = new Libro();
                tabla[pos]->id = id;
                tabla[pos]->titulo = titulo;
                ocupado[pos] = true;
            }
            habilitados++;
        }
    }

    void recuperarAux(int id) {
        bool encontrado = false;
        int pos = hash1(id);
        if(ocupado[pos] && tabla[pos]->id == id) {
            cout << tabla[pos]->titulo  << " " << (tabla[pos]->disponible ? "H" : "D") << endl;
            return;
        }
        int pos2 = hash2(id);
        int intento = 0;
        while (ocupado[pos] && intento < largo) {
            pos = (pos + intento * pos2) % largo;
            intento++;
            if(ocupado[pos] && tabla[pos]->id == id) {
                cout << tabla[pos]->titulo  << " " << (tabla[pos]->disponible ? "H" : "D") << endl;
                encontrado = true;
            }
        }
        if (encontrado) cout << "libro_no_encontrado" << endl;
    }

    void cambioEstadoAux(int id) {
        int pos = hash1(id);
        bool encontrado = false;
        if(ocupado[pos] && tabla[pos]->id == id) {
            tabla[pos]->disponible = !tabla[pos]->disponible;
            if(tabla[pos]->disponible) {
                habilitados++;
                deshabilitados--;
            } else {
                habilitados--;
                deshabilitados++;
            }
            encontrado = true;
        }
        int pos2 = hash2(id);
        int intento = 0;
        while (ocupado[pos] && intento < largo) {
            pos = (pos + intento * pos2) % largo;
            intento++;
            if(ocupado[pos] && tabla[pos]->id == id) {
                tabla[pos]->disponible = !tabla[pos]->disponible;
                if(tabla[pos]->disponible) {
                    habilitados++;
                    deshabilitados--;
                } else {
                    habilitados--;
                    deshabilitados++;
                }
                encontrado = true;
            }
        }
        if (!encontrado) cout << "libro_no_encontrado" << endl;
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

    string informe() {
        cout << to_string(habilitados + deshabilitados) << " " << to_string(habilitados) << " " << to_string(deshabilitados) << endl;
    }

    void cambioEstado(int id) {
        return cambioEstadoAux(id);
    }
};

#endif
