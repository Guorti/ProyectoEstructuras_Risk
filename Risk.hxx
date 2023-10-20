#ifndef RISK_HXX
#define RISK_HXX

#include "Risk.h"
#include "binary_tree/BinaryTree.h"
#include "huffman_data/HuffmanData.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <queue>
#include <random>
#include <algorithm>

using namespace std;

void Risk::setTurnoPartida(int turnoPartida){
    this->turnoPartida=turnoPartida;
}

void Risk::setReclamoCartas(int reclamoCartas){
    this->reclamoCartas=reclamoCartas;
}


list<Jugador>& Risk::getJugadores() {
    return jugadores;
}

list<int>& Risk::getTurnosJugadores(){
    return turnosJugadores;
}

//GUARDADO HUFFMAN


void Risk::guardarPartidaBin(string nombreArchivo){
    std::ostringstream ss;

    allDataToString(ss);

    //HUFFMAN

    std::ostringstream ssBin;

    //Iterar sobre la cadena de caracteres, si el caractér no habia aparecido, contar su frecuencia.
    unordered_map<char, int> charCount;

    for (int i=0;i<ss.str().size();i++) {
        // Si el caracter no está en el map, inicializar su cuenta en 1, si ya esta incrementar.
        if (charCount.find(ss.str()[i]) == charCount.end()) {
            charCount[ss.str()[i]] = 1;
        } else {
            charCount[ss.str()[i]]++;
        }
    }

    //Creamos una cola de prioridad de nodos para llevar a cabo huffman

    vector<BinaryNode<HuffmanData>*> colaFrecuenciasHeap;
    for (unordered_map<char, int>::iterator it = charCount.begin(); it != charCount.end(); ++it) {
        colaFrecuenciasHeap.push_back(new BinaryNode<HuffmanData>(HuffmanData(it->first, it->second)));
        std::push_heap( colaFrecuenciasHeap.begin( ), colaFrecuenciasHeap.end( ),  BinaryNode<HuffmanData>::BinaryNodeComparator());
    }


    //push_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());

    //Se realiza el algoritmo huffman utilizando la cola de prioridad
    int sumaFrecuencia;
    while(colaFrecuenciasHeap.size() != 1){
        pop_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());
        BinaryNode<HuffmanData>* pNodeAux = colaFrecuenciasHeap.back();
        colaFrecuenciasHeap.pop_back();

        pop_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());
        BinaryNode<HuffmanData>* pNodeAux2 = colaFrecuenciasHeap.back();
        colaFrecuenciasHeap.pop_back();

        sumaFrecuencia=pNodeAux->getData().getFrecuencia()+pNodeAux2->getData().getFrecuencia();

        BinaryNode<HuffmanData>* tempNode = new BinaryNode<HuffmanData>(HuffmanData(sumaFrecuencia));
        tempNode->setLeft(pNodeAux);
        tempNode->setRight(pNodeAux2);

        colaFrecuenciasHeap.push_back(tempNode);

        push_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());

    }

    //Creamos el arbol con el nodo final
    BinaryNode<HuffmanData>* nodeAux = colaFrecuenciasHeap.back();
    //huffmanTree = BinaryTree<HuffmanData>(nodeAux);
    huffmanTree.setRoot(nodeAux);

    huffmanTree.mapHuffman(Mappeo);
    //std::cout<<"hola RISK"<<std::endl;
    /*
    cout<<"\n\nMappeo Huffman"<<endl;
    for (unordered_map<char, string>::iterator it = Mappeo.begin(); it != Mappeo.end(); ++it) {
        ss << it->first << ";" << it->second << std::endl;
    }
    */

    //CONVERSION STRING BINARIO
    for (int i=0;i<ss.str().size();i++) {
        unordered_map<char, string>::iterator it = Mappeo.find(ss.str()[i]);
        if (it != Mappeo.end()) {
            ssBin << it->second;
        }
    }


    //FIN HUFFMAN
    // Open a file named "output.txt" for writing
    std::ofstream outputFile(nombreArchivo, std::ios::out | std::ios::binary);

    // Check if the file is successfully opened
    if (outputFile.is_open()) {
        //Escribimos cada caracter junto a su frecuencia
        outputFile <<"MAPPEOHUFFMAN:"<<endl;
        for (unordered_map<char, int>::iterator it = charCount.begin(); it != charCount.end(); ++it) {
            outputFile << it->first << "_" << it->second << std::endl;
        }
        outputFile <<"#"<<endl;

        // Write the variable to the file
        outputFile << ssBin.str();

        // Close the file
        outputFile.close();

        std::cout << "Los datos se han escrito en el archivo binario." << std::endl;
    }else {
        std::cout << "Fallo al abrir el archivo." << std::endl;
    }

}
//FIN GUARDADO HUFFMAN



