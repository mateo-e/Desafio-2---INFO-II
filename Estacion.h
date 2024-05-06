#ifndef ESTACION_H
#define ESTACION_H
#include <string>

using namespace std;

class Estacion
{
private:

    string *nombre;
    string *lineas_queCruzan;
    short int *tiempo_siguiente;
    short int *tiempo_anterior;
    Estacion **anterior;
    Estacion **siguiente;

public:
    //constructor
    Estacion(string *nombre, short int *tiempoAnterior,short int *tiempoSiguiente, Estacion *anterior, Estacion *siguiente); // constructor para estacion normal
    Estacion(string *nombre, string *linea, short int *tiempoAnterior, short int *tiempoSiguiente, Estacion *anterior, Estacion *siguiente); // constructor para estacion de transferencia

    //destructor
    ~Estacion();


    //atributos publicos
    short int num_conexiones;
    bool es_transferencia;


    //metodos
    string *getNombre();
    void setNombre(string &newNombre);
    string *getLineas_queCruzan();
    void setLineas_queCruzan(string *newLinea);
    Estacion **getAnterior() const;
    void setAnterior(Estacion *newAnterior,string * linea);
    Estacion **getSiguiente() const;
    void setSiguiente(Estacion *newSiguiente,string * linea);
    short *getTiempo_siguiente() const;
    void setTiempo_siguiente(short *newTiempo_siguiente,string * linea);
    short *getTiempo_anterior() const;
    void setTiempo_anterior(short *newTiempo_anterior,string * linea);
};

#endif // ESTACION_H
