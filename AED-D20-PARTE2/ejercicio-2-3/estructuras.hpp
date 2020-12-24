#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#include "../utils/utils.hpp"

const char *EQUIPOS[] =
    { "Francia"
    , "Croacia"
    , "Belgica"
    , "Inglaterra"
    , "Uruguay"
    , "Brasil"
    , "Suecia"
    , "Rusia"
    , "Colombia"
    , "Espana"
    , "Dinamarca"
    , "Mexico"
    , "Portugal"
    , "Suiza"
    , "Japon"
    , "Argentina"
    , "Senegal"
    , "Iran"
    , "Corea del Sur"
    , "Peru"
    , "Nigeria"
    , "Alemania"
    , "Serbia"
    , "Tunez"
    , "Polonia"
    , "Arabia Saudita"
    , "Marruecos"
    , "Islandia"
    , "Costa Rica"
    , "Australia"
    , "Egipto"
    , "Panama"
    }
;

struct Jugador
{
    char nombre_jugador[20];
    int fecha;
    int goles;
};

struct Fecha
{
    int fecha;
    Nodo<Jugador> *jugadores;
};

struct Equipo
{
    const char *nombre;
    int goles;
};

Jugador crearJugador(Gol g)
{
    Jugador j;
    j.goles = 1;
    j.fecha = g.fecha;
    strcpy(j.nombre_jugador, g.nombre_jugador);
    return j;
}

Fecha crearFecha(Jugador j)
{
    Fecha f;
    f.fecha = j.fecha;
    Nodo<Jugador> *nuevaSub = new Nodo<Jugador>();
    nuevaSub->info = j;
    nuevaSub->sig = NULL;
    f.jugadores = nuevaSub;
    return f;
}

Equipo crearEquipo(int cod_equipo, int goles)
{
    Equipo e;
    e.nombre = EQUIPOS[cod_equipo];
    e.goles = goles;
    return e;
}

int criterioJugadorGol(Jugador j, Gol g)
{
    return strcmp(j.nombre_jugador, g.nombre_jugador) == 0 ? 0 : -1;
}

int criterioJugador(Jugador j1, Jugador j2)
{
    return strcmp(j1.nombre_jugador, j2.nombre_jugador) == 0 ? 0 : -1;
}

int criterioGoles(Jugador j1, Jugador j2)
{
    return j2.goles - j1.goles;
}

int criterioFechaJugador(Fecha f1, Jugador j2)
{
    return f1.fecha - j2.fecha;
}

int criterioFecha(Fecha f1, Fecha f2)
{
    return f1.fecha - f2.fecha;
}

int criterioEquipo(Equipo e1, Equipo e2)
{
    return e2.goles - e1.goles;
}

bool esEnContra(Jugador j)
{
    return strncmp(j.nombre_jugador, "e.c.", 4) == 0;
}

#endif