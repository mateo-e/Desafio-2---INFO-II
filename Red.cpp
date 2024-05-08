#include "Red.h"

Red::Red(string * nombrePrimeraLinea)
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

Linea *Red::buscarLinea(string *nombreLinea)
{
    Linea *actual = primerLinea;

    for(int i = 0; i < num_lineas ; i ++)
    {
        if(*(actual->getNombre()) == *nombreLinea)
            return actual;
        actual = actual->getSig_linea();
    }

    return NULL; // en caso de no encontrar la linea especificada
}

void Red::eliminarLinea(string *linea)
{
    Linea *remove = buscarLinea(linea);

    if(remove->eliminarTodaEstacion()) // si la linea no tiene estaciones de transferencia
    {
        remove->~Linea();
        cout << "Se ha eliminado la linea CORRECTAMENTE" << endl ;
    }


}

void Red::mostrarLineas()
{
    cout << endl;
    Linea *actual = primerLinea; // se inicializa

    for(int i = 0; i < num_lineas; i ++ )
    {
        cout << "-> " << *(actual->getNombre()) << endl; // se imprime cada nombre de las lineas

        actual = actual->getSig_linea(); // se pasa a la siguiente linea
    }

    cout << endl;
}

void Red::agregarLinea()
{
    string *nueva = new string, aux;
    cout << endl << "Ingrese el nombre de la nueva linea: ";
    cin >> *nueva;

    if(buscarLinea(nueva) != NULL) // si la linea ya existe
    {
        cout << endl << "Esta linea ya existe" << endl;
        return;
    }

    cout << endl << endl << "Mostrando lineas disponibles...";

    mostrarLineas();

    cout << "Ingrese el nombre de la linea con que linea quiere conectar a "<<*nueva<<" (ingrese 'r' para salir): ";
    cin>>aux;

    if(aux == "r") //salida
        return;

    Linea *linea_conexion = buscarLinea(&aux);

    if(linea_conexion == NULL) // si la linea ingresada no existe
    {
        cout << endl << "Ingresaste una linea inexistente" << endl;
        return;
    }


    else if(linea_conexion->num_estacionesTrans == 0) // si no tiene ninguna estacion de transferencia
    {
        cout << "Esta linea no tiene ninguna estacion de tranferencia, cree una antes de continuar";
        return;
    }

    // se imprimen solo las estaciones de transferencia de la linea con la cual se quiere conectar


    Estacion *actual = linea_conexion->getPrimeraEstacion();

    for(int i = 0; i < linea_conexion->num_estaciones; i++) // se muestran las estaciones de tranferencia de la linea de conexion
    {
        if(actual->es_transferencia)
            cout << "-> " << *(actual->getNombre()) << endl;

        actual = actual->getSiguiente();
        cout << endl;
    }


    cout << "Nombre la estacion con la cual quiere conectar a la nueva linea (ingrese 'r' para salir): "; cin>>aux;

    if(aux == "r")
        return;


    Estacion * estacionConexion = linea_conexion->buscarEstacion(&aux); // se busca la estacion ingresada

    if(estacionConexion == NULL)
    {
        cout << endl << "Ingresaste una estacion inexistente" << endl;
        return;
    }

    else if(! estacionConexion->es_transferencia) // si se ingresa una estacion que no es de transferencia
    {
        cout << endl << "Ingresaste una estacion que no es de transferencia" << endl;
        return;
    }


    // se rellena cada uno de los espacion de la estacion de tranferencia seleccionada
    // cada uno de estos espacios se indexa con ayuda del nombre de la nueva linea y se agrega al arreglo correspondiente
    estacionConexion->num_conexiones++;

    if(estacionConexion->num_conexiones % 10 == 0) // si se llega a un tope en el tamaño de las conexiones (este tamaño se aumenta de 10 en 10)
        estacionConexion->redimensionar();

    estacionConexion->setLineas_queCruzan(nueva);
    estacionConexion->setAnterior(nullptr,nueva);
    estacionConexion->setSiguiente(nullptr,nueva);
    estacionConexion->setTiempo_anterior(nullptr,nueva);
    estacionConexion->setTiempo_siguiente(nullptr,nueva);



    Linea *nueva_linea = new Linea(nueva,estacionConexion);

    nueva_linea->setSig_linea(primerLinea); // la nueva linea se inserta de primera en la red


    primerLinea = nueva_linea;

    num_lineas++;

    cout << endl << "Se ha creado la nueva linea CORRECTAMENTE";
}

