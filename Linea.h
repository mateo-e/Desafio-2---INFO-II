#ifndef LINEA_H
#define LINEA_H
#include <string>
#include "Estacion.h"
#include <iostream>
#include <math.h>

using namespace std;

class Linea
{
private:
    string *nombre;
    short int num_estaciones;
    Estacion *primeraEstacion;
    Linea *sig_linea;
public:
    Linea(string *nombre_linea);
    ~Linea();

    // acciones
    void mostrarEstaciones();
    Estacion * buscarEstacion(string *nombre);
    short int posicionarEstacion(string *nombre);
    void agregarEstacion();
    void eliminarEstacion(string *nombre);
    void eliminarTodaEstacion();

    // getters y setters
    string *getNombre();
    void setNombre(string &newNombre);
    short int getNum_estaciones() const;
    void setNum_estaciones(short newNum_estaciones);
    Linea *getSig_linea() const;
    void setSig_linea(Linea *newSig_linea);
    Estacion *getPrimeraEstacion() const;
    void setPrimeraEstacion(Estacion *newPrimeraEstacion);
};

#endif // LINEA_H
