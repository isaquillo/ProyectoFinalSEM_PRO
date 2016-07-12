#include "Cliente.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAX_CLIENTES 20
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

#define AGREGAR 1
#define MOSTRAR 2
#define BUSCAR 3
#define MODIFICAR 4
#define REGRESAR 5

#define CAMBIA_NOMBRE 1
#define CAMBIA_FECHA_NAC 2
#define CAMBIA_DIRECCION 3
#define CAMBIA_TEL_MOVIL 4
#define CAMBIA_TEL_CASA 5
#define CAMBIA_TEL_RECADOS 6
#define SALIR 7


extern int numClientes;
extern void pausar();
extern int menuClase(string cadena);
extern int menuAgregarRegistro();
extern void errorAgregarRegistro(string cadena);
extern void errorRegistroInexistente(string cadena);
extern void errorArchivo(string archivo);
extern void errorEntradaInvalida();


Cliente::Cliente()
{

}


Cliente::~Cliente()
{

}


void Cliente::menuClientes()
{
    ofstream escribirClientes;
    ifstream leerClientes;
    ofstream escribirNumClientes;
    ifstream leerNumClientes;
    string codigo;
    bool encontrado;
    int opcionMenuClientes = 0;
    while (opcionMenuClientes != REGRESAR)
    {
        opcionMenuClientes = menuClase("Cliente");
        switch (opcionMenuClientes)
        {
        case AGREGAR:
            escribirClientes.open("Clientes.txt", ios::out | ios::app);
            if (escribirClientes.is_open())
            {
                int opcion;
                system(CLEAR);
                do
                {
                    if (numClientes < MAX_CLIENTES)
                    {
                        agregarCliente();
                        escribirClientes << dameCodigo() << endl
                                         << dameNombre() << endl
                                         << dameFechaNac() << endl
                                         << dameDireccion() << endl
                                         << dameTelMovil() << endl
                                         << dameTelCasa() << endl
                                         << dameTelRecados() << endl << endl;
                        numClientes++;
                        escribirNumClientes.open("NumClientes.txt", ios::out);
                        if (escribirNumClientes.is_open())
                        {
                            escribirNumClientes << numClientes;
                            do
                            {
                                opcion = menuAgregarRegistro();
                            }
                            while (opcion < 1 || opcion > 2);
                        }
                        else
                        {
                            errorArchivo("NumClientes.txt");
                        }
                        escribirNumClientes.close();
                    }
                    else
                    {
                        errorAgregarRegistro("clientes");
                        opcion = 0;
                    }
                }
                while (opcion == 1);
            }
            else
            {
                errorArchivo("Clientes.txt");
            }
            escribirClientes.close();
            break;

        case MOSTRAR: // Mostrar clientes
            system(CLEAR);
            if (numClientes > 0)
            {
                cout << "CLIENTES REGISTRADOS" << endl << endl;
                mostrarClientes();
                cin.ignore();
                cout << endl << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("clientes");
            }
            break;

        case BUSCAR: // Busqueda de una cita
            if (numClientes > 0)
            {
                system(CLEAR);
                cout << "BUSCAR CITA" << endl << endl;
                cin.ignore();
                cout << "Ingresa el codigo del cliente a buscar: ";
                getline(cin, codigo);
                encontrado = buscarCliente(codigo);
                if (encontrado == true)
                {
                    cout << endl << "Registro encontrado..." << endl << endl;
                    mostrarUnCliente(codigo);
                }
                else
                {
                   cout << endl << "No se encontro ningun cliente con ese codigo..." << endl << endl;
                }
                cout << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("clientes");
            }
            break;
        case MODIFICAR:
            if (numClientes > 0)
            {
                system(CLEAR);
                cout << "MODIFICAR UN REGISTRO" << endl << endl;
                cin.ignore();
                cout << "Ingresa el codigo del cliente a modificar: ";
                getline(cin, codigo);
                encontrado = buscarCliente(codigo);
                if (encontrado == true)
                {
                    modificarCliente(codigo);
                }
                else
                {
                    cout << "No se encontro ningun cliente con ese codigo..." << endl << endl;
                }
                pausar();
            }
            else
            {
                errorRegistroInexistente("clientes");
            }
            break;
        case REGRESAR:
            ;
            break;
        default:
            errorEntradaInvalida();
        }
    }
}

