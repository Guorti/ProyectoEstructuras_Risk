// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN
// This includes the catch.hpp file
#include "lib/catch.hpp"
#include "Jugador.h"
#include "Continente.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Risk.h"

// Include the header file of the class that you are testing

// Create a test case
TEST_CASE("Guardar")
{
    // Create a section, this is just to organize your tests
    SECTION("Guardado de archivo de texto con datos quemados")
    {
        bool abrioArchivoTexto;
        bool archivoContieneDatos;
        std::string primerLineaArchivo;

        Risk Risk1;
        //Quemamos informacion por defecto del juego Risk. Cartas, paises, continentes
        Risk1.setTestData();
        //Definimos turnos de los jugadores
        Risk1.getTurnosJugadores() = {1, 2, 3};

        //Definimos ciertos jugadores de prueba
        Jugador jugadorInstance1(1, "Daniel", 1, 40);
        //Cargamos cartas
        jugadorInstance1.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance1.getCartasVector().push_back(Carta("Artilleria", 5, 0));
        Jugador jugadorInstance2(2, "Miguel", 2, 45);
        jugadorInstance2.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance2.getCartasVector().push_back(Carta("Artilleria", 5, 0));
        Jugador jugadorInstance3(3, "Julian", 3, 50);
        jugadorInstance3.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance3.getCartasVector().push_back(Carta("Artilleria", 5, 0));

        Risk1.getJugadores().push_back(jugadorInstance1);
        Risk1.getJugadores().push_back(jugadorInstance2);
        Risk1.getJugadores().push_back(jugadorInstance3);


        Risk1.setTurnoPartida(-1);
        Risk1.setReclamoCartas(2);

        Risk1.guardarPartidaText("Test.txt");

        //Se intenta abrir elarchivo creado
        std::ifstream inputFile("Test.txt", std::ios::in); // Open the file for reading

        if (!inputFile.is_open()) {
            abrioArchivoTexto = false;
        }
        else{
            abrioArchivoTexto = true;
        }
        //Se analiza la primer linea del archivo
        getline(inputFile, primerLineaArchivo);
        if(primerLineaArchivo == "TURNOSJUGADORES:"){
            archivoContieneDatos = true;
        }
        else{
            archivoContieneDatos = false;
        }

        inputFile.close();

        INFO("Se intenta crear un archivo, se comprueban sus datos y existencia")

        //Se comprueban las banderas de existencia y veracidad de datos, si no concuerdan el test fallará.
        REQUIRE(abrioArchivoTexto == true);
        REQUIRE(archivoContieneDatos == true);
    }

}


TEST_CASE("Guardar Comprimido")
{
    SECTION("Guardado de archivo binario")
    {
        bool abrioArchivoTexto;
        std::string primerLineaArchivo;

        Risk Risk1;

        //Quemamos informacion por defecto del juego Risk. Cartas, paises, continentes
        Risk1.setTestData();
        //Definimos turnos de los jugadores
        Risk1.getTurnosJugadores() = {1, 2, 3};
        //Definimos ciertos jugadores de prueba
        Jugador jugadorInstance1(1, "Daniel", 1, 40);
        //Cargamos cartas
        jugadorInstance1.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance1.getCartasVector().push_back(Carta("Artilleria", 5, 0));
        Jugador jugadorInstance2(2, "Miguel", 2, 45);
        jugadorInstance2.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance2.getCartasVector().push_back(Carta("Artilleria", 5, 0));
        Jugador jugadorInstance3(3, "Julian", 3, 50);
        jugadorInstance3.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance3.getCartasVector().push_back(Carta("Artilleria", 5, 0));

        Risk1.getJugadores().push_back(jugadorInstance1);
        Risk1.getJugadores().push_back(jugadorInstance2);
        Risk1.getJugadores().push_back(jugadorInstance3);


        Risk1.setTurnoPartida(-1);
        Risk1.setReclamoCartas(2);

        Risk1.guardarPartidaBin("TestBin.bin");

        //Se intenta abrir elarchivo creado
        std::ifstream inputFile("TestBin.bin", std::ios::in); // Open the file for reading

        if (!inputFile.is_open()) {
            abrioArchivoTexto = false;
        }
        else{
            abrioArchivoTexto = true;
        }

        inputFile.close();

        INFO("Se intenta crear un archivo binario, se revisa su creacion")

        //Se comprueban las banderas de existencia y veracidad de datos, si no concuerdan el test fallará.
        REQUIRE(abrioArchivoTexto == true);
    }
    //el to string sea igual al descomprimido

    //Se realiza un to string con los datos actuales, si despues de cargar el archivo
    //el tstring sigue siendo el mismo, la prueba será satisfactoria

}

TEST_CASE("Descompresion satisfactoria")
{
    Risk Risk1;
    Risk RiskTestCarga;
    std::ostringstream datosIniciales;
    std::ostringstream datosDescomprimidos;

    SECTION("Quemado de datos y guardado de archivo binario")
    {

        //Quemamos informacion por defecto del juego Risk. Cartas, paises, continentes
        Risk1.setTestData();
        //Definimos turnos de los jugadores
        Risk1.getTurnosJugadores() = {1, 2, 3};
        //Definimos ciertos jugadores de prueba
        Jugador jugadorInstance1(1, "Daniel", 1, 40);
        //Cargamos cartas
        jugadorInstance1.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance1.getCartasVector().push_back(Carta("Artilleria", 5, 0));
        Jugador jugadorInstance2(2, "Miguel", 2, 45);
        jugadorInstance2.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance2.getCartasVector().push_back(Carta("Artilleria", 5, 0));
        Jugador jugadorInstance3(3, "Julian", 3, 50);
        jugadorInstance3.getCartasVector().push_back(Carta("Caballeria", 1, 0));
        jugadorInstance3.getCartasVector().push_back(Carta("Artilleria", 5, 0));

        Risk1.getJugadores().push_back(jugadorInstance1);
        Risk1.getJugadores().push_back(jugadorInstance2);
        Risk1.getJugadores().push_back(jugadorInstance3);


        Risk1.setTurnoPartida(-1);
        Risk1.setReclamoCartas(2);


        Risk1.guardarPartidaBin("TestDescompresion.bin");


        Risk1.allDataToString(datosIniciales);
        cout<<"INICIALES1-+-+-+-+-+-+-+-+-+-+-+-+-+-+:"<<endl;
        cout<<datosIniciales.str();


        RiskTestCarga.inicializarPartida("TestDescompresion.bin");
        RiskTestCarga.allDataToString(datosDescomprimidos);

        cout<<"DESCOMPRESOS-+-+-+-+-+-+-+-+-+-+-+-+-+--++-+-+-+-+--+:"<<endl;
        cout<<datosDescomprimidos.str();

        REQUIRE(datosIniciales.str() == datosDescomprimidos.str());

    }
}