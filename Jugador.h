// Jugador.h
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Carta.h"

//CLASE JUGADOR-------------------------
class Jugador {
private:
    int idJugador;
    std::string nombre;
    int color;
    int armadas;
    std::vector<Carta> cartasJugador;
    
public:
    Jugador(int id, const std::string& nombre, int color, int unidadesInf)
        : idJugador(id), nombre(nombre), color(color), armadas(unidadesInf) {}

    Jugador() : idJugador(0), nombre(""), color(0), armadas(0) {}
    
    
    int getIdJugador (){
      return idJugador;
    }

    std::string getNombre(){
      return nombre;
    }


    int getColor (){
      return color;
    }


    int getArmadas(){
      return armadas;
    }

    void setArmadas(int armies){
      armadas = armies;
    }

    std::vector<Carta>&  getCartasVector(){
      return cartasJugador;
    }

    bool revisionCartas();

    void displayInfo();

//------
};

#include "Jugador.hxx"

#endif