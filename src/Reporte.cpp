#include "Reporte.h"
#include "Cita.h"
#include "Cliente.h"
#include "Tecnico.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAX_REPORTES 20
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

#define CAMBIA_CODIGO_CITA 1
#define CAMBIA_COSTO_TOTAL 2
#define SALIR 3

extern int numReportes;
extern void pausar();
extern int menuClase(string cadena);
extern int menuAgregarRegistro();
extern void errorAgregarRegistro(string cadena);
extern void errorRegistroInexistente(string cadena);
extern void errorArchivo(string archivo);
extern void errorEntradaInvalida();

Reporte::Reporte()
{
    //ctor
}

Reporte::~Reporte()
{
    //dtor
}

void Reporte::menuReportes()
{
    bool encontrado;
    ofstream escribirReportes;
    ofstream escribirNumReportes;
    string codigo;
    int opcionMenuReportes = 0;
    while (opcionMenuReportes != REGRESAR)
    {
        opcionMenuReportes = menuClase("Reporte");
        switch (opcionMenuReportes)
        {
        case AGREGAR: // Agregar tecnicos
            escribirReportes.open("Reportes.txt", ios::out | ios::app);
            if (escribirReportes.is_open())
            {
                int opcion;
                system(CLEAR);
                do
                {
                    if (numReportes < MAX_REPORTES)
                    {
                        agregarReporte();
                        escribirReportes << dameCodigo() << endl
                                         << dameCodigoCita() << endl
                                         << dameCostoTotal() << endl << endl;
                        numReportes++;
                        escribirNumReportes.open("NumReportes.txt", ios::out);
                        if (escribirNumReportes.is_open())
                        {
                            escribirNumReportes << numReportes;
                            do
                            {
                                opcion = menuAgregarRegistro();
                            }
                            while (opcion < 1 || opcion > 2);
                        }
                        else
                        {
                            errorArchivo("NumReportes.txt");
                        }
                        escribirNumReportes.close();
                    }
                    else
                    {
                        errorAgregarRegistro("reportes");
                        opcion = 0;
                    }
                }
                while (opcion == 1);
            }
            else
            {
                errorArchivo("Reportes.txt");
            }
            escribirReportes.close();
            break;

        case MOSTRAR: // Mostrar tecnicos

            system(CLEAR);
            if (numReportes > 0)
            {
                cout << "REPORTES REGISTRADOS" << endl << endl;
                mostrarReportes();
                cin.ignore();
                cout << endl << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("reportes");
            }
            break;

        case BUSCAR: // Busqueda de una cita
            if (numReportes > 0)
            {
                system(CLEAR);
                cout << "BUSCAR REPORTE" << endl << endl;
                cin.ignore();
                cout << "Ingresa el codigo del reporte a buscar: ";
                getline(cin, codigo);
                encontrado = buscarReporte(codigo);
                if (encontrado == true)
                {
                    cout << endl << "Registro encontrado..." << endl << endl;
                    mostrarUnReporte(codigo);
                }
                else
                {
                    cout << "No se encontro ningun reporte con ese codigo..." << endl << endl;
                }
                cout << endl;
                pausar();
            }
            else
            {
                errorRegistroInexistente("reporte");
            }
            break;

        case MODIFICAR:
            if (numReportes > 0)
            {
                system(CLEAR);
                cout << "MODIFICAR UN REGISTRO" << endl << endl;
                cin.ignore();
                cout << "Ingresa el codigo del reporte a modificar: ";
                getline(cin, codigo);
                encontrado = buscarReporte(codigo);
                if (encontrado == true)
                {
                    modificarReporte(codigo);
                }
                else
                {
                    cout << "No se encontro ningun reporte con ese codigo..." << endl << endl;
                }
                pausar();
            }
            else
            {
                errorRegistroInexistente("reporte");
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

void Reporte::agregarReporte()
{
    bool encontrado = false;
    Cliente auxCliente;
    Cita auxCita;
    string codigo;
    string codigoCita;
    float costoTotal;
    system(CLEAR);
    cout << "REGISTRO DE NUEVO REPORTE" << endl << endl;
    cout << numReportes << " registros de " << MAX_REPORTES << " posibles..." <<endl << endl;
    cout << "Ingresa los datos del reporte..." << endl;
    cin.ignore();
    cout << "Codigo: ";
    getline(cin, codigo);
    do
    {
        cout << "Codigo de la cita: ";
        getline(cin, codigoCita);
        encontrado = auxCita.buscarCita(codigoCita);
        if (encontrado == false)
        {
            cout << "El codigo de la cita es incorrecto. Vuelve a capturar..." << endl << endl;
        }
    }
    while (encontrado == false);
    cout << "Costo total: ";
    cin >> costoTotal;
    // Llamadas a metodos setters de la clase
    fijaCodigo(codigo);
    fijacodigoCita(codigoCita);
    fijaCostoTotal(costoTotal);
}

void Reporte::mostrarReportes()
{
    Cita auxCita;
    ifstream leerReportes;
    ifstream leerNumReportes;
    string codigo;
    string codigoCita;
    float costoTotal;
    string extraLine;
    leerReportes.open("Reportes.txt", ios::in);
    if (leerReportes.is_open())
    {
        getline(leerReportes,codigo);
        while (!leerReportes.eof())
        {
            getline(leerReportes,codigoCita);
            leerReportes >> costoTotal;
            getline(leerReportes,extraLine);
            getline(leerReportes,extraLine);
            cout << "Codigo de Reporte:     " << codigo << endl;
            cout << "Info de la Cita..."<< endl;
            auxCita.mostrarUnaCita(codigoCita);
            cout << "Costo total:           " << costoTotal << endl;
            cout << "---------------------------------------------------------------------" << endl;
            getline(leerReportes,codigo);
        }
    }
    else
    {
        errorArchivo("Tecnicos.txt");
    }
    leerReportes.close();
}

void Reporte::mostrarUnReporte(string codigox)
{
    bool encontrado = false;
    Cita auxCita;
    ifstream leerReportes;
    ifstream leerNumReportes;
    string codigo;
    string codigoCita;
    float costoTotal;
    string extraLine;
    leerReportes.open("Reportes.txt", ios::in);
    if (leerReportes.is_open())
    {
        getline(leerReportes,codigo);
        while (!leerReportes.eof() && encontrado == false)
        {
            getline(leerReportes,codigoCita);
            leerReportes >> costoTotal;
            getline(leerReportes,extraLine);
            getline(leerReportes,extraLine);
            if (codigox == codigo)
            {
                cout << "Codigo:                " << codigo << endl;
                cout << "Info de la Cita..." << endl;
                auxCita.mostrarUnaCita(codigoCita);
                cout << "Costo total:           " << costoTotal << endl;
                encontrado = true;
            }
            else
            {
                getline(leerReportes,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Tecnicos.txt");
    }
    leerReportes.close();
}

bool Reporte::buscarReporte(string codigox)
{
    bool encontrado = false;
    ifstream leerReportes;
    string codigo;
    string codigoCliente;
    string codigoTecnico;
    string codigoCita;
    float costoTotal;
    string extraLine;
    leerReportes.open("Reportes.txt", ios::in);
    if (leerReportes.is_open())
    {
        getline(leerReportes,codigo);
        while (!leerReportes.eof() && encontrado == false)
        {
            getline(leerReportes,codigoCliente);
            leerReportes >> costoTotal;
            getline(leerReportes,extraLine);
            getline(leerReportes,extraLine);
            if (codigox == codigo)
            {
                encontrado = true;
            }
            else
            {
                getline(leerReportes,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Reportes.txt");
    }
    leerReportes.close();
    return encontrado;
}

void Reporte::modificarReporte(string codigox)
{
    Cliente auxCliente;
    Tecnico auxTecnico;
    Cita auxCita;
    ofstream escribirReportes;
    ofstream escribirAuxiliar;
    ifstream leerReportes;
    bool encontrado;
    string codigo;
    string codigoCita, codigoCitax;
    float costoTotal, costoTotalx;
    string extraLine;
    int opcion;
    leerReportes.open("Reportes.txt",ios::in);
    escribirAuxiliar.open("Auxiliar.txt",ios::out);
    if (leerReportes.is_open() && escribirAuxiliar.is_open())
    {
        getline(leerReportes,codigo);
        while(!leerReportes.eof())
        {
            getline(leerReportes,codigoCita);
            leerReportes >> costoTotal;
            getline(leerReportes,extraLine);
            getline(leerReportes,extraLine);
            if (codigox == codigo)
            {
                mostrarUnReporte(codigo);
                do
                {
                    cout << endl << "Campo a modificar.." << endl;
                    cout << "1) Codigo de cita" << endl;
                    cout << "2) Costo total" << endl;
                    cout << "3) Regresar " << endl;
                    cout << "Elige una opcion: ";
                    cin >> opcion;
                    switch (opcion)
                    {
                    case CAMBIA_CODIGO_CITA:
                        system(CLEAR);
                        cin.ignore();
                        do
                        {
                            cout << "Ingresa el nuevo codigo de la cita: ";
                            getline(cin, codigoCitax);
                            encontrado = auxCita.buscarCita(codigoCitax);
                            if (encontrado == false)
                            {
                                cout << "El codigo de la cita es incorrecto.";
                                cout << "Vuelve a capturar..." << endl << endl;
                            }
                        }
                        while (encontrado == false);
                        escribirAuxiliar << codigo << endl
                                         << codigoCitax << endl
                                         << costoTotal << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;
                        break;
                    case CAMBIA_COSTO_TOTAL:
                        system(CLEAR);
                        cin.ignore();
                        cout << "Ingresa el nuevo costo: ";
                        cin >> costoTotalx;
                        escribirAuxiliar << codigo << endl
                                         << codigoCita << endl
                                         << costoTotalx << endl << endl;
                        cout << endl << "Registro modificado exitosamente..." << endl << endl;

                        break;
                    case SALIR:
                        break;
                    default:
                        errorEntradaInvalida();
                    } // fin de switch
                }
                while (!SALIR);
                getline(leerReportes,codigo);
            }
            else
            {
                escribirAuxiliar << codigo << endl
                                 << codigoCita << endl
                                 << costoTotal << endl << endl;
                getline(leerReportes,codigo);
            }
        }
    }
    else
    {
        errorArchivo("Reportes.txt");
    }
    leerReportes.close();
    escribirAuxiliar.close();
    remove("Reportes.txt");
    rename("Auxiliar.txt", "Reportes.txt");
}









