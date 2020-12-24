#ifndef UTILS_H_
#define UTILS_H_

    #include <iostream>
    #include <string.h>
    #include <wchar.h>
    #include <locale.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <iomanip>

    #define GRUPOS 8
    #define BOLILLEROS 4
    #define CONFEDERACIONES 6

    struct Seleccion
    {
        int bolillero;
        char nombreDeEquipo[15];
        char confederacion[10];
    };

    FILE *open(std::string path, const char *modo)
    {
        FILE *f = fopen(path.c_str(), modo);
        if (f == NULL)
        {
            std::cout << "ERROR: No se pudo abrir el archivo " << path << std::endl;
            exit(-1);
        }

        return f;
    }

    FILE *openGrupo(char grupo, const char *modo)
    {
        std::string pathInicial = "../Grupo ";
        std::string formato = ".dat";
        return open(pathInicial + grupo + formato, modo);
    }

    template <typename T>
    void write(FILE *f, T v)
    {
        fwrite(&v, sizeof(T), 1, f);
        return;
    }

    template <typename T>
    T read(FILE *f)
    {
        T buff;
        fread(&buff, sizeof(T), 1, f);
        return buff;
    }

#endif