#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

struct Gol{
	int id_gol;
	int cod_equipo;
	int fecha;
	char nombre_jugador[20];
	int id_partido;
};

template<typename T> void write(FILE* f, T v){
    fwrite(&v,sizeof(T),1,f);
    return;
}

template<typename T> T read(FILE* f){
    T buff;
    fread(&buff,sizeof(T),1,f);
    return buff;
}

Gol crearGol(int id_gol, int cod_equipo, int fecha, string nombre_jugador, int id_partido){
	Gol a;
	a.id_gol = id_gol;
	a.cod_equipo = cod_equipo;
	a.fecha = fecha;
	strcpy(a.nombre_jugador,nombre_jugador.c_str());
	a.id_partido = id_partido;
	
	return a;
}

int main(){
	int i = 1;
	Gol a;
	FILE* f = fopen("../goles.DAT","wb+");

	// -------------- FRANCIA -------------------- //
	a = crearGol(i++,1,20180616,"Griezmann",5);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180616,"e.c. Behich",5);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180621,"Mbappe",21);
	write<Gol>(f,a);
	a = crearGol(0,1,20180626, "NULL", 36);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180630,"Griezmann",49);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180630,"Pavard",49);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180630,"Mbappe",49);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180630,"Mbappe",49);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180706,"Varane",57);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180706,"Griezmann",57);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180710,"Umtiti",61);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180715,"e.c. Mandzukic",64);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180715,"Griezmann",64);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180715,"Pogba",64);
	write<Gol>(f,a);
	a = crearGol(i++,1,20180715,"Mbappe",64);
	write<Gol>(f,a);
	
	// -------------- CROACIA -------------------- //
	a = crearGol(i++,2,20180616,"e.c. Etebo",7);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180616,"Modric",7);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180621,"Rebic",22);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180621,"Modric",22);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180621,"Rakitic",22);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180626,"Badelj",39);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180626,"Perisic",39);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180701,"Mandzukic",52);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180707,"Kramaric",60);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180707,"Vida",60);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180711,"Perisic",62);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180711,"Mandzukic",62);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180715,"Perisic",64);
	write<Gol>(f,a);
	a = crearGol(i++,2,20180715,"Mandzukic",64);
	write<Gol>(f,a);
	
	// -------------- BÉLGICA -------------------- //
	a = crearGol(i++,3,20180618,"Mertens",12);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180618,"Lukaku",12);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180618,"Lukaku",12);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180623,"Hazard",28);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180623,"Lukaku",28);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180623,"Lukaku",28);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180623,"Hazard",28);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180623,"Batshuayi",28);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180628,"Januzaj",44);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180702,"Vertonghen",54);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180702,"Fellaini",54);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180702,"Chadli",54);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180706,"e.c. Fernandinho",58);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180706,"De Bruyne",58);
	write<Gol>(f,a);
	a = crearGol(0,3,20180710,"NULL",61);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180714,"Meunier",63);
	write<Gol>(f,a);
	a = crearGol(i++,3,20180714,"Hazard",63);
	write<Gol>(f,a);
	
	// ---------------- INGLATERRA ---------------- //
	a = crearGol(i++,4,20180618,"Kane",13);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180618,"Kane",13);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180624,"Stones",29);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180624,"Kane",29);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180624,"Lingard",29);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180624,"Stones",29);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180624,"Kane",29);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180624,"Kane",29);
	write<Gol>(f,a);
	a = crearGol(0,4,20180628,"NULL",44);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180703,"Kane",56);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180707,"Maguire",59);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180707,"Alli",59);
	write<Gol>(f,a);
	a = crearGol(i++,4,20180711,"Trippier",62);
	write<Gol>(f,a);
	
	// --------------- URUGUAY --------------------- //
	a = crearGol(i++,5,20180615,"Gimenez",2);
	write<Gol>(f,a);
	a = crearGol(i++,5,20180620,"Suarez",17);
	write<Gol>(f,a);
	a = crearGol(i++,5,20180625,"Suarez",32);
	write<Gol>(f,a);
	a = crearGol(i++,5,20180625,"e.c. Cheryshev",32);
	write<Gol>(f,a);
	a = crearGol(i++,5,20180625,"Cavani",32);
	write<Gol>(f,a);
	a = crearGol(i++,5,20180630,"Cavani",50);
	write<Gol>(f,a);
	a = crearGol(i++,5,20180630,"Cavani",50);
	write<Gol>(f,a);
	a = crearGol(0,5,20180706,"NULL",57);
	write<Gol>(f,a);
	
	// ----------------- BRASIL -------------------- //
	a = crearGol(i++,6,20180617,"Coutinho",9);
	write<Gol>(f,a);
	a = crearGol(i++,6,20180622,"Coutinho",24);
	write<Gol>(f,a);
	a = crearGol(i++,6,20180622,"Neymar",24);
	write<Gol>(f,a);
	a = crearGol(i++,6,20180627,"Paulinho",40);
	write<Gol>(f,a);
	a = crearGol(i++,6,20180627,"Thiago Silva",40);
	write<Gol>(f,a);
	a = crearGol(i++,6,20180702,"Neymar",53);
	write<Gol>(f,a);
	a = crearGol(i++,6,20180702,"Firmino",53);
	write<Gol>(f,a);
	a = crearGol(i++,6,20180706,"Renato Augusto",58);
	write<Gol>(f,a);
	
	// ------------------- SUECIA ------------------ //
	a = crearGol(i++,7,20180618,"Granqvist",14);
	write<Gol>(f,a);
	a = crearGol(i++,7,20180623,"Toivonen",27);
	write<Gol>(f,a);
	a = crearGol(i++,7,20180627,"Augustinsson",43);
	write<Gol>(f,a);
	a = crearGol(i++,7,20180627,"Granqvist",43);
	write<Gol>(f,a);
	a = crearGol(i++,7,20180627,"e.c. Alvarez",43);
	write<Gol>(f,a);
	a = crearGol(i++,7,20180703,"Forsberg",55);
	write<Gol>(f,a);
	a = crearGol(0,7,20180707,"NULL",59);
	write<Gol>(f,a);

	
	// ------------------- RUSIA ------------------- //
	a = crearGol(i++,8,20180614,"Gazinski",1);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180614,"Cheryshev",1);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180614,"Dzyuba",1);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180614,"Cheryshev",1);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180614,"Golovin",1);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180619,"e.c. Fathy",16);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180619,"Cheryshev",16);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180619,"Dzyuba",16);
	write<Gol>(f,a);
	a = crearGol(0,8,20180625,"NULL",32);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180701,"Dzyuba",51);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180707,"Cheryshev",60);
	write<Gol>(f,a);
	a = crearGol(i++,8,20180707,"Fernandes",60);
	write<Gol>(f,a);
	
	// -------------------- COLOMBIA ---------------- //
	a = crearGol(i++,9,20180619,"Quintero",14);
	write<Gol>(f,a);
	a = crearGol(i++,9,20180624,"Mina",31);
	write<Gol>(f,a);
	a = crearGol(i++,9,20180624,"Falcao",31);
	write<Gol>(f,a);
	a = crearGol(i++,9,20180624,"Cuadrado",31);
	write<Gol>(f,a);
	a = crearGol(i++,9,20180628,"Mina",48);
	write<Gol>(f,a);
	a = crearGol(i++,9,20180703,"Mina",56);
	write<Gol>(f,a);
	
	// -------------------- ESPAÑA ----------------- //
	a = crearGol(i++,10,20180615,"Diego Costa",4);
	write<Gol>(f,a);
	a = crearGol(i++,10,20180615,"Diego Costa",4);
	write<Gol>(f,a);
	a = crearGol(i++,10,20180615,"Nacho",4);
	write<Gol>(f,a);
	a = crearGol(i++,10,20180620,"Diego Costa",19);
	write<Gol>(f,a);
	a = crearGol(i++,10,20180625,"Isco",35);
	write<Gol>(f,a);
	a = crearGol(i++,10,20180625,"Aspas",35);
	write<Gol>(f,a);
	a = crearGol(i++,10,20180701,"e.c. Ignashevich",51);
	write<Gol>(f,a);
	
	// -------------------- DINAMARCA --------------- //
	a = crearGol(i++,11,20180616,"Poulsen",6);
	write<Gol>(f,a);
	a = crearGol(i++,11,20180621,"Eriksen",20);
	write<Gol>(f,a);
	a = crearGol(0,11,20180626, "NULL", 36);
	write<Gol>(f,a);
	a = crearGol(i++,11,20180701,"Jorgensen",52);
	write<Gol>(f,a);
	
	// ------------------- MÉXICO ------------------ //
	a = crearGol(i++,12,20180617,"Lozano",10);
	write<Gol>(f,a);
	a = crearGol(i++,12,20180623,"Vela",26);
	write<Gol>(f,a);
	a = crearGol(i++,12,20180623,"Hernandez",26);
	write<Gol>(f,a);
	a = crearGol(0,12,20180702,"NULL",53);
	write<Gol>(f,a);

	
	// ------------------- PORTUGAL --------------- //
	a = crearGol(i++,13,20180615,"Ronaldo",4);
	write<Gol>(f,a);
	a = crearGol(i++,13,20180615,"Ronaldo",4);
	write<Gol>(f,a);
	a = crearGol(i++,13,20180615,"Ronaldo",4);
	write<Gol>(f,a);
	a = crearGol(i++,13,20180620,"Ronaldo",18);
	write<Gol>(f,a);
	a = crearGol(i++,13,20180625,"Quaresma",34);
	write<Gol>(f,a);
	a = crearGol(i++,13,20180630,"Pepe",50);
	write<Gol>(f,a);
	
	// ------------------- SUIZA ------------------ //
	a = crearGol(i++,14,20180617,"Zuber",9);
	write<Gol>(f,a);
	a = crearGol(i++,14,20180622,"Xhaka",25);
	write<Gol>(f,a);
	a = crearGol(i++,14,20180622,"Shaqiri",25);
	write<Gol>(f,a);
	a = crearGol(i++,14,20180627,"Dzemaili",41);
	write<Gol>(f,a);
	a = crearGol(i++,14,20180627,"Drmic",41);
	write<Gol>(f,a);
	a = crearGol(0,14,20180703,"NULL",55);
	write<Gol>(f,a);

	
	// ------------------- JAPÓN ----------------- //
	a = crearGol(i++,15,20180619,"Kagawa",14);
	write<Gol>(f,a);
	a = crearGol(i++,15,20180619,"Osako",14);
	write<Gol>(f,a);
	a = crearGol(i++,15,20180624,"Inui",30 );
	write<Gol>(f,a);
	a = crearGol(i++,15,20180624,"Honda",30);
	write<Gol>(f,a);
	a = crearGol(0,15,20180628,"NULL",47);
	write<Gol>(f,a);
	a = crearGol(i++,15,20180702,"Haraguchi",54);
	write<Gol>(f,a);
	a = crearGol(i++,15,20180702,"Inui",54);
	write<Gol>(f,a);
	
	// ------------------ ARGENTINA -------------- //
	a = crearGol(i++,16,20180616,"Aguero",6);
	write<Gol>(f,a);
	a = crearGol(0,16,20180621,"NULL",22);
	write<Gol>(f,a);
	a = crearGol(i++,16,20180626,"Messi",38);
	write<Gol>(f,a);
	a = crearGol(i++,16,20180626,"Rojo",38);
	write<Gol>(f,a);
	a = crearGol(i++,16,20180630,"Di Maria",49);
	write<Gol>(f,a);
	a = crearGol(i++,16,20180630,"Mercado",49);
	write<Gol>(f,a);
	a = crearGol(i++,16,20180630,"Aguero",49);
	write<Gol>(f,a);
	
	// ----------------- SENEGAL ------------------ //
	a = crearGol(i++,17,20180619,"e.c. Cionek",15);
	write<Gol>(f,a);
	a = crearGol(i++,17,20180619,"Niang",15);
	write<Gol>(f,a);
	a = crearGol(i++,17,20180624,"Mane",30);
	write<Gol>(f,a);
	a = crearGol(i++,17,20180624,"Wague",30);
	write<Gol>(f,a);
	a = crearGol(0,17,20180628,"NULL",48);
	write<Gol>(f,a);
	
	// ---------------- IRÁN ---------------------- //
	a = crearGol(i++,18,20180615,"Bouhaddouz",3);
	write<Gol>(f,a);
	a = crearGol(0,18,20180620,"NULL",19);
	write<Gol>(f,a);
	a = crearGol(i++,18,20180625,"Ansarifard",34);
	write<Gol>(f,a);
	
	
	// ---------------- COREA DEL SUR ------------- //
	a = crearGol(0,19,20180618,"NULL",14);
	write<Gol>(f,a);
	a = crearGol(i++,19,20180623,"Heung-Min Son",26);
	write<Gol>(f,a);
	a = crearGol(i++,19,20180627,"Young-Gwon Kim",42);
	write<Gol>(f,a);
	a = crearGol(i++,19,20180627,"Heung-Min Son",42);
	write<Gol>(f,a);
	
	// ---------------- PERÚ ---------------------- //
	a = crearGol(0,20,20180616,"NULL",6);
	write<Gol>(f,a);
	a = crearGol(0,20,20180621,"NULL",21);
	write<Gol>(f,a);
	a = crearGol(i++,20,20180626,"Carrillo",37);
	write<Gol>(f,a);
	a = crearGol(i++,20,20180626,"Guerrero",37);
	write<Gol>(f,a);
	
	// ---------------- NIGERIA ------------------- //
	a = crearGol(0,21,20180616,"NULL",7);
	write<Gol>(f,a);
	a = crearGol(i++,21,20180622,"Musa",23);
	write<Gol>(f,a);
	a = crearGol(i++,21,20180622,"Musa",23);
	write<Gol>(f,a);
	a = crearGol(i++,21,20180626,"Moses",38);
	write<Gol>(f,a);
	
	// ---------------- ALEMANIA ------------------ //
	a = crearGol(0,22,20180617,"NULL",10);
	write<Gol>(f,a);
	a = crearGol(i++,22,20180623,"Reus",27);
	write<Gol>(f,a);
	a = crearGol(i++,22,20180623,"Kroos",27);
	write<Gol>(f,a);
	a = crearGol(0,22,20180627,"NULL",42);
	write<Gol>(f,a);

	
	// ---------------- SERBIA ------------------- //
	a = crearGol(i++,23,20180617,"Kolarov",8);
	write<Gol>(f,a);
	a = crearGol(i++,23,20180622,"Mitrovic",25);
	write<Gol>(f,a);
	a = crearGol(0,23,20180627,"NULL",40);
	write<Gol>(f,a);
	
	// ---------------- TÚNEZ ------------------- //
	a = crearGol(i++,24,20180618,"Sassi",13);
	write<Gol>(f,a);
	a = crearGol(i++,24,20180623,"Bronn",28);
	write<Gol>(f,a);
	a = crearGol(i++,24,20180623,"Khazri",28);
	write<Gol>(f,a);
	a = crearGol(i++,24,20180628,"Youssef",45);
	write<Gol>(f,a);
	a = crearGol(i++,24,20180628,"Khazri",45);
	write<Gol>(f,a);
	
	// ---------------- POLONIA ----------------- //
	a = crearGol(i++,25,20180619,"Krychowiak",15);
	write<Gol>(f,a);
	a = crearGol(0,25,20180624,"NULL",31);
	write<Gol>(f,a);
	a = crearGol(i++,25,20180628,"Bednarek",47);
	write<Gol>(f,a);
	
	// ---------------- ARABIA SAUDITA ---------- //
	a = crearGol(0,26,20180614,"NULL",1);
	write<Gol>(f,a);
	a = crearGol(0,26,20180620,"NULL",17);
	write<Gol>(f,a);
	a = crearGol(i++,26,20180625,"Al-Faraj",33);
	write<Gol>(f,a);
	a = crearGol(i++,26,20180625,"Al-Dawsari",33);
	write<Gol>(f,a);
	
	// ---------------- MARRUECOS --------------- //
	a = crearGol(0,27,20180615,"NULL",3);
	write<Gol>(f,a);
	a = crearGol(0,27,20180620,"NULL",18);
	write<Gol>(f,a);
	a = crearGol(i++,27,20180625,"Boutaib",35);
	write<Gol>(f,a);
	a = crearGol(i++,27,20180625,"En-Nesyri",35);
	write<Gol>(f,a);
	
	// ---------------- ISLANDIA ---------------- //
	a = crearGol(i++,28,20180616,"Finnbogason",6);
	write<Gol>(f,a);
	a = crearGol(0,28,20180622,"NULL",23);
	write<Gol>(f,a);
	a = crearGol(i++,28,20180626,"Sigurdsson",39);
	write<Gol>(f,a);
	
	// ---------------- COSTA RICA -------------- //
	a = crearGol(0,29,20180617,"NULL",8);
	write<Gol>(f,a);
	a = crearGol(0,29,20180622,"NULL",24);
	write<Gol>(f,a);
	a = crearGol(i++,29,20180627,"Waston",41);
	write<Gol>(f,a);
	a = crearGol(i++,29,20180627,"e.c. Sommer",41);
	write<Gol>(f,a);
	
	// ---------------- AUSTRALIA --------------- //
	a = crearGol(i++,30,20180616,"Jedinak",5);
	write<Gol>(f,a);
	a = crearGol(i++,30,20180621,"Jedinak",20);	
	write<Gol>(f,a);
	a = crearGol(0,30,20180626,"NULL",37);
	write<Gol>(f,a);
	
	// ---------------- EGIPTO ------------------ //
	a = crearGol(0,31,20180615,"NULL",2);
	write<Gol>(f,a);
	a = crearGol(i++,31,20180619,"Salah",16);
	write<Gol>(f,a);
	a = crearGol(i++,31,20180625,"Salah",33);
	write<Gol>(f,a);
	
	// ---------------- PANAMÁ ------------------ //
	a = crearGol(0,32,20180618,"NULL",12);
	write<Gol>(f,a);
	a = crearGol(i++,32,20180624,"Baloy",29);
	write<Gol>(f,a);
	a = crearGol(i++,32,20180628,"e.c. Meriah",45);
	write<Gol>(f,a);

	fclose(f);
	
	// ------------------ LECTURA -------------------- //
	
	f = fopen("../goles.DAT","rb+");

	a = read<Gol>(f);
	while( !feof(f) ){
		if(strcmp(a.nombre_jugador,"NULL")!=0){
			cout << a.nombre_jugador << ", " << a.id_gol << ", " << a.cod_equipo << ", " << a.fecha << ", " << a.id_partido << endl;
		}
		a = read<Gol>(f);
	}
	fclose(f);

return 0;
}
