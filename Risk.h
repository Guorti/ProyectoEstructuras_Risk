// Risk.h
#ifndef RISK_H
#define RISK_H

class Risk {
    
private:
    std::list<Continente> continentes;
  std::list<Jugador> jugadores;
  int turnoPartida=-1;

public:
    bool inicio_J = false;
    bool j_Terminado = false;
    
    void inicializar();
    int lanzarDado();
    void turno(int turno);
    int moverInfanteria(std::list<Pais>::iterator primerPais, std::list<Pais>::iterator segundoPais);
    std::vector<int> dadosRojosFunc();
    std::vector<int> dadosBlancosFunc();
    int ataquePais(std::list<Pais>::iterator atacantePais, std::list<Pais>::iterator defensorPais);
    std::list<Pais>::iterator seleccionTerrenoColindante(std::list<Pais>::iterator itdorDominio);
    std::list<Pais>::iterator seleccionTerrenoColindanteEnemigo(std::list<Pais>::iterator itdorDominio);
    std::list<Pais>::iterator seleccionDominio(std::list<Jugador>::iterator itdorJugador);
    
    
    
};

#include "Risk.hxx"

#endif
