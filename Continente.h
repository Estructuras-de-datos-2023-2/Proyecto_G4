// Librerías

#include <iostream>
#include <vector>
#include "Pais.h"

using namespace std;

// Definición de la clase Continente

class Continente
{
private:
    int numero; // Número de identificación del continente
    int contador; // Contador de ocupación del continente
    string nombre; // Nombre del continente
    vector <Pais> paises; // Vector de países que componen el continente
public:
    Continente(); // Constructor por defecto
    Continente(string); // Constructor con nombre

    bool verificarTerritorio(int, string); // Verifica si un territorio pertenece a un jugador específico
    void llenarListaPaises(); // Llena la lista de países del continente
    void agregarPais(Pais); // Agrega un país al continente
    string buscarPais(int); // Busca un país por número y devuelve su nombre
    vector <Pais> borrarPais(int); // Borra un país de la lista del continente
    void mostrarPaises(); // Muestra los países del continente
    bool paisOcupado(int); // Verifica si un país está ocupado
    string verificarContinente(string); // Verifica si un jugador controla todo el continente
    bool verificarPaises(); // Verifica si todos los países en el continente tienen propietario
    void sumarTropas(int, int); // Suma tropas a un país en el continente
    void restarTropas(int, int); // Resta tropas a un país en el continente
    vector<Pais> obtenerDisponibles(); // Obtiene una lista de países disponibles (sin propietario)
    string obtenerPropietario(int); // Obtiene el propietario de un país en el continente
    void marcarOcupado(int, string); // Marca un país como ocupado por un jugador
    void mostrarVecinos(int); // Muestra los países vecinos de un país en el continente
    void getPaisTropas(int); // Muestra las tropas en un país del continente
    void cambiarPropietario(int, string); // Cambia el propietario de un país en el continente

    int getCantiPaises(); // Obtiene la cantidad de países en el continente
    void setContador(int); // Establece el contador de ocupación del continente
    int getContador(); // Obtiene el contador de ocupación del continente
    int getNumero(); // Obtiene el número de identificación del continente
    void setNumero(int); // Establece el número de identificación del continente
    void setNombre(string); // Establece el nombre del continente
    string getNombre(); // Obtiene el nombre del continente
    vector <Pais> getPaises(); // Obtiene el vector de países del continente
    void setPaises(vector <Pais>); // Establece el vector de países del continente
    int getTropas(int); // Obtiene la cantidad de tropas en un país del continente

    string toString(); // Método para obtener una representación en cadena
};
