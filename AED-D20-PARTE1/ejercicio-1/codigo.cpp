#include "../utils/utils.hpp"

using namespace std;

Seleccion crearSeleccion(int bolillero, string nombreDeEquipo, string confederacion){
	Seleccion a;
	a.bolillero = bolillero;
	strcpy(a.nombreDeEquipo, nombreDeEquipo.c_str());
	strcpy(a.confederacion, confederacion.c_str());
	
	return a;
}

void mostrarPaises(Seleccion paises[][EQUIPOSPORGRUPO]){
	cout<<"PAISES CLASIFICADOS: "<<endl <<endl;
	cout<< left << setw(15)<< "PAIS" << setw(15) << "CONFEDERACION" << "BOLILLERO" <<endl;
	cout<<"---------------------------------------"<<endl;
    for(int j=0; j<EQUIPOSPORGRUPO; j++){
		for(int i=0; i<GRUPOS; i++){
    		cout<< left << setw(15) << paises[i][j].nombreDeEquipo << setw(15) << paises[i][j].confederacion <<  paises[i][j].bolillero << endl;
		}
	}
	cout<<endl;
}

void ingresarPaises(Seleccion paises[][EQUIPOSPORGRUPO]){
	paises[0][0] = crearSeleccion(1, "Rusia", "UEFA");
	paises[1][0] = crearSeleccion(1, "Alemania", "UEFA");
	paises[2][0] = crearSeleccion(1, "Brasil", "Conmebol");
	paises[3][0] = crearSeleccion(1, "Portugal", "UEFA");
	paises[4][0] = crearSeleccion(1, "Argentina", "Conmebol");
	paises[5][0] = crearSeleccion(1, "Belgica", "UEFA");
	paises[6][0] = crearSeleccion(1, "Polonia", "UEFA");
	paises[7][0] = crearSeleccion(1, "Francia", "UEFA");
    paises[0][1] = crearSeleccion(2, "Espana", "UEFA");
	paises[1][1] = crearSeleccion(2, "Peru", "Conmebol");
	paises[2][1] = crearSeleccion(2, "Suiza", "UEFA");
	paises[3][1] = crearSeleccion(2, "Inglaterra", "UEFA");
	paises[4][1] = crearSeleccion(2, "Colombia", "Conmebol");
	paises[5][1] = crearSeleccion(2, "Mexico", "Concacaf");
	paises[6][1] = crearSeleccion(2, "Uruguay", "Conmebol");
	paises[7][1] = crearSeleccion(2, "Croacia", "UEFA");
    paises[0][2] = crearSeleccion(3, "Dinamarca", "UEFA");
	paises[1][2] = crearSeleccion(3, "Islandia", "UEFA");
	paises[2][2] = crearSeleccion(3, "Costa Rica", "Concacaf");
	paises[3][2] = crearSeleccion(3, "Suecia", "UEFA");
	paises[4][2] = crearSeleccion(3, "Tunez", "CAF");
	paises[5][2] = crearSeleccion(3, "Egipto", "CAF");
	paises[6][2] = crearSeleccion(3, "Senegal", "CAF");
	paises[7][2] = crearSeleccion(3, "Iran", "AFC");
	paises[0][3] = crearSeleccion(4, "Serbia", "UEFA");
	paises[1][3] = crearSeleccion(4, "Nigeria", "CAF");
	paises[2][3] = crearSeleccion(4, "Australia", "AFC");
	paises[3][3] = crearSeleccion(4, "Japon", "AFC");
	paises[4][3] = crearSeleccion(4, "Marruecos", "CAF");
	paises[5][3] = crearSeleccion(4, "Panama", "Concacaf");
	paises[6][3] = crearSeleccion(4, "Corea del Sur", "AFC");
	paises[7][3] = crearSeleccion(4, "Arabia Saudita", "AFC");
}

void guardarPaises(FILE* f, Seleccion paises[][EQUIPOSPORGRUPO]){
   	for (int i=0; i<GRUPOS; i++){
      	for (int j = 0; j<EQUIPOSPORGRUPO; j++){
        	write<Seleccion>(f, paises[i][j]);
      	}
   	}
	cout<<"Paises guardados con exito."<<endl;
}

int main() {
	setlocale(LC_ALL, "");
	Seleccion paises[GRUPOS][EQUIPOSPORGRUPO];
	ingresarPaises(paises);
	mostrarPaises(paises);
	
	FILE *f = fopen("../Mundial.dat","w+b");
	guardarPaises(f, paises);
    fclose(f);
	
	return 0;
}
