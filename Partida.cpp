// Incluye la declaración de la clase Partida

#include "Partida.h"

// Librerías

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <random>

// Definición de color

#define AMARILLO     "\033[33m"
#define BLANCO       "\033[37m"
#define AZUL_OSCURO  "\033[34m"

using namespace std;

// Declaración de la función auxiliar "separar"

vector <string> separar(string,char);

// Constructor por defecto de la clase Partida

Partida::Partida()
{

}

// Método para agregar un jugador a la partida

void Partida::agregarJugador(string n, string c, int i)
{
    Jugador * j = new Jugador (n,c,i);
    this->jugadores.push_back(*j);
}

// Método para obtener la lista de jugadores

vector <Jugador> Partida::getJugadores()
{
    return this->jugadores;
}

// Método para establecer la lista de continentes

void Partida::setContinentes(vector<Continente>c)
{
    this->continentes = c;
}

// Método para verificar si todos los continentes han sido conquistados por un jugador

bool Partida::verificarContinentes()
{
    int i = 0;
    for(Continente c : continentes)
    {
        if(c.getContador() == c.getCantiPaises())
            i++;
    }
    if(i == continentes.size())
        return true;
    return false;
}

// Método para solicitar al jugador que elija un continente

int Partida::pedirContinente(string nombre)
{
    int continente;
    do
    {
        mostrarContinentes();
        cout<<endl<< AMARILLO <<nombre<< ", porfavor digite el número del continente que desea escoger: ";
        cin>>continente;
        if(continente<1 || continente>6)
            cout<<endl<< AMARILLO <<"Ingresó un valor inválido, inténte de nuevo"<<endl;
    }
    while(continente<1 || continente>6);
    return continente;
}

// Método para solicitar al jugador que elija un país para atacar desde

int Partida::pedirPais(string nombre, Continente c)
{
    int pais;
    bool encontrado = false;
    do
    {
        c.mostrarPaises(); // Muestra la lista de países en el continente
        cout<<endl<< AMARILLO <<nombre<< ", digite el número del país que desea escoger: ";
        cin>>pais;
  // Si el jugador elige 0, se le pide que elija un continente primero
        if(pais == 0)
            c = continentes[pedirContinente(nombre) - 1];
           // Si el país no se encuentra o ya está ocupado, se le indica al jugador
        else if(c.buscarPais(pais) == "Error :(" || !c.paisOcupado(pais))
            cout<<endl<< AMARILLO <<"El país no fue encontrado o está ocupado, inténte de nuevo"<<endl;
        else
            encontrado = true;
    }
    while(!encontrado);
    return pais;
}

// Método para que cada jugador escoja sus territorios iniciales

void Partida::escogerTerritorio()
{
    int c, p;
    for(Jugador &j : jugadores)
    {
        c = pedirContinente(j.getNombre()) - 1; // El jugador elige un continente
        p = pedirPais(j.getNombre(), continentes[c]); // El jugador elige un país dentro del continente
        string territorio = continentes[c].buscarPais(p); // Obtiene el nombre del país elegido
        j.agregarTerritorio(territorio); // Agrega el territorio al jugador
        j.restarInfanteria(1); // Resta una tropa de infantería al jugador
        continentes[c].marcarOcupado(p, j.getNombre()); // Marca el país como ocupado por el jugador
    }
}

// Método para asignar territorios iniciales a los jugadores

void Partida::asignarTerritorios()
{
    cout << endl << AMARILLO <<"¡A hora vamos a escoger sus territorios!" << endl;
    continentes = leerContinentes(); // Lee la información de los continentes y países desde un archivo
    while(!verificarContinentes()) // Mientras no todos los continentes estén conquistados
        escogerTerritorio(); // Cada jugador escoge un territorio
    while(!verTropas()) // Mientras no todos los jugadores tengan tropas
        asignarUltimasTropas(); // Se asignan las últimas tropas restantes a los territorios
    for(Jugador &j : jugadores)
        j.mostrarTerritorios(); // Se muestran los territorios asignados a cada jugador
}

