#include <iostream>
#include <string>
#include "Red.h"

void agregarEstacion(Red *red);
void eliminarEstacion(Red *red);
void num_estaciones(Red *red);
void localizarEstacion(Red *red);
void eliminarLinea(Red *red);
void contarEstaciones(Red *red);

using namespace std;

 // unica instancia de red

int main()
{

}

void agregarEstacion(Red *red)
{
    string *linea = new string;

    cout << endl <<"Lineas disponibles: " << endl;

    red->mostrarLineas();

    cout << "Ingrese el nombre de la linea para la nueva estacion (la linea debe existir en la lista anterior): "; cin >> *linea;


    Linea *buscada = red->buscarLinea(linea);
    if(buscada) // si la linea existe
        buscada->agregarEstacion();
    else
    {
        cout << endl << "La linea ingresada no existe, intentelo nuevamente" << endl;
    }

    delete linea;
}

void eliminarEstacion(Red *red)
{
    string *linea = new string;

    cout << endl << "Lineas disponibles: " << endl;

    red->mostrarLineas();

    cout << endl << endl << "Ingrese la linea de la estacion a eliminar: "; cin >> *linea;

    cout << "las estaciones de la linea " << *linea << " son: " << endl;

    Linea *linea_buscada = red->buscarLinea(linea);
    linea_buscada->mostrarEstaciones();

    string *estacion = new string;
    cout << endl << "Ingrese la estacion: "; cin >> *estacion;

    if(linea_buscada->buscarEstacion(estacion)) // si la estacion ingresada existe
        linea_buscada->eliminarEstacion(estacion);

    else
        cout << endl << "Ingresaste una estacion inexistente" << endl;

    delete estacion;
    delete linea;

}

void num_estaciones(Red *red)
{
    string *linea = new string;

    cout << endl << "Ingrese el nombre de la linea: ";
    cin >> *linea;

    Linea *buscada = red->buscarLinea(linea);

    if(buscada)
        cout << endl << "la linea " << *linea << " tiene " << buscada->num_estaciones << " estaciones" << endl;
    else
        cout << endl <<  "Ingresaste el nombre de una linea inexistente." << endl;

    delete linea;
}

void localizarEstacion(Red *red)
{
    string *linea = new string;


    cout << endl << "Ingrese la linea: ";
    cin >> *linea;

    Linea *linea_buscada = red->buscarLinea(linea);

    if(! linea_buscada)
    {
        cout << endl << "Ingresaste una linea inexistene";
        return;
    }

    string * estacion = new string;

    cout << endl << "Ingrese la estacion: ";
    cin >> *estacion;

    if(linea_buscada->posicionarEstacion(estacion) != -1 ) // se verifica la existencia de la estacion dentro de la linea ingresada
        cout << "La estacion " << *estacion << " SI existe dentro de la linea " << *linea;
    else
        cout << "La estacion " << *estacion << " NO existe dentro de la linea " << *linea;

    delete estacion;

    delete linea;
}

void eliminarLinea(Red *red)
{
    string * linea = new string;

    cout << endl << "Ingrese el nombre de la linea a eliminar: ";
    cin >> *linea;

    red->eliminarLinea(linea); // se elimina la linea (todas las comprobaciones necesarias se hacen dentro de la implementacion)

}


void contarEstaciones(Red *red)
{
    short int totalTransferencia, total;

    for(short int i = 0 ; i < red->num_lineas ; i ++)
    {
        total += ((red->getPrimerLinea())+i)->num_estaciones;
        totalTransferencia += ((red->getPrimerLinea())+i)->num_estacionesTrans;
    }

    total -= (totalTransferencia / 2); // cada estacion de transferencia se cuenta dos veces

    cout << endl << "Esta red tiene un total de " << total << "estaciones" << endl;
}

