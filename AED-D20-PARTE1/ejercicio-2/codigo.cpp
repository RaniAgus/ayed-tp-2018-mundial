#include "../utils/utils.hpp"

using namespace std;

bool debug = false;

Seleccion paises[GRUPOS][EQUIPOSPORGRUPO];

void mostrar(int bolillerosAMostrar) {
    char grupo = 65;
	cout << "------------------------------------------------------------" << endl;
	for(int i = 0; i < GRUPOS; i++){
    	cout << "GRUPO "<< grupo <<endl;
    	for(int j = 0; j < bolillerosAMostrar; j++){
    		cout << left << setw(15) << paises[i][j].nombreDeEquipo;
		}
		cout << endl;
		cout << "------------------------------------------------------------" << endl;
		grupo++;
	}	
	cout << endl;
}

int confederacionCmp(Seleccion e1, string s2)
{
	string s1 = e1.confederacion;
	return s1 > s2 ? 1 : s1 < s2 ? -1 : 0;

} 

int verificarGrupos(int bolillerosSorteados) {
	string confederaciones[CONFEDERACIONES] = 
		{ "UEFA"
		, "Conmebol"
		, "Concacaf"
		, "AFC"
		, "CAF"
		, "OFC"
		}
	;
	int cant_limite[CONFEDERACIONES] = { 2, 1, 1, 1, 1, 1 };
	
	for (int grupo = 0; grupo < GRUPOS; grupo++) {
		int cant_equipos[CONFEDERACIONES] = { 0, 0, 0, 0, 0, 0 };
		
		for(int bolillero = 0; bolillero < bolillerosSorteados; bolillero++){
			for(int i = 0; i < CONFEDERACIONES; i++) {
				if(confederacionCmp(paises[grupo][bolillero], confederaciones[i]) == 0) {
					cant_equipos[i]++;
					if(cant_equipos[i] > cant_limite[i]) {
						return -1;
					}
				}
			}
		}
	}
	return 1;
}

bool esAnfitrion(int bolillero, int grupo) {
	return bolillero == 0 && grupo == 0;
}

void intercambiar(int grupo1, int grupo2, int bolillero) {
	Seleccion temp = paises[grupo1][bolillero];
	paises[grupo1][bolillero] = paises[grupo2][bolillero];
	paises[grupo2][bolillero] = temp;
}

void sortear() {
    for (int bolilleroActual = 0; bolilleroActual < EQUIPOSPORGRUPO; bolilleroActual++){
    	while(true) {
	    	for (int grupoASortear = 0; grupoASortear < GRUPOS; grupoASortear++){
	    		if (!esAnfitrion(bolilleroActual, grupoASortear)) {
					int equipoElegido = rand() % (GRUPOS - grupoASortear) + grupoASortear;
					intercambiar(grupoASortear, equipoElegido, bolilleroActual);
				}   		
			}	
			cout << "BOLILLERO " << bolilleroActual + 1 << " SORTEADO" << endl;
	    	mostrar(bolilleroActual + 1);
			
			if(verificarGrupos(bolilleroActual + 1) < 0) {
				if(debug) {
					cout << "La conformacion de los grupos no es valida, se volvera a sortear el bolillero" << endl;
					cin.get();
					system("clear");
				}
			} else {
				break;
			}
		}
		cin.get();
		system("clear");
	}
	return;
}

void leerPaises(FILE* f){
	for(int i = 0; i < GRUPOS; i++){
    	for(int j = 0; j < EQUIPOSPORGRUPO; j++){
			paises[i][j] = read<Seleccion>(f);
		}
	}	
}

void guardarGrupos() {
	for(int i = 0; i < GRUPOS; i++){
		FILE* f = openGrupo('A' + i, "w+b");
    	for(int j = 0; j < EQUIPOSPORGRUPO; j++){
    		write<Seleccion>(f, paises[i][j]);
		}
    	fclose(f);
	}
	cout<<"Grupos guardados con exito."<<endl;
}

int main(int argc, char** argv) {
	for (int i = 0; i < argc; i++) {
		if(strcmp(argv[i],"-d") == 0){
			debug = true;
			cout << "Modo debug" << endl;
		}
	}

	setlocale(LC_ALL, "");
	srand(time(NULL));
	
	FILE* f = fopen("../Mundial.dat","r+b");
	leerPaises(f);
	fclose(f);
	
	cout << "Pulse cualquier tecla para sortear la fase de grupos." << endl;
	cin.get();

	do {
		system("clear");
		sortear();
    	cout << "FASE DE GRUPOS SORTEADA" << endl;
    	mostrar(EQUIPOSPORGRUPO);
    	cout <<"Ingresa enter para guardar y salir. Ingresa cualquier otra tecla para volver a sortear."<< endl;
	} while (cin.get() != '\n');
	guardarGrupos();
    
    return 0;
}
