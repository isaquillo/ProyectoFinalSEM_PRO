#include "Tecnico.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAX_TECNICOS 20
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

#define AGREGAR 1
#define MOSTRAR 2
#define BUSCAR 3
#define MODIFICAR 4
#define SALIR 5

#define CAMBIA_NOMBRE 1
#define CAMBIA_FECHA_NAC 2
#define CAMBIA_DIRECCION 3
#define CAMBIA_TEL_MOVIL 4
#define CAMBIA_TEL_CASA 5
#define REGRESAR 6

extern int numTecnicos;
extern void pausar();
extern int menuClase(string cadena);
extern int menuAgregarRegistro();
extern void errorAgregarRegistro(string cadena);
extern void errorRegistroInexistente(string cadena);
extern void errorArchivo(string archivo);
extern void errorEntradaInvalida();

Tecnico::Tecnico()
{

}


Tecnico::~Tecnico()
{

}

void Tecnico::menuTecnicos()
{
    bool encontrado;
    ofstream escribirTecnicos;
    ifstream leerTecnicos;
    ofstream escribirNumTecnicos;
    ifstream leerNumTecnicos;
    string codigo;
    int opcionMenuTecnicos = 0;
    while (opcionMenuTecnicos != SALIR)
    {
        opcionMenuTecnicos = menuClase("Tecnico");
        switch (opcionMenuTecnicos)
        {
        case AGREGAR:
            escribirTecnicos.open("Tecnicos.txt", ios::out | ios::app);
            if (escribirTecnicos.is_open())
            {
                int opcion;
                system(CLEAR);
                do
                {
                    if (numTecnicos < MAX_TECNICOS)
                    {
                        agregarTecnico();
                        escribirTecnicos << dameCodigo() << endl
                                         << dameNombre() << endl
                                         << dameFechaNac() << endl
                                         << dameDireccion() << endl
                                         << dameTelMovil() << endl
                                         << dameTelCasa() << endl << endl;
                        numTecnicos++;
                        escribirNumTecnicos.open("NumTecnicos.txt", ios::out);
                        if (escribirNumTecnicos.is_open())
                        {
                            escribirNumTecnicos << numTecnicos;
                            do
                            {
                                opcion = menuAgregarRegistro();
                            }
                            while (opcion < 1 || opcion > 2);
                        }
                        else
                        {
                            errorArchivo("NumTecnicos.txt");
                        }
                        escribirNumTecnicos.close();
                    }
                    else
                    {
                        errorAgregarRegistro("tecnicos");
                        opcion = 0;
                    }
                }
                while (opcion == 1);
            }
            else
            {
                errorArchivo("Tecnicos.txt");
            }
            escribirTecnicos.close();
            break;

        case MOSTRAR: // Mostrar tecnicos
            system(CLEAR);
            if (numTecnicos > 0)
            {
                cout << "TECNICOS REGISTRADOS" << endl << endl;
                mostrarTecnicos();
                cin.ignore();
                cout << endl << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("tecnicos");
            }
            break;

        case BUSCAR:
            system(CLEAR);
            if (numTecnicos > 0)
            {
                system(CLEAR);
                cout << "BUSCAR TECNICO" << endl << endl;
                cin.ignore();
                cout << "Ingresa el codigo del tecnico a buscar: " << endl;
                getline(cin, codigo);
                encontrado = buscarTecnico(codigo);
                if (encontrado == true)
                {
                    cout << endl << "Registro encontrado..." << endl << endl;
                    mostrarUnTecnico(codigo);
                }
                else
                {
                    cout <<endl<< "No se encontro ningun tecnico con ese codigo..."<< endl << endl;
                }
                cout << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("tecnicos");
            }
            break;

        case MODIFICAR:
            system(CLEAR);
            if (numTecnicos > 0)
            {
                system(CLEAR);
                cout << "MODIFICAR UN REGISTRO" << endl << endl;
                cin.ignore();
                cout << "Ingresa el codigo del tecnico a modificar: ";
                getline(cin, codigo);
                encontrado = buscarTecnico(codigo);
                if (encontrado == true)
                {
                    modificarTecnico(codigo);
                }
                else
                {
                    cout << "No se encontro ningun tecnico con ese codigo..." << endl << endl;
                }
                pausar();
            }
            else
            {
                errorRegistroInexistente("tecnicos");
            }
            break;
        case SALIR:
            ;
            break;
        default:
            cin.ignore();
            errorEntradaInvalida();
        }
    }
}
void Tecnico::agregarTecnico()
{
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[2];

    system(CLEAR);
    cout << "REGISTRO DE NUEVO TECNICO" << endl << endl;
    cout << numTecnicos << " registros de " << MAX_TECNICOS << " posibles..." <<endl << endl;
    cout << "Ingresa los datos del tecnico..." << endl;
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

    // Llamadas a métodos setters de la clase
    fijaCodigo(codigo);
    fijaNombre(nombre);
    fijaFechaNac(fechaNacimiento);
    fijaDireccion(direccion);
    fijaTelMovil(telefonos[0]);
    fijaTelCasa(telefonos[1]);
}

