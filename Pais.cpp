// Incluir el archivo de cabecera correspondiente

#include "Pais.h"

//Definir códigos de colores para la salida en consola

#define AMARILLO     "\033[33m"
#define BLANCO       "\033[37m"
#define AZUL_OSCURO  "\033[34m"

using namespace std;

// Constructor por defecto

Pais::Pais()
{

}

// Constructor con nombre, número y cantidad de tropas

Pais::Pais(string n, int num, int tropas)
{
    this->nombre = n;
    this->numero = num;
    this->tropas = tropas;
}

// Constructor con nombre y número

Pais::Pais(string n, int num)
{
    this->nombre = n;
    this->numero = num;
}

// Agregar un país vecino a la lista de países vecinos

void Pais::agregarPaisVecino(string pais)
{
    this->paisesVecinos.push_back(pais);
}

// Mostrar los países vecinos en consola

void Pais::mostrarPaisesVecinos()
{
    cout<<endl<< AMARILLO <<"Fronteras de: "<<this->nombre<<endl;
    for(int i = 0; i < this -> paisesVecinos.size(); i++)
        cout <<endl << this->paisesVecinos[i];
    cout<<endl;
}

// Establecer el nombre del país

void Pais::setNombre(string n)
{
    this->nombre = n;
}

// Obtener el nombre del país

string Pais::getNombre()
{
    return this->nombre;
}

// Establecer el número del país

void Pais::setNumero(int n)
{
    this->numero = n;
}

// Obtener el número del país

int Pais::getNumero()
{
    return this->numero;
}

// Establecer el propietario del país

void Pais::setPropietario(string p)
{
    this->propietario = p;
}

// Obtener el propietario del país

string Pais::getPropietario()
{
    return this->propietario;
}

// Establecer la cantidad de tropas en el país

void Pais::setTropas(int t)
{
    this->tropas = t;
}

// Obtener la cantidad de tropas en el país

int Pais::getTropas()
{
    return this->tropas;
}

// Sumar una cantidad de tropas al país

void Pais::sumarTropas(int n)
{
    this->tropas += n;
}

// Restar una cantidad de tropas al país

void Pais::restarTropas(int n)
{
    this->tropas -= n;
}

