#ifndef REPORTE_H
#define REPORTE_H

#include <iostream>

using namespace std;


class Reporte
{
    friend class Cita;

    public:
        Reporte();
        virtual ~Reporte();
        // Setters
        void fijaCodigo(string val){codigo=val;};
        void fijacodigoCita(string val){codigoCita=val;};
        void fijaCostoTotal(float val){costoTotal=val;};
        // Getters
        string dameCodigo(){return codigo;};
        string dameCodigoCita(){return codigoCita;};
        float dameCostoTotal(){return costoTotal;};
        // Funciones miembro
        void menuReportes();
        void agregarReporte();
        void mostrarReportes();
        void mostrarUnReporte(string codigox);
        bool buscarReporte(string x);
        void modificarReporte(string x);
    protected:
    private:
        string codigo;
        string codigoCita;
        float costoTotal;
};

#endif // REPORTE_H