void Red::calcularTiempos()
{
    cout << endl << "Lineas disponibles..." << endl;
    mostrarLineas();

    string *linea = new string;

    cout << endl << "Ingrese la linea a recorrer: "; cin >> *linea;

    Linea * linea_buscada = buscarLinea(linea);

    if(linea_buscada) // si la linea ingresada existe
    {

        string * est1 = new string, *est2 = new string;

        cout << endl << "Estaciones de la linea"<< *linea << " disponibles: ";

        linea_buscada->mostrarEstaciones();

        Estacion *inicio, *final;

        cout << endl << "Ingrese la estacion de inicio: "; cin >> *est1;

        inicio = linea_buscada->buscarEstacion(est1);

        if(inicio == NULL)
        {
            cout << endl << "Ingresaste una estacion inexistente";
            return;
        }

        cout << endl << "Ingrese la estacion de fin: "; cin >> *est2;

        final = linea_buscada->buscarEstacion(est2);

        if(final == NULL)
        {
            cout << endl << "Ingresaste una estacion inexistente";
            return;
        }

        short int pos_1,pos_2,total = 0;

        pos_1 = linea_buscada->posicionarEstacion(est1); // se busca las posiciones con respecto al primera puntero de la linea
        pos_2 = linea_buscada->posicionarEstacion(est2);

        if(pos_1 < pos_2) // si la primera estacion se encuentra primero se usan los punteros 'siguientes'
        {
            while(inicio != final)
            {
                if(inicio->es_transferencia)
                {
                    for(short int i = 0; i < inicio->num_conexiones; i++) // se manda a indexar el siguiente camino y su tiempo por medio del nombre de la linea actual
                    {
                        if(inicio->getLineas_queCruzan(&i) == *linea) // se busca la posicion del nombre de esta linea dentro de este arreglo
                        {
                            total += inicio->getTiempo_siguiente(&i); // se indexa esa posicion una vez encontrada
                            inicio = inicio->getSiguiente(&i);
                            break;
                        }
                    }
                }
                else
                {
                    total += inicio->getTiempo_siguiente();
                    inicio = inicio->getSiguiente(); // se direcciona este puntero al siguiente
                }
            }
        }
        else // si la segunda estacion se encuentra primero se usan los punteros 'anteriores'
        {
            while(inicio != final)
            {
                if(inicio->es_transferencia)
                {
                    for(short int i = 0; i < inicio->num_conexiones; i++) // se manda a indexar el siguiente camino y su tiempo por medio del nombre de la linea actual
                    {
                        if(inicio->getLineas_queCruzan(&i) == *linea) // se busca la posicion del nombre de esta linea dentro de este arreglo
                        {
                            total += inicio->getTiempo_anterior(&i); // se indexa esa posicion una vez encontrada
                            inicio = inicio->getAnterior(&i);
                            break;
                        }
                    }
                }
                else
                {
                    total += inicio->getTiempo_anterior();
                    inicio = inicio->getAnterior(); // se direcciona este puntero al siguiente
                }
            }
        }

        // una vez se tiene el total:

        cout << endl << "El tiempo para llegar desde la estacion " << *est1 << " hasta " << *est2 << " es de: " << total;

        delete est1;
        delete est2;

    }
    else
    {
        cout << endl << "Ingresaste una linea inexistente" << endl;
        return;
    }

    delete linea;
}




