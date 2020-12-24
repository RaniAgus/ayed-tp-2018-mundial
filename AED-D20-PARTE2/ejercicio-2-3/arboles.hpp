#ifndef ARBOLES_H_
#define ARBOLES_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

template <typename T>
struct Arbol
{
    T dato;
    Arbol<T> *izq;
    Arbol<T> *der;
};

template <typename T>
void insertarEnArbol(Arbol<T> *&nodo, T v, int (*criterio)(T, T))
{
    if (nodo == NULL)
    {
        nodo = new Arbol<T>();
        nodo->dato = v;
        nodo->izq = NULL;
        nodo->der = NULL;
    }
    else
    {
        if (criterio(nodo->dato, v) > 0)
        {
            insertarEnArbol(nodo->izq, v, criterio);
        }
        else
        {
            insertarEnArbol(nodo->der, v, criterio);
        }
    }
}

template <typename T>
void recorrerArbolInorden(Arbol<Equipo> *nodo, void (*closure)(T))
{
    if (nodo != NULL)
    {
        recorrerArbolInorden(nodo->izq, closure);
        closure(nodo->dato);
        recorrerArbolInorden(nodo->der, closure);
    }
}

template <typename T>
void liberarArbol(Arbol<T> *nodo)
{
    if (nodo->izq != NULL)
    {
        liberarArbol(nodo->izq);
    }
    if (nodo->der != NULL)
    {
        liberarArbol(nodo->der);
    }
    delete nodo;
}

#endif