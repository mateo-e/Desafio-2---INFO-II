#include "Red.h"

Red::Red(string nombrePrimeraLinea)
{
    primerLinea = new Linea (nombrePrimeraLinea);
    num_lineas = 1;
}

short int Red::getNum_lineas() const
{
    return num_lineas;
}

Linea *Red::getPrimerLinea() const
{
    return primerLinea;
}

void Red::setNum_lineas(int *num)
{
    num_lineas = *num;
}

void Red::setPrimerLinea(Linea *primer)
{
    primerLinea = primer;
}



