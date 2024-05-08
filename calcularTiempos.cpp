#include "Red.h"
#include <iostream>

using namespace std;

void calcularTiempos(Red *red)
{
    cout << endl << "Lineas disponibles..." << endl;
    red->mostrarLineas();

    string *linea = new string;

    cout << endl << "Ingrese la linea a recorrer: "; cin >> *linea;

    Linea * linea_buscada = red->buscarLinea(linea);

    if(linea_buscada) // si la linea ingresada existe
    {

        string * est1 = new string, *est2 = new string;

        cout << endl << "Estaciones de la linea"<< *linea << " disponibles: ";

        linea_buscada->mostrarEstaciones();

        Estacion *inicio, *final;

        cout << endl << "Ingrese la estacion de inicio: "; cin >> *est1;

        inicio = linea_buscada->buscarEstacion(est1);

        if(inicio == NULL)
        {
            cout << endl << "Ingresaste una estacion inexistente";
            return;
        }

        cout << endl << "Ingrese la estacion de fin: "; cin >> *est2;

        final = linea_buscada->buscarEstacion(est2);

        if(final == NULL)
        {
            cout << endl << "Ingresaste una estacion inexistente";
            return;
        }

        short int pos_1,pos_2,total = 0;

        pos_1 = linea_buscada->posicionarEstacion(est1); // se busca las posiciones con respecto al primera puntero de la linea
        pos_2 = linea_buscada->posicionarEstacion(est2);

        if(pos_1 < pos_2) // si la primera estacion se encuentra primero se usan los punteros 'siguientes'
        {
            while(inicio != final)
            {
                if(inicio->es_transferencia)
                {
                    for(short int i = 0; i < inicio->num_conexiones; i++) // se manda a indexar el siguiente camino y su tiempo por medio del nombre de la linea actual
                    {
                        if(inicio->getLineas_queCruzan(&i) == *linea) // se busca la posicion del nombre de esta linea dentro de este arreglo
                        {
                            total += inicio->getTiempo_siguiente(&i); // se indexa esa posicion una vez encontrada
                            inicio = inicio->getSiguiente(&i);
                            break;
                        }
                    }
                }
                else
                {
                    total += inicio->getTiempo_siguiente();
                    inicio = inicio->getSiguiente(); // se direcciona este puntero al siguiente
                }
            }
        }
        else // si la segunda estacion se encuentra primero se usan los punteros 'anteriores'
        {
            while(inicio != final)
            {
                if(inicio->es_transferencia)
                {
                    for(short int i = 0; i < inicio->num_conexiones; i++) // se manda a indexar el siguiente camino y su tiempo por medio del nombre de la linea actual
                    {
                        if(inicio->getLineas_queCruzan(&i) == *linea) // se busca la posicion del nombre de esta linea dentro de este arreglo
                        {
                            total += inicio->getTiempo_anterior(&i); // se indexa esa posicion una vez encontrada
                            inicio = inicio->getAnterior(&i);
                            break;
                        }
                    }
                }
                else
                {
                    total += inicio->getTiempo_anterior();
                    inicio = inicio->getAnterior(); // se direcciona este puntero al siguiente
                }
            }
        }

        // una vez se tiene el total:

        cout << endl << "El tiempo para llegar desde la estacion " << *est1 << " hasta " << *est2 << " es de: " << total;

        delete est1;
        delete est2;

    }
    else
    {
        cout << endl << "Ingresaste una linea inexistente" << endl;
        return;
    }

    delete linea;
}
