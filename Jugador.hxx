#ifndef JUGADOR_HXX
#define JUGADOR_HXX

#include "Jugador.h"
#include <iostream>



//-----------------------
     //METODOS


    void Jugador::displayInfo() {
        std::cout << "idJugador: " << idJugador << std::endl;
        std::cout << "nombre: " << nombre << std::endl;
        std::cout << "color: " << color << std::endl;
        std::cout << "armadas: " << armadas << std::endl;
    }

bool Jugador::revisionCartas() {
    std::vector<Carta>::iterator itdorCarta = cartasJugador.begin();
    int cartaCount[4] = {0}; // Indice 0: Caballeria, 1: Artilleria, 2: Infanteria, 3: Comodin

    for (int i = 0; i < cartasJugador.size(); i++) {
        std::string tipo = cartasJugador[i].getTipoUnidad();
        if (tipo == "Caballeria") cartaCount[0]++;
        else if (tipo == "Artilleria") cartaCount[1]++;
        else if (tipo == "Infanteria") cartaCount[2]++;
        else if (cartasJugador[i].isComodin()) cartaCount[3]++;
    }

    if (cartaCount[0] >= 1 && cartaCount[1] >= 1 && cartaCount[2] >= 1) {
        // cada una de un tipo
        while (cartaCount[0] > 0 && cartaCount[1] > 0 && cartaCount[2] > 0) {
            itdorCarta = cartasJugador.begin();
            while (itdorCarta != cartasJugador.end()) {
                if ((itdorCarta->getTipoUnidad() == "Caballeria" && cartaCount[0] > 0) ||
                    (itdorCarta->getTipoUnidad() == "Artilleria" && cartaCount[1] > 0) ||
                    (itdorCarta->getTipoUnidad() == "Infanteria" && cartaCount[2] > 0)) {
                    itdorCarta = cartasJugador.erase(itdorCarta);
                    cartaCount[0]--;
                    cartaCount[1]--;
                    cartaCount[2]--;
                    break; // Exit inner loop
                } else {
                    ++itdorCarta;
                }
            }
        }
        return true;
    }

    if (cartaCount[0] >= 3) {
        // 3 cartas de Caballeria
        while (cartaCount[0] >= 3) {
            itdorCarta = cartasJugador.begin();
            while (itdorCarta != cartasJugador.end() && cartaCount[0] >= 3) {
                if (itdorCarta->getTipoUnidad() == "Caballeria") {
                    itdorCarta = cartasJugador.erase(itdorCarta);
                    cartaCount[0]--;
                } else {
                    ++itdorCarta;
                }
            }
        }
        return true;
    }

    if (cartaCount[1] >= 3) {
        // tres cartas de Artilleria
        while (cartaCount[1] >= 3) {
            itdorCarta = cartasJugador.begin();
            while (itdorCarta != cartasJugador.end() && cartaCount[1] >= 3) {
                if (itdorCarta->getTipoUnidad() == "Artilleria") {
                    itdorCarta = cartasJugador.erase(itdorCarta);
                    cartaCount[1]--;
                } else {
                    ++itdorCarta;
                }
            }
        }
        return true;
    }

    if (cartaCount[2] >= 3) {
        // 3 cartas de Infanteria
        while (cartaCount[2] >= 3) {
            itdorCarta = cartasJugador.begin();
            while (itdorCarta != cartasJugador.end() && cartaCount[2] >= 3) {
                if (itdorCarta->getTipoUnidad() == "Infanteria") {
                    itdorCarta = cartasJugador.erase(itdorCarta);
                    cartaCount[2]--;
                } else {
                    ++itdorCarta;
                }
            }
        }
        return true;
    }

    if (cartaCount[0] >= 1 && cartaCount[1] >= 1 && cartaCount[3] >= 2) {
        //  Caballeria, Artilleria y Comodin
        itdorCarta = cartasJugador.begin();
        while (itdorCarta != cartasJugador.end()) {
            if ((itdorCarta->getTipoUnidad() == "Caballeria" && cartaCount[0] > 0) ||
                (itdorCarta->getTipoUnidad() == "Artilleria" && cartaCount[1] > 0) ||
                (itdorCarta->isComodin() && cartaCount[3] >= 2)) {
                itdorCarta = cartasJugador.erase(itdorCarta);
                if (itdorCarta->getTipoUnidad() == "Caballeria") cartaCount[0]--;
                else if (itdorCarta->getTipoUnidad() == "Artilleria") cartaCount[1]--;
                else if (itdorCarta->isComodin()) cartaCount[3]--;
            } else {
                ++itdorCarta;
            }
        }
        return true;
    }

    return false;
}




#endif
