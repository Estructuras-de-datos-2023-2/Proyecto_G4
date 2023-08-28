/*
*********************************************************************************************
Autores: Daniel Alejandro Terán- Juan Felipe Morales Espitia     PUJ
Fecha: 27/08/2023
Tema: Entrega 01 del Proyecto RISK Estructura de Datos
********************************************************************************************
*/


//Librerias

#include <iostream>
#include <locale>
#include <string.h>
#include <fstream>
#include <list>
#include <queue>
#include "Partida.h"
#define AMARILLO     "\033[33m"
#define ROJO     "\033[31m"
#define BLANCO       "\033[37m"
#define AZUL_OSCURO  "\033[34m"


using namespace std;

//Declaración de funciones

void comandos();
void pantalla_inicio();
void ayuda();
bool inicializar(bool);
void leerJugadores();
bool inicializarArchivo(bool,string);
void turno(bool,string);
void conquista_barata(bool);
void guardar(bool,string,fstream&);
void guardar_comprimido(bool,string,fstream&);
void costo_conquista(bool);
void llenarColores(list<string>*);
string asignarColor(int, list<string> *);
string getNombreArchivo(string);
string getId(string);
int asignarInfanteria(int);
queue <Jugador> pedirColaJugadores();

// Variables globales

int cantJugadores = 0;

queue <Jugador> colaJugadores;

Partida * partida = new Partida();

//Main
int main()
{
    setlocale(LC_ALL, "");
    comandos();
}

// Función para gestionar los comandos del juego

void comandos()
{
    pantalla_inicio();
    int seleccion;
    string comando, separado;
    bool inicializado = false;
    fstream txt, bin;
    do
    {

        cout<<endl<<"$";
        getline(cin, comando, '\n');

        if(comando=="inicializar")
            inicializado = inicializar(inicializado);
        else if(comando.find("inicializar")==0)
            inicializado = inicializarArchivo(inicializado,comando);
        else if(comando=="ayuda")
            ayuda();
        else if(comando=="conquista_mas_barata")
            conquista_barata(inicializado);
        else if(comando.find("turno")==0)
            turno(inicializado, comando);
        else if(comando.find("guardar")==0)
            guardar(inicializado, comando, txt);
        else if(comando.find("guarda_comprimido")==0)
            guardar_comprimido(inicializado, comando, bin);
        else if(comando=="costo_conquista")
            costo_conquista(inicializado);
        else if(comando=="salir")
            cout<<endl<< AMARILLO <<"Cerrando el juego...";
        else
            cout<<endl<< AMARILLO <<"Se ingresó un comando erróneo."<<endl;
    }
    while(comando != "salir");
}

void pantalla_inicio()
{
    cout<<"+--------------------------------------------------------------------+" << endl;
    cout << "|                            BIENVENIDO A:                           |" << endl;
    cout << "+--------------------------------------------------------------------+" << endl;
    cout<< ROJO<<  << "RRRRRRRRRRRRRRRRR   IIIIIIIIII   SSSSSSSSSSSSSSS KKKKKKKKK    KKKKKKK" <<endl;
    cout  << "R::::::::::::::::R  I::::::::I SS:::::::::::::::SK:::::::K    K:::::K" << endl;
    cout  << "R::::::RRRRRR:::::R I::::::::IS:::::SSSSSS::::::SK:::::::K    K:::::K" << endl;
    cout  << "RR:::::R     R:::::RII::::::IIS:::::S     SSSSSSSK:::::::K   K::::::K" << endl;
    cout  << "  R::::R     R:::::R  I::::I  S:::::S            KK::::::K  K:::::KKK" << endl;
    cout  << "  R::::R     R:::::R  I::::I  S:::::S              K:::::K K:::::K   " << endl;
    cout  << "  R::::RRRRRR:::::R   I::::I   S::::SSSS           K::::::K:::::K    " << endl;
    cout  << "  R:::::::::::::RR    I::::I    SS::::::SSSSS      K:::::::::::K     " << endl;
    cout  << "  R::::RRRRRR:::::R   I::::I      SSS::::::::SS    K:::::::::::K     " << endl;
    cout  << "  R::::R     R:::::R  I::::I         SSSSSS::::S   K::::::K:::::K    " << endl;
    cout  << "  R::::R     R:::::R  I::::I              S:::::S  K:::::K K:::::K   " << endl;
    cout  << "  R::::R     R:::::R  I::::I              S:::::SKK::::::K  K:::::KKK" << endl;
    cout  << "RR:::::R     R:::::RII::::::IISSSSSSS     S:::::SK:::::::K   K::::::K" << endl;
    cout  << "R::::::R     R:::::RI::::::::IS::::::SSSSSS:::::SK:::::::K    K:::::K" << endl;
    cout  << "R::::::R     R:::::RI::::::::IS:::::::::::::::SS K:::::::K    K:::::K" << endl;
    cout  << "RRRRRRRR     RRRRRRRIIIIIIIIII SSSSSSSSSSSSSSS   KKKKKKKKK    KKKKKKK" << BLANCO << endl;
    cout  << "+--------------------------------------------------------------------+" << endl;
    cout  << "|               Digite el comando 'ayuda' (sin comillas)             |" << endl;
    cout  << "|      para obtener información de los comandos disponibles.        |" << endl;
    cout << "+--------------------------------------------------------------------+" << endl;
}