void Risk::inicializarPartida(string nombreArchivo){
    std::stringstream extensionRecibida;
    extensionRecibida << nombreArchivo;
    std::string segmento;
    std::vector<std::string> seglist;

    string linea;
    string lineaAux;
    string auxiliar;
    int contador;

    std::ostringstream ssConvert;
    queue<char> ordenBinarios;

    Jugador jugadorInstance;
    Continente continenteInstance;
    Pais paisInstance;

    continentes.clear();
    turnosJugadores.clear();
    cartas.clear();


    while(std::getline(extensionRecibida, segmento, '.'))
    {
        seglist.push_back(segmento);
    }

    if(seglist[1]=="txt") {

        //Cargar desde archivo de texto
        std::ifstream inputFile(nombreArchivo, std::ios::in); // Open the file for reading
        std::string atributos[9];


        if (!inputFile.is_open()) {
            std::cout << "Error abriendo el archivo" << std::endl;
            return;
        }
        while (getline(inputFile, linea)) {
            contador = 0;

            if (linea == "TURNOSJUGADORES:") {
                getline(inputFile, linea);
                istringstream ss(linea);

                while (getline(ss, auxiliar, ';')) {
                    turnosJugadores.push_back(stoi(auxiliar));
                }
            }

            if (linea == "ATRIBUTOSJUGADORES:") {
                jugadores.clear();
                getline(inputFile, linea);
                getline(inputFile, linea);
                while (linea != "#") {
                    contador = 0;
                    istringstream ss(linea);
                    while (getline(ss, auxiliar, ';')) {
                        atributos[contador] = auxiliar;
                        contador++;
                    }
                    jugadorInstance = Jugador(stoi(atributos[0]), atributos[1], stoi(atributos[2]), stoi(atributos[3]));
                    //Leer apartado de cartas
                    getline(inputFile, linea);
                    //Revisa si tiene cartas
                    if (linea == "CARTAS:") {
                        getline(inputFile, linea);
                        getline(inputFile, linea);
                        while (linea != "#") {
                            istringstream ss(linea);
                            contador = 0;
                            while (getline(ss, auxiliar, ';')) {
                                atributos[contador] = auxiliar;
                                contador++;
                            }
                            jugadorInstance.getCartasVector().push_back(
                                    Carta(atributos[0], stoi(atributos[1]), stoi(atributos[2])));
                            getline(inputFile, linea);
                        }
                        getline(inputFile, linea);
                    } else {
                        getline(inputFile, linea);
                    }
                    jugadores.push_back(jugadorInstance);
                }

                contador = 0;
                getline(inputFile, linea);
                istringstream ss(linea);


            }

            if (linea == "CONTINENTE:") {

                getline(inputFile, linea);
                istringstream ss(linea);
                while (getline(ss, auxiliar, ';')) {
                    atributos[contador] = auxiliar;
                    contador++;
                }
                continenteInstance = Continente(stoi(atributos[0]), atributos[1]);
                getline(inputFile, linea);
                getline(inputFile, linea);
                getline(inputFile, linea);
                while (linea != "#") {
                    contador = 0;
                    istringstream ss(linea);
                    while (getline(ss, auxiliar, ';')) {
                        atributos[contador] = auxiliar;
                        contador++;
                    }
                    paisInstance = Pais(stoi(atributos[0]), atributos[1], stoi(atributos[2]), stoi(atributos[3]), {});
                    //continenteInstance.getPaisesList().push_back(Pais(stoi(atributos[0]), atributos[1], stoi(atributos[2]),
                    //stoi(atributos[3]), {}));
                    //Leer apartado colindantes
                    getline(inputFile, linea);
                    getline(inputFile, linea);
                    istringstream sss(linea);
                    while (getline(sss, auxiliar, ';')) {
                        paisInstance.getPaisesColindantes().push_back(stoi(auxiliar));
                    }
                    continenteInstance.getPaisesList().push_back(paisInstance);
                    getline(inputFile, linea);
                }
                continentes.push_back(continenteInstance);
            }

                if (linea == "CARTASRISK:") {
                    getline(inputFile, linea);
                    getline(inputFile, linea);
                    //logica cargar cartas

                    while (linea != "#") {
                        istringstream ss(linea);
                        contador = 0;
                        while (getline(ss, auxiliar, ';')) {
                            atributos[contador] = auxiliar;
                            contador++;
                        }
                        cartas.push_back(Carta(atributos[0], stoi(atributos[1]), stoi(atributos[2])));
                        getline(inputFile, linea);
                    }
                }

                if (linea == "TURNOPARTIDA:") {
                    getline(inputFile, linea);
                    turnoPartida = stoi(linea);
                }
                if (linea == "RECLAMOCARTAS:") {
                    getline(inputFile, linea);
                    reclamoCartas = stoi(linea);
                }
        }
        inicio_J=true;
    }
    if(seglist[1]=="bin") {
        unordered_map<char, int> charCount;
        bool specialFlag = false;

        std::string atributos[9];

        std::ifstream inputFile(nombreArchivo, std::ios::in); // Open the file for reading
        std::ifstream inputFileAux(nombreArchivo, std::ios::in);

        if (!inputFile.is_open()) {
            std::cout << "Error abriendo el archivo" << std::endl;
            return;
        }

        getline(inputFile, linea);
        getline(inputFile, linea);

        getline(inputFileAux, lineaAux);
        getline(inputFileAux, lineaAux);
        while(linea != "#"){
            contador = 0;
            istringstream ss(linea);
            while (getline(ss, auxiliar, '_')) {
                atributos[contador] = auxiliar;
                contador++;
            }
            if(specialFlag==true){
                charCount['\n'] = stoi(atributos[1]);
                specialFlag=false;
            }else{
                charCount[(atributos[0])[0]] = stoi(atributos[1]);
            }

            getline(inputFileAux, lineaAux);

            if(lineaAux.size()==0){
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                inputFile.ignore();
                specialFlag=true;
            }
            getline(inputFile, linea);
        }

        getline(inputFile, linea);

        inputFile.close();
        inputFileAux.close();

        //LOGICA PARA ARMAR EL HUFFMAN TREE

        //Creamos una cola de prioridad de nodos para llevar a cabo huffman

        vector<BinaryNode<HuffmanData>*> colaFrecuenciasHeap;
        for (unordered_map<char, int>::iterator it = charCount.begin(); it != charCount.end(); ++it) {
            colaFrecuenciasHeap.push_back(new BinaryNode<HuffmanData>(HuffmanData(it->first, it->second)));
            std::push_heap( colaFrecuenciasHeap.begin( ), colaFrecuenciasHeap.end( ),  BinaryNode<HuffmanData>::BinaryNodeComparator());
        }


// Convert the vector into a heap
        //push_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());

        //Se realiza el algoritmo huffman utilizando la cola de prioridad
        int sumaFrecuencia;
        while(colaFrecuenciasHeap.size() != 1){
            pop_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());
            BinaryNode<HuffmanData>* pNodeAux = colaFrecuenciasHeap.back();
            colaFrecuenciasHeap.pop_back();

            pop_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());
            BinaryNode<HuffmanData>* pNodeAux2 = colaFrecuenciasHeap.back();
            colaFrecuenciasHeap.pop_back();

            sumaFrecuencia=pNodeAux->getData().getFrecuencia()+pNodeAux2->getData().getFrecuencia();

            BinaryNode<HuffmanData>* tempNode = new BinaryNode<HuffmanData>(HuffmanData(sumaFrecuencia));
            tempNode->setLeft(pNodeAux);
            tempNode->setRight(pNodeAux2);

            colaFrecuenciasHeap.push_back(tempNode);

            push_heap(colaFrecuenciasHeap.begin(), colaFrecuenciasHeap.end(), BinaryNode<HuffmanData>::BinaryNodeComparator());

        }

        //Creamos el arbol con el nodo final
        BinaryNode<HuffmanData>* nodeAux = colaFrecuenciasHeap.back();
        //huffmanTree = BinaryTree<HuffmanData>(nodeAux);
        huffmanTree.setRoot(nodeAux);




        for(int i=0;i<linea.size();i++){
            ordenBinarios.push(linea[i]);
        }

        ssConvert = huffmanTree.binaryToChar(ordenBinarios);

        //Convertimos el ostream a string
        string contenidoOstr = ssConvert.str();
        //Convertimos el string a istrinstream para usar \n como delimitador
        istringstream iss(contenidoOstr);


        getline(iss, linea);
        //Cargar los datos
        while (linea != "#FIN#") {
            contador = 0;

            if (linea == "TURNOSJUGADORES:") {
                getline(iss, linea);
                istringstream ss(linea);

                while (getline(ss, auxiliar, ';')) {
                    turnosJugadores.push_back(stoi(auxiliar));
                }
            }

            if (linea == "ATRIBUTOSJUGADORES:") {
                jugadores.clear();
                getline(iss, linea);
                getline(iss, linea);
                while (linea != "#") {
                    contador = 0;
                    istringstream ss(linea);
                    while (getline(ss, auxiliar, ';')) {
                        atributos[contador] = auxiliar;
                        contador++;
                    }
                    jugadorInstance = Jugador(stoi(atributos[0]), atributos[1], stoi(atributos[2]), stoi(atributos[3]));
                    //Leer apartado de cartas
                    getline(iss, linea);
                    //Revisa si tiene cartas
                    if (linea == "CARTAS:") {
                        getline(iss, linea);
                        getline(iss, linea);
                        while (linea != "#") {
                            istringstream ss(linea);
                            contador = 0;
                            while (getline(ss, auxiliar, ';')) {
                                atributos[contador] = auxiliar;
                                contador++;
                            }
                            jugadorInstance.getCartasVector().push_back(
                                    Carta(atributos[0], stoi(atributos[1]), stoi(atributos[2])));
                            getline(iss, linea);
                        }
                        getline(iss, linea);
                    } else {
                        getline(iss, linea);
                    }
                    jugadores.push_back(jugadorInstance);
                }
                contador = 0;

            }

            if (linea == "CONTINENTE:") {

                getline(iss, linea);
                istringstream ss(linea);
                while (getline(ss, auxiliar, ';')) {
                    atributos[contador] = auxiliar;
                    contador++;
                }
                continenteInstance = Continente(stoi(atributos[0]), atributos[1]);
                getline(iss, linea);
                getline(iss, linea);
                getline(iss, linea);
                while (linea != "#") {
                    contador = 0;
                    istringstream ss(linea);
                    while (getline(ss, auxiliar, ';')) {
                        atributos[contador] = auxiliar;
                        contador++;
                    }
                    paisInstance = Pais(stoi(atributos[0]), atributos[1], stoi(atributos[2]), stoi(atributos[3]), {});
                    //continenteInstance.getPaisesList().push_back(Pais(stoi(atributos[0]), atributos[1], stoi(atributos[2]),
                    //stoi(atributos[3]), {}));
                    //Leer apartado colindantes
                    getline(iss, linea);
                    getline(iss, linea);
                    istringstream sss(linea);
                    while (getline(sss, auxiliar, ';')) {
                        paisInstance.getPaisesColindantes().push_back(stoi(auxiliar));
                    }
                    continenteInstance.getPaisesList().push_back(paisInstance);
                    getline(iss, linea);
                }
                continentes.push_back(continenteInstance);
                //getline(iss, linea);
            }

            if (linea == "CARTASRISK:") {
                getline(iss, linea);
                getline(iss, linea);
                //logica cargar cartas

                while (linea != "#") {
                    istringstream ss(linea);
                    contador = 0;
                    while (getline(ss, auxiliar, ';')) {
                        atributos[contador] = auxiliar;
                        contador++;
                    }
                    cartas.push_back(Carta(atributos[0], stoi(atributos[1]), stoi(atributos[2])));
                    getline(iss, linea);
                }
            }

            if (linea == "TURNOPARTIDA:") {
                getline(iss, linea);
                turnoPartida = stoi(linea);
            }
            if (linea == "RECLAMOCARTAS:") {
                getline(iss, linea);
                reclamoCartas = stoi(linea);
            }
            getline(iss, linea);
        }
        inicio_J=true;
    }
}


