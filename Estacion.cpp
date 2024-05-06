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

bool Estacion::getEs_transferencia() const
{
    return es_transferencia;
}

void Estacion::setEs_transferencia(bool newEs_transferencia)
{
    es_transferencia = newEs_transferencia;
}

short Estacion::getNum_conexiones() const
{
    return num_conexiones;
}

void Estacion::setNum_conexiones(short newNum_conexiones)
{
    num_conexiones = newNum_conexiones;
}

string *Estacion::getLineas_queCruzan() const
{
    return lineas_queCruzan;
}

void Estacion::setLineas_queCruzan(string *newLinea)
{
    lineas_queCruzan[num_conexiones] = *newLinea;
}

Estacion **Estacion::getAnterior() const
{
    return anterior;
}

void Estacion::setAnterior(Estacion *newAnterior)
{
    anterior[num_conexiones] = newAnterior;
}

Estacion **Estacion::getSiguiente() const
{
    return siguiente;
}

void Estacion::setSiguiente(Estacion *newSiguiente)
{
    siguiente[0] = newSiguiente;
}

// estacion normal
short *Estacion::getTiempo_siguiente() const
{
    return tiempo_siguiente;
}

void Estacion::setTiempo_siguiente(short *newTiempo_siguiente, short int pos)
{
    tiempo_siguiente[pos] = *newTiempo_siguiente;
}

short *Estacion::getTiempo_anterior() const
{
    return tiempo_anterior;
}

void Estacion::setTiempo_anterior(short *newTiempo_anterior,short int pos)
{
    tiempo_anterior[pos] = *newTiempo_anterior;
}

Estacion::Estacion(string *nombre, short *tiempoAnterior, short *tiempoSiguiente, Estacion *anterior, Estacion *siguiente)
{
    this->nombre = nombre;

    es_transferencia = false;

    num_conexiones = 1;

    this->tiempo_anterior = new short int [1];
    this->tiempo_anterior = tiempoAnterior;

    this->tiempo_siguiente = new short int [1];
    this->tiempo_siguiente = tiempoSiguiente;

    this->anterior = new Estacion * [1];
    this->anterior[0] = anterior;

    this->siguiente = new Estacion * [1];
    this->siguiente[0] = siguiente;

}

// estacion de transferencia
Estacion::Estacion(string *nombre, string *linea, short int *tiempoAnterior,short int *tiempoSiguiente, Estacion *anterior, Estacion *siguiente)
{
    this->nombre = nombre;

    this->es_transferencia = true;

    num_conexiones = 1;

    this->lineas_queCruzan = new string [10];
    this->lineas_queCruzan[0] = *linea; // se agrega la primera linea desde la cual se está creando la estacion


    this->tiempo_anterior = new short int[10];
    this->tiempo_anterior[0] = *tiempoAnterior;

    this->tiempo_siguiente = new short int[10];
    this->tiempo_siguiente[0] = *tiempoSiguiente;

    // se guardan los punteros anteriores y siguientes dependiendo de la linea por la cual se esté recorriendo
    this->anterior = new Estacion * [10];
    this->anterior[0] = anterior;

    this->siguiente = new Estacion * [10];
    this->siguiente[0] = siguiente;
}

Estacion::~Estacion()
{
    delete[] lineas_queCruzan;
    delete[] tiempo_siguiente;
    delete[] tiempo_anterior;
    delete[] anterior;
    delete[] siguiente;
}