// Método para asignar las últimas tropas restantes a los territorios de los jugadores

void Partida::asignarUltimasTropas() 
{
    string territorio;
    vector <int> pos;
    int i=0;
    for(Jugador &j : this->jugadores)
    {
        j.mostrarTerritorios(); // Muestra los territorios que tiene el jugador
        territorio = pedirTerritorio(i); // El jugador elige un territorio para asignar tropas
        pos = getPosicionesPais(territorio); // Obtiene la posición del país en el que se asignarán tropas
        continentes[pos[0]].sumarTropas(pos[1], 1); // Incrementa el número de tropas en el país
        j.restarInfanteria(1); // Resta una tropa de infantería al jugador
        continentes[pos[0]].getPaisTropas(pos[1]); // Muestra el número actual de tropas en el país
        cout<<endl<<"Le quedan "<<j.getInfanteria()<<" tropas"<<endl; // Muestra las tropas restantes del jugador
        i++;
    }
}

// Método para que el jugador elija un territorio al que quiera asignar tropas

string Partida::pedirTerritorio(int pos)
{
    string t;
    do{
        cout<<endl<< AZUL_OSCURO <<"Digite el nombre de un territorio para colocar una tropa: ";
        cin>>t;
      
// Si el territorio no pertenece al jugador, se le indica al jugador
      
        if(jugadores[pos].buscarTerritorio(t) == "error")
            cout<<endl<< AZUL_OSCURO <<"Dato erróneo, inténtelo de nuevo"<<endl;
    }while(jugadores[pos].buscarTerritorio(t) == "error");
    return t;
}

// Método para verificar si todos los jugadores tienen tropas restantes

bool Partida::verTropas()
{
    int i = 0;
    for(Jugador &j : this->jugadores)
    {
        if(j.getInfanteria() == 0)
            i++;
    }
    if(i == jugadores.size())
        return true;
    return false;
}

// Método para buscar un continente por su número

Continente Partida::buscarContinente(int n)
{
    for(Continente c : continentes)
    {
        if(n == c.getNumero())
            return c;
    }
    Continente * c = new Continente ();
    return *c;
}

// Método para leer la información de los continentes y países desde un archivo

vector<Continente> Partida::leerContinentes()
{ 
    fstream archivo; // Crear un objeto para trabajar con archivos
    string leer, token;
    vector<string> cadenas, vecinos;
    vector <Continente> lista; // Vector para almacenar los continentes leídos
    int i = 0; // Contador para el número de continentes
    archivo.open("territorios.txt"); // Abrir el archivo "territorios.txt" en modo lectura
    if (!archivo) // Si no se puede abrir el archivo
        cout << AZUL_OSCURO <<  "No se pudo abrir el archivo." << endl;
    else
    {
        getline(archivo,leer); // Leer una línea del archivo (el primer indicador de continente)
        while(leer != "FIN") // Repetir mientras no se alcance el final del archivo
        {
            i++; // Incrementar el contador de continentes
            if(leer != "#") // Si la línea no es un comentario
            {
                Continente c; // Crear un objeto Continente para almacenar la información
                getline(archivo,leer); // Leer el nombre del continente desde el archivo
                c.setNombre(leer); // Establecer el nombre del continente en el objeto
                c.setNumero(i); // Establecer el número del continente en el objeto
                c.setContador(0); // Inicializar el contador de tropas en 0
                getline(archivo,leer); // Leer la siguiente línea (indicador de inicio de países)
                getline(archivo,leer); // Leer la siguiente línea (primera línea de información del país)
                while(leer != "#") // Repetir mientras no se alcance el final de la sección de países
                {
                    Pais p; // Crear un objeto Pais para almacenar la información del país
                    cadenas = separar(leer, '-'); // Separar la línea en partes utilizando el separador '-'
                    p.setNumero(stoi(cadenas[0])); // Convertir y establecer el número del país
                    p.setNombre(cadenas[1]); // Establecer el nombre del país
                    p.setPropietario("libre"); // Establecer el propietario inicial del país
                    getline(archivo,leer); // Leer la siguiente línea (indicador de países vecinos)
                    vecinos = separar(leer, '/'); // Separar la línea en partes utilizando el separador '/'
                    for(int i = 0; i < vecinos.size(); i++) // Recorrer los países vecinos
                        p.agregarPaisVecino(vecinos[i]); // Agregar cada país vecino al objeto Pais
                    getline(archivo,leer); // Leer la siguiente línea (primera línea del siguiente país)
                    c.agregarPais(p); // Agregar el objeto Pais al objeto Continente
                }
                getline(archivo,leer); // Leer la siguiente línea (indicador de fin de la sección de países)
                lista.push_back(c); // Agregar el objeto Continente al vector de continentes
            }
            if(archivo.eof()) // Si se llega al final del archivo
                break; // Salir del bucle
        }
    }
    return lista; // Devolver el vector de continentes leídos
}

