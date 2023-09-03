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

    bool Jugador::revisionCartas(){
        int carta1=0;
        int carta2=0;
        int carta3=0;
        int carta4=0;//Comodin
        if(cartasJugador.size()>=3){
            for(int i=0;i<cartasJugador.size();i++){
                if(cartasJugador[i].getTipoUnidad()=="Caballeria"){
                    carta1++;
                }
                if(cartasJugador[i].getTipoUnidad()=="Artilleria"){
                    carta2++;
                }
                if(cartasJugador[i].getTipoUnidad()=="Infanteria"){
                    carta3++;
                }
                if(cartasJugador[i].isComodin()){
                    carta4++;
                }
            }
            if(carta1>=1&&carta2>=1&&carta3>=1){
                return 1;
            }
            if(carta1>=3||carta2>=3||carta3>=3){
                return 1;
            }
            if(carta1>=1&&carta2>=1&&carta4>1||carta1>=1&&carta3>=1&&carta4>1||carta2>=1&&carta3>=1&&carta4>1){
                return 1;
            }
        }
        return 0;
    }

    

#endif