void Tecnico::mostrarTecnicos()
{
    ifstream leerTecnicos;
    ifstream leerNumTecnicos;
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[2];
    string extraLine;
    leerTecnicos.open("Tecnicos.txt", ios::in);
    if (leerTecnicos.is_open())
    {
        getline(leerTecnicos,codigo);
        while (!leerTecnicos.eof())
        {
            getline(leerTecnicos,nombre);
            getline(leerTecnicos,fechaNacimiento);
            getline(leerTecnicos,direccion);
            getline(leerTecnicos,telefonos[0]);
            getline(leerTecnicos,telefonos[1]);
            getline(leerTecnicos,extraLine);
            cout << "Codigo:                " << codigo << endl;
            cout << "Nombre:                " << nombre << endl;
            cout << "Fecha de nacimiento:   " << fechaNacimiento << endl;
            cout << "Direccion:             " << direccion << endl;
            cout << "Telefono movil:        " << telefonos[0] << endl;
            cout << "Telefono de casa:      " << telefonos[1] << endl;
            cout << "---------------------------------------------------------------------" << endl;
            getline(leerTecnicos,codigo);
        }
    }
    else
    {
        errorArchivo("Tecnicos.txt");
    }
    leerTecnicos.close();
}

void Tecnico::mostrarUnTecnico (string codigox)
{
    bool encontrado;
    ifstream leerTecnicos;
    ifstream leerNumTecnicos;
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[2];
    string extraLine;
    encontrado = false;
    leerTecnicos.open("Tecnicos.txt", ios::in);
    if (leerTecnicos.is_open())
    {
        getline(leerTecnicos,codigo);
        while (!leerTecnicos.eof() && encontrado == false)
        {
            getline(leerTecnicos,nombre);
            getline(leerTecnicos,fechaNacimiento);
            getline(leerTecnicos,direccion);
            getline(leerTecnicos,telefonos[0]);
            getline(leerTecnicos,telefonos[1]);
            getline(leerTecnicos,extraLine);
            if (codigox == codigo)
            {
                cout << "Codigo:                " << codigo << endl;
                cout << "Nombre:                " << nombre << endl;
                cout << "Fecha de nacimiento:   " << fechaNacimiento << endl;
                cout << "Direccion:             " << direccion << endl;
                cout << "Telefono movil:        " << telefonos[0] << endl;
                cout << "Telefono de casa:      " << telefonos[1] << endl;
                encontrado = true;
            }
            else
            {

                getline(leerTecnicos,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Tecnicos.txt");
    }
    leerTecnicos.close();
}

bool Tecnico::buscarTecnico(string codigox)
{
    bool encontrado = false;
    ifstream leerTecnicos;
    ifstream leerNumTecnicos;
    string codigo;
    string nombre;
    string fechaNacimiento;
    string direccion;
    string telefonos[2];
    string extraLine;
    leerTecnicos.open("Tecnicos.txt", ios::in);
    if (leerTecnicos.is_open())
    {
        getline(leerTecnicos,codigo);
        while (!leerTecnicos.eof() && encontrado == false)
        {
            getline(leerTecnicos,nombre);
            getline(leerTecnicos,fechaNacimiento);
            getline(leerTecnicos,direccion);
            getline(leerTecnicos,telefonos[0]);
            getline(leerTecnicos,telefonos[1]);
            getline(leerTecnicos,extraLine);
            if (codigox == codigo)
            {
                encontrado = true;
            }
            else
            {
                getline(leerTecnicos,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Tecnicos.txt");
    }
    leerTecnicos.close();
    return encontrado;
}

void Tecnico::modificarTecnico(string codigox)
{
    ofstream escribirTecnicos;
    ifstream leerTecnicos;
    ofstream escribirNumTecnicos;
    ifstream leerNumTecnicos;
    ofstream escribirAuxiliar;
    string codigo;
    string nombre, nombrex;
    string fechaNacimiento, fechaNacimientox;
    string direccion, direccionx;
    string telefonos[2], telefonox;
    string extraLine;
    int opcion;
    leerTecnicos.open("Tecnicos.txt",ios::in);
    escribirAuxiliar.open("Auxiliar.txt",ios::out);
    if (leerTecnicos.is_open() && escribirAuxiliar.is_open())
    {
        getline(leerTecnicos,codigo);
        while(!leerTecnicos.eof())
        {
            getline(leerTecnicos,nombre);
            getline(leerTecnicos,fechaNacimiento);
            getline(leerTecnicos,direccion);
            getline(leerTecnicos,telefonos[0]);
            getline(leerTecnicos,telefonos[1]);
            getline(leerTecnicos,extraLine);
            if (codigox == codigo)
            {
                cout << endl;
                mostrarUnTecnico(codigo);
                do
                {
                    cout << endl;
                    cout << "Campo a modificar.." << endl << endl;
                    cout << "1) Nombre" << endl;
                    cout << "2) Fecha de nacimiento" << endl;
                    cout << "3) Direccion" << endl;
                    cout << "4) Telefono movil" << endl;
                    cout << "5) Telefono de casa" << endl;
                    cout << "6) Regresar " << endl << endl;
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
                                         << telefonos[1] << endl << endl;
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
                                         << telefonos[1] << endl << endl;
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
                                         << telefonos[1] << endl << endl;
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
                                         << telefonos[1] << endl << endl;
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
                                         << telefonox << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        break;
                    case REGRESAR:
                        break;
                    default:
                        errorEntradaInvalida();
                    } // Fin de switch
                }
                while (!REGRESAR);
                getline(leerTecnicos,codigo);
            } // Fin de if
            else
            {
                escribirAuxiliar << codigo << endl
                                 << nombre << endl
                                 << fechaNacimiento << endl
                                 << direccion << endl
                                 << telefonos[0] << endl
                                 << telefonos[1] << endl << endl;
                getline(leerTecnicos,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Tecnicos.txt");
    }
    leerTecnicos.close();
    escribirAuxiliar.close();
    remove("Tecnicos.txt");
    rename("Auxiliar.txt", "Tecnicos.txt");
}

