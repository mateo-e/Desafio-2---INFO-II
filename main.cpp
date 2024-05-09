#include <iostream>
#include <string>
#include "Red.h"

void agregarEstacion(Red *red);
void eliminarEstacion(Red *red);
void num_estaciones(Red *red);
void localizarEstacion(Red *red);
void eliminarLinea(Red *red);
void contarEstaciones(Red *red);
bool buscarEnArreglo(Estacion **, Estacion *, short int *);

using namespace std;

 // unica instancia de red

int main()
{
    cout <<"BIENVENIDO" << endl;
    string * nombre = new string;
    short int band = 1;

    cout << "Ingrese el nombre de la primera linea de la red: ";
    cin >> *nombre;

    Red red(nombre);

    cout << endl << "Se ha creado la red" << endl;

    do
    {
        cout << endl <<  "Ingrese una opcion: \n1. Agregar una estacion a una linea \n2. Eliminar una estacion de una linea \n3. Saber cuantas lineas tiene la red \n4. Saber cuantas estaciones tiene una linea dada \n5. Saber si una estacion dada pertenece a una linea especifica \n6. Agregar una linea a la red \n7. Eliminar una linea de la red \n8. Saber cuantas estaciones tiene una red \n9. Calcular tiempo de llegada \n0. Salir \n\nOpcion: ";
        cin >> band;

        switch(band)
        {
        case 1:
            cout << endl << "Seleccionaste Agregar una Estacion" << endl;
            agregarEstacion(&red);
            break;

        case 2:
            cout << endl << "Seleccionaste eliminar estacion" << endl;
            eliminarEstacion(&red);
            break;

        case 3:
            cout << endl << "Seleccionaste numero de lineas" << endl;
            cout << endl << "La red actual tiene un total de " << red.num_lineas << " lineas." << endl;
            break;

        case 4:
            cout << endl << "Seleccionaste numero de estaciones" << endl;
            num_estaciones(&red);
            break;

        case 5:
            cout << endl << "Seleccionaste localizar estacion" << endl;
            localizarEstacion(&red);
            break;

        case 6:
            cout << endl << "Seleccionaste agregar linea" << endl;
            red.agregarLinea();
            break;

        case 7:
            cout << endl << "Seleccionaste eliminar linea" << endl;
            eliminarLinea(&red);
            break;

        case 8:
            cout << endl << "Seleccionaste contar estaciones" << endl;
            contarEstaciones(&red);
            break;

        case 9:
            cout << endl << "Seleccionaste calcular tiempos" << endl;
            red.calcularTiempos();
            break;

        case 0:
            cout << endl << "Seleccionaste Salir del sistema, hasta luego" << endl;
            break;

        default:
            cout << "Numero fuera del rango valido" << endl;
        }



        cout << endl;

    }while(band != 0);


    return 0;
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
    short int totalTransferencia = 0, total = 0;

    Linea * actual = (red->getPrimerLinea());

    for(short int i = 0 ; i < red->num_lineas ; i ++)
    {// se hace un numero maximo de estaciones de transferencia posible
        totalTransferencia += actual->num_estacionesTrans;
        actual = actual->getSig_linea(); // se redirecciona a la siguiente luego de sumar las estaciones
    }

    short int cont = 0;
    Estacion ** visitadas = new Estacion * [totalTransferencia]; // se crea un arreglo donde se guardan las direcciones de las estaciones de tranferencia visitadas

    actual = (red->getPrimerLinea()); // se reinicia de nuevo el ciclo

    for(short int i = 0 ; i < red->num_lineas ; i ++)
    {

        if(actual->num_estacionesTrans > 0) // si tiene mas de una estacion de transferencia
        {
            Estacion * estacion_act = actual->getPrimeraEstacion();

            for(short int u = 0; u < actual->num_estacionesTrans;)
            {
                if(estacion_act->es_transferencia)
                {
                    if(! buscarEnArreglo(visitadas,estacion_act,&totalTransferencia)) // busco si esta estacion ya fue contada anteriormente
                    {
                        total++; // se cuenta la transferencia actual
                        visitadas[cont] = estacion_act;
                        cont++;
                    }
                    u++;

                }
                estacion_act = estacion_act->getSiguiente(); // se pasa a la siguiente estacion

                if(estacion_act == NULL) // si se llega al final
                    break;
            }
        }
        total += actual->num_estaciones - actual->num_estacionesTrans; // ya se contaron las estaciones de transferencia, es por eso que se restan de las totales
        actual = actual->getSig_linea(); // se redirecciona a la siguiente luego de sumar las estaciones
    }

    delete[] visitadas;
    cout << endl << "Esta red tiene un total de " << total << " estaciones" << endl;
}

bool buscarEnArreglo(Estacion ** arr, Estacion * buscada, short int * tam)
{
    for(short int i = 0; i < *tam; i++)
    {
        if(*(arr+i) == buscada)
            return true; // si se encuentra la estacion buscada
    }

    return false;
}
