#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

const int CANTEQUIPOS = 32;
const int CANTPARTIDOS = 7;
const string EQUIPOS [] = {
	"Francia",
	"Croacia",
	"Belgica",
	"Inglaterra",
	"Uruguay",
	"Brasil",
	"Suecia",
	"Rusia",
	"Colombia",
	"Espana",
	"Dinamarca",
	"Mexico",
	"Portugal",
	"Suiza",
	"Japon",
	"Argentina",
	"Senegal",
	"Iran",
	"Corea del Sur",
	"Peru",
	"Nigeria",
	"Alemania",
	"Serbia",
	"Tunez",
	"Polonia",
	"Arabia Saudita",
	"Marruecos",
	"Islandia",
	"Costa Rica",
	"Australia",
	"Egipto",
	"Panama"
};

template<typename T>
struct Nodo {
	T info;
	Nodo<T>* sig;
};

template<typename T>
struct Arbol {
	T dato;
	Arbol<T> *izq;
	Arbol<T> *der;
};

struct Gol{
	int id_gol;
	int cod_equipo;
	int fecha;
	char nombre_jugador[20];
	int id_partido;

};

struct Jugador{
	char nombre_jugador[20];
	int fecha;
	int goles;
};

struct Fecha{
	int fecha;
	Nodo<Jugador>* sub;
};

struct Equipo{
	int cod_equipo;
	int goles;
};

Gol crearGol(int id_gol, int cod_equipo, int fecha, char nombre_jugador[], int id_partido){
	Gol a;
	a.id_gol = id_gol;
	a.cod_equipo = cod_equipo;
	a.fecha = fecha;
	strcpy(a.nombre_jugador, nombre_jugador);
	a.id_partido = id_partido;
	return a;
}

Jugador crearJugador(Gol g){
	Jugador j;
	j.goles = 1;
	j.fecha = g.fecha;
	strcpy(j.nombre_jugador, g.nombre_jugador);
	return j;
}

Fecha crearFecha(Jugador j){
	Fecha f;
	f.fecha = j.fecha;
	Nodo<Jugador>* nuevaSub = new Nodo<Jugador>();
	nuevaSub->info = j;
	nuevaSub->sig = NULL;
	f.sub = nuevaSub;
	return f;
}

Equipo crearEquipo(int cod_equipo, int goles){
	Equipo e;
	e.cod_equipo = cod_equipo;
	e.goles = goles;
	return e;
}

template<typename T> T read(FILE* f)
{
    T buff;
    fread(&buff,sizeof(T),1,f);
    return buff;
}

int criterioJugadorGol(Jugador j, Gol g){
	return strcmp(j.nombre_jugador,g.nombre_jugador)==0?0:-1;
}

int criterioJugador(Jugador j1, Jugador j2){
	return strcmp(j1.nombre_jugador,j2.nombre_jugador)==0?0:-1;
}

int criterioGoles(Jugador j1, Jugador j2){
	return j2.goles-j1.goles;
}

int criterioFecha(Fecha f1, Fecha f2){
	return f1.fecha-f2.fecha;
}

template <typename T>
void agregarNodo(Nodo<T>*& p, T v) {
	Nodo<T>* nuevo = new Nodo<T>();
	nuevo->info = v;
	nuevo->sig = NULL;
	if( p==NULL ) {
		p = nuevo;
	} else {
		Nodo<T>* aux = p;
		while(aux->sig!=NULL ) {
			aux = aux->sig;
		}
		aux->sig = nuevo;
	}
}

template <typename T>
T eliminarPrimerNodo(Nodo<T>*& p) {
	T ret = p->info;
	Nodo<T>* aux = p;
	p = p->sig;
	delete aux;
	return ret;
}

template <typename T>
Nodo<T>* insertarOrdenado(Nodo<T>*& p, T v, int (*criterio)(T,T)) {
	Nodo<T>* nuevo = new Nodo<T>();
	nuevo->info = v;
	nuevo->sig = NULL;
	Nodo<T>* ant = NULL;
	Nodo<T>* aux = p;
	while( aux!=NULL && criterio(aux->info,v)<=0 ) {
		ant = aux;
		aux = aux->sig;
	}
	if( ant==NULL ) {
		p = nuevo;
	} else {
		ant->sig = nuevo;
	}
	nuevo->sig = aux;
	return nuevo;
}

