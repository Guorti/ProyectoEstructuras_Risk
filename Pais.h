// Pais.h
#ifndef PAIS_H
#define PAIS_H

class Pais {
private:
    int idPais;
    std::string nombrePais;
    int cantidadArmadas;
    int colorOcupacion;
    std::list<int> paisesColindantes;
    
public:
    Pais(int idPa, const std::string& nombre, int infanterias, int color, const std::list<int> paisesCol)
        : idPais(idPa), nombrePais(nombre), cantidadArmadas(infanterias), colorOcupacion(color), paisesColindantes(paisesCol) {}

 
    Pais() : idPais(-1), nombrePais(""), cantidadArmadas(0), colorOcupacion(0) {}
    
    int getIDPais() {
        return idPais;
      }

    std::string getNombrePais(){
      return nombrePais;
    }
    
    int getCantidadArmadas() {
        return cantidadArmadas;
    }

    int getColorOcupacion() {
        return colorOcupacion;
    }

    void setCantidadArmadas(int cInf) {
        cantidadArmadas=cInf;
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
