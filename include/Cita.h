#ifndef CITA_H
#define CITA_H

#include <iostream>

using namespace std;

class Cita
{
    friend class Tecnico;
    friend class Cliente;
    public:
        Cita();
        virtual ~Cita();
        // Setters
        void fijaCodigo(string val){codigo=val;};
        void fijaCodigoCliente(string val){cliente=val;};
        void fijaCodigoTecnico(string val){tecnico=val;};
        void fijaDiaCita(string val){diaCita=val;};
        void fijaHoraCita(string val){horaCita=val;};
        // Getters
        string dameCodigo(){return codigo;};
        string dameCodigoCliente(){return cliente;};
        string dameCodigoTecnico(){return tecnico;};
        string dameDiaCita(){return diaCita;};
        string dameHoraCita(){return horaCita;};
        // Funciones miembro
        void menuCitas();
        void agregarCita();
        void mostrarCitas();
        void mostrarUnaCita(string codigox);
        bool buscarCita(string x);
        bool buscarFecha(string diax, string horax);
        void modificarCita(string x);
    protected:
    private:
        string codigo;
        string cliente;
        string tecnico;
        string diaCita;
        string horaCita;
};

#endif // CITA_H
