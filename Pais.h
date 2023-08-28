//Librerias

#include <iostream>
#include <vector>

using namespace std;

// Definición de la clase Pais

class Pais
{
private:
    string nombre; // Nombre del país
    int numero; // Número del país
    string propietario; // Propietario del país
    int tropas; // Cantidad de tropas en el país
    vector <string> paisesVecinos; // Vector que almacena los países vecinos
public:// Constructores
    Pais(); // Constructor por defecto
    Pais(string,int); // Constructor con nombre y número
    Pais(string,int,int); // Constructor con nombre, número y tropas

// Métodos para manejar países vecinos

// Agrega un país vecino a la lista

    void agregarPaisVecino(string);

// Muestra los países vecinos en consola

    void mostrarPaisesVecinos();

  // Métodos para establecer y obtener el nombre del país

    void setNombre(string);
    string getNombre();

// Métodos para establecer y obtener el número del país

    void setNumero(int);
    int getNumero();

// Métodos para establecer y obtener el propietario del país

    void setPropietario(string);
    string getPropietario();

 // Métodos para manejar la cantidad de tropas en el país

    void sumarTropas(int);
    void restarTropas(int);
    void setTropas(int);
    int getTropas();

};
