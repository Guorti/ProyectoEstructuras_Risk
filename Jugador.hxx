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

    

#endif
