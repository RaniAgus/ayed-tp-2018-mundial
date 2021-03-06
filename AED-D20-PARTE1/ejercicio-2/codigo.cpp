#include "../utils/utils.hpp"

bool debug = false;

Seleccion paises[GRUPOS][BOLILLEROS];

void obtenerSelecciones();
void sortearBolillero(int bolillero);
bool esAnfitrion(int bolillero, int grupo);
void intercambiarSelecciones(int grupo1, int grupo2, int bolillero);
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
            std::cout << "Modo debug" << std::endl;
        }
    }

    setlocale(LC_ALL, "");
    srand(time(NULL));

    obtenerSelecciones();
    std::cout << "Pulse cualquier tecla para sortear la fase de grupos." << std::endl;
    std::cin.get();

    do
    {
        system("clear");
        for (int i = 0; i < BOLILLEROS; i++)
        {
            sortearBolillero(i);
        }
        std::cout << "FASE DE GRUPOS SORTEADA" << std::endl;
        mostrarGruposSorteados(BOLILLEROS);
        std::cout << "Ingresa enter para guardar y salir. Ingresa cualquier caracter para volver a sortear." << std::endl;
    } while (std::cin.get() != '\n');

    guardarSorteo();

    return 0;
}

/**
* @NAME obtenerSelecciones
* @DESC Rellena la matriz global de países leyéndolos desde el archivo de entrada. 
* Asume que primero se leerá al anfitrión (Rusia) y luego a todos los equipos 
* restantes ordenados por ranking FIFA.
*/
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

/**
* @NAME sortearBolillero
* @DESC Dado un número de bolillero (0-3), ordena los equipos correspondientes
* bajo el algoritmo selección. El criterio de selección es un número aleatorio. 
*/
void sortearBolillero(int bolillero)
{
    do
    {
        for (int grupoASortear = 0; grupoASortear < GRUPOS; grupoASortear++)
        {
            if (!esAnfitrion(bolillero, grupoASortear))
            {
                int equipoElegido = rand() % (GRUPOS - grupoASortear) + grupoASortear;
                intercambiarSelecciones(grupoASortear, equipoElegido, bolillero);
            }
        }
    } while (verificarConfederaciones(bolillero + 1) < 0);
    std::cout << "BOLILLERO " << bolillero + 1 << " SORTEADO" << std::endl;
    mostrarGruposSorteados(bolillero + 1);
    std::cin.get();
    system("clear");
}

/**
* @NAME esAnfitrion
* @DESC Devuelve true si el bolillero a sortear es la cabeza de serie del
* grupo A, para así omitirlo.
*/
bool esAnfitrion(int bolillero, int grupo)
{
    return bolillero == 0 && grupo == 0;
}

/**
* @NAME intercambiarSelecciones
* @DESC Dados dos grupos de un mismo bolillero, los intercambia dentro de
* la matriz.
*/
void intercambiarSelecciones(int grupo1, int grupo2, int bolillero)
{
    Seleccion temp = paises[grupo1][bolillero];
    paises[grupo1][bolillero] = paises[grupo2][bolillero];
    paises[grupo2][bolillero] = temp;
}

/**
* @NAME verificarConfederaciones
* @DESC Dada una cantidad de bolilleros sorteados, verifica que todos los
* grupos (filas) cumplan con el límite de equipos de una misma confederación
* en él.
*/
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
                    std::cout << "La conformacion del grupo " << static_cast<unsigned char>('A' + grupo) << " no es valida, se volvera a sortear el bolillero" << std::endl;
                    mostrarGruposSorteados(bolillero + 1);
                    std::cin.get();
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
    std::string confederaciones_str[CONFEDERACIONES] =
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

/**
* @NAME mostrarGruposSorteados
* @DESC Dada una cantidad de bolilleros a mostrar, imprime por pantalla la conformación 
* de los grupos en la matriz hasta esa cantidad
*/
void mostrarGruposSorteados(int bolillerosAMostrar)
{
    char grupo = 65;
    std::cout << "------------------------------------------------------------" << std::endl;
    for (int i = 0; i < GRUPOS; i++)
    {
        std::cout << "GRUPO " << grupo << std::endl;
        for (int j = 0; j < bolillerosAMostrar; j++)
        {
            std::cout << std::left << std::setw(15) << paises[i][j].nombreDeEquipo;
        }
        std::cout << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        grupo++;
    }
    std::cout << std::endl;
}

/**
* @NAME guardarSorteo
* @DESC Guarda en un archivo por grupo la conformación de cada uno según la matriz
* global de países.
*/
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
    std::cout << "Grupos guardados con exito." << std::endl;
}