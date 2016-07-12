
// Inclusión de las clases del proyecto
#include "Tecnico.h"
#include "Cliente.h"
#include "Cita.h"
#include "Reporte.h"

// Librerías
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>

using namespace std;

// Establecer el máximo de registros de cada objeto
#define MAX_TECNICOS 5
#define MAX_CLIENTES 20
#define MAX_CITAS 20
#define MAX_REPORTES 20

// Para portabilizar la funcion limpiar pantalla
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

// Uso de constantes simbólicas para los case del switch
#define TECNICOS 1
#define CLIENTES 2
#define CITAS 3
#define REPORTES 4
#define SALIR 5
#define AGREGAR 1
#define MOSTRAR 2
#define BUSCAR 3
#define MODIFICAR 4
#define REGRESAR 5

// Prototipos de funciones
void menuTecnicos();
void menuClientes();
void menuCitas();
void menuReportes();
void fijarNumRegistros(char* cadena, int *nPtr);
void pausar();
void errorMenu(string cadena1, string cadena2);
void errorArchivo(string archivo);
void errorEntradaInvalida();
void errorAgregarRegistro(string cadena);
void errorRegistroInexistente(string cadena);
int menuClase(string cadena);
int menuAgregarRegistro();

// Variables globales
int numClientes;
int numTecnicos;
int numCitas;
int numReportes;

// Inicio del programa
int main()
{
    Cliente clientes;
    Tecnico tecnicos;
    Cita citas;
    Reporte reportes;
    int *ptrNumTec;
    int *ptrNumCli;
    int *ptrNumCit;
    int *ptrNumRep;
    ptrNumTec = &numTecnicos;
    ptrNumCli = &numClientes;
    ptrNumCit = &numCitas;
    ptrNumRep = &numReportes;

    fijarNumRegistros("NumTecnicos.txt", ptrNumTec);
    fijarNumRegistros("NumClientes.txt", ptrNumCli);
    fijarNumRegistros("NumCitas.txt", ptrNumCit);
    fijarNumRegistros("NumReportes.txt", ptrNumRep);

    int opcionMenuPrincipal;
    do
    {
        system(CLEAR);
        cout << "*************NUCLEO DE DIAGNOSTICO**********\n\n";
        cout << "Menu Principal:" << endl << endl;
        cout << "1) Menu Tecnicos" << endl;
        cout << "2) Menu Clientes" << endl;
        cout << "3) Menu Citas " << endl;
        cout << "4) Menu Reportes" << endl;
        cout << "5) Salir del programa" << endl;
        cout << "\nElige una opcion:  ";
        cin >> opcionMenuPrincipal;

        switch (opcionMenuPrincipal)
        {
        case TECNICOS:
            tecnicos.menuTecnicos();
            break;
        case CLIENTES:
            if (numTecnicos > 0) { clientes.menuClientes(); }
            else { errorMenu("Tecnicos","Clientes"); cin.ignore(); };
            break;
        case CITAS:
            if (numClientes > 0) { citas.menuCitas(); }
            else { errorMenu("Clientes","Citas"); cin.ignore(); }
            break;
        case REPORTES:
            if (numCitas > 0) { reportes.menuReportes(); }
            else { errorMenu("Citas","Reportes"); cin.ignore(); };
            break;
        case SALIR:
            ;
            break;
        default:
            cin.ignore();
            errorEntradaInvalida();
        }

    }
    while (opcionMenuPrincipal != SALIR);
    return 0;
}

void fijarNumRegistros(char* cadena, int *nPtr)
{
    ofstream escritura;
    ifstream lectura;
    FILE * archivo;
    archivo = fopen(cadena, "r");
    if (archivo == NULL)
    {
        escritura.open(cadena, ios::out);
        *nPtr = 0;
        escritura << *nPtr;
        escritura.close();
        fclose(archivo);
    }
    else
    {
        lectura.open(cadena, ios::in);
        if (lectura.is_open())
        {
            lectura >> *nPtr;
            lectura.close();
        }
        else
        {
            errorArchivo(cadena);
        }
    }
}

void pausar()
{
    cout << "Presione ENTER para continuar...";
    cin.ignore();
}

void errorMenu(string cadena1, string cadena2)
{
    system(CLEAR);
    cout << "Aun no hay "<<cadena1<<" registrados(as).";
    cout << " Imposible acceder al menu "<< cadena2 << ".";
    cout << endl << endl;
    pausar();
}

void errorArchivo(string archivo)
{
    system(CLEAR);
    cout << "Error al abrir el archivo " << archivo;
    cout << ". El programa se cerrara." << endl << endl;
    pausar();
    exit(1);
}

void errorEntradaInvalida()
{
    cout << endl << endl;
    cout << "Entrada invalida. Vuelve a elegir por favor..." << endl << endl;
    pausar();
}

void errorAgregarRegistro(string cadena)
{
    cout << "Ya no se pueden agregar mas " << cadena << "..." << endl << endl;
    cin.ignore();
    pausar();
}

void errorRegistroInexistente(string cadena)
{
    cout << "Aun no hay " << cadena << " registrados(as)..." << endl << endl;
    cin.ignore();
    pausar();
}

int menuClase(string cadena)
{
    int opcion;
    system(CLEAR);
    cout << "NUCLEO DE DIAGNOSTICO" << endl << endl;
    cout << "Menu " << cadena << "s" <<endl << endl;
    cout << "1) Agregar " << cadena <<endl;
    cout << "2) Mostrar " << cadena << "(s) registrados" << endl;
    cout << "3) Buscar " << cadena << endl;
    cout << "4) Modificar un registro de " << cadena << endl;
    cout << "5) Regresar" << endl << endl;
    cout << "Elige una opcion:  ";
    cin >> opcion;
    return opcion;
}

int menuAgregarRegistro()
{
    int opcion;
    system(CLEAR);
    cout << "Deseas agregar otro registro\?" << endl << endl;
    cout << "1) Si" << endl;
    cout << "2) No" << endl << endl << "Elige: ";
    cin >> opcion;
    if (opcion < 1 || opcion > 2)
    {
        errorEntradaInvalida();
    }
    return opcion;
}



