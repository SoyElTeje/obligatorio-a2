#include <string>
#include <iostream>
#include "definiciones5.cpp"
using namespace std;

class GrafoLista
{
private:
    Arista **vertices;
    int cantidadV;
    bool dirigido;
    bool ponderado;
    string *ciudades;
    bool *misiones;

public:
    GrafoLista(int cantV, bool esDirigido, bool esPonderado = true)
    {
        vertices = new Arista *[cantV + 1]();
        cantidadV = cantV;
        dirigido = esDirigido;
        ponderado = esPonderado;
        ciudades = new string[cantV + 1];
        misiones = new bool[cantV + 1];
    }

    ~GrafoLista()
    {
        for (int i = 1; i <= cantidadV; i++)
        {
            Arista *actual = vertices[i];
            while (actual != nullptr)
            {
                Arista *temp = actual;
                actual = actual->sig;
                delete temp;
            }
        }
        delete[] vertices;
        delete[] ciudades;
        delete[] misiones;
    }

    void agregarArista(int origen, int destino, int peso = 1)
    {
        Arista *nuevaArista = new Arista();
        nuevaArista->origen = origen;
        nuevaArista->destino = destino;
        nuevaArista->peso = peso;
        nuevaArista->sig = vertices[origen];
        vertices[origen] = nuevaArista;

        if (!dirigido)
        {
            Arista *inversa = new Arista();
            inversa->origen = destino;
            inversa->destino = origen;
            inversa->peso = peso;
            inversa->sig = vertices[destino];
            vertices[destino] = inversa;
        }
    }

    void imprimir()
    {
        cout << endl
             << "Lista de adyacencia:" << endl;
        for (int i = 1; i <= cantidadV; i++)
        {
            cout << i << ": ";
            Arista *actual = adyacentes(i);
            while (actual != NULL)
            {
                cout << actual->destino;
                if (ponderado)
                {
                    cout << " (" << actual->peso << ")";
                }
                if (actual->sig != NULL)
                {
                    cout << " -> ";
                }
                actual = actual->sig;
            }
            cout << endl;
        }
    }

    Arista *adyacentes(int vertice)
    {
        return vertices[vertice];
    }

    int cantidadVertices()
    {
        return cantidadV;
    }
    // ELIMINAR?
    void agregarCiudad(int vertice, string ciudad)
    {
        ciudades[vertice] = ciudad;
    }

    int **dijkstra(int origen)
    {
        bool *visitados = new bool[cantidadV + 1];
        for (int i = 1; i <= cantidadV; i++)
        {
            visitados[i] = false;
        }
        int *costos = new int[cantidadV + 1];
        for (int i = 1; i <= cantidadV; i++)
        {
            costos[i] = INT_MAX;
        }
        costos[origen] = 0;
        int *vengo = new int[cantidadV + 1];
        for (int i = 1; i <= cantidadV; i++)
        {
            vengo[i] = -1;
        }
        vengo[origen] = origen;
        ColaPrioridadExtendida *cola = new ColaPrioridadExtendida((cantidadV + 1) * (cantidadV + 1));
        cola->insertar(origen, origen, 0);
        while (!cola->estaVacia())
        {
            Arista *actual = cola->desencolar();
            visitados[actual->destino] = true;
            Arista *ady = adyacentes(actual->destino);
            while (ady != NULL)
            {
                if (!visitados[ady->destino] && costos[actual->destino] + ady->peso < costos[ady->destino])
                {
                    costos[ady->destino] = costos[actual->destino] + ady->peso;
                    vengo[ady->destino] = actual->destino;
                    cola->insertar(actual->destino, ady->destino, costos[ady->destino]);
                }
                ady = ady->sig;
            }
        }
        int **ret = new int *[2];
        ret[0] = costos;
        ret[1] = vengo;
        delete[] visitados;
        return ret;
    }

    void imprimirEnOrden(int *vengoDe, int origen, int fin)
    {
        if (fin == origen)
        {
            cout << ciudades[origen];
        }
        else
        {
            imprimirEnOrden(vengoDe, origen, vengoDe[fin]);
            cout << " -> " << ciudades[fin];
        }
    }
};

struct ListaEnteros
{
    int num;
    ListaEnteros *sig;
};

struct Dependencias
{
    int idMision;
    ListaEnteros *dependencias;
};

class GrafoOT
{
private:
    GrafoLista *grafoDependencias;
    int cantV;
    int *gradoEntrada;
    bool *misionesHechas;

public:
    GrafoOT(int cantidadElementos)
    {
        cantV = cantidadElementos;
        grafoDependencias = new GrafoLista(cantV, true, false);
        gradoEntrada = new int[cantV + 1]();
        misionesHechas = new bool[cantV + 1]();
    }

    ~GrafoOT()
    {
        delete grafoDependencias;
        delete[] gradoEntrada;
        delete[] misionesHechas;
    }