void Risk::guardarPartidaText(string nombreArchivo){
    std::ostringstream ss;

        allDataToString(ss);

        // Open a file named "output.txt" for writing
        std::ofstream outputFile(nombreArchivo);

        // Check if the file is successfully opened
        if (outputFile.is_open()) {

            // Write the variable to the file
            outputFile << ss.str();

            // Close the file
            outputFile.close();

            std::cout << "Los datos se han escrito en el archivo." << std::endl;
        }else {
            std::cout << "Fallo al abrir el archivo." << std::endl;
        }
}



  void Risk::inicializar(){

    bool flag;
    std::string nombre;
    int color;
    int opcionColor=0;
    std::list<int> coloresList = {1, 2, 3, 4, 5, 6};
    int contador=0;
    int consolaContinente;
    int consolaPais;


      huffmanTree = BinaryTree<HuffmanData>();

      //Quemamos las cartas a utilizar

      cartas.push_back(Carta("Comodin",0,1)); cartas.push_back(Carta("Comodin",0,1));

      cartas.push_back(Carta("Caballeria", 1, 0));cartas.push_back(Carta("Infanteria", 2, 0));cartas.push_back(Carta("Artilleria", 3, 0));cartas.push_back(Carta("Caballeria", 4, 0));
      cartas.push_back(Carta("Artilleria", 5, 0));cartas.push_back(Carta("Infanteria", 6, 0));cartas.push_back(Carta("Infanteria", 7, 0));cartas.push_back(Carta("Caballeria", 8, 0));
      cartas.push_back(Carta("Caballeria", 9, 0));cartas.push_back(Carta("Artilleria", 10, 0));cartas.push_back(Carta("Infanteria", 11, 0));cartas.push_back(Carta("Caballeria", 12, 0));
      cartas.push_back(Carta("Artilleria", 13, 0));cartas.push_back(Carta("Infanteria", 14, 0));cartas.push_back(Carta("Infanteria", 15, 0));cartas.push_back(Carta("Artilleria", 16, 0));
      cartas.push_back(Carta("Artilleria", 17, 0));cartas.push_back(Carta("Infanteria", 18, 0));cartas.push_back(Carta("Caballeria", 19, 0));cartas.push_back(Carta("Caballeria", 20, 0));
      cartas.push_back(Carta("Caballeria", 21, 0));cartas.push_back(Carta("Artilleria", 22, 0));cartas.push_back(Carta("Infanteria", 23, 0));cartas.push_back(Carta("Caballeria", 24, 0));
      cartas.push_back(Carta("Caballeria", 25, 0));cartas.push_back(Carta("Infanteria", 26, 0));cartas.push_back(Carta("Infanteria", 27, 0));cartas.push_back(Carta("Caballeria", 28, 0));
      cartas.push_back(Carta("Infanteria", 29, 0));cartas.push_back(Carta("Artilleria", 30, 0));cartas.push_back(Carta("Infanteria", 31, 0));cartas.push_back(Carta("Artilleria", 32, 0));
      cartas.push_back(Carta("Artilleria", 33, 0));cartas.push_back(Carta("Artilleria", 34, 0));cartas.push_back(Carta("Infanteria", 35, 0));cartas.push_back(Carta("Caballeria", 36, 0));
      cartas.push_back(Carta("Artilleria", 37, 0));cartas.push_back(Carta("Caballeria", 38, 0));cartas.push_back(Carta("Artilleria", 39, 0));cartas.push_back(Carta("Caballeria", 40, 0));
      cartas.push_back(Carta("Caballeria", 41, 0));cartas.push_back(Carta("Infanteria", 42, 0));


    continentes.push_back(
        Continente(0, "America del Norte", {
            Pais(1,"Alaska", 0, 0, {6,2,22}),
            Pais(2,"Alberta", 0, 0, {1,2,6,9,7}),
            Pais(3,"America Central", 0, 0, {32,9,4}),
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
            Pais(10,"Gran Bretana", 0, 0, {11,13,12,16}),
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
    if(cantidadJugadores <=2||cantidadJugadores>6){
      std::cout<<"No cumple la cantidad de jugadores necesarios"<<std::endl<<std::endl;
      inicio_J=false;
      return;
    }


    //Se revuelven la cartas (Funcion dada por gpt)
    std::random_device rd;
    std::mt19937 rng(rd());
    shuffle(cartas.begin(), cartas.end(),rng);
   
    for(int i=1;i<cantidadJugadores+1;i++){
      flag=false;

    system("cls");
      std::cout<<"Jugador "<<i<<" ingrese su nombre: ";
      std::cin>>nombre;
   

        std::cout<<"\nSELECCION DEL COLOR"<<std::endl<<std::endl;
     

      do{
        for (std::list<int>::iterator itdor = coloresList.begin(); itdor != coloresList.end(); ++itdor){
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
          itdor = coloresList.erase(itdor);
        }
      }
        if(flag==false){
          std::cout<<"Color invalido"<<std::endl;
        }
      }while(opcionColor<1||opcionColor>6||flag==false);

      if(cantidadJugadores==3){
        turnosJugadores = {1, 2, 3};
        jugadores.push_back(Jugador(i,nombre,opcionColor,35));
       
      }
      if(cantidadJugadores==4){
        turnosJugadores = {1, 2, 3, 4};
        jugadores.push_back(Jugador(i,nombre,opcionColor,30));
       
      }
      if(cantidadJugadores==5){
        turnosJugadores = {1, 2, 3, 4, 5};
        jugadores.push_back(Jugador(i,nombre,opcionColor,25));
       
      }
      if(cantidadJugadores==6){
        turnosJugadores = {1, 2, 3, 4, 5, 6};
        jugadores.push_back(Jugador(i,nombre,opcionColor,20));
       
      }
    }


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
              if(itdorP->getCantidadArmadas()==0){

                itdorP->setColorOcupacion(itdorJugadores->getColor());
                itdorP->setCantidadArmadas(itdorP->getCantidadArmadas()+1);
                itdorJugadores->setArmadas(itdorJugadores->getArmadas()-1);

                system("cls");
                std::cout<<"\nEl jugador "<< itdorJugadores->getIdJugador()<<" reclamo el territorio "<<itdorP->getNombrePais()<<"!"<<std::endl;
               
                //Se realiza para ir al siguiente turno
                if(itdorJugadores->getIdJugador()==jugadores.end()->getIdJugador()){
                  itdorJugadores=jugadores.begin();
                }else{
                  itdorJugadores++;
                }
              }else if(itdorP->getColorOcupacion()!=0){
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
 
              if(itdorJugadores->getArmadas()>0){
                std::cout<<"Posee "<<itdorJugadores->getArmadas()<<" Armadas\n";
                std::cout<<"Ingrese la cantidad de armadas que ingresara: ";
                std::cin>>consola;
                if(itdorJugadores->getArmadas()>=consola){
                 itdorP->setCantidadArmadas(itdorP->getCantidadArmadas()+consola);
                  itdorJugadores->setArmadas(itdorJugadores->getArmadas()-consola);
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
          contador=contador + itdorJug->getArmadas();
        }
        if(contador==0){
          flag=true;
        }
        }while(flag==false);
    return;
  }

void Risk::sacarCarta(std::list<Jugador>::iterator itdorJugador) {
    itdorJugador->getCartasVector().push_back(*cartas.begin());
    cartas.begin()->displayCartaInfo();
    cartas.erase(cartas.begin());
}




//LANZAR DADO--------------------

int Risk::generarAleatorio() {

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
      int cartasRecibidas=0;
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
    if(paisesJugador==42){
        j_Terminado=true;
        std::cout<<"El jugador "<<itdorJugador->getNombre()<<" Ha ganado\n";
        return;
    }

    //Para reclamar cartas y subir tal cantidad
    if(itdorJugador->revisionCartas()){

        std::cout<<"El Jugador "<<itdorJugador->getIdJugador()<<" puede reclamar: "<< reclamoCartas <<" Fichas debido a sus cartas\n";
        std::cout<<"Desea reclamarlas? (1)SI (2)NO\n";
        std::cin>>opcion;
        if(opcion==1){
            itdorJugador->setArmadas(itdorJugador->getArmadas()+reclamoCartas);
            reclamoCartas=reclamoCartas+2;
            ingresarTropas(itdorJugador);
        }
    }


    
   
    std::cout<<"El Jugador "<<itdorJugador->getIdJugador()<<" puede reclamar: "<<(contadorTerritorios(itdorJugador)/3)<<" Fichas debido a sus territorios\n";
    std::cout<<"Desea reclamarlas (1) SI (2)NO\n";
    std::cin>>opcion;
    if(opcion==1&&(contadorTerritorios(itdorJugador)/3)!=0){
        itdorJugador->setArmadas(itdorJugador->getArmadas()+(contadorTerritorios(itdorJugador)/3));
        ingresarTropas(itdorJugador);
    }
   
   
    flag =false;
    flag2 =false;
    do{
        std::cout<<"\n\n\nATACAR!"<<std::endl;
        std::cout<<"A continuacion seleccione uno de sus dominios por el cual atacar\n";
        itdorPaisSeleccion=seleccionDominio(itdorJugador);
        cartasRecibidas =cartasRecibidas + ataquePais(itdorPaisSeleccion, seleccionTerrenoColindanteEnemigo(itdorPaisSeleccion));
        std::cout<<"Desea dejar de atacar? (1) Si - (0) No"<<std::endl;
            std::cin>>opcionAtacar; 
            
            if(opcionAtacar == 1){
                flag2 = true;
            }else{
                flag2 = false;
            }
    }while(flag2==false);
    if(cartasRecibidas>=1){
        system("cls");
        for(int i=0;i<cartasRecibidas;i++){
            sacarCarta(itdorJugador);
        }

        std::cout<<"\n\nSe le han agregado "<< cartasRecibidas <<" cartas\n";
        //saca una carta del vector de cartas
    }
    
    
    //fortificar
    flag = false;
    flag2 =false;
     do{
         std::cout<<"\n\nFORTIFICAR!"<<std::endl;
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
        
       
        if(cantidad<primerPais->getCantidadArmadas()){
            
            
            
            
        primerPais->setCantidadArmadas(primerPais->getCantidadArmadas()-cantidad);
        segundoPais -> setCantidadArmadas(segundoPais->getCantidadArmadas()+cantidad);
        
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

   int Risk::contadorTerritorios(std::list<Jugador>::iterator itdorJugador){
    int contador=0;
       for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
           for (std::list<Pais>::iterator itdorP = (itdorCont->getPaisesList().begin()); itdorP != itdorCont->getPaisesList().end();++itdorP) {
               if(itdorJugador->getColor()==itdorP->getColorOcupacion()){
                   contador++;
               }
           }
       }
    return contador;
    }

 
  std::vector<int> Risk::dadosFunc(int cantidadDados) {
    std::vector<int> dados;

    if(cantidadDados==1){
        dados.push_back(generarAleatorio());
    }
    if(cantidadDados==2){
      for(int i=0;i<cantidadDados;i++){
        dados.push_back(generarAleatorio());
      }
    }
    if(cantidadDados==3){
      for(int i=0;i<cantidadDados;i++){
        dados.push_back(generarAleatorio());
      }
    }
    // Se ordenan para tener los dos mayores datos (Chat gpt me lo recomendó, utiliza algo llamado introSort)
    std::sort(dados.begin(), dados.end(), std::greater<int>());
    if(cantidadDados==3){
        dados.resize(2);
    }

    return dados;
}
 
 
 //---------------------------------------------------------------------------
  int Risk::ataquePais(std::list<Pais>::iterator atacantePais, std::list<Pais>::iterator defensorPais){
      std::vector<int> dadosRojos;
      std::vector<int> dadosBlancos;
      int opcion;
      int tropasAtaque;
      bool flag;
      bool flagAux;
      bool flagOpcion;
     int ronda=0;
     int opcionSeleccion;
      
      if(atacantePais->getIDPais()==defensorPais->getIDPais()){
           return 0;
       }
     
      do{
        
        std::cout<<"Indique con cuantas armadas realizara el ataque desde "<<atacantePais->getNombrePais()<<", Maximo 3\n";
        std::cout<<"Infanteria disponible: "<<atacantePais->getCantidadArmadas()<<"\n";
        std::cin>>tropasAtaque;
        if(tropasAtaque>=atacantePais->getCantidadArmadas()|| tropasAtaque>3){
            flag=false;
            std::cout<<"Cantidad invalida\n";
            return 0;
        }else{
            flag=true;
        }
      }while(flag==false);
      
      //Le restamos al pais la cantidad de tropas que fueron a atacar
       atacantePais->setCantidadArmadas(atacantePais->getCantidadArmadas()-tropasAtaque);
     
      //HACER LO DE LOS DADOS Y CONTINUAR HASTA QUE ALGUNO DE LOS PAISES SE QUEDE SIN TROPAS
      flag=false;
      flagAux=false;
      flagOpcion=false;

      do{
        //Si el defensor tiene mas de 2 tropas en el territorio se usaran 2 dados
        if(defensorPais->getCantidadArmadas()>=2){
            dadosBlancos=dadosFunc(2);
        }else{
            dadosBlancos=dadosFunc(1);
        }

        //Si el atacante ataca con 3 armadas, se usaran 3 dados
        if(tropasAtaque==3){
          dadosRojos=dadosFunc(3);
        }
        if(tropasAtaque==2){
          dadosRojos=dadosFunc(2);
        }
        if(tropasAtaque==1){
          dadosRojos=dadosFunc(1);
        }

          std::cout<<"Ronda: "<<ronda<<"\n";
          if(dadosRojos[0]>dadosBlancos[0]&&defensorPais->getCantidadArmadas()>0){
              //reduzco ejercito del defensor
              defensorPais->setCantidadArmadas(defensorPais->getCantidadArmadas()-1);
              std::cout<<"Dados Rojos: "<<dadosRojos[0]<<"\n";
              std::cout<<"Dados Blancos: "<<dadosBlancos[0]<<"\n";
              std::cout<<"Gana Atacante.\n";
              std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
              std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadArmadas()<<"\n\n";
              if(tropasAtaque>1&&defensorPais->getCantidadArmadas()>1){
                if(dadosRojos[1]<=dadosBlancos[1]){
                  //reduzco ejercito del atacante
                  tropasAtaque=tropasAtaque-1;
                  std::cout<<"Dados Rojos: "<<dadosRojos[1]<<"\n";
                  std::cout<<"Dados Blancos: "<<dadosBlancos[1]<<"\n";
                  std::cout<<"Gana Defensor.\n";
                  std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
                  std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadArmadas()<<"\n\n";
                }else{
                    //reduzco ejercito del defensor
                    defensorPais->setCantidadArmadas(defensorPais->getCantidadArmadas()-1);
                    std::cout<<"Dados Rojos: "<<dadosRojos[1]<<"\n";
                    std::cout<<"Dados Blancos: "<<dadosBlancos[1]<<"\n";
                    std::cout<<"Gana Atacante.\n";
                    std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
                    std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadArmadas()<<"\n\n";
                }
              }
          }
          if(dadosRojos[0]<=dadosBlancos[0]&&defensorPais->getCantidadArmadas()>0){
              //reduzco ejercito del atacante
              tropasAtaque=tropasAtaque-1;
              std::cout<<"Dados Rojos: "<<dadosRojos[0]<<"\n";
              std::cout<<"Dados Blancos: "<<dadosBlancos[0]<<"\n";
              std::cout<<"Gana Defensor.\n";
              std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
              std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadArmadas()<<"\n\n";
              if(tropasAtaque>1&&defensorPais->getCantidadArmadas()>1){
                if(dadosRojos[1]<=dadosBlancos[1]){
                  //reduzco ejercito del atacante
                  tropasAtaque=tropasAtaque-1;
                  std::cout<<"Dados Rojos: "<<dadosRojos[1]<<"\n";
                  std::cout<<"Dados Blancos: "<<dadosBlancos[1]<<"\n";
                  std::cout<<"Gana Defensor.\n";
                  std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
                  std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadArmadas()<<"\n\n";
                }else{
                    //reduzco ejercito del defensor
                    defensorPais->setCantidadArmadas(defensorPais->getCantidadArmadas()-1);
                    std::cout<<"Dados Rojos: "<<dadosRojos[1]<<"\n";
                    std::cout<<"Dados Blancos: "<<dadosBlancos[1]<<"\n";
                    std::cout<<"Gana Atacante.\n";
                    std::cout<<"Tropas Atacante: "<<tropasAtaque<<"\n";
                    std::cout<<"Tropas Defensor: "<<defensorPais->getCantidadArmadas()<<"\n\n";
                }
              }
              
          }
          if(defensorPais->getCantidadArmadas()<=0){
              //pedir al usuario poner una cantidad de tropas en el Pais
              //cambiar el color de ocupacion
              flag=true;
              atacantePais->setCantidadArmadas(atacantePais->getCantidadArmadas()+tropasAtaque);
              std::cout<<"Cantidad de tropas a disposicion: "<<atacantePais->getCantidadArmadas()<<"\n";
              do{
                  std::cout<<"Ha ganado la batalla, Seleccione un cantidad de tropas para ocupar\n";
                  std::cin>>opcion;
                  if(opcion>=atacantePais->getCantidadArmadas()){
                      flagAux=false;
                  }
                  else{
                      flagAux=true;
                      defensorPais->setColorOcupacion(atacantePais->getColorOcupacion());
                      atacantePais->setCantidadArmadas(atacantePais->getCantidadArmadas()-opcion);
                      defensorPais->setCantidadArmadas(opcion);
                      return 1;
                  }
              }while(flagAux==false);
              
          }
          if(tropasAtaque<=0){
              //Mostrar que el asalto ha acabado
              std::cout<<"Usted ha perdido la batalla contra "<<defensorPais->getNombrePais()<<"\n";
              atacantePais->setCantidadArmadas(atacantePais->getCantidadArmadas()+tropasAtaque);
              flag=true;
              return 0;
          }

          do{
            std::cout<<"Desea seguir atacando? 1(SI) 2(NO)\n";
            std::cin>>opcionSeleccion;
            if(opcionSeleccion==2){
              std::cout<<"Sus "<<tropasAtaque<<" han regresado satisfactoriamente\n";
              atacantePais->setCantidadArmadas(atacantePais->getCantidadArmadas()+tropasAtaque);
              flagOpcion=true;
              flag=true;
            }else{
                flagOpcion=true;
                flag=false;
            }
          }while(flagOpcion==false);
          
          ronda++;
          
      }while(flag==false);
     return 0;
     
  }

void Risk::ingresarTropas(std::list<Jugador>::iterator itdorJugador) {
    int flag=false;
    int consolaContinente;
    int consolaPais;
    int consola;
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
                        if(itdorJugador->getArmadas()>0){
                            std::cout<<"Posee "<<itdorJugador->getArmadas()<<" Unidades de infanteria\n";
                            std::cout<<"Ingrese la cantidad de infanterias que ingresara: ";
                            std::cin>>consola;
                            if(itdorJugador->getArmadas()>=consola){
                                itdorP->setCantidadArmadas(itdorP->getCantidadArmadas()+consola);
                                itdorJugador->setArmadas(itdorJugador->getArmadas()-consola);
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





void Risk::allDataToString(std::ostringstream &ss){


    ss << "TURNOSJUGADORES:\n";

    for (std::list<int>::iterator itdor = turnosJugadores.begin(); itdor != turnosJugadores.end();++itdor) {

        ss << *itdor;
        if(next(itdor) != turnosJugadores.end()){
            ss << ";";
        }
    }

    ss << "\n";
    ss << "ATRIBUTOSJUGADORES:\n";
    ss << "#\n";

    for (std::list<Jugador>::iterator itdor = jugadores.begin(); itdor != jugadores.end();++itdor) {
        //Id jugador
        ss << itdor->getIdJugador() << ";";

        //Nombre Jugador
        ss << itdor->getNombre() << ";";

        //Color Jugador
        ss << itdor->getColor() << ";";

        //Armadas Jugador
        ss << itdor->getArmadas() << "\n";

        if(itdor->getCartasVector().size() > 0){
            ss << "CARTAS:\n";
            ss << "#\n";
            for (std::vector<Carta>::iterator itdorCartas = itdor->getCartasVector().begin(); itdorCartas != itdor->getCartasVector().end(); ++itdorCartas) {
                ss << itdorCartas->getTipoUnidad() << ";";
                ss << itdorCartas->getCodigoPais() << ";";
                ss << itdorCartas->isComodin() << "\n";
            }
            ss << "#\n";
        }else{
            ss << "SINCARTAS:\n";
        }
    }
    ss << "#\n";
    for (std::list<Continente>::iterator itdorCont = continentes.begin(); itdorCont != continentes.end();++itdorCont) {
        ss << "CONTINENTE:\n";
        ss << itdorCont->getIdContinente() << ";";
        ss << itdorCont->getNombreContinente() << "\n";
        ss << "PAISES:\n";
        ss << "#\n";

        for (std::list<Pais>::iterator itdorPais = itdorCont->getPaisesList().begin(); itdorPais != itdorCont->getPaisesList().end();++itdorPais) {
            ss << itdorPais->getIDPais() << ";";
            ss << itdorPais->getNombrePais() << ";";
            ss << itdorPais->getCantidadArmadas() << ";";
            ss << itdorPais->getColorOcupacion() << "\n";
            ss << "COLINDANTES:" << "\n";
            for(std::list<int>::iterator itdorColind = itdorPais->getPaisesColindantes().begin(); itdorColind != itdorPais->getPaisesColindantes().end();++itdorColind){
                ss << *itdorColind;
                if(next(itdorColind) != itdorPais->getPaisesColindantes().end()){
                    ss << ";";
                }
            }
            ss << "\n";
        }
        ss << "#\n";
    }

    ss << "CARTASRISK:\n";
    ss << "#\n";
    for(std::vector<Carta>::iterator itdorCartasR = cartas.begin(); itdorCartasR != cartas.end(); ++itdorCartasR){
        ss << itdorCartasR->getTipoUnidad() << ";";
        ss << itdorCartasR->getCodigoPais() << ";";
        ss << itdorCartasR->isComodin() << "\n";
    }
    ss << "#\n";
    ss << "TURNOPARTIDA:\n";
    ss << turnoPartida << "\n";
    ss << "RECLAMOCARTAS:\n";
    ss << reclamoCartas << "\n";
    ss << "#FIN#\n";

}

void Risk::setTestData(){

    cartas.push_back(Carta("Comodin",0,1)); cartas.push_back(Carta("Comodin",0,1));

    cartas.push_back(Carta("Caballeria", 1, 0));cartas.push_back(Carta("Infanteria", 2, 0));cartas.push_back(Carta("Artilleria", 3, 0));cartas.push_back(Carta("Caballeria", 4, 0));
    cartas.push_back(Carta("Artilleria", 5, 0));cartas.push_back(Carta("Infanteria", 6, 0));cartas.push_back(Carta("Infanteria", 7, 0));cartas.push_back(Carta("Caballeria", 8, 0));
    cartas.push_back(Carta("Caballeria", 9, 0));cartas.push_back(Carta("Artilleria", 10, 0));cartas.push_back(Carta("Infanteria", 11, 0));cartas.push_back(Carta("Caballeria", 12, 0));
    cartas.push_back(Carta("Artilleria", 13, 0));cartas.push_back(Carta("Infanteria", 14, 0));cartas.push_back(Carta("Infanteria", 15, 0));cartas.push_back(Carta("Artilleria", 16, 0));
    cartas.push_back(Carta("Artilleria", 17, 0));cartas.push_back(Carta("Infanteria", 18, 0));cartas.push_back(Carta("Caballeria", 19, 0));cartas.push_back(Carta("Caballeria", 20, 0));
    cartas.push_back(Carta("Caballeria", 21, 0));cartas.push_back(Carta("Artilleria", 22, 0));cartas.push_back(Carta("Infanteria", 23, 0));cartas.push_back(Carta("Caballeria", 24, 0));
    cartas.push_back(Carta("Caballeria", 25, 0));cartas.push_back(Carta("Infanteria", 26, 0));cartas.push_back(Carta("Infanteria", 27, 0));cartas.push_back(Carta("Caballeria", 28, 0));
    cartas.push_back(Carta("Infanteria", 29, 0));cartas.push_back(Carta("Artilleria", 30, 0));cartas.push_back(Carta("Infanteria", 31, 0));cartas.push_back(Carta("Artilleria", 32, 0));
    cartas.push_back(Carta("Artilleria", 33, 0));cartas.push_back(Carta("Artilleria", 34, 0));cartas.push_back(Carta("Infanteria", 35, 0));cartas.push_back(Carta("Caballeria", 36, 0));
    cartas.push_back(Carta("Artilleria", 37, 0));cartas.push_back(Carta("Caballeria", 38, 0));cartas.push_back(Carta("Artilleria", 39, 0));cartas.push_back(Carta("Caballeria", 40, 0));
    cartas.push_back(Carta("Caballeria", 41, 0));cartas.push_back(Carta("Infanteria", 42, 0));


    continentes.push_back(
            Continente(0, "America del Norte", {
                    Pais(1,"Alaska", 0, 0, {6,2,22}),
                    Pais(2,"Alberta", 0, 0, {1,2,6,9,7}),
                    Pais(3,"America Central", 0, 0, {32,9,4}),
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
                    Pais(10,"Gran Bretana", 0, 0, {11,13,12,16}),
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

}

#endif
