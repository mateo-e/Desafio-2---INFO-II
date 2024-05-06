#include <iostream>
#include <string>
#include "Red.h"

void agregar_estacion();

using namespace std;

int main()
{
    cout <<"BIENVENIDO" << endl;
    string * nombre = new string;
    short int opcion;

    cout << "Ingrese el nombre de la primera linea de la red";
    cin >> *nombre;

    Red red(nombre);

    cout << endl << "Se ha creado la red" << endl << endl;

    do
    {
        cout << "Ingrese una opcion: \n1. d";
        switch(opcion)
        {

        }

    }while(opcion != 0);

}
