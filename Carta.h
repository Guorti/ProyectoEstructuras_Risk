// Carta.h
#ifndef CARTA_H
#define CARTA_H


class Carta {
private:
    
    std::string tipoUnidad;
    int codigoPais;
    bool comodin;
    
public:
    Carta(const std::string& tipoU, int codigoP, bool comod) : tipoUnidad(tipoU), codigoPais(codigoP), comodin(comod) {}
    Carta() : tipoUnidad(""), codigoPais(-1), comodin(0) {}
    
    std::string getTipoUnidad() {
        return tipoUnidad;
      }

    int getCodigoPais() {
        return codigoPais;
      }

    bool isComodin() {
        return comodin;
      }

    void displayCartaInfo();

};

#include "Carta.hxx"

#endif