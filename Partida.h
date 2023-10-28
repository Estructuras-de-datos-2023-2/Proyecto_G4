#ifndef PARTIDA_H
#define PARTIDA_H

//Definicion de la clase Jugador.h y OCntinente.h
#include "Jugador.h"
#include "Continente.h"

using namespace std;

//Definicion clase Partida

class Partida
{
private:
    vector<Jugador> jugadores; // Vector de jugadores participantes en la partida
    vector<Continente> continentes; // Vector de continentes en el juego
public:
    Partida(); // Constructor de la clase Partida
    void inicializar(); // Inicializa el juego con jugadores, continentes y territorios
    void turno(int); // Realiza el turno de un jugador en la partida
    void agregarJugador(string,string,int); // Agrega un jugador a la partida con su nombre, color y estrategia
    vector <Jugador> getJugadores(); // Obtiene el vector de jugadores en la partida
    void setContinentes(vector<Continente>); // Establece los continentes en la partida
    void asignarTerritorios(); // Asigna territorios a los jugadores de manera aleatoria
    void mostrarContinentes(); // Muestra los nombres de los continentes en la partida
    bool verificarContinentes(); // Verifica si todos los continentes tienen al menos un territorio asignado
    void escogerTerritorio(); // Permite a los jugadores elegir un territorio para empezar
    int pedirContinente(string); // Solicita a un jugador que elija un continente
    int pedirPais(string, Continente); // Solicita a un jugador que elija un país de un continente específico
    Continente buscarContinente(int); // Busca un continente por su número
    vector<Continente> leerContinentes(); // Lee los continentes y sus territorios desde un archivo
    int buscarJugador(string);  // Busca un jugador por su nombre y devuelve su posición en el vector de jugadores
    void ubicarEjercito(int); // Ubica tropas al inicio del turno de un jugador
    int tropasAdicionales(string); // Calcula las tropas adicionales que un jugador recibe al inicio de su turno
    void agregarTropasTerr(int); // Permite a un jugador agregar tropas a sus territorios
    int pedirTropas(int);  // Solicita a un jugador la cantidad de tropas que desea agregar
    string pedirPais(int); // Solicita a un jugador el nombre de un país
    void atacar(int); // Permite a un jugador realizar ataques
    void buscarPaisesVecinos(int, int); // Muestra los países vecinos de un territorio
    vector<int> paisAAtacar(string); // Permite a un jugador elegir un país para atacar
    vector<int> getPosicionesPais(string); // Obtiene las posiciones de un país en el vector de continentes
    void batalla(vector <int>,vector <int>); // Simula una batalla entre un atacante y un defensor
    void fortalecer(int); // Permite a un jugador fortalecer sus territorios al final de su turno
    int verificarTropas(int, string); // Verifica y limita la cantidad de tropas que un jugador puede enviar
    bool verTropas(); // Verifica si un jugador aún tiene tropas disponibles
    vector <int> lanzarDados(int); // Simula el lanzamiento de dados y devuelve los resultados
    void asignarUltimasTropas(); // Asigna las últimas tropas al finalizar un turno
    string pedirTerritorio(int); // Solicita a un jugador el nombre de un territorio

};
#endif // Partida.h