template <typename T, typename K>
Nodo<T>* buscar(Nodo<T>* p, K v, int (*criterio)(T,K)) {
	Nodo<T>* aux = p;
	while( aux!=NULL && criterio(aux->info,v)!=0 ) {
		aux=aux->sig;
	}
	return aux;
}

template <typename T>
void ordenar(Nodo<T>*& p, int (*criterio)(T,T)) {
	Nodo<T>* q = NULL;
	while(p!=NULL) {
		T v = eliminarPrimerNodo<T>(p);
		insertarOrdenado<T>(q,v,criterio);
	}
	p = q;
}

template <typename T>
void liberar(Nodo<T>*& p) {
	Nodo<T>* aux;
	while( p!=NULL ) {
		aux = p;
		p = p->sig;
		delete aux;
	}
}

bool esEnContra(Jugador j){
	return strncmp(j.nombre_jugador,"e.c.",4)==0? true:false;
}

void cargarArchivo(Nodo<Jugador>* partidos[][CANTPARTIDOS], const char* ruta){
	for(int i=0; i<CANTEQUIPOS;i++){
		for(int j=0; j<CANTPARTIDOS; j++){
			liberar<Jugador>(partidos[i][j]);
		}
	}
	int partido = 0;
	int equipo = 0;
	Nodo<Jugador>* aux = NULL;
	FILE* f = fopen(ruta, "rb+");
	Gol lectura = read<Gol>(f);
	Gol ant;
	while(!feof(f)){
		if(strcmp(lectura.nombre_jugador,"NULL")!=0){
			aux = buscar<Jugador,Gol>(partidos[equipo][partido],lectura,criterioJugadorGol);
			if(aux==NULL){
				agregarNodo<Jugador>(partidos[equipo][partido],crearJugador(lectura));
			} else {
				aux->info.goles++;
			}
		}
		ant = lectura;
		lectura = read<Gol>(f);
		if(ant.cod_equipo != lectura.cod_equipo){
			partido = 0;
			equipo++;
		} else if(ant.id_partido != lectura.id_partido) {
			partido++;
		}
	}
	fclose(f);
	return;
}

void insertarEquipo(Arbol<Equipo>*& nodo, Equipo v) {
	if(nodo==NULL) {
		nodo = new Arbol<Equipo>();
		nodo->dato = v;
		nodo->izq=NULL;
		nodo->der=NULL;
	} else {
		if(v.goles > nodo->dato.goles) {
			insertarEquipo(nodo->izq,v);
		} else {
			insertarEquipo(nodo->der,v);
		}
	}
}

void inOrden(Arbol<Equipo>* nodo){
	if(nodo!=NULL){
		inOrden(nodo->izq);
		cout << left << setw(15) << EQUIPOS[nodo->dato.cod_equipo] << setw (5) << nodo->dato.goles << endl;
		inOrden(nodo->der);
	}
}

void golesPorEquipo(Nodo<Jugador>* partidos[][CANTPARTIDOS]){
	int goles=0;
	Nodo<Jugador>* jug = NULL;
	Nodo<Equipo>* equipos = NULL;
	for(int equipo=0; equipo<CANTEQUIPOS; equipo++){
		for(int partido=0; partido<CANTPARTIDOS; partido++){
			jug = partidos[equipo][partido];
			while(jug!=NULL){
				goles += jug->info.goles;
				jug=jug->sig;
			}
		}
		agregarNodo<Equipo>(equipos, crearEquipo(equipo, goles));
		goles=0;
	}
	Nodo<Equipo>* aux = equipos;
	Arbol<Equipo>* raiz = NULL;
	while(aux!=NULL){
		insertarEquipo(raiz, aux->info);		
		aux = aux->sig;
	}
	system("clear");
	cout << left << setw(15) << "PAIS" << setw(5) << "GOLES" <<endl;
	inOrden(raiz);
	return;
}

