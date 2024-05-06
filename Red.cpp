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

    remove->eliminarTodaEstacion();

    remove->~Linea();

    cout << "Se ha eliminado la linea CORRECTAMENTE" << endl ;
}

void Red::mostrarLineas()
{


}

void Red::agregarLinea()
{
    string *nueva = new string, aux;
    cout << endl << "Ingrese el nombre de la nueva linea: ";
    cin >> *nueva;

    cout << endl << "Ingrese el nombre de la linea con que linea quiere conectar a (ingrese 'r' para regresar)" << *nueva << endl;

    mostrarLineas();
    cin>>aux;

    if(aux == "r")
        return;

    Linea *linea_conexion = buscarLinea(&aux);

    if(linea_conexion == NULL) // si no se encuentra la linea ingresada
    {
        cout << "Ingresaste una liena inexistente";
        return;
    }
    else if(linea_conexion->num_estacionesTrans == 0) // si no tiene ninguna estacion de transferencia
    {
        cout << "Esta linea no tiene ninguna estacion de tranferencia, cree una";
        return;
    }


    cout << "Seleccione la estacion con la cual quiere conectar a la linea";

    for(int i = 0; i < linea_conexion->num_estacionesTrans; i++) // se muestran las estaciones de tranferencia de la linea de conexion
    {
        if((linea_conexion->getPrimeraEstacion()[i]).es_transferencia)
            cout << *(linea_conexion->getPrimeraEstacion()[i].getNombre()) << endl;
    }


    cout << "Estacion (ingrese 'r' para regresar): "; cin>>aux;

    if(aux == "r")
        return;


    Estacion * estacionConexion = linea_conexion->buscarEstacion(&aux); // se busca la estacion ingresada

    if(estacionConexion == NULL)
    {
        cout << endl << "Ingresaste una estacion inexistente" << endl;
        return;
    }

    estacionConexion->setLineas_queCruzan(nueva);


    // se rellena cada uno de los espacion de la estacion de tranferencia seleccionada
    // cada uno de estos espacios se indexa con ayuda del nombre de la nueva linea y se agrega al arreglo correspondiente
    estacionConexion->setAnterior(nullptr,nueva);
    estacionConexion->setSiguiente(nullptr,nueva);
    estacionConexion->setTiempo_anterior(nullptr,nueva);
    estacionConexion->setTiempo_siguiente(nullptr,nueva);


    Linea *nueva_linea = new Linea(nueva,estacionConexion);

    nueva_linea->setSig_linea(primerLinea); // la nueva linea se inserta de primera en la red

    primerLinea = nueva_linea;

    num_lineas++;

    cout << endl << "Se ha creado la nueva linea CORRECTAMENTE";
}




