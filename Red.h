#ifndef RED_H
#define RED_H
#include <string>
#include "Linea.h"

using namespace std;

class Red
{
private:
    Linea *primerLinea;

public:
    Red(string *nombrePrimeraLinea);

    // atributo publico
    int num_lineas;

    // getters
    short int getNum_lineas() const;
    Linea *getPrimerLinea() const;

    // setters
    void setNum_lineas(int *num);
    void setPrimerLinea(Linea *primer);

    // metodos
    Linea *buscarLinea(string *linea);
    void eliminarLinea(string *linea);
    void mostrarLineas();
    void agregarLinea();
    void calcularTiempos();

};

#endif // RED_H
