#include <iostream>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;
const int GRUPOS = 8;
const int EQUIPOSPORGRUPO = 4;

template<typename T> T read(FILE* f)
{
    T buff;
    fread(&buff,sizeof(T),1,f);
    return buff;
}

struct Seleccion{
    int bolillero;
    char nombreDeEquipo[15];
    char confederacion[10];
    
};

struct Equipo{
    int grupo;
    char nombreDeEquipo[15];
    char confederacion[10];
};

void mostrarPaises(Equipo paises[]){
	cout<< left << setw(15)<< "PAÍS" << setw(15) << "CONFEDERACIÓN" << "GRUPO" <<endl;
	cout<<"---------------------------------------"<<endl;
    for(int i=0; i<32; i++){
    	cout<< left << setw(15) << paises[i].nombreDeEquipo << setw(15) << paises[i].confederacion <<  paises[i].grupo << endl;
	}
	cout<<endl;
}

Equipo crearEquipo(int grupo, string nombreDeEquipo, string confederacion){
	Equipo a;
	a.grupo = grupo;
	strcpy(a.nombreDeEquipo, nombreDeEquipo.c_str());
	strcpy(a.confederacion, confederacion.c_str());
	return a;
}

template <typename T> void ordenar(T arr[], int len, int (*criterio)(T,T)) {
	bool ordenado=false;
	while(!ordenado){ 
		ordenado=true;
		for(int i=0; i<len-1; i++){
			if( criterio(arr[i],arr[i+1])>0 ){
				T aux = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = aux;
				ordenado = false;
			}
		}
	}
}

int nombreAZ(Equipo e1, Equipo e2) {
	string s1 = e1.nombreDeEquipo;
	string s2 = e2.nombreDeEquipo;
	return s1>s2?1:s1<s2?-1:0;
} 

int confederacionAZ(Equipo e1, Equipo e2) {
	string s1 = e1.confederacion;
	string s2 = e2.confederacion;
	return s1>s2?1:s1<s2?-1:0;
} 

int grupo09(Equipo e1, Equipo e2){
	return e1.grupo-e2.grupo;
}

void leerEquipos(Equipo paises[]){    
	
	FILE* f;
	string archivo="";
    string direccion="../Archivos/Grupo ";
    char grupo='A';
    string formato=".dat";
	
    int len=0;
	Seleccion a;
	for(int i=0; i<GRUPOS; i++){
    	archivo=direccion+grupo+formato;
    	const char* c= archivo.c_str();
		f = fopen(c,"r+b");
    	for(int j=0; j<EQUIPOSPORGRUPO; j++){
    		a = read<Seleccion>(f);
    		paises[len] = crearEquipo(i+1, a.nombreDeEquipo, a.confederacion);
    		len++;
    		
		}
    	fclose(f);
		grupo++;
	}
	
}

int main(){
	setlocale(LC_ALL, "");
    
    Equipo paises[GRUPOS*EQUIPOSPORGRUPO];
	leerEquipos(paises);
	
	int menu=0;
	
	do{
		cout<< "1: Ordenar por número de grupo"<<endl;
		cout<< "2: Ordenar por nombre de equipo"<<endl;
		cout<< "3: Ordenar por confederación"<<endl;
		cout<< "4: Ordenar por número de grupo y confederación"<<endl;
		cout<< "5: Ordenar por número de grupo, confederación y nombre de equipo"<<endl;
		cout<< "0: Salir"<<endl;
		cin>>menu;
		
		switch(menu){
			case 1:
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, grupo09);
				mostrarPaises(paises);
			break;
			case 2:
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, nombreAZ);
				mostrarPaises(paises);
			break;
			case 3:
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, confederacionAZ);
				mostrarPaises(paises);
			break;
			case 4:
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, confederacionAZ);
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, grupo09);
				mostrarPaises(paises);						
			break;
			case 5:
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, nombreAZ);
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, confederacionAZ);
				ordenar<Equipo>(paises, GRUPOS*EQUIPOSPORGRUPO, grupo09);
				mostrarPaises(paises);				
			break;
			case 0:
			break;
			default:
				cout<<"Opción incorrecta"<<endl;
		}
		system("pause");
		system("CLS");
	}while(menu!=0);
	
	
	
	return 0;
}
