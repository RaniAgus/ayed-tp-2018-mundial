#include "../utils/utils.hpp"
#include "listas.hpp"
#include "estructuras.hpp"
#include "arboles.hpp"

using namespace std;

#define CANTEQUIPOS 32
#define CANTPARTIDOS 7

#define imprimirFecha(fecha) \
	(fecha) % 100 << "/" << ((fecha) / 100) % 100 << "/" << (fecha) / 10000

Nodo<Jugador> *partidos[CANTEQUIPOS][CANTPARTIDOS] = {NULL};

void liberarPartidos();
void cargarArchivo(const char *ruta);
Gol leerSiguiente(FILE *f, Gol anterior, int *partido, int *equipo);
void golesPorEquipo();
void goleadores();
Nodo<Jugador> *agregarGolesAJugador(Nodo<Jugador> *jugadores, Jugador jug);
void goleadoresPorFecha();
Nodo<Fecha> *agregarJugadorAFecha(Nodo<Fecha> *fechas, Jugador jugador);

int main()
{
	int menu = 1;
	while (true)
	{
		switch (menu)
		{
		case 1:
			liberarPartidos();
			cargarArchivo("../goles.dat");
			break;
		case 2:
			golesPorEquipo();
			break;
		case 3:
			goleadores();
			break;
		case 4:
			goleadoresPorFecha();
			break;
		case 0:
			liberarPartidos();
			return 0;
		}

		cout << "GOLES DEL MUNDIAL 2018" << endl;
		cout << "1: Volver a cargar los datos" << endl;
		cout << "2: Ver cantidad de goles por equipo" << endl;
		cout << "3: Ver tabla de goleadores" << endl;
		cout << "4: Ver los goleadores de cada fecha" << endl;
		cout << "0: Salir" << endl;
		cin >> menu;
		system("clear");
	}
	return 0;
}

/**
* @NAME liberarPartidos
* @DESC Libera la matriz global de partidos y su contenido
*/
void liberarPartidos()
{
	for (int i = 0; i < CANTEQUIPOS; i++)
	{
		for (int j = 0; j < CANTPARTIDOS; j++)
		{
			liberarLista<Jugador>(partidos[i][j]);
			partidos[i][j] = NULL;
		}
	}
}

/**
* @NAME cargarArchivo
* @DESC Carga la matriz global de partidos a partir de un archivo de estructuras
* Gol, ordenado por equipo y por partido.
*/
void cargarArchivo(const char *ruta)
{
	liberarPartidos();
	int partido = 0, equipo = 0;
	FILE *f = open(ruta, "rb+");
	Gol lectura = read<Gol>(f);
	while (!feof(f))
	{
		if (strcmp(lectura.nombre_jugador, ""))
		{
			Nodo<Jugador> *aux = buscarEnLista<Jugador, Gol>(partidos[equipo][partido], lectura, criterioJugadorGol);
			if (aux == NULL)
			{
				agregarNodo<Jugador>(partidos[equipo][partido], crearJugador(lectura));
			}
			else
			{
				aux->info.goles++;
			}
		}
		lectura = leerSiguiente(f, lectura, &partido, &equipo);
	}
	fclose(f);
	cout << "Datos cargados correctamente." << endl;
}

/**
* @NAME leerSiguiente
* @DESC Lee el siguiente Gol desde el archivo y lo compara con la lectura
* anterior para verificar en dónde ubicarlo
*/
Gol leerSiguiente(FILE *f, Gol anterior, int *partido, int *equipo)
{
	Gol lectura = read<Gol>(f);
	if (anterior.cod_equipo != lectura.cod_equipo)
	{
		*partido = 0;
		(*equipo)++;
	}
	else if (anterior.id_partido != lectura.id_partido)
	{
		(*partido)++;
	}
	return lectura;
}

/**
* @NAME golesPorEquipo
* @DESC A partir de la matriz cargada, obtiene la cantidad de goles que convirtió
* un cada equipo para luego guardarlo en un árbol, para luego imprimir por pantalla 
* el resultado obtenido.
*/
void golesPorEquipo()
{
	Arbol<Equipo> *raiz = NULL;
	for (int equipo = 0; equipo < CANTEQUIPOS; equipo++)
	{
		int goles = 0;
		for (int partido = 0; partido < CANTPARTIDOS; partido++)
		{
			for (Nodo<Jugador> *jug = partidos[equipo][partido]; jug != NULL; jug = jug->sig)
			{
				goles += jug->info.goles;
			}
		}
		insertarEnArbol<Equipo>(raiz, crearEquipo(equipo, goles), criterioEquipo);
	}
	cout << left << setw(15) << "PAIS" << setw(5) << "GOLES" << endl;
	recorrerArbolInorden<Equipo>(raiz, [](Equipo e) -> void {
		cout << left << setw(15) << e.nombre << setw(5) << e.goles << endl;
	});
	liberarArbol(raiz);
}

