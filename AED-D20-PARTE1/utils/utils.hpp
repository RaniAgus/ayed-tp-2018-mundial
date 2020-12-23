#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

#define GRUPOS 8
#define EQUIPOSPORGRUPO 4
#define CONFEDERACIONES 6

using namespace std;

struct Seleccion {
    int bolillero;
    char nombreDeEquipo[15];
    char confederacion[10];
    
};

struct Equipo {
    int grupo;
    char nombreDeEquipo[15];
    char confederacion[10];
};

template<typename T> void write(FILE* f, T v)
{
    fwrite(&v,sizeof(T),1,f);
    return;
}

template<typename T> T read(FILE* f)
{
    T buff;
    fread(&buff,sizeof(T),1,f);
    return buff;
}

FILE* openGrupo(char grupo, const char* modo) {
    string pathInicial = "../Grupo ";
	string formato = ".dat";
	string archivo =  pathInicial + grupo + formato;
    return fopen(archivo.c_str(), modo);
}

#endif