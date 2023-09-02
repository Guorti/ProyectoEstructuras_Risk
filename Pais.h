// Pais.h
#ifndef PAIS_H
#define PAIS_H

class Pais {
private:
    int idPais;
    std::string nombrePais;
    int cantidadInfanterias;
    int colorOcupacion;
    std::list<int> paisesColindantes;
    
public:
    Pais(int idPa, const std::string& nombre, int infanterias, int color, const std::list<int> paisesCol)
        : idPais(idPa), nombrePais(nombre), cantidadInfanterias(infanterias), colorOcupacion(color), paisesColindantes(paisesCol) {}

 
    Pais() : idPais(-1), nombrePais(""), cantidadInfanterias(0), colorOcupacion(0) {}
    
    int getIDPais() {
        return idPais;
      }

    std::string getNombrePais(){
      return nombrePais;
    }
    
    int getCantidadInfanterias() {
        return cantidadInfanterias;
    }

    int getColorOcupacion() {
        return colorOcupacion;
    }

    void setCantidadInfanterias(int cInf) {
        cantidadInfanterias=cInf;
    }

    void setColorOcupacion(int cOcupacion) {
        colorOcupacion=cOcupacion;
    }

    std::list<int>& getPaisesColindantes() {
        return paisesColindantes;
    }
    
    
    void displayInfo();
    void getInfoPais();

};

#include "Pais.hxx"

#endif
