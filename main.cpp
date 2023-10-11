#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "Jugador.h"
#include "Pais.h"
#include "Continente.h"
#include "Risk.h"
#include "Carta.h"


std::string consola;

//INTERFAZ



int main() {


    srand(time(NULL));

  Risk Risk1;
  string nombreArchivo;

    std::cout << " .----------------.  .----------------.  .----------------.  .----------------. \n";
    std::cout << "| .--------------. || .--------------. || .--------------. || .--------------. |\n";
    std::cout << "| |  _______     | || |     _____    | || |    _______   | || |  ___  ____   | |\n";
    std::cout << "| | |_   __ \\    | || |    |_   _|   | || |   /  ___  |  | || | |_  ||_  _|  | |\n";
    std::cout << "| |   | |__) |   | || |      | |     | || |  |  (__ \\_|  | || |   | |_/ /    | |\n";
    std::cout << "| |   |  __ /    | || |      | |     | || |   '.___`-.   | || |   |  __'.    | |\n";
    std::cout << "| |  _| |  \\ \\_  | || |     _| |_    | || |  |`\\____) |  | || |  _| |  \\ \\_  | |\n";
    std::cout << "| | |____| |___| | || |    |_____|   | || |  |_______.'  | || | |____||____| | |\n";
    std::cout << "| |              | || |              | || |              | || |              | |\n";
    std::cout << "| '--------------' || '--------------' || '--------------' || '--------------' |\n";
    std::cout << " '----------------'  '----------------'  '----------------'  '----------------' \n";

    std::cout<<"Bienvenido"<<std::endl;
    while(consola!= "salir"){
      int numeroTurno;
      std::string numero ;
      std::string consolaTurno;

        std::cout<<std::endl<<"$ ";
        getline(std::cin, consola);
        std::cout<<std::endl;
     
      if(consola == "turno 1" || consola == "turno 2"||consola == "turno 3"|| consola == "turno 4"|| consola == "turno 5"|| consola == "turno 6"){
if (!consola.empty()) {
      consolaTurno =consola.substr(0,5);;
      numero = consola.substr(6,1);
}
      }
       
     
      if(consolaTurno == "turno" && numero == "1"){
        numeroTurno = 1;
      }else if(consolaTurno == "turno" && numero == "2"){
        numeroTurno = 2;
      }else if(consolaTurno == "turno" && numero == "3"){
        numeroTurno = 3;
      }else if(consolaTurno == "turno" && numero == "4"){
        numeroTurno = 4;
      }else if(consolaTurno == "turno" && numero == "5"){
        numeroTurno = 5;
      }else if(consolaTurno == "turno" && numero == "6"){
        numeroTurno = 6;
      }

        if(consola == "help"){
            std::cout<<"Estos son los comandos disponibles, digite help <comando deseado> para conocer la funcion del comando:"<<std::endl;
            std::cout<<"\ninicializar"<<std::endl;
            std::cout<<"\nsalir"<<std::endl;
            std::cout<<"\nturno <id_jugador>: "<<std::endl;
            std::cout<<"\nguardar <nombre_archivo>"<<std::endl;
            std::cout<<"\nguardar_comprimido <nombre_archivo>"<<std::endl;
            std::cout<<"\ncosto_conquista <territorio>"<<std::endl;
            std::cout<<"\nconquista_mas_barata"<<std::endl;

        }

        else if(consola == "help inicializar"){
            std::cout<<"inicializar: Este comando inicializa el juego."<<std::endl;
            std::cout<<std::endl;
            std::cout<<"inicializar <nombre_archivo>: Este comando te permite iniciar el juego con el archivo de nombre <nombre_archivo> o un archivo binario."<<std::endl;
        }

        else if(consola=="help salir"){
            std::cout<<"salir: Este comando te permite salir del juego, finalizar el programa."<<std::endl;
        }
        else if(consola=="help turno"){
            std::cout<<"turno: Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)."<<std::endl;
        }
        else if(consola=="help guardar_comprimido"){
            std::cout<<"guardar_comprimido <nombre_archivo>: Este archivo guarda la partida en un archivo binario usando la codificacion de Huffman."<<std::endl;
        }
        else if(consola =="help guardar"){
            std::cout<<"guardar <nombre_archivo>: El comando guarda el juego en un archivo de texto sin codificacion, que contiene la cantidad de jugadores, y los datos de cada uno."<<std::endl;
        }
        else if(consola == "help conquista_mas_barata"){
            std::cout<<"conquista_mas_barata: Este comando calcula el territorio que resulte en la menor pérdida de unidades de ejército para el jugador en su turno."<<std::endl;
        }
        else if(consola =="help costo_conquista"){
            std::cout<<"costo_conquista <territorio>: El programa calcula el costo y la secuencia de territorios a conquistar para que el jugador controle un territorio dado por él. Ataca desde el territorio más cercano que ya controla."<<std::endl;
        }
       else if(consolaTurno == "turno"){
           
Risk1.turno(numeroTurno);
           
        }else if (consola == "conquista_mas_barata"){
            std::cout<<"Comando exitoso!"<<std::endl;
        }else if(consola =="salir"){
           
        }
        else if(consola =="inicializar archivo"){
            if(Risk1.inicio_J == true){
                std::cout<<"(Juego en curso) El juego ya ha sido inicializado."<<std::endl;
            }else{
                std::cout<<"Ingrese el nombre del archivo a cargar."<<std::endl;
                std::cin>> nombreArchivo;
                //Risk1.allDataToString();
                Risk1.inicializarPartida(nombreArchivo);
                std::cout<<"Comando exitoso!"<<std::endl;
            }

        }else if(consola=="guardar"){
           if(Risk1.inicio_J == false){
               std::cout<<"(Juego no inicializado) Esta partida no ha sido inicializada correctamente."<<std::endl;
           }else{
               std::cout<<"Ingrese el nombre del nuevo archivo."<<std::endl;
               std::cin>> nombreArchivo;
               //Risk1.allDataToString();
               Risk1.guardarPartida(nombreArchivo);
               std::cout<<"Comando exitoso!"<<std::endl;
           }


        }else if(consola =="inicializar"){
            if(Risk1.inicio_J == false){
                Risk1.inicio_J = true;
              Risk1.inicializar();
            } else {
                std::cout<<"(Juego en curso) El juego ya ha sido inicializado"<<std::endl;
            }
        }else if(consola =="guardar_comprimido"){
            std::cout<<"Comando exitoso!"<<std::endl;
        }else if(consola =="costo_conquista"){
            std::cout<<"Comando exitoso!"<<std::endl;
        }else{
            std::cout<<"Error: '"<<consola<<"' no es un comando, use help para conocer los comandos disponibles."<<std::endl;
        }

    }
    return 0;
}
