#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>

using namespace std;

class Cliente
{
    public:
        Cliente();
        virtual ~Cliente();
        // Setters
        void fijaCodigo(string val){codigo=val;};
        void fijaNombre(string val){nombre=val;};
        void fijaFechaNac(string val){fechaNacimiento=val;};
        void fijaDireccion(string val){direccion=val;};
        void fijaTelMovil(string val){telefonos[0]=val;};
        void fijaTelCasa(string val){telefonos[1]=val;};
        void fijaTelRecados(string val){telefonos[2]=val;};
        // Getters
        string dameCodigo(){return codigo;};
        string dameNombre(){return nombre;};
        string dameFechaNac(){return fechaNacimiento;};
        string dameDireccion(){return direccion;};
        string dameTelMovil(){return telefonos[0];};
        string dameTelCasa(){return telefonos[1];};
        string dameTelRecados(){return telefonos[2];};
        // Funciones miembro
        void menuClientes();
        void agregarCliente();
        void mostrarClientes();
        void mostrarUnCliente(string codigox);
        bool buscarCliente(string x);
        void modificarCliente(string x);
    protected:
    private:
        string codigo;
        string nombre;
        string fechaNacimiento;
        string direccion;
        string telefonos[3];
};

#endif // CLIENTE_H
