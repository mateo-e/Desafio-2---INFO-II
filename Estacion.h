#ifndef ESTACION_H
#define ESTACION_H
#include <string>

using namespace std;

class Estacion
{
protected:

    string *nombre;
    string *lineas_queCruzan;
    bool es_transferencia;
    short int num_conexiones;
    short int *tiempo_siguiente;
    short int *tiempo_anterior;
    Estacion **anterior;
    Estacion **siguiente;

public:
    Estacion(string *nombre, short int *tiempoAnterior,short int *tiempoSiguiente, Estacion *anterior, Estacion *siguiente); // constructor para estacion normal
    Estacion(string *nombre, string *linea, short int *tiempoAnterior, short int *tiempoSiguiente, Estacion *anterior, Estacion *siguiente); // constructor para estacion de transferencia

    //destructor
    ~Estacion();


    string *getNombre();
    void setNombre(string &newNombre);
    bool getEs_transferencia() const;
    void setEs_transferencia(bool newEs_transferencia);
    short getNum_conexiones() const;
    void setNum_conexiones(short newNum_conexiones);
    string *getLineas_queCruzan() const;
    void setLineas_queCruzan(string *newLinea);
    Estacion **getAnterior() const;
    void setAnterior(Estacion *newAnterior);
    Estacion **getSiguiente() const;
    void setSiguiente(Estacion *newSiguiente);
    short *getTiempo_siguiente() const;
    void setTiempo_siguiente(short *newTiempo_siguiente, short int pos);
    short *getTiempo_anterior() const;
    void setTiempo_anterior(short *newTiempo_anterior, short int pos);
};

#endif // ESTACION_H
