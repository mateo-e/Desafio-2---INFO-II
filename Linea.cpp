#include "Linea.h"

string *Linea::getNombre()
{
    return nombre;
}

void Linea::setNombre(string &newNombre)
{
    delete[] nombre; // se libera la memoria anterior
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
    num_estaciones = 0;
    num_estacionesTrans = 0;
    sig_linea = NULL;
    agregarEstacion(); // se agrega la primera estacion
}

Linea::Linea(string *nombre_linea, Estacion *estacionConexion)
{
    this->nombre = nombre_linea;
    num_estaciones = 0;
    num_estacionesTrans = 0;
    sig_linea = NULL;

    primeraEstacion = estacionConexion;

    estacionConexion->num_conexiones++; // se aumenta su numero de conexiones
    if(estacionConexion->num_conexiones % 10 == 0) // si se llega a un tope en el tamaño de las conexiones (este tamaño se aumenta de 10 en 10)
        estacionConexion->redimensionar();

    estacionConexion->getLineas_queCruzan()[estacionConexion->num_conexiones] = *nombre; // se agrega el nombre de la nueva linea a las lineas que cruzan a la estacion de tranferencia
}

Linea::~Linea()
{
    // antes de su invocacion se libera la memoria dinamica creada en cada estacion
}

void Linea::mostrarEstaciones()
{

}

Estacion *Linea::buscarEstacion(string *nombre)
{

}

short int Linea::posicionarEstacion(string *nombre)
{

}

void Linea::editar_estacion(Estacion *ant, Estacion *sig, Estacion *nueva, short *tiempo_ant, short *tiempo_sig)
{
    if(ant != nullptr)
    {
        ant->setSiguiente(nueva,this->getNombre()); // se redireccionan la estacion anterior y siguiente
        ant->setTiempo_siguiente(tiempo_ant,this->getNombre());
    }

    if(sig != nullptr) // si es una estacion del borde
    {
        sig->setAnterior(nueva,this->getNombre());
        sig->setTiempo_anterior(tiempo_sig,this->getNombre());
    }
}

void Linea::agregarEstacion()
{
    // se imprimen las estaciones de la linea actual,
    int opcion;
    cout << endl << "Ingrese la ubicacion de la nueva estacion " <<  endl;
    if(num_estaciones > 1) // si existe mas de dos estaciones
    {
        cout << "1 - Principio" << endl << "2 - Final" << endl << "3 - Entre estaciones" << endl << "Opcion: ";
        cin >> opcion;
    }
    else if(num_estaciones > 0) // si existe por lo menos una estacion
    {
        cout << "1 - Principio" << endl << "2 - Final" << endl << "Opcion: ";
        cin >> opcion;
    }
    else // si no existe ninguna estacion se manda directamente a la opcion 1
        opcion = 1;

    cout<< endl << endl;

    switch(opcion)
    {
    case 1:
    {
        string *nombre = new string;
        short int * tiempo;

        if(num_estaciones == 0)
            cout << "Se esta creando la primera estacion" << endl;

        do
        {
            cout << endl << endl<< "Ingrese el nombre de la nueva estacion: ";
            cin >> *nombre;
        }while(posicionarEstacion(nombre) != -1); // si la estacion ya existia

        char aux;
        cout << endl << "¿La estacion podra ser usada de transferencia en el futuro? (y/n)";
        cin >> aux;



        if(num_estaciones > 0)
        {
            cout << "Ingrese el tiempo de la estacion " << *nombre << " hacia la estacion " << this->getPrimeraEstacion()->getNombre();
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

            cout << endl <<  "se ha creado la primera estacion" << endl;
        }
        num_estaciones ++;
        cout << "Se ha creado la nueva estacion CORRECTAMENTE";

        break;

    }

    case 2:
    {
        string *nombre = new string;
        short int * tiempo;

        do
        {
            cout << endl << endl<< "Ingrese el nombre de la nueva estacion: ";
            cin >> *nombre;
        }while(posicionarEstacion(nombre) != -1); // si la estacion ya existia

        char aux;
        cout << endl << "¿La estacion podra ser usada de transferencia en el futuro? (y/n)";
        cin >> aux;

        // se halla la ultima estacion
        Estacion *ultimaEstacion = primeraEstacion + num_estaciones - 1;

        cout << "Ingrese el tiempo de la estacion " << *nombre << " hacia la estacion " << *(ultimaEstacion->getNombre());
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
                cout << endl << "La estacion que ingresaste no se encuentra en la linea "<< this->getNombre() << endl;
            else
            {
                cout << "ingrese el tiempo de la estacion " << A << " hacia la estacion nueva: ";
                cin >> *tiempo_1;
            }

        }while(pos_1 == -1);


        do
        {
            cout << endl << "Ingrese una de las estaciones contiguas a " << A;

            cin >> B;
            pos_2 = posicionarEstacion(&B);

            if(pos_2 == -1 || abs(pos_1 - pos_2 != 1) || pos_1 == pos_2)
                cout << "Ha ocurrido un problema al intentar agregar la estacion." << endl << "Asegurate que la estacion exista y que sea contigua a la primera estacion ingresada." << endl;
            else
            {
                cout << "ingrese el tiempo de la estacion " << B << " hacia la estacion nueva: ";
                cin >> *tiempo_2;
            }

        }while(pos_2 == -1 || abs(pos_1 - pos_2 != 1) || pos_1 == pos_2); // se repite cada que no se encuentre la estacion ingresada, que ambas estaciones no esten continuas o que se halla ingresado la misma estacion dos veces

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
            cout << endl << "¿La estacion podra ser usada de transferencia en el futuro? (y/n)";
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

            cout << endl << "¿La estacion podra ser usada de transferencia en el futuro? (y/n)";
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
    else if(num_estaciones < 2) // si queda una estacion o no hay ninguna
    {
        cout << "No se puede eliminar esta estacion";
        return;
    }

    est->~Estacion();
}

void Linea::eliminarTodaEstacion()
{
    // se comprueba si existe estacion de tranferencia
    for(int i = 0; i < num_estaciones; i ++)
    {
        if((primeraEstacion + i)->es_transferencia)
        {
            cout << endl << "Esta linea tiene estacion de transferencia" << endl;
            return;
        }
    }

    for(int i = 0; i < num_estaciones; i ++)
        (primeraEstacion + i)->~Estacion();
}


