/*
*********************************************************************************************
Autores: Daniel Alejandro Terán- Juan Felipe Morales Espitia     PUJ
Fecha: 13/08/2023
Tema: Entrega 00 del Proyecto RISK Estructura de Datos
********************************************************************************************
*/



#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>

#define AMARILLO     "\033[33m"
#define ROJO     "\033[31m"
#define BLANCO       "\033[37m"
#define AZUL_OSCURO  "\033[34m"

using namespace std;

// Declaración de funciones
void pantalla_inicio();
void ayuda();
bool inicializar(bool);
bool inicializarArchivo(bool, string);
void turno(bool, string);
void conquista_barata(bool);
void guardar(bool, string, fstream&);
void guardar_comprimido(bool, string, fstream&);
void costo_conquista(bool);
string obtenerNombreArchivo(string);
int obtenerId(string);

int main() {
    // Declaración de variables
    int seleccion;
    string comando, separado;
    bool inicializado = false;
    fstream txt, bin;
    pantalla_inicio();

    // Bucle principal
    do {
        cout << endl << "$";


        getline(cin, comando);

        // Evaluación de comandos
        if (comando == "inicializar") {
            inicializado = inicializar(inicializado);
        }
        else if (comando.find("inicializar") == 0) {
            inicializado = inicializarArchivo(inicializado, comando);
        }
        else if (comando == "ayuda") {
            ayuda();
        }
        else if (comando == "conquista_mas_barata") {
            conquista_barata(inicializado);
        }
        else if (comando.find("turno") == 0) {
            turno(inicializado, comando);
        }
        else if (comando.find("guardar") == 0) {
            guardar(inicializado, comando, txt);
        }
        else if (comando.find("guarda_comprimido") == 0) {
            guardar_comprimido(inicializado, comando, bin);
        }
        else if (comando == "costo_conquista") {
            costo_conquista(inicializado);
        }
        else if (comando == "salir") {
            return 0;
        }
        else if(!inicializado){
            cout << endl << "Esta partida no ha sido inicializada correctamente." << endl;
        }
        else{
            cout << endl << "Comando no valido" <<endl;
        }
    } while (comando != "salir");
}

void pantalla_inicio(){
    cout<< setw(100) <<"+--------------------------------------------------------------------+" << endl;
    cout<< setw(100) << "|                            BIENVENIDO A:                           |" << endl;
    cout<< setw(100) << "+--------------------------------------------------------------------+" << endl;
    cout<< ROJO<< setw(100) << "RRRRRRRRRRRRRRRRR   IIIIIIIIII   SSSSSSSSSSSSSSS KKKKKKKKK    KKKKKKK" <<endl;
    cout<< setw(100) << "R::::::::::::::::R  I::::::::I SS:::::::::::::::SK:::::::K    K:::::K" << endl;
    cout<< setw(100) << "R::::::RRRRRR:::::R I::::::::IS:::::SSSSSS::::::SK:::::::K    K:::::K" << endl;
    cout<< setw(100) << "RR:::::R     R:::::RII::::::IIS:::::S     SSSSSSSK:::::::K   K::::::K" << endl;
    cout<< setw(100) << "  R::::R     R:::::R  I::::I  S:::::S            KK::::::K  K:::::KKK" << endl;
    cout<< setw(100) << "  R::::R     R:::::R  I::::I  S:::::S              K:::::K K:::::K   " << endl;
    cout<< setw(100) << "  R::::RRRRRR:::::R   I::::I   S::::SSSS           K::::::K:::::K    " << endl;
    cout<< setw(100) << "  R:::::::::::::RR    I::::I    SS::::::SSSSS      K:::::::::::K     " << endl;
    cout<< setw(100) << "  R::::RRRRRR:::::R   I::::I      SSS::::::::SS    K:::::::::::K     " << endl;
    cout<< setw(100) << "  R::::R     R:::::R  I::::I         SSSSSS::::S   K::::::K:::::K    " << endl;
    cout<< setw(100) << "  R::::R     R:::::R  I::::I              S:::::S  K:::::K K:::::K   " << endl;
    cout<< setw(100) << "  R::::R     R:::::R  I::::I              S:::::SKK::::::K  K:::::KKK" << endl;
    cout<< setw(100) << "RR:::::R     R:::::RII::::::IISSSSSSS     S:::::SK:::::::K   K::::::K" << endl;
    cout<< setw(100) << "R::::::R     R:::::RI::::::::IS::::::SSSSSS:::::SK:::::::K    K:::::K" << endl;
    cout<< setw(100) << "R::::::R     R:::::RI::::::::IS:::::::::::::::SS K:::::::K    K:::::K" << endl;
    cout<< setw(100) << "RRRRRRRR     RRRRRRRIIIIIIIIII SSSSSSSSSSSSSSS   KKKKKKKKK    KKKKKKK" << BLANCO << endl;
    cout<< setw(100) << "+--------------------------------------------------------------------+" << endl;
    cout<< setw(100) << "|               Digite el comando 'ayuda' (sin comillas)             |" << endl;
    cout<< setw(100) << "|      para obtener información de los comandos disponibles.        |" << endl;
    cout<< setw(100) << "+--------------------------------------------------------------------+" << endl;
}