void Cliente::agregarCliente()
{
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[3];

    system(CLEAR);
    cout << "REGISTRO DE NUEVO CLIENTE" << endl << endl;
    cout << numClientes << " registros de " << MAX_CLIENTES << " posibles..." <<endl << endl;
    cout << "Ingresa los datos del cliente..." << endl;
    cin.ignore();
    cout << "Codigo: ";
    getline(cin, codigo);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Fecha de nacimiento: ";
    getline(cin, fechaNacimiento);
    cout << "Direccion: ";
    getline(cin, direccion);
    cout << "Telefono movil: ";
    getline(cin, telefonos[0]);
    cout << "Telefono de casa: ";
    getline(cin, telefonos[1]);
    cout << "Telefono para recados: ";
    getline(cin, telefonos[2]);

    // Llamadas a métodos setters de la clase
    fijaCodigo(codigo);
    fijaNombre(nombre);
    fijaFechaNac(fechaNacimiento);
    fijaDireccion(direccion);
    fijaTelMovil(telefonos[0]);
    fijaTelCasa(telefonos[1]);
    fijaTelRecados(telefonos[2]);
}

void Cliente::mostrarClientes()
{
    ifstream leerClientes;
    ifstream leerNumClientes;
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[3];
    string extraLine;
    leerClientes.open("Clientes.txt", ios::in);
    if (leerClientes.is_open())
    {
        getline(leerClientes,codigo);
        while (!leerClientes.eof())
        {
            getline(leerClientes,nombre);
            getline(leerClientes,fechaNacimiento);
            getline(leerClientes,direccion);
            getline(leerClientes,telefonos[0]);
            getline(leerClientes,telefonos[1]);
            getline(leerClientes,telefonos[2]);
            getline(leerClientes,extraLine);
            cout << "Codigo:                " << codigo << endl;
            cout << "Nombre:                " << nombre << endl;
            cout << "Fecha de nacimiento:   " << fechaNacimiento << endl;
            cout << "Direccion:             " << direccion << endl;
            cout << "Telefono movil:        " << telefonos[0] << endl;
            cout << "Telefono de casa:      " << telefonos[1] << endl;
            cout << "Telefono de recados:   " << telefonos[2] << endl;
            cout << "---------------------------------------------------------------------" << endl;
            getline(leerClientes,codigo);
        }
    }
    else
    {
        errorArchivo("Clientes.txt");
    }
    leerClientes.close();
}

