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
    Estacion(string *nombre, short int *tiempoAnterior_, short int *tiempoSiguiente_, Estacion *anterior, Estacion *siguiente); // constructor para estacion normal
    Estacion(string *nombre, string *linea, short int *tiempoAnterior_, short int *tiempoSiguiente_, Estacion *anterior, Estacion *siguiente); // constructor para estacion de transferencia

    //destructor
    ~Estacion();


    //atributos publicos
    short int num_conexiones;
    bool es_transferencia;


    //metodos
    string *getNombre();
    void setNombre(string &newNombre);
    string getLineas_queCruzan(short *pos);
    void setLineas_queCruzan(string *newLinea);
    Estacion *getAnterior(short *pos);
    Estacion *getAnterior();
    void setAnterior(Estacion *newAnterior,string * linea);
    Estacion *getSiguiente(short *pos);
    Estacion *getSiguiente();
    void setSiguiente(Estacion *newSiguiente,string * linea);
    short getTiempo_siguiente(short int *pos);
    short getTiempo_siguiente();
    void setTiempo_siguiente(short *newTiempo_siguiente,string * linea);
    short getTiempo_anterior(short int *pos);
    short getTiempo_anterior();
    void redimensionar();
    void setTiempo_anterior(short *newTiempo_anterior,string * linea);
};

#endif // ESTACION_H
