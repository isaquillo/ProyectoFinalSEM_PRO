#ifndef TECNICO_H
#define TECNICO_H

#include <iostream>

using namespace std;

class Tecnico
{
    public:
        Tecnico();
        virtual ~Tecnico();
        // Setters
        void fijaCodigo(string val){codigo=val;};
        void fijaNombre(string val){nombre=val;};
        void fijaFechaNac(string val){fechaNacimiento=val;};
        void fijaDireccion(string val){direccion=val;};
        void fijaTelMovil(string val){telefonos[0]=val;};
        void fijaTelCasa(string val){telefonos[1]=val;};
        // Getters
        string dameCodigo(){return codigo;};
        string dameNombre(){return nombre;};
        string dameFechaNac(){return fechaNacimiento;};
        string dameDireccion(){return direccion;};
        string dameTelMovil(){return telefonos[0];};
        string dameTelCasa(){return telefonos[1];};
        // Funciones miembro
        void menuTecnicos();
        void agregarTecnico();
        void mostrarTecnicos();
        void mostrarUnTecnico(string codigox);
        bool buscarTecnico(string x);
        void modificarTecnico(string x);
    protected:
    private:
        string codigo;
        string nombre;
        string fechaNacimiento;
        string direccion;
        string telefonos[2];
};

#endif // TECNICO_H
