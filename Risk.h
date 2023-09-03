// Risk.h
#ifndef RISK_H
#define RISK_H

//No se halló razon del porque se tuvo que utilizar in include con la clase Carta, sin ello falla
#include "Carta.h"

class Risk {
    
private:
    std::list<Continente> continentes;
    std::list<Jugador> jugadores;
    std::list<Carta> cartas;
    int turnoPartida=-1;

public:
    bool inicio_J = false;
    bool j_Terminado = false;
    
    void inicializar();
    int generarAleatorio();
    void turno(int turno);
    int moverInfanteria(std::list<Pais>::iterator primerPais, std::list<Pais>::iterator segundoPais);
    std::vector<int> dadosFunc(int cantidadDados);
    int ataquePais(std::list<Pais>::iterator atacantePais, std::list<Pais>::iterator defensorPais);
    std::list<Pais>::iterator seleccionTerrenoColindante(std::list<Pais>::iterator itdorDominio);
    std::list<Pais>::iterator seleccionTerrenoColindanteEnemigo(std::list<Pais>::iterator itdorDominio);
    std::list<Pais>::iterator seleccionDominio(std::list<Jugador>::iterator itdorJugador);
    int contadorTerritorios(std::list<Jugador>::iterator itdorJugador);
    
    
    
};

#include "Risk.hxx"

#endif