// Función para mostrar la ayuda y descripciones de los comandos

void ayuda()
{
     cout << endl << AMARILLO << " » CONFIGURACIÓN DEL JUEGO « " << endl;
    cout << endl << AZUL_OSCURO << "*** inicializar ***\n" << BLANCO << " ☺ Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas" << endl;
    cout << endl << AZUL_OSCURO << "*** turno <id_jugador> *** \n" << BLANCO << " ☺ Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)." << endl;
    cout << endl << AMARILLO << " » ALMACENAMIENTO DE PARTIDAS « " << endl;
    cout << endl << AZUL_OSCURO << "*** salir *** \n" << BLANCO<< " ☺ Termina la ejecución de la aplicación." << endl;
    cout << endl << AZUL_OSCURO << "*** guardar <nombre_archivo> *** \n" << BLANCO << " ☺ El estado actual del juego es guardado en un archivo de texto." << endl;
    cout << endl << AZUL_OSCURO << "*** guardar_comprimido <nombre_archivo> *** \n" << BLANCO << " ☺ El estado actual del juego es guardado en un archivo binario." << endl;
    cout << endl << AZUL_OSCURO << "*** inicializar <nombre_archivo> *** \n" << BLANCO << " ☺ Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>." << endl;
    cout << endl << AMARILLO << " » ESTRATEGIAS DE JUEGO « " << endl;
    cout << endl << AZUL_OSCURO << "*** costo_conquista <territorio> *** \n" << BLANCO << " ☺ Se calcula el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario. " << endl;
    cout << endl << AZUL_OSCURO << "*** conquista_mas_barata *** \n" << BLANCO << " ☺ De todos los territorios posibles, calcular aquel que pueda implicar un menor número de unidades de ejército perdidas." << endl;
}

// Función para inicializar el juego

bool inicializar(bool b)
{
    if(b)
        cout<<endl << AMARILLO<< "***El juego ya ha sido inicializado.***"<< endl;
    else
    {
        b = true;
        leerJugadores();
        partida->asignarTerritorios();
        cout<<endl <<AMARILLO<< "***El juego se ha inicializado correctamente.***"<< endl;
        colaJugadores = pedirColaJugadores();
    }
    return b;
}

// Función para leer jugadores y asignarles territorios

void leerJugadores()
{
    string nombre, color;
    list <string> * colores = new list<string> ();
    llenarColores(colores);
    do
    {
        cout<<endl<<AMARILLO<< "***Ingrese la cantidad de jugadores (3-6): ";
        cin>>cantJugadores;
        if(cantJugadores<3 || cantJugadores>6)
        {
            cout <<endl << AMARILLO<<"Ingresó un valor inválido, inténtelo de nuevo"<< endl;
        }
    }
    while(cantJugadores<3 || cantJugadores>6);
    for(int i=0; i<cantJugadores; i++)
    {
        cout<< endl << AZUL_OSCURO<< "Ingrese el nombre o identificador del jugador "<< i+1<<": ";
        cin>>nombre;
        color = asignarColor(cantJugadores, colores);
        int tropas = asignarInfanteria(cantJugadores);
        cout<<endl<< AZUL_OSCURO<<"TROPAS PARA ESTE JUEGO: "<<tropas<<endl;
        partida -> agregarJugador(nombre, color, tropas);
    }
}

// Función para asignar infantería según cantidad de jugadores

int asignarInfanteria(int cantJugadores)
{
    if(cantJugadores == 3)
        return 35;

    else if(cantJugadores == 4)
        return 30;

    else if(cantJugadores == 5)
        return 25;

    else if(cantJugadores == 6)
        return 20;

    else
        return 0;
}

// Función para llenar lista de colores disponibles

void llenarColores(list <string> *colores)
{
    colores->push_back("amarillo");
    colores->push_back("azul");
    colores->push_back("rojo");
    colores->push_back("verde");
    colores->push_back("gris");
    colores->push_back("negro");
}

// Función para asignar color a un jugador

