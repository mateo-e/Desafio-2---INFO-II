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
    Estacion *primeraEstacion;
    Linea *sig_linea;

public:
    // constructores
    Linea(string *nombre_linea); // constructor para cuando es la primera linea de todas
    Linea(string *nombre_linea, Estacion * estacionConexion); // constructor para cuando se une a otra linea por medio de la estacion de tranferencia

    // destructores
    ~Linea();

    // atributos publicos
    short int num_estaciones;
    short int num_estacionesTrans;

    // metodos
    void mostrarEstaciones();
    Estacion * buscarEstacion(string *nombre);
    short int posicionarEstacion(string *nombre);
    void editar_estacion(Estacion *ant, Estacion *sig, Estacion *nueva, short int * tiempo_ant, short int * tiempo_sig);
    void agregarEstacion();
    void eliminarEstacion(string *nombre);
    void eliminarTodaEstacion();

    // getters y setters
    string *getNombre();
    void setNombre(string &newNombre);
    Linea *getSig_linea() const;
    void setSig_linea(Linea *newSig_linea);
    Estacion *getPrimeraEstacion() const;
    void setPrimeraEstacion(Estacion *newPrimeraEstacion);
};

#endif // LINEA_H