// Método para mostrar la lista de continentes

void Partida::mostrarContinentes()
{
    for(Continente &c : continentes)
    {
        cout<<endl<<c.getNumero()<<". "<<c.getNombre()<<endl;
    }
}

// Método para buscar y devolver la posición de un jugador en el vector de jugadores

int Partida::buscarJugador(string nombre)
{
    int i = 0;
    for(Jugador &j : jugadores)
    {
        if(nombre == j.getNombre())
            return i; // Devuelve la posición del jugador si se encuentra en el vector
        i++;
    }
    return -1; // Devuelve -1 si el jugador no se encuentra en el vector
}

// Método para ubicar nuevas tropas en un territorio de un jugador

void Partida::ubicarEjercito(int pos)
{
    int nuevasTropas = 0;
    nuevasTropas = jugadores[pos].contarTerritorios()/3; // Calcula la cantidad básica de tropas
    nuevasTropas += tropasAdicionales(jugadores[pos].getNombre()); // Agrega las tropas por continentes controlados
    jugadores[pos].sumarInfanteria(nuevasTropas); // Aumenta la cantidad de tropas del jugador
}

// Método para determinar la cantidad de tropas adicionales que recibe un jugador por continentes controlados

int Partida::tropasAdicionales (string nombre)
{
    for(Continente c : continentes)  // Itera a través de los continentes
    {
        string continente = c.verificarContinente(nombre); // Verifica si el jugador controla el continente
        if(continente != "nada") // Si el jugador controla el continente
        {
          // Asigna la cantidad de tropas adicionales según el continente
            if(continente == "Australia" || continente == "America del Sur")
                return 2;
            else if(continente == "Asia")
                return 7;
            else if(continente == "Africa")
                return 3;
            else if(continente=="America del norte"||continente=="Europa")
                return 5;
        }
    }
    return 0; // Devuelve 0 si el jugador no controla ningún continente
}

// Método para pedir al jugador la cantidad de tropas que desea agregar en su turno

int Partida::pedirTropas(int pos)
{
    int trop, actuales;
    do
    {
        cout << endl << AMARILLO << "Cuantas tropas desea agregar: ";
        cin >> trop;
        actuales = jugadores[pos].getInfanteria();
        if(trop <= jugadores[pos].getInfanteria())
            jugadores[pos].restarInfanteria(trop);
        else
            cout<<endl<< AMARILLO <<"Ingresó más tropas de las que tiene, inténtelo de nuevo"<<endl;
    }
    while(trop > actuales);
    return trop; // Devuelve la cantidad de tropas que el jugador desea agregar
}

// Método para pedir al jugador el nombre de un país que posee

string Partida::pedirPais(int pos)
{
    string pais;
    bool fallo = false, acierto = false;
    do
    {
        cin >> pais;
        if(jugadores[pos].buscarTerritorio(pais) == "error")
        {
            fallo = true;
            cout<<endl<< AMARILLO <<"No posee este territorio"<<endl;
        }
    }
    while(fallo);
    return pais; // Devuelve el nombre del país ingresado por el jugador
}

// Método para permitir al jugador agregar tropas a sus territorios

