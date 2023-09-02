// Jugador.h
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

//CLASE JUGADOR-------------------------
class Jugador {
private:
    int idJugador;
    std::string nombre;
    int color;
    int armadas;
    int cartas=0;
    
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

    void setArmadas(int armadas){
      armadas = armadas;
    }
    
    void setCartas(int ncartas){
      cartas = ncartas;
    }

    int getCartas(){
      return cartas;
    }
    
    void displayInfo();

//------
};

#include "Jugador.hxx"

#endif