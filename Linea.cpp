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

short int Linea::getNum_estaciones() const
{
    return num_estaciones;
}

void Linea::setNum_estaciones(short newNum_estaciones)
{
    num_estaciones = newNum_estaciones;
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

Linea::Linea(string *nombre_linea)
{
    this->nombre = nombre_linea;
    num_estaciones = 0;
    sig_linea = NULL;
    agregarEstacion(); // se agrega la primera estacion
}

Linea::~Linea()
{
    this->eliminarTodaEstacion(); // se libera la memoria dinamica creada en cada estacion
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
                nueva_estacion = new Estacion(nombre,this->getNombre(),nullptr,tiempo,nullptr,primeraEstacion);
            else
                nueva_estacion = new Estacion(nombre,nullptr,tiempo,nullptr,primeraEstacion);



            buscarEstacion(primeraEstacion->getNombre())->setAnterior(nueva_estacion); // se redirecciona el puntero de la siguiente estacion
            buscarEstacion(primeraEstacion->getNombre())->setTiempo_anterior(tiempo,0);

            primeraEstacion = nueva_estacion;
        }

        else
        {
            if(aux == 'y')
                primeraEstacion = new Estacion(nombre,this->getNombre(),nullptr,nullptr,nullptr,nullptr);
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
            nueva_estacion = new Estacion(nombre,this->getNombre(),tiempo,nullptr,ultimaEstacion,nullptr);
        else
            nueva_estacion = new Estacion(nombre,tiempo,nullptr,ultimaEstacion,nullptr); // la nueva ultima estacion apunta a null en el espacio que corresponde a la siguiente estacion

        ultimaEstacion->setSiguiente(nueva_estacion);
        ultimaEstacion->setTiempo_siguiente(tiempo,0);

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
                nueva_estacion = new Estacion(nombre,this->getNombre(),tiempo_1,tiempo_2,est_1,est_2);
            else
                nueva_estacion = new Estacion(nombre,tiempo_1,tiempo_2,est_1,est_2);

            // se crea una nueva estacion en donde la estacion anterior es A y la siguiente es B

            est_1->setSiguiente(nueva_estacion); // se redireccionan la estacion anterior y siguiente
            est_1->setTiempo_siguiente(tiempo_1,0);

            est_2->setAnterior(nueva_estacion);
            est_2->setTiempo_anterior(tiempo_2,0);
        }

        else // si la segunda estacion ingresada se encuentra antes que la primera
        {
            // se crea una nueva estacion en donde la estacion anterior es B y la siguiente es A

            cout << endl << "¿La estacion podra ser usada de transferencia en el futuro? (y/n)";
            cin >> aux;

            if(aux == 'y') // en caso de ser de transferenciA
                nueva_estacion = new Estacion(nombre,this->getNombre(),tiempo_2,tiempo_1,est_2,est_1);
            else
                nueva_estacion = new Estacion(nombre,tiempo_2,tiempo_1,est_2,est_1);

            est_2->setSiguiente(nueva_estacion); // se redireccionan la estacion anterior y siguiente
            est_2->setTiempo_siguiente(tiempo_2,0);

            est_1->setAnterior(nueva_estacion);
            est_2->setTiempo_anterior(tiempo_1,0);
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

    est->~Estacion();
}

void Linea::eliminarTodaEstacion()
{
    for(int i = 0; i < num_estaciones; i ++)
        (primeraEstacion + i)->~Estacion();
}