// Mostrar la ayuda y descripciones de los comandos
void ayuda() {
    cout << setw(55)<< endl << AMARILLO << " » CONFIGURACIÓN DEL JUEGO « " << endl;
    cout << endl << AZUL_OSCURO << "*** inicializar ***\n" << BLANCO << " ☺ Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas" << endl;
    cout << endl << AZUL_OSCURO << "*** turno <id_jugador> *** \n" << BLANCO << " ☺ Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)." << endl;
    cout << setw(55)<< endl << AMARILLO << " » ALMACENAMIENTO DE PARTIDAS « " << endl;
    cout << endl << AZUL_OSCURO << "*** salir *** \n" << BLANCO<< " ☺ Termina la ejecución de la aplicación." << endl;
    cout << endl << AZUL_OSCURO << "*** guardar <nombre_archivo> *** \n" << BLANCO << " ☺ El estado actual del juego es guardado en un archivo de texto." << endl;
    cout << endl << AZUL_OSCURO << "*** guardar_comprimido <nombre_archivo> *** \n" << BLANCO << " ☺ El estado actual del juego es guardado en un archivo binario." << endl;
    cout << endl << AZUL_OSCURO << "*** inicializar <nombre_archivo> *** \n" << BLANCO << " ☺ Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>." << endl;
    cout << setw(55)<< endl << AMARILLO << " » ESTRATEGIAS DE JUEGO « " << endl;
    cout << endl << AZUL_OSCURO << "*** costo_conquista <territorio> *** \n" << BLANCO << " ☺ Se calcula el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario. " << endl;
    cout << endl << AZUL_OSCURO << "*** conquista_mas_barata *** \n" << BLANCO << " ☺ De todos los territorios posibles, calcular aquel que pueda implicar un menor número de unidades de ejército perdidas." << endl;
}

// Función para inicializar el juego
bool inicializar(bool b) {
    if (b) {
        cout << endl << "El juego ya ha sido inicializado." << endl;
    } else {
        b = true;
        cout << endl << "El juego se ha inicializado correctamente." << endl;
    }
    return b;
}
// Función para inicializar el juego desde un archivo
bool inicializarArchivo(bool b, string s) {
    if (b) {
        cout << endl << "El juego ya ha sido inicializado." << endl;
    } else {
        b = true;
        string nombreArchivo = obtenerNombreArchivo(s);
        cout << endl << "'" << nombreArchivo << "'" << " no contiene información válida para inicializar el juego." << endl;
    }
    return b;
}

// Función para procesar el turno de un jugador
void turno(bool b, string s) {
    if (b) {
        int id = obtenerId(s);
        cout << endl << "El turno del jugador " << id << " ha terminado." << endl;
    } else {
        cout << endl << "Esta partida no ha sido inicializada correctamente." << endl;
    }
}

// Función para simular una conquista barata
void conquista_barata(bool juego) {
    if (juego == false) {
        cout << endl << "El juego no ha sido inicializado correctamente" << endl;
    } else {
        cout << endl << "Jugador no válido" << endl;
    }
}

// Función para calcular el costo de una conquista
void costo_conquista(bool b) {
    if (b) {
        cout << endl << "Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército." << endl;
    } else {
        cout << endl << "Esta partida no ha sido inicializada correctamente." << endl;
    }
}
// Función para guardar el estado del juego en un archivo de texto
void guardar(bool b, string s, fstream& txt) {
    if (b) {
        string nombreArchivo = obtenerNombreArchivo(s) + ".txt";
        txt.open(nombreArchivo, ios::out);
        if (!txt) {
            cout << endl << "La partida no ha sido guardada correctamente." << endl;
        } else {
            cout << endl << "La partida ha sido guardada correctamente en '" << nombreArchivo << "'" << endl;
        }
        txt.close();
    } else {
        cout << endl << "Esta partida no ha sido inicializada correctamente." << endl;
    }
}

// Función para guardar el estado del juego en un archivo binario
void guardar_comprimido(bool b, string s, fstream& bin) {
    if (b) {
        string nombreArchivo = obtenerNombreArchivo(s) + ".dat";
        bin.open(nombreArchivo, ios::binary | ios::out);
        if (!bin) {
            cout << endl << "La partida no ha sido codificada ni guardada correctamente." << endl;
        } else {
            cout << endl << "La partida ha sido codificada y guardada correctamente en '" << nombreArchivo << "'" << endl;
            bin.close();
        }
    } else {
        cout << endl << "Esta partida no ha sido inicializada correctamente." << endl;
    }
}

// Función para obtener el ID de jugador desde el comando
int obtenerId(string x) {
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    int id = stoi(aux);
    return id;
}

// Función para obtener el nombre de archivo desde el comando
string obtenerNombreArchivo(string x) {
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    return aux;
}






