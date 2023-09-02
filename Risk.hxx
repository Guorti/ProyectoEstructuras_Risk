#ifndef RISK_HXX
#define RISK_HXX

#include "Risk.h"


  void Risk::inicializar(){
    int cantidadJugadores;
    int cantidadFichas;
    bool flag;
    std::string nombre;
    int color;
    int opcionColor=0;
    std::list<int> coloresList = {1, 2, 3, 4, 5, 6};
    int contador=0;
    std::list<int> turnosJugadores;
    int consolaContinente;
    int consolaPais;


    continentes.push_back(
        Continente(0, "America del Norte", {
            Pais(1,"Alaska", 0, 0, {6,2,22}),
            Pais(2,"Alberta", 0, 0, {1,2,6,9,7}),
            Pais(3,"América Central", 0, 0, {32,9,4}),
            Pais(4,"Estados Unidos Orientales", 0, 0, {3,9,7,8}),
            Pais(5,"Groenlandia", 0, 0, {6,7,8,11}),
            Pais(6,"Territorio Noroccidental", 0, 0, {1,2,7,5}),
            Pais(7,"Ontario", 0, 0, {6,2,9,4,8,5}),
            Pais(8,"Quebec", 0, 0, {5,7,4}),
            Pais(9,"Estados Unidos Occidentales", 0, 0, {2,7,4,3}),
        })
    );

    continentes.push_back(
        Continente(1, "Europa", {
            Pais(10,"Gran Bretaña", 0, 0, {11,13,12,16}),
            Pais(11,"Islandia", 0, 0, {5,13,10}),
            Pais(12,"Europa del Norte", 0, 0, {10,16,14,13}),
            Pais(13,"Escandinavia", 0, 0, {11,10,12,15}),
            Pais(14,"Europa del Sur", 0, 0, {12,16,15,23,37,35}),
            Pais(15,"Ucrania", 0, 0, {13,12,14,23,17,27}),
            Pais(16,"Europa Occidental", 0, 0, {10,12,14,37}),
        })
    );

    continentes.push_back(
        Continente(2, "Asia", {
            Pais(17,"Afghanistan", 0, 0, {18,19,27,23,15}),
            Pais(18,"China", 0, 0, {19,25,24,17}),
            Pais(19,"India", 0, 0, {25,18,17,23}),
            Pais(20,"Irkutsk", 0, 0, {24,22,28,26}),
            Pais(21,"Japon", 0, 0, {24,22}),
            Pais(22,"Kamchatka", 0, 0, {21,20,24,28}),
            Pais(23,"Medio Oriente", 0, 0, {17,19,15,35,14}),
            Pais(24,"Mongolia", 0, 0, {22,20,21,18,26}),
            Pais(25,"Siam", 0, 0, {40,18,19}),
            Pais(26,"Siberia", 0, 0, {20,18,27,28,24}),
            Pais(27,"Ural", 0, 0, {17,15,26}),
            Pais(28,"Yakutsk", 0, 0, {26,20,22,18}),
        })
    );

    continentes.push_back(
        Continente(3, "America del Sur", {
            Pais(29,"Argentina", 0, 0, {30,31}),
            Pais(30,"Brasil", 0, 0, {29,31,32,37}),
            Pais(31,"Peru", 0, 0, {29,30,32}),
            Pais(32,"Venezuela", 0, 0, {30,31,3}),
        })
    );

    continentes.push_back(
        Continente(4, "Africa", {
            Pais(33,"Congo", 0, 0, {34,37,38}),
            Pais(34,"Africa Oriental", 0, 0, {33,35,36,37,38}),
            Pais(35,"Egipto", 0, 0, {34,37,23,14}),
            Pais(36,"Madagascar", 0, 0, {34,38}),
            Pais(37,"Africa del Norte", 0, 0, {33,34,35,30,14,16}),
            Pais(38,"Africa del Sur", 0, 0, {33,34,36}),
        })
    );

    continentes.push_back(
        Continente(5,"Australia", {
            Pais(39,"Australia Oriental", 0, 0, {41,42}),
            Pais(40,"Indonesia", 0, 0, {41,42,25}),
            Pais(41,"Nueva Guinea", 0, 0, {39,40,42}),
            Pais(42,"Australia Occidental", 0, 0, {39,40,41}),
        })
    );


   

    system("cls");
    std::cout<<"(Inicializacion satisfactoria) El juego se ha inicializado correctamente!"<<std::endl<<std::endl;
    std::cout<<"Ingrese la cantidad de jugadores: ";
    std::cin>>cantidadJugadores;
    if(cantidadJugadores==2||cantidadJugadores>6){
      std::cout<<"No cumple la cantidad de jugadores necesarios"<<std::endl<<std::endl;
      inicio_J=false;
      return;
    }

 
   
    for(int i=1;i<cantidadJugadores+1;i++){
      flag=false;

    system("cls");
      std::cout<<"Jugador "<<i<<" ingrese su nombre: ";
      std::cin>>nombre;
   

        std::cout<<"\nSELECCION DEL COLOR"<<std::endl<<std::endl;
     

      do{
        for (std::list<int>::iterator itdor = coloresList.begin(); itdor != coloresList.end();       ++itdor){
          if(*itdor==1){
            std::cout<<"1.- Verde"<<std::endl;
          }
          if(*itdor==2){
            std::cout<<"2.- Azul"<<std::endl;
          }
          if(*itdor==3){
            std::cout<<"3.- Rojo"<<std::endl;
          }
          if(*itdor==4){
            std::cout<<"4.- Amarillo"<<std::endl;
          }
          if(*itdor==5){
            std::cout<<"5.- Negro"<<std::endl;
          }
          if(*itdor==6){
            std::cout<<"6.- Gris"<<std::endl;
          }
         
        }
        std::cout<<"\nJugador "<<i<<" digite alguno de los colores: ";  // (verde, azul, rojo, amarillo, negro y gris)
      std::cin>>opcionColor;

      for (std::list<int>::iterator itdor = coloresList.begin(); itdor != coloresList.end(); ++itdor) {
        if (*itdor == opcionColor) {
          flag=true;
          itdor = coloresList.erase(itdor);  // erase returns the next valid iterator
        }
      }
        if(flag==false){
          std::cout<<"Color invalido"<<std::endl;
        }
      }while(opcionColor<1||opcionColor>6||flag==false);

      if(cantidadJugadores==3){
        turnosJugadores = {1, 2, 3};
        cantidadFichas=35;
        jugadores.push_back(Jugador(i,nombre,opcionColor,35));
       
      }
      if(cantidadJugadores==4){
        turnosJugadores = {1, 2, 3, 4};
        cantidadFichas=30;
        jugadores.push_back(Jugador(i,nombre,opcionColor,30));
       
      }
      if(cantidadJugadores==5){
        turnosJugadores = {1, 2, 3, 4, 5};
        cantidadFichas=25;
        jugadores.push_back(Jugador(i,nombre,opcionColor,25));
       
      }
      if(cantidadJugadores==6){
        turnosJugadores = {1, 2, 3, 4, 5, 6};
        cantidadFichas=20;
        jugadores.push_back(Jugador(i,nombre,opcionColor,20));
       
      }
    }

    //MOSTRAR LA INTERFAZ PARA ELEGIR DONDE PONER INFANTERIA

    system("cls");

    std::cout<<"SELECCION DEL CONTINENTE!"<<std::endl;

    std::list<int>::iterator itdorT = turnosJugadores.begin();

    std::list<Jugador>::iterator itdorJugadores = jugadores.begin();

   

   
    //42 iteraciones para agregar 1 infanteria en todos los paises
    for(int i=0;i<42;i++){
      do{
      contador=0;
      //std::cout<<"\nJugador "<<*itdorT <<" estos son los continentes"<<std::endl<<std::endl;
     
      std::cout<<"\nJugador "<<itdorJugadores->getIdJugador()<<" estos son los continentes\n"<<std::endl;
     
      for (std::list<Continente>::iterator itdor = continentes.begin(); itdor != continentes.end();++itdor) {
        std::cout<<"("<<contador<<") "<<itdor->getNombreContinente()<<"\n";
        contador++;
      }
      std::cout<<"\nDigite alguno de los continentes: ";
      std::cin>>consolaContinente;

      std::cout<<std::endl;
   
    system("cls");

      if(consolaContinente == 0){
        std::cout<<"AMERICA DEL NORTE"<<std::endl<<std::endl;
      }else  if(consolaContinente == 1){
        std::cout<<"EUROPA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 2){
        std::cout<<"ASIA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 3){
        std::cout<<"AMERICA DEL SUR"<<std::endl<<std::endl;
      }else  if(consolaContinente == 4){
        std::cout<<"AFRICA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 5){
        std::cout<<"AUSTRALIA"<<std::endl<<std::endl;
      }

     
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
       
        if(itdorCont->getIdContinente()==consolaContinente){
          itdorCont->getPaises();
       
          flag=false;
          std::cout<<"Digite el pais que desea ocupar: ";
          std::cin>>consolaPais;
          //Funcion dentro de continente que itere sobre la lista de paises hasta que encuentre el
          //seleccionado por el usuario y modofique los datos respectivos
         
          for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
     
            if(itdorP->getIDPais()==consolaPais){
              flag=true;
              if(itdorP->getCantidadInfanterias()==0){

             
               
                itdorP->setColorOcupacion(itdorJugadores->getColor());
                itdorP->setCantidadInfanterias(itdorP->getCantidadInfanterias()+1);
                itdorJugadores->setUnidadesInfanteria(itdorJugadores->getUnidadesInfanteria()-1);

                system("cls");
                std::cout<<"\nEl jugador "<< itdorJugadores->getIdJugador()<<" reclamo el territorio "<<itdorP->getNombrePais()<<"!"<<std::endl;
                itdorJugadores->setCartas(itdorJugadores->getCartas()+1);
               

                if(itdorJugadores->getIdJugador()==jugadores.end()->getIdJugador()){
                  itdorJugadores=jugadores.begin();
                }else{
                  itdorJugadores++;
                }
              }else{
                 system("cls");
                std::cout<<"El territorio "<<itdorP->getNombrePais()<<" ya fue reclamado por el color "<<itdorP->getColorOcupacion()<<std::endl;
                flag=false;                
              }
             
           
          }
          }
     
      }
    }
      //ADELANTAR UN TURNO, HACE UN CONDICIONAL QUE REVISE SI EL TURNO ES IGUAL AL FINAL DE LA LISTA,
      //VUELVA A LA POSICION 1.
        }while(flag==false);
    }

   
    std::cout<<"\nSe han ocupado todos los territorios!!\n";
    std::cout<<"\nA continuacion cada jugador pondra de a una infanteria en cada uno de sus territorios!!\n";