/**
* @NAME goleadores
* @DESC A partir de la matriz cargada, obtiene una lista de jugadores ordenada
* según la cantidad de goles convertidos (separando los goles en contra), para luego 
* imprimir por pantalla el resultado obtenido.
*/
void goleadores()
{
	Nodo<Jugador> *jugadores = NULL;
	int enContra = 0;
	for (int equipo = 0; equipo < CANTEQUIPOS; equipo++)
	{
		for (int partido = 0; partido < CANTPARTIDOS; partido++)
		{
			for (Nodo<Jugador> *jug = partidos[equipo][partido]; jug != NULL; jug = jug->sig)
			{
				if (!esEnContra(jug->info))
				{
					jugadores = agregarGolesAJugador(jugadores, jug->info);
				}
				else
				{
					enContra++;
				}
			}
		}
	}
	cout << left << setw(20) << "JUGADOR" << setw(5) << "GOLES" << endl;
	for (Nodo<Jugador> *jug = jugadores; jug != NULL; jug = jug->sig)
	{
		cout << left << setw(20) << jug->info.nombre_jugador << setw(3) << jug->info.goles << endl;
	}
	cout << left << setw(20) << "GOLES EN CONTRA" << enContra << endl;
	liberarLista<Jugador>(jugadores);
}

/**
* @NAME agregarGolesAJugador
* @DESC Dado un jugador, lo busca en la lista recibida por parámetro.
* En caso de encontrarlo, le suma la cantidad de goles y vuelve a ordenar la
* lista. Sino, crea uno nuevo y lo agrega a la misma.
*/
Nodo<Jugador> *agregarGolesAJugador(Nodo<Jugador> *jugadores, Jugador jug)
{
	Nodo<Jugador> *jugEnc = buscarEnLista<Jugador, Jugador>(jugadores, jug, criterioJugador);
	if (jugEnc == NULL)
	{
		agregarNodo<Jugador>(jugadores, jug);
	}
	else
	{
		jugEnc->info.goles += jug.goles;
		ordenarLista<Jugador>(jugadores, criterioGoles);
	}

	return jugadores;
}

/**
* @NAME goleadoresPorFecha
* @DESC A partir de la matriz cargada, obtiene una lista de fechas, cada una con
* una lista de los jugadores que convirtieron ese día. Luego, imprime por pantalla 
* el resultado obtenido.
*/
void goleadoresPorFecha()
{
	Nodo<Fecha> *fechas = NULL;

	for (int partido = 0; partido < CANTPARTIDOS; partido++)
	{
		for (int equipo = 0; equipo < CANTEQUIPOS; equipo++)
		{
			for (Nodo<Jugador> *jug = partidos[equipo][partido]; jug != NULL; jug = jug->sig)
			{
				fechas = agregarJugadorAFecha(fechas, jug->info);
			}
		}
	}

	for (Nodo<Fecha> *aux = fechas; aux != NULL; aux = aux->sig)
	{
		cout << "GOLES DEL DIA " << imprimirFecha(aux->info.fecha) << ": " << endl;
		cout << left << setw(20) << "JUGADOR" << setw(5) << "GOLES" << endl;
		for (Nodo<Jugador> *jug = aux->info.jugadores; jug != NULL; jug = jug->sig)
		{
			cout << left << setw(20) << jug->info.nombre_jugador << setw(5) << jug->info.goles << endl;
		}
	}
	liberarLista<Fecha>(fechas);
}

/**
* @NAME agregarJugadorAFecha
* @DESC Dado un jugador, busca la fecha en la que convirtió en la lista recibida 
* por parámetro. En caso de encontrarla, inserta al jugador según la cantidad de
* goles convertidos ese día. Sino, crea una nueva con el jugador en cuestión y la 
* agrega a la misma.
*/
Nodo<Fecha> *agregarJugadorAFecha(Nodo<Fecha> *fechas, Jugador jugador)
{
	Nodo<Fecha> *encontrado = buscarEnLista<Fecha, Jugador>(fechas, jugador, criterioFechaJugador);
	if (encontrado != NULL)
		insertarOrdenado<Jugador>(encontrado->info.jugadores, jugador, criterioGoles);
	else
		insertarOrdenado<Fecha>(fechas, crearFecha(jugador), criterioFecha);

	return fechas;
}