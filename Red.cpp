#include "Red.h"

Red::Red(string * nombrePrimeraLinea)
{
    primerLinea = new Linea (nombrePrimeraLinea);
    num_lineas = 1;
}

short int Red::getNum_lineas() const
{
    return num_lineas;
}

Linea *Red::getPrimerLinea() const
{
    return primerLinea;
}

void Red::setNum_lineas(int *num)
{
    num_lineas = *num;
}

void Red::setPrimerLinea(Linea *primer)
{
    primerLinea = primer;
}

Linea *Red::buscarLinea(string *nombreLinea)
{

}

void Red::eliminarLinea(string *linea)
{
    Linea *remove = buscarLinea(linea);

    remove->~Linea();

    cout << "Se ha eliminado la linea CORRECTAMENTE" << endl ;
}

void Red::mostrarLineas()
{

}

void Red::agregarLinea()
{
    string *nombre = new string;
    cout << endl << "Ingrese el nombre de la nueva linea: ";
    cin >> *nombre;

    Linea *nueva_linea = new Linea(nombre);

    nueva_linea->setSig_linea(primerLinea); // la nueva linea se inserta de primera

    primerLinea = nueva_linea;

    cout << endl << "Se ha creado la nueva linea CORRECTAMENTE";
}