int flagAux=false;
int consola;

    //---*

//CAMBIARLO POR LA CANTIDAD TOTAL DE TROPAS
itdorJugadores=jugadores.begin();
      do{
      //MUESTRA TERRENOS DONDE TIENE DOMINIOS
   

    std::cout<<"\nJugador "<<itdorJugadores->getIdJugador()<<" estos son sus territorios\n"<<std::endl;
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
        if(itdorP->getColorOcupacion()==itdorJugadores->getColor()){
          std::cout<<"("<<itdorCont->getIdContinente()<<") "<<itdorCont->getNombreContinente()<<"\n";
          break;
        }
      }
    }

      std::cout<<"\nDigite alguno de los continentes: ";
      std::cin>>consolaContinente;
      std::cout<<std::endl;
   
    system("cls");

      if(consolaContinente == 0){
        std::cout<<"AMERICA DEL NORTE"<<std::endl<<std::endl;
      }else  if(consolaContinente == 1){
        std::cout<<"EUROPA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 2){
        std::cout<<"ASIA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 3){
        std::cout<<"AMERICA DEL SUR"<<std::endl<<std::endl;
      }else  if(consolaContinente == 4){
        std::cout<<"AFRICA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 5){
        std::cout<<"AUSTRALIA"<<std::endl<<std::endl;
      }

    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
       
        if(itdorCont->getIdContinente()==consolaContinente){
          for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
            if(itdorP->getColorOcupacion()==itdorJugadores->getColor()){
              itdorP->getInfoPais();
            }
          }
          flag=false;
          std::cout<<"Si no puede ver ningun país disponible para ocupar, inserte cualquier numero para volver al menu de continentes"<<std::endl;
          std::cout<<"Digite el pais que desea ocupar: ";
          std::cin>>consolaPais;
          //Funcion dentro de continente que itere sobre la lista de paises hasta que encuentre el
          //seleccionado por el usuario y modofique los datos respectivos
         
          for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
     
            if(itdorP->getIDPais()==consolaPais&&itdorP->getColorOcupacion()==itdorJugadores->getColor()){
 
              if(itdorJugadores->getUnidadesInfanteria()>0){
                std::cout<<"Posee "<<itdorJugadores->getUnidadesInfanteria()<<" Unidades de infanteria\n";
                std::cout<<"Ingrese la cantidad de infanterias que ingresara: ";
                std::cin>>consola;
                if(itdorJugadores->getUnidadesInfanteria()>=consola){
                 itdorP->setCantidadInfanterias(itdorP->getCantidadInfanterias()+consola);
                  itdorJugadores->setUnidadesInfanteria(itdorJugadores->getUnidadesInfanteria()-consola);
                  system("cls");
                std::cout<<"\nEl jugador "<< itdorJugadores->getIdJugador()<<" agrego a "<<itdorP->getNombrePais()<<" "<< consola <<" Unidades"<<"!"<<std::endl;
                 
                    if(itdorJugadores->getIdJugador()==jugadores.end()->getIdJugador()){
                      itdorJugadores=jugadores.begin();
                    }else{
                      itdorJugadores++;
                    }
                }
              }else{
                 system("cls");
                std::cout<<"Jugador "<<itdorJugadores->getIdJugador()<<" no tiene unidades de infanteria\n";
                flag=false;
                itdorJugadores++;
              }
          }
          }
      }
    }
        contador=0;
        for (std::list<Jugador>::iterator itdorJug = jugadores.begin(); itdorJug != jugadores.end();++itdorJug) {
          contador=contador + itdorJug->getUnidadesInfanteria();
        }
        if(contador==0){
          flag=true;
        }
        }while(flag==false);
    return;
  }


 //----------------------------------------