void Partida::agregarTropasTerr(int pos)
{
    char seguir;
    int trop;
    string pais;
    do
    {
        cout<<endl<< AMARILLO <<"Cuenta con "<<jugadores[pos].getInfanteria()<<" tropas para agregar"<<endl;
        jugadores[pos].ToTerritorios();
        cout << endl << AZUL_OSCURO << "Digite el nombre del pais al que le desea agregar tropas: ";
        pais = pedirPais(pos); // Solicita al jugador que ingrese el país al que desea agregar tropas
        vector <int> k = getPosicionesPais(pais);
        cout<<endl<< AZUL_OSCURO << pais<<" Cuenta con  "<<continentes[k[0]].getTropas(k[1])<<" tropas"<<endl;
        trop = pedirTropas(pos);  // Solicita al jugador la cantidad de tropas a agregar
        continentes[k[0]].sumarTropas(k[1], trop); // Solicita al jugador la cantidad de tropas a agregar
        cout<<endl<< AZUL_OSCURO << pais<<" quedó con "<<continentes[k[0]].getTropas(k[1])<<" tropas"<<endl;
        cout << endl << AZUL_OSCURO <<  "Desea agregar mas tropas: si = s, no = n" << endl;
        cin>>seguir;
        cout<<endl<< AZUL_OSCURO << "Quedaron "<<jugadores[pos].getInfanteria()<<" tropas para agregar"<<endl;
    }
    while(jugadores[pos].getInfanteria() > 0 && seguir == 's');
}

// Método para llevar a cabo las acciones de ataque entre los territorios

void Partida::atacar(int pos)
{
    string pais,atacar;
    bool seguir = false;
    vector <int> i, j;
    jugadores[pos].mostrarTerritorios();

   // Selecciona el país desde el cual el jugador desea atacar
    do
    {
        cout<<endl<<"Digite el nombre del país desde el cual desea atacar: ";
        pais = pedirPais(pos);
        i = getPosicionesPais(pais);
        if(continentes[i[0]].getTropas(i[1]) < 2)
            cout<<endl<<"No puede atacar desde un país que tiene solo una tropa"<<endl;
    }
    while(continentes[i[0]].getTropas(i[1]) < 2);
    buscarPaisesVecinos(i[0], i[1]);

  // Selecciona el país a atacar
    do
    {
        j = paisAAtacar(pais);
        if(continentes[j[0]].verificarTerritorio(j[1], jugadores[pos].getNombre()))
            cout<<endl<<"Usted posee este territorio, no lo puede atacar"<<endl;
        else
            seguir = true;
    }
    while(!seguir);

  // Inicia la batalla entre los dos países seleccionados
    batalla(i, j);
}

// Método para obtener las posiciones de un país en la estructura de datos

vector<int> Partida::getPosicionesPais(string pais)
{
    vector<Pais>paises;
    vector<int>pos;
    for(int i = 0; i<continentes.size(); i++)
    {
        paises = continentes[i].getPaises();
        for(int j=0; j<paises.size(); j++)
        {
            if(pais == paises[j].getNombre())
            {
                pos.push_back(i); // Posición del continente
                pos.push_back(j); // Posición del país dentro del continente
            }
        }
    }
    return pos; // Devuelve las posiciones del continente y el país en un vector
}

// Método para seleccionar el país objetivo de un ataque

vector <int> Partida::paisAAtacar(string pais)
{
    string atacar;
    vector <Pais> paises;
    vector <int> pos;
    bool encontrado = false;
    do
    {
        cout<<endl<< AMARILLO <<"Digite el nombre del país a atacar: ";
        cin>>atacar;
        pos = getPosicionesPais(atacar);
        paises = continentes[pos[0]].getPaises();
      // Comprueba si el país ingresado coincide con uno de los países vecinos disponibles
        if(atacar == paises[pos[1]].getNombre())
            encontrado = true;
        else
            cout<<endl<< AMARILLO <<"No se encontró este país, inténtelo de nuevo"<<endl;
    }
    while(!encontrado);
    return pos; // Devuelve las posiciones del continente y el país en un vector
}

