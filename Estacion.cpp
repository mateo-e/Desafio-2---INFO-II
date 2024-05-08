#include "Estacion.h"


string *Estacion::getNombre()
{
    return nombre;
}

void Estacion::setNombre(string &newNombre)
{
    delete[] nombre; // se libera el anterior
    nombre = &newNombre;
}


string Estacion::getLineas_queCruzan(short int * pos)
{
    return lineas_queCruzan[*pos];
}

void Estacion::setLineas_queCruzan(string *newLinea)
{
    lineas_queCruzan[num_conexiones] = *newLinea;
}

Estacion *Estacion::getAnterior(short *pos)
{
    return anterior[*pos];
}

Estacion *Estacion::getAnterior()
{
    return anterior[0];
}

void Estacion::setAnterior(Estacion *newAnterior,string *linea)
{
    if(num_conexiones % 10 == 0) // si se supera la capacidad de los arreglos actuales
        redimensionar();

    // se indexa la linea actual(necesario para estaciones de tranferencia)

    if(es_transferencia)
    {
        for(short int i = 0; i < num_conexiones; i++)
        {
            if(lineas_queCruzan[i] == *linea)
            {
                anterior[i] = newAnterior;
                break;
            }
        }

    }
    else
        anterior[0] = newAnterior;
}

Estacion *Estacion::getSiguiente(short int *pos)
{
    return siguiente[*pos];
}

Estacion *Estacion::getSiguiente()
{
    return siguiente[0];
}

void Estacion::setSiguiente(Estacion *newSiguiente,string *linea)
{
    if(num_conexiones % 10 == 0) // si se supera la capacidad de los arreglos actuales
        redimensionar();

    // se indexa la linea actual(necesario para estaciones de tranferencia)

    if(es_transferencia)
    {
        for(short int i = 0; i < num_conexiones; i++)
        {
            if(lineas_queCruzan[i] == *linea)
            {
                siguiente[i] = newSiguiente;
                break;
            }
        }

    }
    else
        siguiente[0] = newSiguiente;
}

// estacion normal
short Estacion::getTiempo_siguiente(short int * pos)
{
    return tiempo_siguiente[*pos];
}

short Estacion::getTiempo_siguiente()
{
    return tiempo_siguiente[0];
}

void Estacion::setTiempo_siguiente(short *newTiempo_siguiente, string * linea)
{
    if(num_conexiones % 10 == 0) // si se supera la capacidad de los arreglos actuales
        redimensionar();

    // se indexa la linea actual(necesario para estaciones de tranferencia)

    if(es_transferencia)
    {
        for(short int i = 0; i < num_conexiones; i++)
        {
            if(lineas_queCruzan[i] == *linea)
            {
                tiempo_siguiente[i] = *newTiempo_siguiente;
                break;
            }
        }


    }
    else
        tiempo_siguiente[0] = *newTiempo_siguiente;
}

short Estacion::getTiempo_anterior(short int *pos)
{
    return tiempo_anterior[*pos];
}

short Estacion::getTiempo_anterior()
{
    return tiempo_anterior[0];
}

void Estacion::redimensionar()
{
    // se copia 1 por uno cada uno de los elementos del arreglo


    string *lineas_queCruzan_nueva = new string [num_conexiones + 10];

    for(short int i = 0; i < num_conexiones; i ++)
        lineas_queCruzan_nueva[i] = lineas_queCruzan[i];

    delete[] lineas_queCruzan; // se borra la original

    lineas_queCruzan = lineas_queCruzan_nueva; // se asigna la nueva

    short int *tiempo_siguiente_nueva = new short int[num_conexiones + 10];

    for(short int i = 0; i < num_conexiones; i ++)
        tiempo_siguiente_nueva[i] = tiempo_siguiente[i];
    delete[] tiempo_siguiente; // se borra la original
    tiempo_siguiente = tiempo_siguiente_nueva; // se asigna la nueva

    short int *tiempo_anterior_nueva = new short int[num_conexiones + 10];

    for(short int i = 0; i < num_conexiones; i ++)
        tiempo_anterior_nueva[i] = tiempo_anterior[i];
    delete[] tiempo_anterior; // se borra la original
    tiempo_anterior = tiempo_anterior_nueva; // se asigna la nueva

    Estacion **anterior_nueva = new Estacion * [num_conexiones + 10];

    for(short int i = 0; i < num_conexiones; i ++)
        anterior_nueva[i] = anterior[i];
    delete[] anterior; // se borra la original
    anterior = anterior_nueva; // se asigna la nueva

    Estacion **siguiente_nueva = new Estacion * [num_conexiones + 10];

    for(short int i = 0; i < num_conexiones; i ++)
        siguiente_nueva[i] = siguiente[i];
    delete[] siguiente; // se borra la original
    siguiente = siguiente_nueva; // se asigna la nueva

}

void Estacion::setTiempo_anterior(short  *newTiempo_anterior,string * linea)
{
    if(num_conexiones % 10 == 0) // si se supera la capacidad de los arreglos actuales (la capacidad es un multiplo de 10)
        redimensionar();

    // se indexa la linea actual(necesario para estaciones de tranferencia)

    if(es_transferencia)
    {
        for(short int i = 0; i < num_conexiones; i++)
        {
            if(lineas_queCruzan[i] == *linea)
            {
                tiempo_anterior[i] = *newTiempo_anterior;
                break;
            }
        }
    }
    else
        tiempo_anterior[0] = *newTiempo_anterior;
}

Estacion::Estacion(string *nombre, short *tiempoAnterior_, short *tiempoSiguiente_, Estacion *anterior, Estacion *siguiente)
{
    this->nombre = nombre;

    es_transferencia = false;

    num_conexiones = 1; 


    this->tiempo_anterior = new short int [1];

    if(tiempoAnterior_)
        this->tiempo_anterior = tiempoAnterior_;

    this->tiempo_siguiente = new short int [1];

    if(tiempoSiguiente_)
        this->tiempo_siguiente = tiempoSiguiente_;

    this->anterior = new Estacion * [1];

    this->anterior[0] = anterior;

    this->siguiente = new Estacion * [1];

    this->siguiente[0] = siguiente;

}

// estacion de transferencia
Estacion::Estacion(string *nombre, string *linea, short int *tiempoAnterior_,short int *tiempoSiguiente_, Estacion *anterior, Estacion *siguiente)
{
    this->nombre = nombre;

    this->es_transferencia = true;

    num_conexiones = 1;

    this->lineas_queCruzan = new string [10];
    this->lineas_queCruzan[0] = *linea; // se agrega la primera linea desde la cual se está creando la estacion


    this->tiempo_anterior = new short int[10];

    if(tiempoAnterior_)// si ese valor no es nulo
        this->tiempo_anterior[0] = *tiempoAnterior_;

    this->tiempo_siguiente = new short int[10];

    if(tiempoSiguiente_)// si ese valor no es nulo
        this->tiempo_siguiente[0] = *tiempoSiguiente_;

    // se guardan los punteros anteriores y siguientes dependiendo de la linea por la cual se esté recorriendo
    this->anterior = new Estacion * [10];

    this->anterior[0] = anterior;

    this->siguiente = new Estacion * [10];

    this->siguiente[0] = siguiente;
}

Estacion::~Estacion()
{
    if(this->es_transferencia)
        delete[] lineas_queCruzan;

    delete[] tiempo_siguiente;
    delete[] tiempo_anterior;
    delete[] anterior;
    delete[] siguiente;
}
