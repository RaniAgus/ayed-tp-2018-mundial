#ifndef LISTAS_H_
#define LISTAS_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

template <typename T>
struct Nodo
{
    T info;
    Nodo<T> *sig;
};

template <typename T>
void agregarNodo(Nodo<T> *&p, T v)
{
    Nodo<T> *nuevo = new Nodo<T>();
    nuevo->info = v;
    nuevo->sig = NULL;
    if (p == NULL)
    {
        p = nuevo;
    }
    else
    {
        Nodo<T> *aux = p;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

template <typename T>
T eliminarPrimerNodo(Nodo<T> *&p)
{
    T ret = p->info;
    Nodo<T> *aux = p;
    p = p->sig;
    delete aux;
    return ret;
}

template <typename T>
Nodo<T> *insertarOrdenado(Nodo<T> *&p, T v, int (*criterio)(T, T))
{
    Nodo<T> *nuevo = new Nodo<T>();
    nuevo->info = v;
    nuevo->sig = NULL;
    Nodo<T> *ant = NULL;
    Nodo<T> *aux = p;
    while (aux != NULL && criterio(aux->info, v) <= 0)
    {
        ant = aux;
        aux = aux->sig;
    }
    if (ant == NULL)
    {
        p = nuevo;
    }
    else
    {
        ant->sig = nuevo;
    }
    nuevo->sig = aux;
    return nuevo;
}

template <typename T, typename K>
Nodo<T> *buscarEnLista(Nodo<T> *p, K v, int (*criterio)(T, K))
{
    Nodo<T> *aux = p;
    while (aux != NULL && criterio(aux->info, v) != 0)
    {
        aux = aux->sig;
    }
    return aux;
}

template <typename T>
void ordenarLista(Nodo<T> *&p, int (*criterio)(T, T))
{
    Nodo<T> *q = NULL;
    while (p != NULL)
    {
        T v = eliminarPrimerNodo<T>(p);
        insertarOrdenado<T>(q, v, criterio);
    }
    p = q;
}

template <typename T>
void liberarLista(Nodo<T> *&p)
{
    while (p != NULL)
    {
        eliminarPrimerNodo(p);
    }
}

#endif