void goleadores(Nodo<Jugador>* partidos[][CANTPARTIDOS]){
	Nodo<Jugador>* jugadores = NULL;
	Nodo<Jugador>* jug = NULL;
	Nodo<Jugador>* jugEnc = NULL;
	int enContra = 0;
	for(int equipo=0; equipo<CANTEQUIPOS; equipo++){
		for(int partido=0; partido<CANTPARTIDOS; partido++){
			jug= partidos[equipo][partido];
			while(jug!=NULL){
				if(!esEnContra(jug->info)){
					jugEnc = buscar<Jugador,Jugador>(jugadores, jug->info, criterioJugador);
					if(jugEnc==NULL){
						agregarNodo<Jugador>(jugadores, jug->info);
					} else {
						jugEnc->info.goles += jug->info.goles;
						ordenar<Jugador>(jugadores, criterioGoles);
					}
				} else {
					enContra++;
				}
				jug = jug->sig;
			}
		}
	}
	jug = jugadores;
	system("clear");
	cout<< left << setw(20) << "JUGADOR" << setw(5) << "GOLES" <<endl;
	while(jug!=NULL){
		cout<< left << setw(20) << jug->info.nombre_jugador << setw(3) << jug->info.goles <<endl;
		jug = jug->sig;
	}
	cout << left << setw(20) << "GOLES EN CONTRA" << enContra << endl;
	liberar<Jugador>(jugadores);
	return;
}

void goleadoresPorFecha(Nodo<Jugador>* partidos[][CANTPARTIDOS]){
	Nodo<Fecha>* fechas = NULL;
	Nodo<Fecha>* aux = NULL;
	Nodo<Jugador>* jug = NULL;
	Nodo<Jugador>* ant = NULL;
	for(int partido = 0; partido<CANTPARTIDOS; partido++){
		for(int equipos = 0; equipos<CANTEQUIPOS; equipos++){
			jug = partidos[equipos][partido];
			while(jug!=NULL){
				aux = fechas;
				while(aux!=NULL && aux->info.fecha != jug->info.fecha){
					aux = aux->sig;
				}
				if(aux == NULL){
					insertarOrdenado<Fecha>(fechas, crearFecha(jug->info), criterioFecha);
				} else {
					insertarOrdenado<Jugador>(aux->info.sub,jug->info, criterioGoles);
				}
				ant = jug;
				jug = jug->sig;
			}
		}
	}
	aux = fechas;
	system("clear");
	while(aux!=NULL){
		cout<< "GOLES DEL DIA " << (aux->info.fecha)%100 << "/" << ((aux->info.fecha)/100)%100 << "/" << (aux->info.fecha)/10000 << ": " << endl;
		cout<< left << setw(20) << "JUGADOR" << setw(5) << "GOLES" << endl;
		jug = aux->info.sub;
		while(jug!=NULL){
			cout<< left << setw(20) << jug->info.nombre_jugador << setw(5) << jug->info.goles << endl;
			jug = jug->sig;
		}
		aux=aux->sig;
	}
	liberar<Fecha>(fechas);
	return;
}

int main(){
	Nodo<Jugador>* partidos[CANTEQUIPOS][CANTPARTIDOS] = { NULL };
	int menu = 0;
	cargarArchivo(partidos, "../goles.DAT");
	while(true){
		cout<< "GOLES DEL MUNDIAL 2018"<<endl;
		cout<< "1: Volver a cargar los datos" <<endl;
		cout<< "2: Ver cantidad de goles por equipo" <<endl;
		cout<< "3: Ver tabla de goleadores" << endl;
		cout<< "4: Ver los goleadores de cada fecha" << endl;
		cout<< "0: Salir" <<endl;
		cin>> menu;
		switch(menu){
			case 1: cargarArchivo(partidos, "goles.DAT"); cout<<"Datos cargados."<<endl; break;
			case 2: golesPorEquipo(partidos); break;
			case 3: goleadores(partidos); break;
			case 4: goleadoresPorFecha(partidos); break;
			case 0: return 0; break;
		}
		system("pause");
		system("clear");
	}
	return 0;
}
