#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>


using namespace std;
const int GRUPOS = 8;
const int EQUIPOSPORGRUPO = 4;

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

struct Seleccion{
    int bolillero;
    char nombreDeEquipo[15];
    char confederacion[10];
};

void mostrar(Seleccion paises[][EQUIPOSPORGRUPO], int bolilleros){
    char grupo = 65;
	cout<<"------------------------------------------------------------"<<endl;
	for(int i=0; i<GRUPOS; i++){
    	cout<< "GRUPO "<< grupo <<endl;
    	for(int j=0; j<bolilleros; j++){
    		cout<< left << setw(15) << paises[i][j].nombreDeEquipo;
		}
		cout<<endl;
		cout<<"------------------------------------------------------------"<<endl;
		grupo++;
	}	
	cout <<endl;
}

int confederacionCmp(Seleccion e1, string s2)
{
	string s1 = e1.confederacion;
	return s1>s2?1:s1<s2?-1:0;

} 

int verificarEquipos(Seleccion paises[][EQUIPOSPORGRUPO], int bolillero){
	
	int uefa=0, conmebol=0, concacaf=0, afc=0, caf=0, ofc=0;
	
	for (int grupo=0; grupo<GRUPOS; grupo++){
		uefa=0, conmebol=0, concacaf=0, afc=0, caf=0, ofc=0;
		
		for(int i=0; i<=bolillero; i++){
			if(confederacionCmp(paises[grupo][i], "UEFA") == 0){ uefa++; }
			if(confederacionCmp(paises[grupo][i], "Conmebol") == 0){ conmebol++; }
			if(confederacionCmp(paises[grupo][i], "Concacaf") == 0){ concacaf++; }
			if(confederacionCmp(paises[grupo][i], "AFC") == 0){ afc++; }
			if(confederacionCmp(paises[grupo][i], "CAF") == 0){ caf++; }
			if(confederacionCmp(paises[grupo][i], "OFC") == 0){ ofc++; }	
		}
		
		if( uefa>2 || conmebol>1 || concacaf>1 || afc>1 || caf>1 || ofc>1){
			return -1;	
		}
	}
	return 1;
}


void sortear(Seleccion paises[][EQUIPOSPORGRUPO]){
	Seleccion temp;
    int equipoelegido = 0;
    for (int bol=0; bol<EQUIPOSPORGRUPO; bol++){
    	do {
	    	for (int grupo=0; grupo<GRUPOS; grupo++){
	    		if (bol != 0 || grupo != 0){
					equipoelegido = rand()%(GRUPOS-grupo) + grupo;
	    			temp = paises[grupo][bol];
	    			paises[grupo][bol] = paises[equipoelegido][bol];
	    			paises[equipoelegido][bol] = temp;
				}   		
			}	
		} while( verificarEquipos(paises, bol) < 0 );
    	cout <<"BOLILLERO "<< bol+1 << " SORTEADO"<<endl;
	    mostrar( paises, bol+1 );
	    system("pause");
		system("CLS");
	}
	return;
}

void leerPaises(FILE* f, Seleccion paises[][EQUIPOSPORGRUPO]){
	for(int i=0; i<GRUPOS; i++){
    	for(int j=0; j<EQUIPOSPORGRUPO; j++){
			paises[i][j] = read<Seleccion>(f);
		}
	}	
}

void guardarGrupos(Seleccion paises[][EQUIPOSPORGRUPO]){
    FILE* f;
    string archivo="";
    string direccion="../archivos/Grupo ";
    char grupo='A';
    string formato=".dat";
	for(int i=0; i<GRUPOS; i++){
    	archivo=direccion+grupo+formato;
    	const char* c= archivo.c_str();
		f = fopen(c,"w+b");
    	for(int j=0; j<EQUIPOSPORGRUPO; j++){
    		write<Seleccion>(f, paises[i][j]);
		}
    	fclose(f);
		grupo++;
	}
	cout<<"Grupos guardados con �xito."<<endl;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	Seleccion paises[GRUPOS][EQUIPOSPORGRUPO];
	
	FILE* f = fopen("../archivos/Mundial.dat","r+b");
	leerPaises(f, paises);
	fclose(f);
	
	cout<<"Pulse cualquier tecla para sortear la fase de grupos."<<endl;
	system("pause");
	
	int menu=0;
	while(menu==0){
		system("CLS");
		sortear(paises);
    	cout <<"FASE DE GRUPOS SORTEADA"<<endl;
    	mostrar(paises, EQUIPOSPORGRUPO);
    	cout <<"Ingresa 0 para volver a sortear. Ingresa cualquier otro n�mero para guardar y salir."<< endl;
    	cin>> menu;
	}	
	guardarGrupos(paises);
    
    return 0;
}
