using namespace std;
#include <algorithm>
#include <iostream>
#include <cmath>

struct Ciudad {
    int x, y, poblacion;
};

struct ParCiudades {
    Ciudad* c1;
    Ciudad* c2;
};

class DYC {
    private:
        Ciudad* ciudades;
        int cantidadCiudades;

        double distanciaEfectiva(Ciudad * c1, Ciudad * c2) {
            double distancia = sqrt((c2->x - c1->x) * (c2->x - c1->x) + (c2->y - c1->y) * (c2->y - c1->y));
            double poblacion = abs(c2->poblacion - c1->poblacion) / static_cast<double>(max(c1->poblacion, c2->poblacion));

            return distancia + poblacion;
        }

        ParCiudades* mejorParDeTresCiudades(Ciudad* ciudades, int inicio, int fin) {
            Ciudad* c1 = &ciudades[inicio];
            Ciudad* c2 = &ciudades[inicio + 1];
            Ciudad* c3 = &ciudades[inicio + 2];

            double distancia12 = distanciaEfectiva(c1, c2);
            double distancia13 = distanciaEfectiva(c1, c3);
            double distancia23 = distanciaEfectiva(c2, c3);

            ParCiudades *par = new ParCiudades;
            if (distancia12 == distancia13 && distancia13 == distancia23) {
                if (c1->poblacion + c2->poblacion > c1->poblacion + c3->poblacion && c1->poblacion + c2->poblacion > c2->poblacion + c3->poblacion) {
                    par->c1 = c1;
                    par->c2 = c2;
                } else if (c1->poblacion + c3->poblacion > c1->poblacion + c2->poblacion && c1->poblacion + c3->poblacion > c2->poblacion + c3->poblacion) {
                    par->c1 = c1;
                    par->c2 = c3;
                } else {
                    par->c1 = c2;
                    par->c2 = c3;
                }
            } else if (distancia12 < distancia13 && distancia12 < distancia23) {
                par->c1 = c1;
                par->c2 = c2;
            } else if (distancia13 < distancia12 && distancia13 < distancia23) {
                par->c1 = c1;
                par->c2 = c3;
            } else {
                par->c1 = c2;
                par->c2 = c3;
            }
            return par;
        }

        ParCiudades * compararPares(ParCiudades * par1, ParCiudades * par2) {
            double distancia1 = distanciaEfectiva(par1->c1, par1->c2);
            double distancia2 = distanciaEfectiva(par2->c1, par2->c2);
            if (distancia1 == distancia2) {
                if (par1->c1->poblacion + par1->c2->poblacion > par2->c1->poblacion + par2->c2->poblacion) {
                    return par1;
                } else {
                    return par2;
                }
            }
            if (distancia1 < distancia2) {
                return par1;
            }
            return par2;
        }

        void merge(Ciudad * ciudades, int inicio, int mitad, int fin, bool ordenarPorX) {
            int largoIzq = mitad - inicio + 1;
            int largoDer = fin - mitad;

            Ciudad * izquierda = new Ciudad[largoIzq];
            Ciudad * derecha = new Ciudad[largoDer];

            for (int i = 0; i < largoIzq; ++i) {
                izquierda[i] = ciudades[inicio + i];
            }

            for (int i = 0; i < largoDer; ++i) {
                derecha[i] = ciudades[mitad + 1 + i];
            }

            int indParteIzq = 0;
            int indParteDer = 0;
            int indEntero = inicio;

            while (indParteIzq < largoIzq && indParteDer < largoDer) {
                if (ordenarPorX) {
                    if (izquierda[indParteIzq].x <= derecha[indParteDer].x) {
                        ciudades[indEntero] = izquierda[indParteIzq];
                        indParteIzq++;
                    } else {
                        ciudades[indEntero] = derecha[indParteDer];
                        indParteDer++;
                    }
                } else {
                    if (izquierda[indParteIzq].y <= derecha[indParteDer].y) {
                        ciudades[indEntero] = izquierda[indParteIzq];
                        indParteIzq++;
                    } else {
                        ciudades[indEntero] = derecha[indParteDer];
                        indParteDer++;
                    }
                }
                indEntero++;
            }

            while (indParteIzq < largoIzq) {
                ciudades[indEntero] = izquierda[indParteIzq];
                indParteIzq++;
                indEntero++;
            }
            while (indParteDer < largoDer) {
                ciudades[indEntero] = derecha[indParteDer];
                indParteDer++;
                indEntero++;
            }

            delete[] izquierda;
            delete[] derecha;
        }

        void mergeSort (Ciudad * ciudades, int inicio, int fin, bool ordenarPorX) {
            if (inicio < fin) {
                int mitad = (inicio + fin) / 2;
                
                mergeSort(ciudades, inicio, mitad, ordenarPorX);

                mergeSort(ciudades, mitad + 1, fin, ordenarPorX);

                merge(ciudades, inicio, mitad, fin, ordenarPorX);
            }
        }

        void ordenarPorX(Ciudad* ciudades, int cantidadCiudades) {
            mergeSort(ciudades, 0, cantidadCiudades - 1, true);
        }

        void ordenarPorY(Ciudad* ciudades, int cantidadCiudades) {
            mergeSort(ciudades, 0, cantidadCiudades - 1, false);
        }

