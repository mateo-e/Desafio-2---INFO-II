#include "Linea.h"

string Linea::getNombre() const
{
    return nombre;
}

void Linea::setNombre(const string &newNombre)
{
    nombre = newNombre;
}

short int Linea::getNum_estaciones() const
{
    return num_estaciones;
}

void Linea::setNum_estaciones(short newNum_estaciones)
{
    num_estaciones = newNum_estaciones;
}

Linea *Linea::getSig_linea() const
{
    return sig_linea;
}

void Linea::setSig_linea(Linea *newSig_linea)
{
    sig_linea = newSig_linea;
}

Estacion *Linea::getPrimeraEstacion() const
{
    return primeraEstacion;
}

void Linea::setPrimeraEstacion(Estacion *newPrimeraEstacion)
{
    primeraEstacion = newPrimeraEstacion;
}

Linea::Linea(string nombre)
{
    this->nombre = nombre;
    num_estaciones = 0;
    primeraEstacion = NULL;
    sig_linea = NULL;
}