// Método para mostrar los países vecinos de un país seleccionado

void Partida::buscarPaisesVecinos(int c, int p)
{
    this->continentes[c].mostrarVecinos(p);
}

// Método para simular una batalla entre dos países

void Partida::batalla(vector <int> ata, vector <int> def)
{
    //ata: Posición del país atacante
    //def: Posición del país defensor
    char seguir;
    int fin = 0;
    do
    {
      // Obtener información de las tropas del atacante y el defensor
        continentes[ata[0]].getPaisTropas(ata[1]);
        continentes[def[0]].getPaisTropas(def[1]);

        vector <int> atacante(3);
        vector <int> defensor(2);

        //// Lanzar dados para el atacante
        //Dados Amarillos
        cout << endl << AMARILLO << "Dados del atacante: " << endl;
        atacante = this->lanzarDados(3);
      
        // Lanzar dados para el defensor
        //Dados Azules
        cout << endl << AZUL_OSCURO << "Dados del defensor: " << endl;
        defensor = this->lanzarDados(2);

        int totatac = atacante.back();
        int aux = atacante[0];
      // Calcular el total de tropas del atacante excluyendo el dado de menor valor
        for(int h = 0; h < atacante.size(); h++)
        {
            if(atacante[h] < aux)
                aux = atacante[h];
        }
        totatac -= aux;

        int totdefen = defensor.back();

        // Comparar resultados de los dados para determinar el ganador
        // Atacante gana
        if(totatac > totdefen)
        {
            cout << endl << AMARILLO << "Gana el atacante!" << endl;
            continentes[def[0]].restarTropas(def[1], 1);
        }

        // Defensor gana
        else if(totatac < totdefen)
        {
            cout << endl << AZUL_OSCURO << "Gana el defensor!" << endl;
            continentes[ata[0]].restarTropas(ata[1], 1);
        }
          
        // Empate, gana el defensor
        else if(totatac == totdefen)
        {
            cout << endl << AZUL_OSCURO << "El resultado fue un empate, gana el defensor!" << endl;
            continentes[ata[0]].restarTropas(ata[1], 1);
        }

        // Verificar si la partida ha terminado debido a la conquista de un territorio
        if(continentes[def[0]].getTropas(def[1]) == 0)
        {
          // El defensor ha perdido todas sus tropas en el país
            cout << endl << AZUL_OSCURO << "Defensor se quedo sin tropas, atacante gana la batalla" << endl;
            fin = 1;
          // Cambiar la propiedad del país conquistado
            int posD = buscarJugador(continentes[def[0]].obtenerPropietario(def[1]));
            jugadores[posD].eliminarTerritorio(continentes[def[0]].buscarPais(def[1]+1));

            continentes[def[0]].cambiarPropietario(def[1], continentes[ata[0]].obtenerPropietario(ata[1]));

            int posA = buscarJugador(continentes[ata[0]].obtenerPropietario(ata[1]));
            jugadores[posA].agregarTerritorio(continentes[def[0]].buscarPais(def[1]+1));
            cout<<endl<<"Nuevo propietario de "<<continentes[def[0]].buscarPais(def[1]+1)<<": "<<continentes[def[0]].obtenerPropietario(def[1])<<endl;

            int tropas;

            tropas = verificarTropas(continentes[ata[0]].getTropas(ata[1]) - 1, continentes[ata[0]].buscarPais(ata[1]+1));

            continentes[ata[0]].restarTropas(ata[1], tropas);
            continentes[def[0]].sumarTropas(def[1], tropas);
        }
        else if(continentes[ata[0]].getTropas(ata[1]) == 1)
        {
          // El atacante solo tiene una tropa restante, la batalla termina
            cout << endl << AMARILLO << "Al atacante solo le queda una tropa, fin de la batalla" << endl;
            fin = 1;
        }

        continentes[ata[0]].getPaisTropas(ata[1]);
        continentes[def[0]].getPaisTropas(def[1]);

        cout << endl << AMARILLO << "Desea seguir atacando, si = s o no = n" << endl;
        cin>>seguir;
    }
    while(seguir == 's' && fin != 1 ); // while hasta acabar "seguir"
}

