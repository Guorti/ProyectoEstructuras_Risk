#ifndef CARTA_HXX
#define CARTA_HXX

#include "Carta.h"

//METODOS
void Carta::displayCartaInfo() {
    std::cout << "Obtuvo la carta\n";
    if(!isComodin()){
        std::cout << "Tipo Unidad: " << tipoUnidad << std::endl;
        std::cout << "Codigo Pais: " << codigoPais << std::endl;
    }else{
        std::cout << "Tipo Unidad: " << "Comodin" << std::endl;
    }



}


#endif
