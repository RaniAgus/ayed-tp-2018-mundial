#include "../utils/utils.hpp"

using namespace std;

bool debug = false;

Seleccion paises[GRUPOS][BOLILLEROS];

void obtenerSelecciones();
void sortearBolillero(int bolillero);
bool esAnfitrion(int bolillero, int grupo);
void intercambiar(int grupo1, int grupo2, int bolillero);
int verificarConfederaciones(int bolillerosSorteados);
int idConfederacion(Seleccion seleccion);
void mostrarGruposSorteados(int bolillerosAMostrar);
void guardarSorteo();

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            debug = true;
            cout << "Modo debug" << endl;
        }
    }

    setlocale(LC_ALL, "");
    srand(time(NULL));

    obtenerSelecciones();
    cout << "Pulse cualquier tecla para sortear la fase de grupos." << endl;
    cin.get();

    do
    {
        system("clear");
        for (int i = 0; i < BOLILLEROS; i++)
        {
            sortearBolillero(i);
        }
        cout << "FASE DE GRUPOS SORTEADA" << endl;
        mostrarGruposSorteados(BOLILLEROS);
        cout << "Ingresa enter para guardar y salir. Ingresa cualquier caracter para volver a sortear." << endl;
    } while (cin.get() != '\n');

    guardarSorteo();

    return 0;
}

void obtenerSelecciones()
{
    FILE *f = open("../Mundial.dat", "r+b");
    for (int i = 0; i < GRUPOS; i++)
    {
        for (int j = 0; j < BOLILLEROS; j++)
        {
            paises[i][j] = read<Seleccion>(f);
        }
    }
    fclose(f);
}

void sortearBolillero(int bolillero)
{
    do
    {
        for (int grupoASortear = 0; grupoASortear < GRUPOS; grupoASortear++)
        {
            if (!esAnfitrion(bolillero, grupoASortear))
            {
                int equipoElegido = rand() % (GRUPOS - grupoASortear) + grupoASortear;
                intercambiar(grupoASortear, equipoElegido, bolillero);
            }
        }
    } while (verificarConfederaciones(bolillero + 1) < 0);
    cout << "BOLILLERO " << bolillero + 1 << " SORTEADO" << endl;
    mostrarGruposSorteados(bolillero + 1);
    cin.get();
    system("clear");
}

bool esAnfitrion(int bolillero, int grupo)
{
    return bolillero == 0 && grupo == 0;
}

void intercambiar(int grupo1, int grupo2, int bolillero)
{
    Seleccion temp = paises[grupo1][bolillero];
    paises[grupo1][bolillero] = paises[grupo2][bolillero];
    paises[grupo2][bolillero] = temp;
}

int verificarConfederaciones(int bolillerosSorteados)
{
    int cant_limite[CONFEDERACIONES] = {2, 1, 1, 1, 1, 1};

    //Verifica grupo por grupo
    for (int grupo = 0; grupo < GRUPOS; grupo++)
    {

        //Guarda la cantidad de equipos en cada confederación
        int cant_equipos[CONFEDERACIONES] = {0, 0, 0, 0, 0, 0};

        //Solo verifica los bolilleros que hayan sido sorteados
        for (int bolillero = 0; bolillero < bolillerosSorteados; bolillero++)
        {
            int confederacion = idConfederacion(paises[grupo][bolillero]);
            cant_equipos[confederacion]++;
            if (cant_equipos[confederacion] > cant_limite[confederacion])
            {
                if (debug)
                {
                    cout << "La conformacion del grupo " << static_cast<unsigned char>('A' + grupo) << " no es valida, se volvera a sortear el bolillero" << endl;
                    mostrarGruposSorteados(bolillero + 1);
                    cin.get();
                    system("clear");
                }
                return -1;
            }
        }
    }
    return 1;
}

int idConfederacion(Seleccion seleccion)
{
    string confederaciones_str[CONFEDERACIONES] =
        {"UEFA", "Conmebol", "Concacaf", "AFC", "CAF", "OFC"};

    for (int i = 0; i < CONFEDERACIONES; i++)
    {
        if (confederaciones_str[i].compare(seleccion.confederacion) == 0)
        {
            return i;
        }
    }
    return -1;
}

void mostrarGruposSorteados(int bolillerosAMostrar)
{
    char grupo = 65;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < GRUPOS; i++)
    {
        cout << "GRUPO " << grupo << endl;
        for (int j = 0; j < bolillerosAMostrar; j++)
        {
            cout << left << setw(15) << paises[i][j].nombreDeEquipo;
        }
        cout << endl;
        cout << "------------------------------------------------------------" << endl;
        grupo++;
    }
    cout << endl;
}

void guardarSorteo()
{
    for (int i = 0; i < GRUPOS; i++)
    {
        FILE *f = openGrupo('A' + i, "w+b");
        for (int j = 0; j < BOLILLEROS; j++)
        {
            write<Seleccion>(f, paises[i][j]);
        }
        fclose(f);
    }
    cout << "Grupos guardados con exito." << endl;
}