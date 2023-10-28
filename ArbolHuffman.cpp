#include "ArbolHuffman.h"
#include "ComparadorNodos.h"
#include <iostream>
#include <sstream>

#include <queue>

NodoHuffman* ArbolHuffman::construirArbol(const std::unordered_map<char, int>& mapaFrecuencia) {
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, ComparadorNodos> monticuloMinimo;

    // Crear nodos hoja para cada carácter y agregarlos al montículo de prioridad
    for (const auto& entrada : mapaFrecuencia) {
        NodoHuffman* nodo = new NodoHuffman(entrada.first, entrada.second);
        monticuloMinimo.push(nodo);
    }

    // Construir el árbol combinando nodos hasta que quede solo un nodo raíz
    while (monticuloMinimo.size() > 1) {
        NodoHuffman* izquierda = monticuloMinimo.top();
        monticuloMinimo.pop();

        NodoHuffman* derecha = monticuloMinimo.top();
        monticuloMinimo.pop();

        NodoHuffman* nodoCombinado = new NodoHuffman('\0', izquierda->frecuencia + derecha->frecuencia);
        nodoCombinado->izquierda = izquierda;
        nodoCombinado->derecha = derecha;

        monticuloMinimo.push(nodoCombinado);
    }

    return monticuloMinimo.top();
}


std::string ArbolHuffman::codificarMensaje(NodoHuffman* raiz, const std::string& mensaje) {
    std::unordered_map<char, std::string> mapaCodificacion;  // Mapa para almacenar la codificación de cada carácter
    codificarMensajeAux(raiz, "", mapaCodificacion);  // Llamada a la función auxiliar de codificación

   std::string mensajeCodificado;
    // Imprimir la codificación del mensaje
    for (char c : mensaje) {
      
       mensajeCodificado += mapaCodificacion[c] + " ";
    }

  return mensajeCodificado;
}

void ArbolHuffman::codificarMensajeAux(NodoHuffman* nodo, std::string codigo, std::unordered_map<char, std::string>& mapaCodificacion) {
  if (nodo == nullptr) {
      return;
  }

  // Si es un nodo hoja, almacenamos su codificación
  if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
      mapaCodificacion[nodo->dato] = codigo;
  }

  // Llamadas recursivas para el hijo izquierdo y derecho
  codificarMensajeAux(nodo->izquierda, codigo + "0", mapaCodificacion);
  codificarMensajeAux(nodo->derecha, codigo + "1", mapaCodificacion);
}
std::stringstream mensajeDecodificado;

std::string ArbolHuffman::decodificarMensaje(NodoHuffman* raiz, const std::string& mensaje) {

    std::string mensajeDecodificado;
    mensajeDecodificado += decodificarMensajeAux(raiz, mensaje);
    return mensajeDecodificado;
}

char ArbolHuffman::decodificarMensajeAux(NodoHuffman* raiz, const std::string& mensaje) {
    NodoHuffman* nodoActual = raiz;
    
  
    for (char bit : mensaje) {
        if (bit == '0') {
            nodoActual = nodoActual->izquierda;
        } else if (bit == '1') {
            nodoActual = nodoActual->derecha;
        }

        // Solo imprimir si es un nodo hoja
        if (nodoActual->izquierda == nullptr && nodoActual->derecha == nullptr) {
            std::cout << nodoActual->dato;
            nodoActual = raiz;  // Reiniciar para decodificar el próximo carácter
        }
    }

    // Asegurarse de imprimir el último carácter si es un nodo hoja
    if (nodoActual != raiz && nodoActual->izquierda == nullptr && nodoActual->derecha == nullptr) {
        std::cout << nodoActual->dato;
        return nodoActual->dato;
    }

    std::cout << std::endl;
}