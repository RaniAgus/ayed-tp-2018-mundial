#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct Gol
{
    int id_gol;
    int cod_equipo;
    int fecha;
    char nombre_jugador[20];
    int id_partido;
};

FILE *open(string path, const char *modo)
{
    FILE *f = fopen(path.c_str(), modo);
    if (f == NULL)
    {
        cout << "ERROR: No se pudo abrir el archivo " << path << endl;
        exit(-1);
    }

    return f;
}

template <typename T>
void write(FILE *f, T v)
{
    fwrite(&v, sizeof(T), 1, f);
    return;
}

template <typename T>
T read(FILE *f)
{
    T buff;
    fread(&buff, sizeof(T), 1, f);
    return buff;
}

#endif