// Función para lanzar dados y obtener resultados

vector <int> Partida::lanzarDados(int n)
{
    int total = 0;
    vector <int> resultados;
    srand(time(0)); // Inicializar la semilla para la generación de números aleatorios
    for(int i = 0; i < n; i++)
    {
        resultados.push_back(rand () % 6 + 1); // Generar un número aleatorio entre 1 y 6
        cout << "[[[" << resultados[i] << "]]]"; // Mostrar el resultado del dado
        total += resultados[i]; // Calcular la suma total de los resultados
    }
    resultados.push_back(total); // Agregar la suma total al final del vector de resultados
    return resultados; // Devolver el vector de resultados
}

// Función para ejecutar el turno de un jugador

void Partida::turno(int pos)
{
    ubicarEjercito(pos); // Colocar tropas al inicio del turno
    agregarTropasTerr(pos); // Agregar tropas a los territorios del jugador
    atacar(pos); // Realizar ataques
    fortalecer(pos); // Reforzar territorios al final del turno
}

// Función para fortalecer territorios al final del turno

void Partida::fortalecer(int pos)
{
    int enviar;
    jugadores[pos].mostrarTerritorios(); // Mostrar los territorios del jugador
    cout<<endl<< AMARILLO <<"Digite el nombre del país del cual desea movilizar tropas: ";
    string pais = pedirPais(pos); // Solicitar el país de origen de las tropas a movilizar
    vector <int> i = getPosicionesPais(pais); // Obtener la posición del país en el vector de continentes
    continentes[i[0]].getPaisTropas(i[1]); // Mostrar la cantidad de tropas en el país
    buscarPaisesVecinos(i[0], i[1]);
    cout<<endl<< AMARILLO <<"Digite el nombre del país al cual desea movilizar tropas: ";
    string vecino = pedirPais(pos); // Mostrar los países vecinos del país seleccionado
    vector <int> j = getPosicionesPais(vecino); // Obtener la posición del país vecino en el vector de continentes
    continentes[j[0]].getPaisTropas(j[1]); // Mostrar la cantidad de tropas en el país vecino
    enviar = verificarTropas(continentes[i[0]].getTropas(i[1])-1, // Verificar cantidad de tropas a enviar
continentes[i[0]].buscarPais(i[1]+1)); 
    continentes[j[0]].sumarTropas(j[1], enviar); // Añadir las tropas enviadas al país vecino
    continentes[i[0]].restarTropas(i[1], enviar); // Restar las tropas enviadas del país de origen
    continentes[j[0]].getPaisTropas(j[1]); // Mostrar la cantidad actualizada de tropas en el país vecino
    continentes[i[0]].getPaisTropas(i[1]); // Mostrar la cantidad actualizada de tropas en el país de origen
}

// Función para verificar y limitar la cantidad de tropas a enviar en un refuerzo

int Partida::verificarTropas(int tropas, string pais)
{
    int enviar;
    do
    {
        cout<<endl<< AMARILLO <<"Puede enviar hasta "<<tropas<<" tropas desde "<<pais<<", ¿Cuántas quiere enviar? ";
        cin>>enviar;
        if(enviar > tropas)
            cout<<endl<< AMARILLO <<"Está enviando más tropas de las que puede, inténte de nuevo"<<endl;
    }
    while(enviar > tropas); // Repetir hasta que la cantidad de tropas a enviar sea válida
    return enviar; // Devolver la cantidad de tropas a enviar
}


// Definición de la función auxiliar "separar"

vector<string> separar(string cadena, char separador)
{
    int posInicial = 0;
    int posEncontrada = 0;
    string separado;
    vector<string> resultado;

    while(posEncontrada >= 0)
    {
        posEncontrada = cadena.find(separador, posInicial);
        separado = cadena.substr(posInicial, posEncontrada - posInicial);
        posInicial = posEncontrada + 1;
        resultado.push_back(separado);
    }

    return resultado;
}
