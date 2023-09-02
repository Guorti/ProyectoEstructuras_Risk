// Jugador.h
#ifndef JUGADOR_H
#define JUGADOR_H

//CLASE JUGADOR-------------------------
class Jugador {
private:
    int idJugador;
    std::string nombre;
    int color;
    int unidadesInfanteria;
    int cartas=0;
    
public:
    Jugador(int id, const std::string& nombre, int color, int unidadesInf)
        : idJugador(id), nombre(nombre), color(color), unidadesInfanteria(unidadesInf) {}

    Jugador() : idJugador(0), nombre(""), color(0), unidadesInfanteria(0) {}
    
    
    int getIdJugador (){
      return idJugador;
    }

    std::string getNombre(){
      return nombre;
    }


    int getColor (){
      return color;
    }


    int getUnidadesInfanteria(){
      return unidadesInfanteria;
    }

    void setUnidadesInfanteria(int UnidadesInfanteria){
      unidadesInfanteria = UnidadesInfanteria;
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