#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "NodoHuffman.h"
#include <unordered_map>
#include <string>

class ArbolHuffman {
public:
    NodoHuffman* construirArbol(const std::unordered_map<char, int>& mapaFrecuencia);
    std::string codificarMensaje(NodoHuffman* raiz, const std::string& mensaje);
    void decodificarMensaje(NodoHuffman* raiz, const std::string& mensajeCodificado);

private:
    void codificarMensajeAux(NodoHuffman* nodo, std::string codigo, std::unordered_map<char, std::string>& mapaCodificacion);
};

#endif // ARBOLHUFFMAN_H