        // void ordenarPorX(Ciudad* ciudades, int cantidadCiudades) {
        //     for (int i = 0; i < cantidadCiudades - 1; ++i) {
        //         for (int j = 0; j < cantidadCiudades - i - 1; ++j) {
        //             if (ciudades[j].x > ciudades[j + 1].x) {
        //                 Ciudad temp = ciudades[j];
        //                 ciudades[j] = ciudades[j + 1];
        //                 ciudades[j + 1] = temp;
        //             }
        //         }
        //     }
        // }




        // void ordenarPorY(Ciudad* ciudades, int cantidadCiudades) {
        //     for (int i = 0; i < cantidadCiudades - 1; ++i) {
        //         for (int j = 0; j < cantidadCiudades - i - 1; ++j) {
        //             if (ciudades[j].y > ciudades[j + 1].y) {
        //                 Ciudad temp = ciudades[j];
        //                 ciudades[j] = ciudades[j + 1];
        //                 ciudades[j + 1] = temp;
        //             }
        //         }
        //     }
        // }


        ParCiudades* mejorPar(Ciudad* ciudades, int cantCiudades) {
            ordenarPorX(ciudades, cantCiudades);
            return mejorParDYC(ciudades, 0, cantCiudades - 1);
        }

        Ciudad * construirFranja(Ciudad* ciudades, int inicio, int fin, double menorDistancia, int& finFranja) {
            Ciudad * franja = new Ciudad[fin - inicio + 1];
            int mitad = (inicio + fin) / 2;
            int j = 0;
            for (int i = inicio; i <= fin; ++i) {
                if (abs(ciudades[i].x - ciudades[mitad].x) < menorDistancia) {
                    franja[j] = ciudades[i];
                    j++;
                }
            }
            finFranja = j;
            return franja;
        }

        ParCiudades * mejorParDeLaFranja(Ciudad* franja, int finFranja) {
            ordenarPorY(franja, finFranja);
            ParCiudades * mejorPar = new ParCiudades;
            mejorPar->c1 = &franja[0];
            mejorPar->c2 = &franja[1];
            double menorDistancia = distanciaEfectiva(mejorPar->c1, mejorPar->c2);
            for (int i = 0; i < finFranja; ++i) {
                for (int j = i + 1; j < finFranja; ++j) {
                    if (abs(franja[j].y - franja[i].y) < menorDistancia) {
                        double distancia = distanciaEfectiva(&franja[i], &franja[j]);
                        if (distancia < menorDistancia) {
                            mejorPar->c1 = &franja[i];
                            mejorPar->c2 = &franja[j];
                            menorDistancia = distancia;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
            return mejorPar;
        }


        ParCiudades* mejorParDYC(Ciudad* ciudades, int inicio, int fin) {
            if (fin - inicio == 2) {
                return mejorParDeTresCiudades(ciudades, inicio, fin);
            }
            if (fin - inicio == 1) {
                ParCiudades *par = new ParCiudades;
                par->c1 = &ciudades[inicio];
                par->c2 = &ciudades[fin];
                return par;
            }
            int mitad = (inicio + fin) / 2;
            ParCiudades* parIzq = mejorParDYC(ciudades, inicio, mitad);
            ParCiudades* parDer = mejorParDYC(ciudades, mitad + 1, fin);
            
            ParCiudades* mejor = compararPares(parDer, parIzq);

            double menorDistancia = distanciaEfectiva(mejor->c1, mejor->c2);
            int finFranja;
            Ciudad * franja = construirFranja(ciudades, inicio, fin, menorDistancia, finFranja);
            if (finFranja == 0) {
                return mejor;
            }
            
            ParCiudades* mejorParFranja = mejorParDeLaFranja(franja, finFranja);
            return compararPares(mejor, mejorParFranja);
        }

        void imprimirPar(ParCiudades* par) {
            if (par->c1->x < par->c2->x) {
                cout << par->c1->x << " " << par->c1->y << " " << par->c1->poblacion << endl;
                cout << par->c2->x << " " << par->c2->y << " " << par->c2->poblacion << endl;
            }
            else if (par->c1->x == par->c2->x) {
                if (par->c1->y < par->c2->y) {
                    cout << par->c1->x << " " << par->c1->y << " " << par->c1->poblacion << endl;
                    cout << par->c2->x << " " << par->c2->y << " " << par->c2->poblacion << endl;
                } else {
                    cout << par->c2->x << " " << par->c2->y << " " << par->c2->poblacion << endl;
                    cout << par->c1->x << " " << par->c1->y << " " << par->c1->poblacion << endl;
                }
            } else {
                cout << par->c2->x << " " << par->c2->y << " " << par->c2->poblacion << endl;
                cout << par->c1->x << " " << par->c1->y << " " << par->c1->poblacion << endl;
            }
        }

        
    public:
        DYC(Ciudad* ciudades, int cantidadCiudades) {
            this->ciudades = ciudades;
            this->cantidadCiudades = cantidadCiudades;
        }

        ~DYC() {
            delete[] ciudades;
        }

        void solucion() {
            ParCiudades* par = mejorPar(this->ciudades, this->cantidadCiudades);
            imprimirPar(par);
        }
};