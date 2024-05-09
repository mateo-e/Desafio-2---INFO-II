#include "Linea.h"

string *Linea::getNombre()
{
    return nombre;
}

void Linea::setNombre(string &newNombre)
{
    nombre = &newNombre;
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


// constructor para cuando es la primera linea de toda la red
Linea::Linea(string *nombre_linea)
{
    this->nombre = nombre_linea;
    num_estaciones = 0; // el valor aumenta dentro de 'agregarEstacion'
    num_estacionesTrans = 0;
    sig_linea = NULL;
    agregarEstacion(); // se agrega la primera estacion
}

Linea::Linea(string *nombre_linea, Estacion *estacionConexion)
{
    this->nombre = nombre_linea;
    num_estaciones = 1;
    num_estacionesTrans = 1;
    sig_linea = NULL;

    primeraEstacion = estacionConexion;
}

Linea::~Linea()
{
    // antes de su invocacion se libera la memoria dinamica creada en cada estacion
}

void Linea::mostrarEstaciones()
{
    Estacion *actual = primeraEstacion; // se inicializa el puntero que direcciona

    for(short int i = 0; i < num_estaciones; i ++)
    {
        if(actual->es_transferencia)
        {
            cout<< "-> " << *(actual->getNombre()) << " - " << *(this->nombre) << endl; // se concatena el nombre de la linea en caso de ser de transferencia

            for(short int u = 0; u < actual->num_conexiones; u++)
            {
                if(actual->getLineas_queCruzan(&u) == *(this->nombre)) // se indexa el nombre de la linea actual dentro de las conexiones de la estacion de tranferenia actual
                {
                    actual = actual->getSiguiente(&u);
                    break;
                }
            }
        }
        else // en caso de no ser de transferencia se imprime normal
        {
            cout<< "-> " << *(actual->getNombre()) << endl;
            actual = actual->getSiguiente();
        }
    }

}

Estacion *Linea::buscarEstacion(string *nombre)
{
    Estacion *actual = primeraEstacion;// se inicializa la estacion actual

    for(short int i = 0; i < num_estaciones; i ++)
    {
        if( *(actual->getNombre()) == *nombre)
            return actual; // en caso de encontrar la estacion con el mismo nombre

        if(actual->es_transferencia)
        {
            for(short int u = 0; u < actual->num_conexiones; u++)
            {
                if(actual->getLineas_queCruzan(&u) == *(this->nombre)) // se indexa el nombre de la linea actual dentro de las conexiones de la estacion de tranferenia actual
                {
                    actual = actual->getSiguiente(&u);
                    break;
                }
            }
        }
        else // en caso de no ser de transferencia se imprime normal
            actual = actual->getSiguiente();
    }

    return NULL; // en caso de no encontrar la estacion
}

short int Linea::posicionarEstacion(string *nombre)
{
    Estacion *actual = primeraEstacion;

    // en caso que se quiera saber la posicion de la estacion
    for(short int i = 0; i < num_estaciones; i ++)
    {
        if( *(actual->getNombre()) == *nombre)
            return i; // en caso de encontrar la estacion con el mismo nombre

        if(actual->es_transferencia)
        {
            for(short int u = 0; u < actual->num_conexiones; u++)
            {
                if(actual->getLineas_queCruzan(&u) == *(this->nombre) && actual) // se indexa el nombre de la linea actual dentro de las conexiones de la estacion de tranferenia actual
                {
                    actual = actual->getSiguiente(&u);
                    break;
                }
            }
        }
        else
            actual = actual->getSiguiente();


    }

    return -1; // en caso de no encontrar la estacion
}

void Linea::editar_estacion(Estacion *ant, Estacion *sig, Estacion *nueva, short *tiempo_ant, short *tiempo_sig)
{
    if(ant != nullptr) // si es una estacion del borde este valor podra ser nulo
    {
        ant->setSiguiente(nueva,this->nombre); // se redireccionan la estacion anterior y siguiente
        ant->setTiempo_siguiente(tiempo_ant,this->nombre);
    }

    if(sig != nullptr) // si es una estacion del borde este valor podra ser nulo
    {
        sig->setAnterior(nueva,this->nombre);
        sig->setTiempo_anterior(tiempo_sig,this->nombre);
    }
}

void Linea::agregarEstacion()
{
    // se imprimen las estaciones de la linea actual,
    int opcion;
    if(num_estaciones > 1) // si existe mas de dos estaciones
    {
        cout << endl << "Ingrese la ubicacion de la nueva estacion " <<  endl;

        cout << "1 - Principio" << endl << "2 - Final" << endl << "3 - Entre estaciones" << endl << "Opcion: ";
        cin >> opcion;
    }
    else if(num_estaciones > 0) // si existe por lo menos una estacion
    {
        cout << endl << "Ingrese la ubicacion de la nueva estacion " <<  endl;

        cout << "1 - Principio" << endl << "2 - Final" << endl << "Opcion: ";
        cin >> opcion;

        if(opcion > 2)
        {
            cout << "ingresaste una opcion invalida";
            return;
        }
    }
    else // si no existe ninguna estacion se manda directamente a la opcion 1
        opcion = 1;

    cout<< endl << endl;

    switch(opcion)
    {
    case 1:
    {
        string *nombre = new string;

        if(num_estaciones == 0)
            cout << "Se esta creando la primera estacion" << endl;

        do
        {
            cout << endl << "Ingrese el nombre de la nueva estacion (debe ser una estacion inexistente): ";
            cin >> *nombre;
        }while(posicionarEstacion(nombre) != -1); // si la estacion ya existia

        char aux;
        cout << endl << "La estacion podra ser usada de transferencia en el futuro? (y/n): ";
        cin >> aux;



        if(num_estaciones > 0)
        {
            short int * tiempo = new short int;

            cout << "Ingrese el tiempo de la estacion " << *nombre << " hacia la estacion " << *(this->getPrimeraEstacion()->getNombre()) << ": ";
            cin >> *tiempo;

            Estacion *nueva_estacion;

            if(aux == 'y') // si es de tranferencia
            {
                nueva_estacion = new Estacion(nombre,this->getNombre(),nullptr,tiempo,nullptr,primeraEstacion);
                num_estacionesTrans ++;
            }
            else
                nueva_estacion = new Estacion(nombre,nullptr,tiempo,nullptr,primeraEstacion);


            editar_estacion(nullptr,this->getPrimeraEstacion(),nueva_estacion,nullptr,tiempo);

            primeraEstacion = nueva_estacion;
        }

        else
        {
            if(aux == 'y')
            {
                primeraEstacion = new Estacion(nombre,this->getNombre(),nullptr,nullptr,nullptr,nullptr);
                num_estacionesTrans ++;
            }
            else
                primeraEstacion = new Estacion (nombre,nullptr,nullptr,nullptr,nullptr); // inicializacion de la primera de todas las estaciones
        }
        num_estaciones ++;
        cout << endl << "Se ha creado la nueva estacion CORRECTAMENTE" << endl;



        break;

    }

    case 2:
    {
        string *nombre = new string;
        short int * tiempo = new short int;

        do
        {
            cout << endl << "Ingrese el nombre de la nueva estacion: ";
            cin >> *nombre;
        }while(posicionarEstacion(nombre) != -1); // si la estacion ya existia

        char aux;
        cout << endl << "La estacion podra ser usada de transferencia en el futuro? (y/n): ";
        cin >> aux;

        // se halla la ultima estacion
        Estacion *ultimaEstacion = primeraEstacion;

        for(short int i = 0; i < num_estaciones; i++)
        {
            if(! ultimaEstacion->getSiguiente()) // si ya no se puede seguir avanzando
                break;
            ultimaEstacion = ultimaEstacion->getSiguiente();// si todavia faltan estaciones
        }

        cout << "Ingrese el tiempo de la estacion " << *nombre << " hacia la estacion " << *(ultimaEstacion->getNombre()) << ": ";
        cin >> *tiempo;

        Estacion *nueva_estacion;

        if(aux == 'y') // si es de transferencia
        {
            nueva_estacion = new Estacion(nombre,this->getNombre(),tiempo,nullptr,ultimaEstacion,nullptr);
            num_estacionesTrans ++;
        }
        else
            nueva_estacion = new Estacion(nombre,tiempo,nullptr,ultimaEstacion,nullptr); // la nueva ultima estacion apunta a null en el espacio que corresponde a la siguiente estacion


        editar_estacion(ultimaEstacion,nullptr,nueva_estacion,tiempo,nullptr);

        cout << "Se ha creado la nueva estacion CORRECTAMENTE";
        num_estaciones++;

        break;
    }
    case 3:
    {

        string A,B,*nombre = new string;
        char aux;
        short int pos_1, pos_2, *tiempo_1 = new short int, *tiempo_2 = new short int;

        mostrarEstaciones();

        cout<< endl << "Elija entre que estaciones quiere agregar la nueva" << endl;
        do
        {
            cout << "Ingrese una de las estaciones: ";

            cin >> A;
            pos_1 = posicionarEstacion(&A);

            if(pos_1 == -1)
                cout << endl << "La estacion que ingresaste no se encuentra en la linea "<< *(this->getNombre()) << endl;
            else
            {
                cout << "ingrese el tiempo de la estacion " << A << " hacia la estacion nueva: ";
                cin >> *tiempo_1;
            }

        }while(pos_1 == -1);


        do
        {
            cout << endl << "Ingrese una de las estaciones contiguas a " << A << ": ";

            cin >> B;
            pos_2 = posicionarEstacion(&B);

            if(pos_2 == -1 || abs(pos_1 - pos_2 ) != 1 || pos_1 == pos_2)
                cout << "Ha ocurrido un problema al intentar agregar la estacion." << endl << "Asegurate que la estacion exista y que sea contigua a la primera estacion ingresada." << endl;
            else
            {
                cout << "ingrese el tiempo de la estacion " << B << " hacia la estacion nueva: ";
                cin >> *tiempo_2;
            }

        }while(pos_2 == -1 || abs(pos_1 - pos_2 ) != 1|| pos_1 == pos_2); // se repite cada que no se encuentre la estacion ingresada, que ambas estaciones no esten continuas o que se halla ingresado la misma estacion dos veces

        // se ingresa la informacion de la nueva estacion

        do
        {
            cout << endl << endl<< "Ingrese el nombre de la nueva estacion: ";
            cin >> *nombre;
        }while(posicionarEstacion(nombre) != -1); // si la estacion ya existia


        // se verifica cual es el orden entre las estaciones ingresadas

        Estacion *nueva_estacion, *est_1 = buscarEstacion(&A), *est_2 = buscarEstacion(&B);

        if(pos_1 < pos_2) // si la primera que se ingreso esta antes en la lista de estaciones
        {
            cout << endl << "La estacion podra ser usada de transferencia en el futuro? (y/n): ";
            cin >> aux;



            if(aux == 'y') // en caso de ser de transferencia
            {
                nueva_estacion = new Estacion(nombre,this->getNombre(),tiempo_1,tiempo_2,est_1,est_2);
                num_estacionesTrans ++;
            }
            else
                nueva_estacion = new Estacion(nombre,tiempo_1,tiempo_2,est_1,est_2);

            // se crea una nueva estacion en donde la estacion anterior es A y la siguiente es B

            editar_estacion(est_1,est_2,nueva_estacion,tiempo_1,tiempo_2);
        }

        else // si la segunda estacion ingresada se encuentra antes que la primera
        {
            // se crea una nueva estacion en donde la estacion anterior es B y la siguiente es A

            cout << endl << "La estacion podra ser usada de transferencia en el futuro? (y/n): ";
            cin >> aux;

            if(aux == 'y') // en caso de ser de transferenciA
            {
                nueva_estacion = new Estacion(nombre,this->getNombre(),tiempo_2,tiempo_1,est_2,est_1);
                num_estacionesTrans ++;
            }
            else
                nueva_estacion = new Estacion(nombre,tiempo_2,tiempo_1,est_2,est_1);


            editar_estacion(est_2,est_1,nueva_estacion,tiempo_2,tiempo_1);
        }

        num_estaciones++;

        cout << "Se ha creado la nueva estacion CORRECTAMENTE";


        break;

    }
    default:
        cout << endl << "Ingresaste una opcion invalida"<<endl;
    }

}

void Linea::eliminarEstacion(string *nombre)
{
    // se halla la estacion a eliminar
    Estacion *est = buscarEstacion(nombre);


    if(est->es_transferencia)
    {
        cout << endl << "No se puede eliminar esta estacion de transferencia" << endl;
        return;
    }
    else if(num_estaciones < 2) // si queda una estacion
    {
        cout << "No se puede eliminar esta estacion";
        return;
    }

    // se redireccionan las estaciones de los bordes

    short int *nuevo_tiempo = new short int(est->getTiempo_anterior() + est->getTiempo_siguiente()); // se suman ambos tiempos

    if(est->getSiguiente()) // si no esta apuntando a nulo en su puntero siguiente
    {
        est->getSiguiente()->setAnterior(est->getAnterior(),this->nombre);
        est->getSiguiente()->setTiempo_anterior(nuevo_tiempo,this->nombre);
    }

    if(est->getAnterior())
    {
        est->getAnterior()->setSiguiente(est->getSiguiente(),this->nombre);
        est->getAnterior()->setTiempo_siguiente(nuevo_tiempo,this->nombre);
    }

    // NO hay ningun caso en el que existe leak of memory ya que si o si se entra a alguno de los anteriores condicionales

    num_estaciones--;

    est->~Estacion();

    cout << endl << "Se ha eliminado la estacion correctamente" << endl;
}

bool Linea::eliminarTodaEstacion()
{
    Estacion *actual = primeraEstacion; // se inicializa en la primera estacion

    // se comprueba si existe estacion de tranferencia
    for(int i = 0; i < num_estaciones; i ++)
    {
        if(actual->es_transferencia)
        {
            cout << endl << "Esta linea tiene estacion de transferencia, por lo tanto no se ha podido eliminar" << endl;
            return false;
        }

        actual = actual->getSiguiente();
    }

    actual = primeraEstacion; // se reinicia una vez se comprueba que no existe estacion de transferencia

    for(int i = 0; i < num_estaciones; i ++)
    {
        actual->~Estacion();
        actual = actual->getSiguiente();
    }

    return true; // en caso de que se eliminara con exito

}


