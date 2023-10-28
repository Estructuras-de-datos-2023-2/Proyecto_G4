// Definición de la clase Jugador

#include "Jugador.h"

//Definir códigos de colores para la salida en consola

#define AMARILLO     "\033[33m"
#define BLANCO       "\033[37m"
#define AZUL_OSCURO  "\033[34m"

using namespace std;

Jugador::Jugador(string n, string c, int i, int a, int ca)
{
    this->nombre = n; // Nombre del jugador
    this->color = c; // Color del jugador
    this->infanteria = i; // Cantidad de unidades de infantería
    this->artilleria = a; // Cantidad de unidades de artillería
    this->caballeria = ca; // Cantidad de unidades de caballería
}

Jugador::Jugador(string n, string c, int i)
{
    this->nombre = n; // Nombre del jugador
    this->color = c; // Color del jugador
    this->infanteria = i; // Cantidad de unidades de infantería
}

void Jugador::agregarTerritorio(string t)
{
    this->territorios.push_back(t); // Agrega un territorio a la lista de territorios del jugador
}

int Jugador::contarTerritorios()
{
    return this->territorios.size(); // Devuelve la cantidad de territorios que posee el jugador
}

void Jugador::eliminarTerritorio(string terr)
{
    for(int i=0; i<territorios.size(); i++)
    {
        if(terr == territorios[i]) // Elimina un territorio de la lista de territorios del jugador
            territorios.erase(territorios.begin() + i);
    }
}

void Jugador::mostrarTerritorios()
{
    cout<<endl<< AMARILLO <<"Territorios del jugador "<<this->nombre<<":"<<endl;
    for(string &t : this->territorios)
    {
        cout<<endl<<t; // Muestra los territorios que posee el jugador
    }
    cout<<endl;
}

vector<string> Jugador:: getTerritorios()
{
    return territorios;  // Devuelve la lista de territorios del jugador
}

void Jugador:: setTerritorios(vector<string> territorios)
{
    this->territorios = territorios; // Establece la lista de territorios del jugador
}

string Jugador::buscarTerritorio(string t)
{
    for(int i=0; i<territorios.size(); i++)
    {
        if(t == territorios[i]) 
            return territorios[i]; // Busca un territorio en la lista y lo devuelve si lo encuentra
    }
    return "error"; // Devuelve "error" si no encuentra el territorio
}

string Jugador::getNombre()
{
    return this->nombre; // Devuelve el nombre del jugador
}

void Jugador::setNombre(string nombre)
{
    this->nombre = nombre; // Establece el nombre del jugador
}

string Jugador::getColor()
{
    return color; // Devuelve el color del jugador
}

void Jugador::setColor(string color)
{
    this->color = color; // Establece el color del jugador
}

void Jugador::restarInfanteria(int n)
{
    this->infanteria -= n; // Resta unidades de infantería al jugador
}

void Jugador::sumarInfanteria(int n)
{
    this->infanteria += n; // Suma unidades de infantería al jugador
}

int Jugador::getInfanteria()
{
    return infanteria; // Devuelve la cantidad de unidades de infantería del jugador
}

void Jugador::setInfanteria(int infanteria)
{
    this->infanteria = infanteria; // Establece la cantidad de unidades de infantería del jugador
}

int Jugador::getArtilleria()
{
    return artilleria; // Devuelve la cantidad de unidades de artillería del jugador
}

void Jugador::setArtilleria(int artilleria)
{
    this->artilleria = artilleria; // Establece la cantidad de unidades de artillería del jugador
}

int Jugador::getCaballeria()
{
    return caballeria; // Devuelve la cantidad de unidades de caballería del jugador
}

void Jugador::setCaballeria(int caballeria)
{
    this->caballeria = caballeria; // Establece la cantidad de unidades de caballería del jugador
}

void Jugador::ToTerritorios()
{
    for(int i=0; i<territorios.size(); i++)
    {
        cout<<endl<<i+1<<". "<<territorios[i]; // Muestra los territorios del jugador con números
    }
}
