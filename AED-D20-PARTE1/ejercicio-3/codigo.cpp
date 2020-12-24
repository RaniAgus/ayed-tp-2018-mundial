#include "../utils/utils.hpp"

struct Equipo
{
    char grupo;
    char nombreDeEquipo[15];
    char confederacion[10];
};

void leerEquipos(Equipo paises[]);
Equipo crearEquipo(int grupo, std::string nombreDeEquipo, std::string confederacion);

template <typename T> 
void ordenar(T arr[], int len, int (*criterio)(T, T));
int nombreAZ(Equipo e1, Equipo e2);
int confederacionAZ(Equipo e1, Equipo e2);
int grupo09(Equipo e1, Equipo e2);

void mostrarPaises(Equipo paises[]);

int main()
{
    setlocale(LC_ALL, "");

    Equipo paises[GRUPOS * BOLILLEROS];
    leerEquipos(paises);

    int menu = 0;

    do
    {
        std::cout << "1: Ordenar por grupo" << std::endl;
        std::cout << "2: Ordenar por nombre de equipo" << std::endl;
        std::cout << "3: Ordenar por confederacion" << std::endl;
        std::cout << "4: Ordenar por grupo y confederacion" << std::endl;
        std::cout << "5: Ordenar por grupo, confederacion y nombre de equipo" << std::endl;
        std::cout << "0: Salir" << std::endl;
        std::cin >> menu;

        switch (menu)
        {
        case 1:
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, grupo09);
            break;
        case 2:
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, nombreAZ);
            break;
        case 3:
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, confederacionAZ);
            break;
        case 4:
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, confederacionAZ);
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, grupo09);
            break;
        case 5:
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, nombreAZ);
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, confederacionAZ);
            ordenar<Equipo>(paises, GRUPOS * BOLILLEROS, grupo09);
            break;
        case 0:
            continue;
        default:
            system("clear");
            std::cout << "Opcion incorrecta" << std::endl;
            continue;
        }
        mostrarPaises(paises);
    } while (menu != 0);

    return 0;
}

void leerEquipos(Equipo paises[]) {
    for (int i = 0; i < GRUPOS; i++)
    {
        FILE *f = openGrupo('A' + i, "r+b");
        for (int j = 0; j < BOLILLEROS; j++)
        {
            Seleccion a = read<Seleccion>(f);
            paises[i * BOLILLEROS + j] = crearEquipo(i, a.nombreDeEquipo, a.confederacion);
        }
        fclose(f);
    }
    std::cout << "Datos cargados con éxito" << std::endl;
}

Equipo crearEquipo(int grupo, std::string nombreDeEquipo, std::string confederacion)
{
    Equipo a;
    a.grupo = 'A' + grupo;
    strcpy(a.nombreDeEquipo, nombreDeEquipo.c_str());
    strcpy(a.confederacion, confederacion.c_str());
    return a;
}

template <typename T>
void ordenar(T arr[], int len, int (*criterio)(T, T))
{
    bool ordenado = false;
    while (!ordenado)
    {
        ordenado = true;
        for (int i = 0; i < len - 1; i++)
        {
            if (criterio(arr[i], arr[i + 1]) > 0)
            {
                T aux = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = aux;
                ordenado = false;
            }
        }
    }
}

int nombreAZ(Equipo e1, Equipo e2)
{
    std::string s1 = e1.nombreDeEquipo;
    std::string s2 = e2.nombreDeEquipo;
    return s1 > s2 ? 1 : s1 < s2 ? -1 : 0;
}

int confederacionAZ(Equipo e1, Equipo e2)
{
    std::string s1 = e1.confederacion;
    std::string s2 = e2.confederacion;
    return s1 > s2 ? 1 : s1 < s2 ? -1 : 0;
}

int grupo09(Equipo e1, Equipo e2)
{
    return e1.grupo - e2.grupo;
}

void mostrarPaises(Equipo paises[])
{
    std::cout << std::left << std::setw(15) << "PAIS" << std::setw(15) << "CONFEDERACION" << "GRUPO" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    for (int i = 0; i < 32; i++)
    {
        std::cout << std::left << std::setw(15) << paises[i].nombreDeEquipo << std::setw(15) << paises[i].confederacion << paises[i].grupo << std::endl;
    }
    std::cout << std::endl;
}