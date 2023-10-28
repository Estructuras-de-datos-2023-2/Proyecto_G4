//Librerias

#include <iostream>
#include <vector>

using namespace std;

// Definición de la clase Jugador

class Jugador
{
private:
    vector<string> territorios; // Lista de territorios que posee el jugador
    string nombre; // Nombre del jugador
    string color; // Color del jugador
    int infanteria; // Cantidad de unidades de infantería del jugador
    int artilleria; // Cantidad de unidades de artillería del jugador
    int caballeria; // Cantidad de unidades de caballería del jugador

public:
    Jugador(string,string, int, int, int); // Constructor para inicializar el jugador con nombre, color e unidades iniciales
    Jugador(string,string,int); // Constructor para inicializar el jugador con nombre, color y unidades de infantería
    void agregarTerritorio(string); // Agrega un territorio a la lista de territorios del jugador
    int contarTerritorios(); // Devuelve la cantidad de territorios que posee el jugador
    string buscarTerritorio(string); // Busca un territorio en la lista de territorios y lo devuelve si lo encuentra
    void eliminarTerritorio(string); // Elimina un territorio de la lista de territorios del jugador

// Getters y setters para los atributos de la clase

    void mostrarTerritorios(); // Muestra los territorios que posee el jugador
    vector<string> getTerritorios(); // Devuelve la lista de territorios del jugador
    void setTerritorios(vector<string>); // Establece la lista de territorios del jugador

    string getNombre(); // Devuelve el nombre del jugador
    void setNombre(string); // Establece el nombre del jugador

    string getColor(); // Devuelve el color del jugador
    void setColor(string); // Establece el color del jugador

    void restarInfanteria(int); // Resta unidades de infantería al jugador
    void sumarInfanteria(int); // Suma unidades de infantería al jugador
    int getInfanteria(); // Devuelve la cantidad de unidades de infantería del jugador
    void setInfanteria(int); // Establece la cantidad de unidades de infantería del jugador

    int getArtilleria(); // Devuelve la cantidad de unidades de artillería del jugador
    void setArtilleria(int); // Establece la cantidad de unidades de artillería del jugador
 
    int getCaballeria(); // Devuelve la cantidad de unidades de caballería del jugador
    void setCaballeria(int); // Establece la cantidad de unidades de caballería del jugador


    void ToTerritorios(); // Muestra los territorios del jugador con números

};
