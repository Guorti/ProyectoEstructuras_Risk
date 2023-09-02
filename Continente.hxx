#ifndef CONTINENTE_HXX
#define CONTINENTE_HXX

#include "Continente.h"

//-----------------------
  //METODOS
  void Continente::displayInfo() {
        std::cout << "Nombre Continente: " << nombreContinente << std::endl;
        for (std::list<Pais>::iterator itdor = paises.begin(); itdor != paises.end();++itdor) {
          itdor->displayInfo();
    }  
  }



#endif