//LANZAR DADO--------------------

int Risk::lanzarDado() {

    // Generar un número aleatorio entre 1 y 6
    return (std::rand() % 6) + 1;

}
//--------------------------------

//TURNO -------------------------------
  void Risk::turno(int turno){
      int colorJugador;
      int consolaPais;
      int consolaContinente;
      int opcion;
      int opcionAtacar;
      int opcionFortificar;
      int consola;
      bool flag;
      bool flag2;
      std::list<Jugador>::iterator itdorJugador;
      std::list<Pais>::iterator itdorPaisSeleccion;
      int turnoFinal;
      
      int paisesJugador;
   
    int cantidadJugadores =jugadores.size();
    
    itdorJugador=jugadores.end();
    turnoFinal=itdorJugador->getIdJugador();
   
    if(inicio_J==false){
        std::cout<<"(Juego no inicializado) Esta partida no ha sido inicializada correctamente\n";
        return;
    }
    if(j_Terminado==true){
        std::cout<<"(Juego terminado) Esta partida ya tuvo un ganador\n";
        return;
    }
    
    for (std::list<Jugador>::iterator itdorJug = jugadores.begin(); itdorJug != jugadores.end();++itdorJug) {
          if(turno==itdorJug->getIdJugador()){
              itdorJugador=itdorJug;
              flag=true;
          }
        }
   
    if(flag==false){
        std::cout<<"(Jugador no válido) El jugador "<<turno<<" no forma parte de esta partida\n";
        return;
    }
    if(turnoPartida==-1){
        std::list<Jugador>::iterator itdorJug = jugadores.begin();
        turnoPartida=itdorJug->getIdJugador();
    }
    if(turnoPartida!=turno){
        std::cout<<"(Jugador fuera de turno) No es el turno del jugador "<<turno<<"\n";
        return;
    }
    
   
   
    colorJugador=itdorJugador->getColor();
    
    //AGREGAR UN CONTADOR DE PAISES Y SI UN CONTADOR DA CERO, IGNORAR SU TURNO
    paisesJugador=0;
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
          if(itdorP->getColorOcupacion()==itdorJugador->getColor()){
              paisesJugador=paisesJugador+1;
          }
      }
    }
    if(paisesJugador==0){
        //SALTA EL TURNO SI ESTE JUGADOR YA NO TIENE PAISES
        if(turnoPartida==turnoFinal){
            turnoPartida=1;
        }else{
            turnoPartida++;
        }
            return;
    }
    
    
    //Cuenta los paises del jugador y si suman 42, finalizará el juego
    paisesJugador=0;
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
          if(itdorP->getColorOcupacion()==itdorJugador->getColor()){
              paisesJugador=paisesJugador+1;
          }
      }
    }
    if(paisesJugador==6){
        j_Terminado=true;
        std::cout<<"El jugador "<<itdorJugador->getNombre()<<" Ha ganado\n";
        return;
    }
    
   
    std::cout<<"El Jugador "<<itdorJugador->getIdJugador()<<" puede reclamar: "<<(itdorJugador->getCartas()/3)<<" Fichas\n";
    std::cout<<"Desea reclamarlas (1) SI (2)NO\n";
    std::cin>>opcion;
    if(opcion==1&&(itdorJugador->getCartas()/3)!=0){
        itdorJugador->setUnidadesInfanteria(itdorJugador->getUnidadesInfanteria()+(itdorJugador->getCartas()/3));
        itdorJugador->setCartas(0);
        flag=false;
        do{
      //MUESTRA TERRENOS DONDE TIENE DOMINIOS
   

    std::cout<<"\nJugador "<<itdorJugador->getIdJugador()<<" estos son sus territorios\n"<<std::endl;
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
        if(itdorP->getColorOcupacion()==itdorJugador->getColor()){
          std::cout<<"("<<itdorCont->getIdContinente()<<") "<<itdorCont->getNombreContinente()<<"\n";
          break;
        }
      }
    }

      std::cout<<"\nDigite alguno de los continentes: ";
      std::cin>>consolaContinente;
      std::cout<<std::endl;
   
    system("cls");

      if(consolaContinente == 0){
        std::cout<<"AMERICA DEL NORTE"<<std::endl<<std::endl;
      }else  if(consolaContinente == 1){
        std::cout<<"EUROPA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 2){
        std::cout<<"ASIA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 3){
        std::cout<<"AMERICA DEL SUR"<<std::endl<<std::endl;
      }else  if(consolaContinente == 4){
        std::cout<<"AFRICA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 5){
        std::cout<<"AUSTRALIA"<<std::endl<<std::endl;
      }

    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
       
        if(itdorCont->getIdContinente()==consolaContinente){
          for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
            if(itdorP->getColorOcupacion()==itdorJugador->getColor()){
              itdorP->getInfoPais();
            }
          }
          flag=false;
          std::cout<<"Si no puede ver ningun país disponible para ocupar, inserte cualquier numero para volver al menu de continentes"<<std::endl;
          std::cout<<"Digite el pais que desea ocupar: ";
          std::cin>>consolaPais;
          //Funcion dentro de continente que itere sobre la lista de paises hasta que encuentre el
          //seleccionado por el usuario y modofique los datos respectivos
         
          for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
     
            if(itdorP->getIDPais()==consolaPais&&itdorP->getColorOcupacion()==itdorJugador->getColor()){
                flag=true;
              if(itdorJugador->getUnidadesInfanteria()>0){
                std::cout<<"Posee "<<itdorJugador->getUnidadesInfanteria()<<" Unidades de infanteria\n";
                std::cout<<"Ingrese la cantidad de infanterias que ingresara: ";
                std::cin>>consola;
                if(itdorJugador->getUnidadesInfanteria()>=consola){
                 itdorP->setCantidadInfanterias(itdorP->getCantidadInfanterias()+consola);
                  itdorJugador->setUnidadesInfanteria(itdorJugador->getUnidadesInfanteria()-consola);
                  system("clear");
                std::cout<<"\nEl jugador "<< itdorJugador->getIdJugador()<<" agrego a "<<itdorP->getNombrePais()<<" "<< consola <<" Unidades"<<"!"<<std::endl;
               
                }else{
                    flag=false;
                }
              }
            }
        }
      }
    }
        }while(flag==false);
    }
   
   
    flag =false;
    flag2 =false;
    do{
        std::cout<<"\n\n\nATACAR!"<<std::endl;
        std::cout<<"A continuacion seleccione uno de sus dominios por el cual atacar\n";
        itdorPaisSeleccion=seleccionDominio(itdorJugador);
        flag = ataquePais(itdorPaisSeleccion, seleccionTerrenoColindanteEnemigo(itdorPaisSeleccion));
        std::cout<<"Desea dejar de atacar? (1) Si - (0) No"<<std::endl;
            std::cin>>opcionAtacar; 
            
            if(opcionAtacar = 1){
                flag2 = true;
            }else{
                flag2 = false;
            }
    }while(flag2==false);
    if(flag==true){
        system("cls");
        std::cout<<"Se le ha agregado 1 carta\n";
        itdorJugador->setCartas(itdorJugador->getCartas()+1);
    }
    
    
    //fortificar 
    
    
    flag = false;
    flag2 =false;
     do{
         std::cout<<"\n\n\nFORTIFICAR!"<<std::endl;
        std::cout<<"\n\nA continuacion seleccione uno de sus territorios de donde quiere mover sus infanterias: ";
        itdorPaisSeleccion=seleccionDominio(itdorJugador);
        
        flag = moverInfanteria(itdorPaisSeleccion, seleccionTerrenoColindante(itdorPaisSeleccion));
        
        std::cout<<"Desea dejar de fortificar? (1) Si - (0) No"<<std::endl;
            std::cin>>opcionFortificar;
            
            if(opcionFortificar==1){
                flag2 = true;
            }else{
                flag2 = false;
            }
    }while(flag2==false);
    
    
    //ESTO ES PARA AVANZAR DE TURNO
    if(turnoPartida==turnoFinal){
        turnoPartida=1;
    }else{
        turnoPartida++;
    }
   
  }
  
  
  
  
  
  int Risk::moverInfanteria(std::list<Pais>::iterator primerPais, std::list<Pais>::iterator segundoPais){
       
       if(primerPais->getIDPais()==segundoPais->getIDPais()){
           return 0;
       }
       
       system("cls");
       int cantidad;
        if(primerPais->getColorOcupacion() == segundoPais->getColorOcupacion()){
            
            primerPais->getInfoPais();
            
            std::cout<<std::endl;
            
            segundoPais->getInfoPais();
            
       std::cout<<"Digite la cantidad de infanterias que quiere mover de "<<primerPais->getNombrePais()<<" a "<<segundoPais->getNombrePais()<<":";
        std::cin>>cantidad;
        
       
        if(cantidad<primerPais->getCantidadInfanterias()){
            
            
            
            
        primerPais->setCantidadInfanterias(primerPais->getCantidadInfanterias()-cantidad);
        
        segundoPais -> setCantidadInfanterias(segundoPais->getCantidadInfanterias()+cantidad);
        
        system("cls");
        
        std::cout<<"Fortificacion exitosa!"<<std::endl;
        
        primerPais->getInfoPais();
            
            std::cout<<std::endl;
            
            segundoPais->getInfoPais();
        
        
        
        
        }else{
            std::cout<<"Cantidad invalida"<<std::endl;
        }
        }else{
            std::cout<<"No se puede mover la infanteria debido a que no ocupas alguno de los terrenos elegidos "<<std::endl;
        }
    return 0;
   }
 
  std::vector<int> Risk::dadosRojosFunc() {
    int valorDado = 0;
    int Aux;
    std::vector<int> dadosRojos;

    dadosRojos.push_back(lanzarDado());
    dadosRojos.push_back(lanzarDado());

    for (int i = 0; i < 3; i++) {
        Aux = lanzarDado();
        if (valorDado <= Aux) {
            dadosRojos.push_back(Aux);
        }
        valorDado = lanzarDado();
    }

    // Se ordenan para tener los dos mayores datos
    std::sort(dadosRojos.begin(), dadosRojos.end(), std::greater<int>());
   
    // Se acomoda el tamaño para descartar el ultimo
    dadosRojos.resize(1);

    return dadosRojos;
}
 
  std::vector<int> Risk::dadosBlancosFunc(){
      std::vector<int> dadosBlancos;
      dadosBlancos.push_back(lanzarDado());
      dadosBlancos.push_back(lanzarDado());
      
      std::sort(dadosBlancos.begin(), dadosBlancos.end(), std::greater<int>());
      
      dadosBlancos.resize(1);
     
      return dadosBlancos;
  }
 
 
 
 
 //---------------------------------------------------------------------------
  int Risk::ataquePais(std::list<Pais>::iterator atacantePais, std::list<Pais>::iterator defensorPais){
      std::vector<int> dadosRojos;
      std::vector<int> dadosBlancos;
      int opcion;
      int tropasAtaque;
      bool flag;
      bool flagAux;
      
      if(atacantePais->getIDPais()==defensorPais->getIDPais()){
           return 0;
       }
     
      do{
        
        std::cout<<"Indique con cuanta infanteria realizara el ataque desde "<<atacantePais->getNombrePais()<<"\n";
        std::cout<<"Infanteria disponible: "<<atacantePais->getCantidadInfanterias()<<"\n";
        std::cin>>tropasAtaque;
        if(tropasAtaque>=atacantePais->getCantidadInfanterias()){
            flag=false;
            std::cout<<"Cantidad invalida\n";
            return 0;
        }else{
            flag=true;
        }
      }while(flag==false);
      
      //Le restamos al pais la cantidad de tropas que fueron a atacar
       atacantePais->setCantidadInfanterias(atacantePais->getCantidadInfanterias()-tropasAtaque);
     
      //HACER LO DE LOS DADOS Y CONTINUAR HASTA QUE ALGUNO DE LOS PAISES SE QUEDE SIN TROPAS
      flag=false;
      flagAux=false;
      int ronda=0;
      do{
          dadosRojos = dadosRojosFunc();
          dadosBlancos = dadosBlancosFunc();
          std::cout<<"Ronda: "<<ronda<<"\n";
          if(dadosRojos[0]>dadosBlancos[0]){
              //reduzco ejercito del atacante
              defensorPais->setCantidadInfanterias(defensorPais->getCantidadInfanterias()-1);
              std::cout<<"Dados Rojos: "<<dadosRojos[0]<<"\n";
              std::cout<<"Dados Blancos: "<<dadosBlancos[0]<<"\n";
              std::cout<<"Gana Atacante.\n";
              std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
              std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadInfanterias()<<"\n\n";
          }
          if(dadosRojos[0]<=dadosBlancos[0]){
              //reduzco ejercito del atacante
              tropasAtaque=tropasAtaque-1;
              //atacantePais->setUnidadesInfanteria(atacantePais->getUnidadesInfanteria()-1);
              std::cout<<"Dados Rojos: "<<dadosRojos[0]<<"\n";
              std::cout<<"Dados Blancos: "<<dadosBlancos[0]<<"\n";
              std::cout<<"Gana Defensor.\n";
              std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
              std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadInfanterias()<<"\n\n";
          }
          if(defensorPais->getCantidadInfanterias()==0){
              //pedir al usuario poner una cantidad de tropas en el Pais
              //cambiar el color de ocupacion
              flag=true;
              atacantePais->setCantidadInfanterias(atacantePais->getCantidadInfanterias()+tropasAtaque);
              std::cout<<"Cantidad de tropas a disposicion: "<<atacantePais->getCantidadInfanterias()<<"\n";
              do{
                  std::cout<<"Ha ganado la batalla, Seleccione un cantidad de tropas para ocupar\n";
                  std::cin>>opcion;
                  if(opcion>=atacantePais->getCantidadInfanterias()){
                      flagAux=false;
                  }
                  else{
                      flagAux=true;
                      defensorPais->setColorOcupacion(atacantePais->getColorOcupacion());
                      defensorPais->setCantidadInfanterias(opcion);
                      return 1;
                  }
              }while(flagAux==false);
              
              
              
          }
          if(tropasAtaque==0){
              //Mostrar que el asalto ha acabado
              std::cout<<"Usted ha perdido la batalla contra "<<defensorPais->getNombrePais()<<"\n";
              atacantePais->setCantidadInfanterias(atacantePais->getCantidadInfanterias()+tropasAtaque);
              flag=true;
          }
          ronda++;
          
      }while(flag==false);
     return 0;
     
  }
  
  
  std::list<Pais>::iterator Risk::seleccionTerrenoColindante(std::list<Pais>::iterator itdorDominio) {
    int consola, consolaContinente, consolaPais;
    bool flag = false;
    std::list<Pais>::iterator aux;
    int contadorColin;

    do {
        //MUESTRA TERRENOS DONDE TIENE DOMINIOS
   contadorColin=0;
    std::cout<<"\nPaises Colindantes de "<<itdorDominio->getNombrePais()<<": \n"<<std::endl;
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
          for(std::list<int>::iterator itdorColindantes = itdorDominio->getPaisesColindantes().begin(); itdorColindantes != itdorDominio->getPaisesColindantes().end();++itdorColindantes){
            if(*itdorColindantes==itdorP->getIDPais()&&itdorP->getColorOcupacion()==itdorDominio->getColorOcupacion()){
           std::cout<<"("<<itdorP->getIDPais()<<") "<<itdorP->getNombrePais()<<"\n";
           contadorColin=contadorColin+1;
          }
        }
      }
    }
    if(contadorColin==0){
        return itdorDominio;
    }
    
   
          flag=false;
          std::cout<<"Digite el dominio que desea seleccionar: ";
          std::cin>>consolaPais;
         
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
          for(std::list<int>::iterator itdorColindantes = itdorDominio->getPaisesColindantes().begin(); itdorColindantes != itdorDominio->getPaisesColindantes().end();++itdorColindantes){
            if(*itdorColindantes==itdorP->getIDPais()&&itdorP->getIDPais()==consolaPais&&itdorP->getColorOcupacion()==itdorDominio->getColorOcupacion()){
                flag=true;
                return itdorP;
          }
        }
      }
    }
     
    } while (flag == false);
    return aux;
  }
  
  
 
  std::list<Pais>::iterator Risk::seleccionTerrenoColindanteEnemigo(std::list<Pais>::iterator itdorDominio) {
    int consola, consolaContinente, consolaPais;
    bool flag = false;
    std::list<Pais>::iterator aux;
    int contadorColin;

    do {
        //MUESTRA TERRENOS DONDE TIENE DOMINIOS
    contadorColin=0;
    std::cout<<"\nPaises Colindantes de "<<itdorDominio->getNombrePais()<<": \n"<<std::endl;
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
          for(std::list<int>::iterator itdorColindantes = itdorDominio->getPaisesColindantes().begin(); itdorColindantes != itdorDominio->getPaisesColindantes().end();++itdorColindantes){
            if(*itdorColindantes==itdorP->getIDPais()&&itdorP->getColorOcupacion()!=itdorDominio->getColorOcupacion()){
            std::cout<<"("<<itdorP->getIDPais()<<") "<<itdorP->getNombrePais()<<"\n";
            contadorColin=contadorColin+1;
          }
        }
      }
    }
    if(contadorColin==0){
        return itdorDominio;
    }
   
          flag=false;
          std::cout<<"Digite el dominio que desea seleccionar: ";
          std::cin>>consolaPais;
         
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
          for(std::list<int>::iterator itdorColindantes = itdorDominio->getPaisesColindantes().begin(); itdorColindantes != itdorDominio->getPaisesColindantes().end();++itdorColindantes){
            if(*itdorColindantes==itdorP->getIDPais()&&itdorP->getIDPais()==consolaPais&&itdorP->getColorOcupacion()!=itdorDominio->getColorOcupacion()){
                flag=true;
                return itdorP;
          }
        }
      }
    }
     
    } while (flag == false);
    return aux;
  }
 

 
  std::list<Pais>::iterator Risk::seleccionDominio(std::list<Jugador>::iterator itdorJugador) {
    int consola, consolaContinente, consolaPais;
    bool flag = false;
    std::list<Pais>::iterator aux;


    do {
        //MUESTRA TERRENOS DONDE TIENE DOMINIOS
   

    std::cout<<"\nJugador "<<itdorJugador->getIdJugador()<<" estos son sus territorios\n"<<std::endl;
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
      for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
        if(itdorP->getColorOcupacion()==itdorJugador->getColor()){
          std::cout<<"("<<itdorCont->getIdContinente()<<") "<<itdorCont->getNombreContinente()<<"\n";
          break;
        }
      }
    }

      std::cout<<"\nDigite alguno de los continentes: ";
      std::cin>>consolaContinente;
      std::cout<<std::endl;
   
    system("cls");

      if(consolaContinente == 0){
        std::cout<<"AMERICA DEL NORTE"<<std::endl<<std::endl;
      }else  if(consolaContinente == 1){
        std::cout<<"EUROPA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 2){
        std::cout<<"ASIA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 3){
        std::cout<<"AMERICA DEL SUR"<<std::endl<<std::endl;
      }else  if(consolaContinente == 4){
        std::cout<<"AFRICA"<<std::endl<<std::endl;
      }else  if(consolaContinente == 5){
        std::cout<<"AUSTRALIA"<<std::endl<<std::endl;
      }

    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
       
        if(itdorCont->getIdContinente()==consolaContinente){
          for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
            if(itdorP->getColorOcupacion()==itdorJugador->getColor()){
              itdorP->getInfoPais();
            }
          }
          flag=false;
          std::cout<<"Si no puede ver ningun país disponible, inserte cualquier numero para volver al menu de continentes"<<std::endl;
          std::cout<<"Digite el dominio que desea seleccionar: ";
          std::cin>>consolaPais;
         
          for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
            if(itdorP->getIDPais()==consolaPais&&itdorP->getColorOcupacion()==itdorJugador->getColor()){
                flag=true;
                return itdorP;
            }
        }
      }
    }
    } while (flag == false);
    return aux;
  }

#endif
