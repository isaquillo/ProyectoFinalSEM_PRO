#include "Cita.h"
#include "Tecnico.h"
#include "Cliente.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAX_CITAS 20
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

#define CAMBIA_CODIGO_CLIENTE 1
#define CAMBIA_CODIGO_TECNICO 2
#define CAMBIA_FECHA_CITA 3
#define SALIR 4

extern int numCitas;
extern void pausar();
extern int menuClase(string cadena);
extern int menuAgregarRegistro();
extern void errorAgregarRegistro(string cadena);
extern void errorRegistroInexistente(string cadena);
extern void errorArchivo(string archivo);
extern void errorEntradaInvalida();

Cita::Cita()
{
    //ctor
}

Cita::~Cita()
{
    //dtor
}

void Cita::menuCitas()
{
    bool encontrado;
    ofstream escribirNumCitas;
    ifstream leerNumCitas;
    ofstream escribirCitas;
    ifstream leerCitas;
    string codigo;
    int opcionMenuCita = 0;
    while (opcionMenuCita != REGRESAR)
    {
        opcionMenuCita = menuClase("Cita");
        switch (opcionMenuCita)
        {
        case AGREGAR: // Agregar citas
            escribirCitas.open("Citas.txt", ios::out | ios::app);
            if (escribirCitas.is_open())
            {
                int opcion;
            system(CLEAR);
            do
            {
                if (numCitas < MAX_CITAS)
                {
                    agregarCita();
                    escribirCitas << dameCodigo() << endl
                      << dameCodigoCliente() << endl
                      << dameCodigoTecnico() << endl
                      << dameDiaCita() << endl
                      << dameHoraCita() << endl << endl;
                    numCitas++;
                    escribirNumCitas.open("NumCitas.txt",ios::out);
                    if (escribirNumCitas.is_open())
                    {
                        escribirNumCitas << numCitas;
                        do
                        {
                            opcion = menuAgregarRegistro();
                        }
                        while (opcion < 1 || opcion > 2);
                    }
                    else
                    {
                        errorArchivo("NumCitas.txt");
                    }
                    escribirNumCitas.close();
                }
                else
                {
                    errorAgregarRegistro("citas");
                    opcion = 0;
                }
            }
            while (opcion == 1);
            }
            else
            {
               errorArchivo("Citas.txt");
            }
            escribirCitas.close();
            break;

        case MOSTRAR: // Mostrar citas
            system(CLEAR);
            if (numCitas > 0)
            {
                cout << "CITAS REGISTRADAS" << endl << endl;
                mostrarCitas();
                cin.ignore();
                cout << endl << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("citas");
            }
            break;

        case BUSCAR: // Busqueda de una cita
            if (numCitas > 0 )
            {
                system(CLEAR);
                cout << "BUSCAR CITA\n\n";
                cin.ignore();
                cout << "Ingresa el codigo de la cita a buscar: ";
                getline(cin, codigo);
                encontrado = buscarCita(codigo);
                if (encontrado == true)
                {
                    cout << endl << "Registro encontrado..." << endl << endl;
                    mostrarUnaCita(codigo);
                }
                else
                {
                    cout << "No se encontro ninguna cita con ese codigo..." << endl << endl;
                }
                cout << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("citas");
            }
            break;

        case MODIFICAR:
            if (numCitas > 0)
            {
                system(CLEAR);
                cout << "MODIFICAR UN REGISTRO" << endl << endl;
                cin.ignore();
                cout << "Ingresa el codigo de la cita a modificar: ";
                getline(cin, codigo);
                encontrado = buscarCita(codigo);
                if (encontrado == true)
                {
                   modificarCita(codigo);
                }
                else
                {
                    cout << "No se encontro ninguna cita con ese codigo..." << endl << endl;
                }
                pausar();
            }
            else
            {
                errorRegistroInexistente("citas");
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

void Cita::agregarCita()
{
    bool encontrado;
    Tecnico auxTecnico;
    Cliente auxCliente;
    string codigo;
    string codigoCliente;
    string codigoTecnico;
    string diaCita;
    string horaCita;

    system(CLEAR);
    cout << "REGISTRO DE NUEVO CITA" << endl << endl;
    cout << numCitas << " registros de " << MAX_CITAS << " posibles..." <<endl << endl;
    cout << "Ingresa los datos de la cita..." << endl;
    cin.ignore();
    cout << "Codigo: ";
    getline(cin, codigo);
    do
    {
        cout << "Codigo del cliente: ";
        getline(cin, codigoCliente);
        encontrado = auxCliente.buscarCliente(codigoCliente);
        if (encontrado == false)
        {
            cout << "El codigo del cliente es incorrecto. Vuelve a capturar..." << endl << endl;
        }
    }
    while (encontrado == false);
    do
    {
        cout << "Codigo del tecnico: ";
        getline(cin, codigoTecnico);
        encontrado = auxTecnico.buscarTecnico(codigoTecnico);
        if (encontrado == false)
        {
            cout << "El codigo del tecnico es incorrecto. Vuelve a capturar..." << endl << endl;
        }
    }
    while (encontrado == false);
    do
    {
        cout << "Dia de la Cita (dd/mm/aa): ";
        getline(cin, diaCita);
        cout << "Hora de la Cita (hh:mm formato 24 horas) : ";
        getline(cin,horaCita);
        encontrado = buscarFecha(diaCita, horaCita);
        if (encontrado == true)
        {
            cout << "Ya hay una cita con esa fecha. Vuelve a capturar..." << endl << endl;
        }
    }
    while (encontrado == true);
    // Llamadas a metodos setters de la clase
    fijaCodigo(codigo);
    fijaCodigoCliente(codigoCliente);
    fijaCodigoTecnico(codigoTecnico);
    fijaDiaCita(diaCita);
    fijaHoraCita(horaCita);
}

void Cita::mostrarCitas()
{
    Cliente auxCliente;
    Tecnico auxTecnico;
    ifstream leerCitas;
    string codigo;
    string codigoCliente;
    string codigoTecnico;
    string diaCita;
    string horaCita;
    string extraLine;
    leerCitas.open("Citas.txt", ios::in);
    if (leerCitas.is_open())
    {
        getline(leerCitas,codigo);
        while (!leerCitas.eof())
        {
            getline(leerCitas,codigoCliente);
            getline(leerCitas,codigoTecnico);
            getline(leerCitas,diaCita);
            getline(leerCitas,horaCita);
            getline(leerCitas,extraLine);
            cout << "Codigo de cita:        " << codigo << endl;
            cout << "Info del Cliente..." << endl;
            auxCliente.mostrarUnCliente(codigoCliente);
            cout << "Info del Tecnico..." << endl;
            auxTecnico.mostrarUnTecnico(codigoTecnico);
            cout << "Dia de la Cita:        " << diaCita << endl;
            cout << "Hora de la Cita:       " << horaCita << " Hrs." << endl;
            cout << "---------------------------------------------------------------------" << endl;
            getline(leerCitas,codigo);
        }
    }
    else
    {
        errorArchivo("Citas.txt");
    }
    leerCitas.close();
}

void Cita::mostrarUnaCita(string codigox)
{
    bool encontrado = false;
    Cliente auxCliente;
    Tecnico auxTecnico;
    ifstream leerCitas;
    string codigo;
    string codigoCliente;
    string codigoTecnico;
    string diaCita;
    string horaCita;
    string extraLine;
    leerCitas.open("Citas.txt", ios::in);
    if (leerCitas.is_open())
    {
        getline(leerCitas,codigo);
        while (!leerCitas.eof() && encontrado == false)
        {
            getline(leerCitas,codigoCliente);
            getline(leerCitas,codigoTecnico);
            getline(leerCitas,diaCita);
            getline(leerCitas,horaCita);
            getline(leerCitas,extraLine);
            if (codigox == codigo)
            {
                cout << "Codigo de cita:        " << codigo  << endl;
                cout << "Info del Cliente..." << endl;
                auxCliente.mostrarUnCliente(codigoCliente);
                cout << "Info del Tecnico..." << endl;
                auxTecnico.mostrarUnTecnico(codigoTecnico);
                cout << "Dia de la Cita:        " << diaCita << endl;
                cout << "Hora de la Cita:       " << horaCita << " Hrs." << endl;
                encontrado = true;
            }
            else
            {
                getline(leerCitas,codigo);
            }

        }
    }
    else
    {
        errorArchivo("Citas.txt");
    }
    leerCitas.close();
}

bool Cita::buscarCita(string codigox)
{
    bool encontrado = false;
    ifstream leerCitas;
    string codigo;
    string cliente;
    string tecnico;
    string fecha;
    string hora;
    string extraLine;
    leerCitas.open("Citas.txt", ios::in);
    if (leerCitas.is_open())
    {
        getline(leerCitas,codigo);
        while (!leerCitas.eof() && encontrado == false)
        {
            getline(leerCitas,cliente);
            getline(leerCitas,tecnico);
            getline(leerCitas,fecha);
            getline(leerCitas,hora);
            getline(leerCitas,extraLine);
            if (codigox == codigo)
            {
                encontrado = true;
            }
            else
            {
                getline(leerCitas,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Citas.txt");
    }
    leerCitas.close();
    return encontrado;
}

void Cita::modificarCita(string codigox)
{
    bool encontrado;
    Tecnico auxTecnico;
    Cliente auxCliente;
    ofstream escribirCitas;
    ofstream escribirAuxiliar;
    ifstream leerCitas;
    string codigo;
    string codigoCliente, codigoClientex;
    string codigoTecnico, codigoTecnicox;
    string diaCita, diaCitax;
    string horaCita, horaCitax;
    string extraLine;
    int opcion;
    leerCitas.open("Citas.txt",ios::in);
    escribirAuxiliar.open("Auxiliar.txt",ios::out);
    if (leerCitas.is_open() && escribirAuxiliar.is_open())
    {
        getline(leerCitas,codigo);
        while(!leerCitas.eof())
        {
            getline(leerCitas,codigoCliente);
            getline(leerCitas,codigoTecnico);
            getline(leerCitas,diaCita);
            getline(leerCitas,horaCita);
            getline(leerCitas,extraLine);
            if (codigox == codigo)
            {
                cout << endl << "Registro encontrado..." << endl << endl;
                mostrarUnaCita(codigo);
                do
                {
                    cout << "Campo a modificar.." << endl << endl;
                    cout << "1) Codigo del cliente" << endl;
                    cout << "2) Codigo del tecnico" << endl;
                    cout << "3) Dia y hora de la Cita" << endl;
                    cout << "4) Regresar " << endl << endl;
                    cout << "Elige una opcion: ";
                    cin >> opcion;
                    switch (opcion)
                    {
                    case CAMBIA_CODIGO_CLIENTE:
                        system(CLEAR);
                        cin.ignore();
                        do
                        {
                           cout << "Ingresa el nuevo codigo del cliente: ";
                            getline(cin,codigoClientex);
                            encontrado = auxCliente.buscarCliente(codigoClientex);
                            if (encontrado == true)
                            {
                                escribirAuxiliar << codigo << endl
                                         << codigoClientex << endl
                                         << codigoTecnico << endl
                                         << diaCita << endl
                                         << horaCita << endl << endl;
                                cout << endl <<"Registro modificado exitosamente." << endl << endl;
                                opcion = 0;
                            }
                            else
                            {
                               cout << "Registro inexistente. Vuelve a capturar..." << endl << endl;
                               pausar();
                            }
                        }
                        while (encontrado == false);

                        break;
                    case CAMBIA_CODIGO_TECNICO:
                        system(CLEAR);
                        cin.ignore();
                        do
                        {
                           cout << "Ingresa el nuevo codigo del tecnico: ";
                            getline(cin,codigoTecnicox);
                            encontrado = auxTecnico.buscarTecnico(codigoTecnicox);
                            if (encontrado == true)
                            {
                                escribirAuxiliar << codigo << endl
                                         << codigoCliente << endl
                                         << codigoTecnicox << endl
                                         << diaCita << endl
                                         << horaCita << endl << endl;
                                cout << endl <<"Registro modificado exitosamente." << endl << endl;
                                opcion = 0;
                            }
                            else
                            {
                               cout << "Registro inexistente. Vuelve a capturar..." << endl << endl;
                               pausar();
                            }
                        }
                        while (encontrado == false);
                        break;
                    case CAMBIA_FECHA_CITA:
                        system(CLEAR);
                        cin.ignore();
                        do
                        {
                            cout << "Ingresa el nuevo dia de la cita (dd/mm/aa): ";
                            getline(cin,diaCitax);
                            cout << "Ingresa la nueva hora de la Cita (hh:mm formato 24 horas): ";
                            getline(cin,horaCitax);
                            encontrado = buscarFecha(diaCitax, horaCitax);
                            if (encontrado == true)
                            {
                                cout << "Esa fecha ya esta ocupada. Ingresa otra..." << endl;
                                pausar();
                            }
                        }
                        while (encontrado == true);
                        escribirAuxiliar << codigo << endl
                                         << codigoCliente << endl
                                         << codigoTecnico << endl
                                         << diaCitax << endl
                                         << horaCitax << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        opcion = 0;
                        break;
                    case SALIR:
                        break;
                    default:
                        errorEntradaInvalida();
                    } // fin de switch
                }
                while (!SALIR);
                getline(leerCitas,codigo);
            }
            else
            {
                escribirAuxiliar << codigo << endl
                                 << codigoCliente << endl
                                 << codigoTecnico << endl
                                 << diaCita << endl
                                 << horaCita << endl << endl;
                getline(leerCitas,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Citas.txt");
    }
    leerCitas.close();
    escribirAuxiliar.close();
    remove("Citas.txt");
    rename("Auxiliar.txt", "Citas.txt");
}

bool Cita::buscarFecha(string diax, string horax)
{
    bool encontrado = false;
    ifstream leerCitas;
    string codigo;
    string codigoCliente;
    string codigoTecnico;
    string diaCita;
    string horaCita;
    string extraLine;
    leerCitas.open("Citas.txt", ios::in);
    if (leerCitas.is_open())
    {
        getline(leerCitas,codigo);
        while (!leerCitas.eof() && encontrado == false)
        {
            getline(leerCitas,codigoCliente);
            getline(leerCitas,codigoTecnico);
            getline(leerCitas,diaCita);
            getline(leerCitas,horaCita);
            getline(leerCitas,extraLine);
            if (diax == diaCita && horax == horaCita)
            {
                encontrado = true;
            }
            else
            {
                getline(leerCitas,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Citas.txt");
    }
    leerCitas.close();
    return encontrado;
}
