#ifndef PAIS_HXX
#define PAIS_HXX

#include "Pais.h" // Include the main header for declarations




//-----------------------
    //METODOS
    void Pais::displayInfo() {
        std::cout << "id Pais: " << idPais << std::endl;
        std::cout << "Nombre Pais: " << nombrePais << std::endl;
        std::cout << "Cantidad Armadas: " << cantidadArmadas << std::endl;
        std::cout << "Color Ocupacion: " << colorOcupacion << std::endl<<std::endl;
    }


    

    void Pais::getInfoPais() {
        std::cout<<"("<<idPais<<") "<<nombrePais<<std::endl;
        std::cout << "Cantidad Armadas: " << cantidadArmadas << std::endl;
        std::cout << "Color Ocupacion: " << colorOcupacion << std::endl<<std::endl;
    }

    

#endif