string asignarColor(int cantJug, list<string> * colores)
{
    string col;
    bool encontrado = false;
    cout << endl << AMARILLO<< "Los colores disponibles son (minúsculas): " <<endl;
    for(string color : *colores)
        cout << endl << color;
    do
    {
        cout << endl << AZUL_OSCURO<< "\nEscoga el color: ";
        cin >> col;
        for(string color : *colores)
        {
            if(col == color)
                encontrado = true;
        }
        if(!encontrado)
            cout << endl << AZUL_OSCURO<< "Ingresó un color erróneo, inténtelo de nuevo";
    }
    while(!encontrado);
    auto it = colores->begin();
    while (it != colores->end())
    {
        if (*it == col)
        {
            it = colores->erase(it); // Elimina el color de la lista
            return col; // Retorna el color elegido
        }
        else
            ++it;
    }
    return col;
}

// Función para inicializar archivo

bool inicializarArchivo(bool b, string s)
{
    if(b)
    {
        cout<<endl<< AMARILLO<<  "El juego ya ha sido inicializado."<<endl;
    }
    else
    {
        b = true;
        string nombreArchivo = getNombreArchivo(s);
        cout<<endl<< "'"<<nombreArchivo<<"'"<<" no contiene información válida para inicializar el juego."<< endl;
    }
    return b;
}

// Función para pedirCola

queue <Jugador> pedirColaJugadores()
{
    queue <Jugador> cola;
    vector <Jugador> jugadores = partida->getJugadores();
    for(Jugador j : jugadores)
        cola.push(j);
    return cola;
}

void turno(bool b, string s)
{
    if(b)
    {
        string id = getId(s);
        int pos = partida->buscarJugador(id);
        Jugador proxJugador = colaJugadores.front();

        if(pos < 0)
            cout<<endl<< AZUL_OSCURO<<"No existe este jugador"<<endl;
        else if(proxJugador.getNombre() != id)
            cout<<endl<< AZUL_OSCURO<<"No es el turno de este jugador"<<endl;
        else
        {
            partida->turno(pos);
            colaJugadores.pop();
            colaJugadores.push(proxJugador);
        }
        cout<<endl << AZUL_OSCURO<< "El turno del jugador " << id << " ha terminado."<< endl;
    }
    else
        cout<<endl << AZUL_OSCURO<< "Esta partida no ha sido inicializada correctamente." << endl;
}

// Función para obtener la conquista_barata

void conquista_barata(bool juego)
{
    if(juego==false)
        cout<<endl<< AMARILLO<< "El juego no ha sido inicializado correctamente" << endl;
    else
        cout<<endl << AZUL_OSCURO<<  "Jugador no válido"<< endl;
}

// Función para obtener el costo de la conquista

void costo_conquista(bool b)
{
    if(b)
    {
        cout<<endl<< AZUL_OSCURO<<  "Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar<n>unidades de ejército."<< endl;
    }
    else
    {
        cout<<endl<< AMARILLO<< "Esta partida no ha sido inicializada correctamente."<< endl;
    }
}

// Función para guardar el archivo .txt

void guardar(bool b, string s, fstream& txt)
{
    if(b)
    {
        string nombreArchivo = getNombreArchivo(s) + ".txt";
        txt.open(nombreArchivo, ios::out);
        if(!txt)
        {
            cout<<endl<< AMARILLO<< "La partida no ha sido guardada correctamente." << endl;
        }
        else
        {
            cout<<endl << AMARILLO<<"La partida ha sido guardada correctamente en '" << nombreArchivo << "'"<< endl;
        }
        txt.close();
    }
    else
    {
        cout<<endl<< AMARILLO<<"Esta partida no ha sido inicializada correctamente."<< endl;
    }
}

// Función para guardar_comprimido el .txt

void guardar_comprimido(bool b, string s, fstream& bin)
{
    if(b)
    {
        string nombreArchivo = getNombreArchivo(s) + ".dat";
        bin.open(nombreArchivo,ios::binary |ios::out);
        if(!bin)
        {
            cout<<endl<< AMARILLO<<"La partida no ha sido codificada ni guardada correctamente."<<endl;
        }
        else
        {
            cout<<endl<< AMARILLO<<"La partida ha sido codificada y guardada correctamente en '" << nombreArchivo << "'"<< endl;
            bin.close();
        }
    }
    else
    {
        cout<<endl<< AMARILLO<<"Esta partida no ha sido inicializada correctamente."<<endl;
    }
}

// Función para obtener el ID del jugador desde el comando

string getId(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    string id = aux;
    return id;
}

// Función para obtener el nombre de archivo desde el comando

string getNombreArchivo(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    return aux;
}