void Cliente::mostrarUnCliente(string codigox)
{
    bool encontrado;
    ifstream leerClientes;
    ifstream leerNumTecnicos;
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[3];
    string extraLine;
    encontrado = false;
    leerClientes.open("Clientes.txt", ios::in);
    if (leerClientes.is_open())
    {
        getline(leerClientes,codigo);
        while (!leerClientes.eof() && encontrado == false)
        {
            getline(leerClientes,nombre);
            getline(leerClientes,fechaNacimiento);
            getline(leerClientes,direccion);
            getline(leerClientes,telefonos[0]);
            getline(leerClientes,telefonos[1]);
            getline(leerClientes,telefonos[2]);
            getline(leerClientes,extraLine);
            if (codigox == codigo)
            {
                cout << "Codigo:                " << codigo << endl;
                cout << "Nombre:                " << nombre << endl;
                cout << "Fecha de nacimiento:   " << fechaNacimiento << endl;
                cout << "Direccion:             " << direccion << endl;
                cout << "Telefono movil:        " << telefonos[0] << endl;
                cout << "Telefono de casa:      " << telefonos[1] << endl;
                cout << "Telefono para recados: " << telefonos[2] << endl;
                encontrado = true;
            }
            else
            {
                getline(leerClientes,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Clientes.txt");
    }
    leerClientes.close();
}

bool Cliente::buscarCliente(string codigox)
{
    bool encontrado = false;
    ifstream leerClientes;
    ifstream leerNumClientes;
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[3];
    string extraLine;
    leerClientes.open("Clientes.txt", ios::in);
    if (leerClientes.is_open())
    {
        getline(leerClientes,codigo);
        while (!leerClientes.eof() && encontrado == false)
        {
            getline(leerClientes,nombre);
            getline(leerClientes,fechaNacimiento);
            getline(leerClientes,direccion);
            getline(leerClientes,telefonos[0]);
            getline(leerClientes,telefonos[1]);
            getline(leerClientes,telefonos[2]);
            getline(leerClientes,extraLine);
            if (codigox == codigo)
            {
                encontrado = true;
            }
            else
            {
                getline(leerClientes,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Clientes.txt");
    }
    leerClientes.close();
    return encontrado;
}

void Cliente::modificarCliente(string codigox)
{
    ofstream escribirAuxiliar;
    ofstream escribirNumClientes;
    ofstream escribirClientes;
    ifstream leerClientes;
    ifstream leerNumClientes;
    string codigo;
    string nombre, nombrex;
    string fechaNacimiento, fechaNacimientox;
    string direccion, direccionx;
    string telefonos[3], telefonox;
    string extraLine;
    int opcion;
    leerClientes.open("Clientes.txt",ios::in);
    escribirAuxiliar.open("Auxiliar.txt",ios::out);
    if (leerClientes.is_open() && escribirAuxiliar.is_open())
    {
        getline(leerClientes,codigo);
        while(!leerClientes.eof())
        {
            getline(leerClientes,nombre);
            getline(leerClientes,fechaNacimiento);
            getline(leerClientes,direccion);
            getline(leerClientes,telefonos[0]);
            getline(leerClientes,telefonos[1]);
            getline(leerClientes,telefonos[2]);
            getline(leerClientes,extraLine);
            if (codigox == codigo)
            {
                cout << endl;
                mostrarUnCliente(codigo);
                do
                {
                    cout << endl;
                    cout << "Campo a modificar.." << endl << endl;
                    cout << "1) Nombre" << endl;
                    cout << "2) Fecha de nacimiento" << endl;
                    cout << "3) Direccion" << endl;
                    cout << "4) Telefono movil" << endl;
                    cout << "5) Telefono de casa" << endl;
                    cout << "6) Telefono de recados" << endl;
                    cout << "7) Regresar " << endl << endl;
                    cout << "Elige una opcion: ";
                    cin >> opcion;
                    switch (opcion)
                    {
                    case CAMBIA_NOMBRE:
                        system(CLEAR);
                        cin.ignore();
                        cout << "Ingresa el nuevo nombre: ";
                        getline(cin,nombrex);
                        escribirAuxiliar << codigo << endl
                                         << nombrex << endl
                                         << fechaNacimiento << endl
                                         << direccion << endl
                                         << telefonos[0] << endl
                                         << telefonos[1] << endl
                                         << telefonos[2] << endl << endl;
                        cout << endl <<"Registro modificado exitosamente..." << endl << endl;
                        break;
                    case CAMBIA_FECHA_NAC:
                        system(CLEAR);
                        cin.ignore();
                        cout << "Ingresa la nueva fecha de nacimiento: ";
                        getline(cin, fechaNacimientox);
                        escribirAuxiliar << codigo << endl
                                         << nombre << endl
                                         << fechaNacimientox << endl
                                         << direccion << endl
                                         << telefonos[0] << endl
                                         << telefonos[1] << endl
                                         << telefonos[2] << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        break;
                    case CAMBIA_DIRECCION:
                        system(CLEAR);
                        cin.ignore();
                        cout << "Ingresa la nueva direccion: ";
                        getline(cin,direccionx);
                        escribirAuxiliar << codigo << endl
                                         << nombre << endl
                                         << fechaNacimiento << endl
                                         << direccionx << endl
                                         << telefonos[0] << endl
                                         << telefonos[1] << endl
                                         << telefonos[2] << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        break;
                    case CAMBIA_TEL_MOVIL:
                        system(CLEAR);
                        cin.ignore();
                        cout << "Ingresa el nuevo telefono movil: ";
                        getline(cin,telefonox);
                        escribirAuxiliar << codigo << endl
                                         << nombre << endl
                                         << fechaNacimiento << endl
                                         << direccion << endl
                                         << telefonox << endl
                                         << telefonos[1] << endl
                                         << telefonos[2] << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        break;
                    case CAMBIA_TEL_CASA:
                        system(CLEAR);
                        cin.ignore();
                        cout << "Ingresa el nuevo telefono de casa: ";
                        getline(cin,telefonox);
                        escribirAuxiliar << codigo << endl
                                         << nombre << endl
                                         << fechaNacimiento << endl
                                         << direccion << endl
                                         << telefonos[0] << endl
                                         << telefonox << endl
                                         << telefonos[2] << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        break;
                    case CAMBIA_TEL_RECADOS:
                        system(CLEAR);
                        cin.ignore();
                        cout << "Ingresa el nuevo telefono para recados: ";
                        getline(cin,telefonox);
                        escribirAuxiliar << codigo << endl
                                         << nombre << endl
                                         << fechaNacimiento << endl
                                         << direccion << endl
                                         << telefonos[0] << endl
                                         << telefonos[1] << endl
                                         << telefonox << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        break;
                    case SALIR:
                        break;
                    default:
                        errorEntradaInvalida();
                    } // fin de switch
                }
                while (!SALIR);
                getline(leerClientes,codigo);
            }
            else
            {
                escribirAuxiliar << codigo << endl
                                 << nombre << endl
                                 << fechaNacimiento << endl
                                 << direccion << endl
                                 << telefonos[0] << endl
                                 << telefonos[1] << endl
                                 << telefonos[2] << endl << endl;
                getline(leerClientes,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Clientes.txt");
    }
    leerClientes.close();
    escribirAuxiliar.close();
    remove("Clientes.txt");
    rename("Auxiliar.txt", "Clientes.txt");
}