    void agregarDependencia(int mision, int dependeDe)
    {
        grafoDependencias->agregarArista(dependeDe, mision);
        gradoEntrada[mision]++;
    }

    void ejecutarMision(int mision)
    {
        misionesHechas[mision] = true;
        Arista *ady = grafoDependencias->adyacentes(mision);
        while (ady != NULL)
        {
            gradoEntrada[ady->destino]--;
            ady = ady->sig;
        }
    }

    void imprimir()
    {
        grafoDependencias->imprimir();
    }

    int cantidadVertices()
    {
        return cantV;
    }

    Arista *adyacentes(int vertice)
    {
        return grafoDependencias->adyacentes(vertice);
    }

    ListaEnteros *queMisionPuedoHacer()
    {
        ListaEnteros *misiones = NULL;
        for (int i = 1; i <= cantV; i++)
        {
            if (gradoEntrada[i] == 0 && !misionesHechas[i])
            {
                ListaEnteros *nueva = new ListaEnteros();
                nueva->num = i;
                nueva->sig = misiones;
                misiones = nueva;
            }
        }

        return misiones;
    }
};

class Misiones
{
private:
    GrafoLista *grafoMisiones;
    GrafoOT *grafoDependencias;
    string *ciudades;
    string *misiones;
    int *mapeoMisionCiudad;
    int cantidadMisiones;
    int cantidadCiudades;

public:
    //ELIMINAR?
    void agregarRuta(int origen, int destino, int peso)
    {
        grafoMisiones->agregarArista(origen, destino, peso);
    }

    void agregarDependencia(int mision, int dependeDe)
    {
        grafoDependencias->agregarDependencia(mision, dependeDe);
    }
    // ELIMINAR?
    void agregarCiudad(int vertice, string ciudad)
    {
        ciudades[vertice] = ciudad;
    }

    void hacerMision(int ciudadMision)
    {
        grafoDependencias->ejecutarMision(ciudadMision);
    }

    int mejorMisionSiguiente(int origen)
    {
        ListaEnteros *misiones = grafoDependencias->queMisionPuedoHacer();
        int *costos = grafoMisiones->dijkstra(origen)[0];
        int min = INT_MAX;
        int idMision = -1;
        while (misiones != NULL)
        {
            int mision = misiones->num;
            if (costos[mision] < min)
            {
                min = costos[mision];
                idMision = mision;
            }
            misiones = misiones->sig;
        }
        return idMision;
    }

    void setMapeoMisionCiudad(int *mapeo)
    {
        mapeoMisionCiudad = mapeo;
    }

    void setNombresMisiones(string *nombres)
    {
        misiones = nombres;
    }
    //ELIMINAR?
    string obtenerCiudadPorId(int idCiudad)
    {
        return ciudades[idCiudad];
    }

    void setMapeoCiudades(string *ciudades)
    {
        this->ciudades = ciudades;
    }

    void imprimirOrdenIdeal(int origen)
    {
        cout << "Ciudad inicial: " << ciudades[origen] << endl;
        int mision = mejorMisionSiguiente(origen);
        int tiempoTotal = 0;
        while (mision != -1)
        {
            int ciudadFin = mapeoMisionCiudad[mision];
            int *pesos = grafoMisiones->dijkstra(origen)[0];
            int *vengoDe = grafoMisiones->dijkstra(origen)[1];
            imprimirCamino(origen, ciudadFin, mision, vengoDe, pesos);
            cout << " -> Mision: " << misiones[mision] << " - " << ciudades[ciudadFin] << " - Tiempo de viaje: " << pesos[ciudadFin];
            cout << endl;
            hacerMision(mision);
            origen = ciudadFin;
            mision = mejorMisionSiguiente(origen);
            tiempoTotal += pesos[ciudadFin];
        }
        cout << "Misiones ejecutadas con exito." << endl;
        cout << "Tiempo total de viaje: " << tiempoTotal << endl;
    }

    void imprimirCamino(int origen, int destino, int idMision, int *vengoDe, int *pesos)
    {
        if (origen == destino)
        {
            cout << ciudades[origen] << "";
            return;
        }
        imprimirCamino(origen, vengoDe[destino], idMision, vengoDe, pesos);
        cout << " -> " << ciudades[destino];
    }

    Misiones(GrafoLista *&grafoCiudades, GrafoOT *grafoOT, int *mapeo)
    {
        grafoMisiones = grafoCiudades;
        grafoDependencias = grafoOT;
        ciudades = new string[grafoCiudades->cantidadVertices() + 1];
        misiones = new string[grafoDependencias->cantidadVertices() + 1];
        mapeoMisionCiudad = mapeo;
    }

    ~Misiones()
    {
        delete grafoMisiones;
        delete grafoDependencias;
        delete[] ciudades;
        delete[] misiones;
        delete[] mapeoMisionCiudad;
    }
};