// Definición de la clase Continente

#include "Continente.h"

//Definir códigos de colores para la salida en consola

#define AMARILLO     "\033[33m"
#define BLANCO       "\033[37m"
#define AZUL_OSCURO  "\033[34m"

// Constructor por defecto

Continente::Continente()
{

}

// Agrega un país a la lista de países del continente

void Continente::agregarPais(Pais p)
{
    this->paises.push_back(p);
}

// Busca un país por número y devuelve su nombre

string Continente::buscarPais(int t)
{
    for(Pais p : this->paises)
    {
        if(t == p.getNumero())
            return p.getNombre();
    }
    return "error";
}

// Verifica si un territorio pertenece a un jugador específico

bool Continente::verificarTerritorio(int n, string jugador)
{
    if(paises[n].getPropietario() == jugador)
        return true;
    return false;
}

// Obtiene una lista de países disponibles (sin propietario)

vector<Pais> Continente::obtenerDisponibles()
{
    vector <Pais> disponibles;
    for(Pais p : this->paises)
    {
        if(p.getPropietario() == "libre")
            disponibles.push_back(p);
    }
    return disponibles;
}

// Borra un país de la lista de países

vector <Pais> Continente::borrarPais(int pais)
{
    for(auto it = paises.begin(); it != paises.end(); ++it)
    {
        if(pais == it->getNumero())
            paises.erase(it);
    }
    return paises;
}

// Cambia el propietario de un país en el continente

void Continente::cambiarPropietario(int n, string nom)
{
    this->paises[n].setPropietario(nom);
}

// Muestra los países en el continente

void Continente::mostrarPaises()
{
    cout<<endl<<this->nombre<<endl;
    cout<<endl<< AMARILLO <<"0. volver a continentes"<<endl;
    for(Pais p : paises)
    {
        cout<<endl<<p.getNumero()<<". "<<p.getNombre()<<endl<<p.getPropietario()<<endl;
    }
}

// Obtiene el propietario de un país en el continente

string Continente::obtenerPropietario(int n)
{
    return this->paises[n].getPropietario();
}

// Muestra los países vecinos de un país en el continente

void Continente::mostrarVecinos(int n)
{
    this->paises[n].mostrarPaisesVecinos();
}

// Verifica si un jugador controla todo el continente

string Continente::verificarContinente(string nombre)
{
    int i = 0;
    for(Pais p : this->paises)
        if(p.getPropietario() == nombre)
            i++;
    if(i == paises.size())
        return this->nombre;
    else
        return "nada";
}

// Verifica si todos los países en el continente tienen propietario

bool Continente::verificarPaises()
{
    int i = 0;
    for(Pais p : this->paises)
    {
        if(p.getPropietario() != "libre")
            i++;
    }
    if(paises.size() == i)
        return true;
    return false;
}

// Marca un país como ocupado por un jugador

void Continente::marcarOcupado(int n, string nombre)
{
    this->paises[n-1].setPropietario(nombre);
    this->paises[n-1].setTropas(1);
    this->contador++;
}

// Verifica si un país está ocupado

bool Continente::paisOcupado(int numero)
{
    if(paises[numero-1].getPropietario() == "libre")
        return true;
    return false;
}

// Suma tropas a un país en el continente

void Continente::sumarTropas(int p, int trop)
{
    this->paises[p].sumarTropas(trop);
}

// Resta tropas a un país en el continente

void Continente::restarTropas(int p, int trop)
{
    this->paises[p].restarTropas(trop);
}

// Métodos Getters y Setters

int Continente::getTropas(int n)
{
    return this->paises[n].getTropas();
}

void Continente::getPaisTropas(int n)
{
    cout<<endl<<"Tropas en "<<paises[n].getNombre()<<": "<<paises[n].getTropas()<<endl;
}

int Continente::getCantiPaises()
{
    return this->paises.size();
}

vector <Pais> Continente::getPaises()
{
    return this->paises;
}

void Continente::setPaises(vector<Pais>p)
{
    this->paises = p;
}

int Continente::getNumero()
{
    return this->numero;
}

void Continente::setNumero(int n)
{
    this->numero = n;
}

void Continente::setNombre(string n)
{
    this->nombre = n;
}

string Continente::getNombre()
{
    return this->nombre;
}

void Continente::setContador(int n)
{
    this->contador = n;
}

int Continente::getContador()
{
    return this->contador;
}

// Método toString para representación en cadena

string Continente::toString()
{
    string cadena = this->nombre;
    for(Pais p : this->paises)
    {
        cadena += "\n" + p.getNombre();
    }
    return cadena;
}
