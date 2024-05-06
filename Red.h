#ifndef RED_H
#define RED_H
#include <string>
#include "Linea.h"

using namespace std;

class Red
{
private:
    int num_lineas;
    Linea *primerLinea;

public:
    Red(string *nombrePrimeraLinea);

    // getters
    short int getNum_lineas() const;
    Linea *getPrimerLinea() const;

    // setters
    void setNum_lineas(int *num);
    void setPrimerLinea(Linea *primer);

    // acciones
    Linea *buscarLinea(string *linea);
    void eliminarLinea(string *linea);
    void mostrarLineas();
    void agregarLinea();

    //destructor
};

#endif // RED_H
