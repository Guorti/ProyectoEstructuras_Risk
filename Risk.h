// Risk.h
#ifndef RISK_H
#define RISK_H

//No se halló razon del porque se tuvo que utilizar in include con la clase Carta, sin ello falla
#include "Carta.h"
#include "binary_tree/BinaryTree.h"
#include "huffman_data/HuffmanData.h"
#include <string>
#include "Continente.h"
#include "Pais.h"

class Risk {

private:

    int cantidadJugadores;
    std::list<int> turnosJugadores;

    std::list<Continente> continentes;
    std::list<Jugador> jugadores;
    std::vector<Carta> cartas;
    int turnoPartida=-1;
    int reclamoCartas=2;

    BinaryTree<HuffmanData> huffmanTree;


public:
    unordered_map<char, string> Mappeo;

    bool inicio_J = false;
    bool j_Terminado = false;

    list<Jugador>& getJugadores();
    list<int>& getTurnosJugadores();


    void setTurnoPartida(int turnoPartida);
    void setReclamoCartas(int reclamoCartas);


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
    void sacarCarta(std::list<Jugador>::iterator itdorJugador);
    void ingresarTropas(std::list<Jugador>::iterator itdorJugador);

    void guardarPartidaText(std::string nombreArchivo);

    void guardarPartidaBin(std::string nombreArchivo);

    void allDataToString(std::ostringstream &ss);

    void inicializarPartida(std::string nombreArchivo);

    void setTestData();

};

#include "Risk.hxx"

#endif
