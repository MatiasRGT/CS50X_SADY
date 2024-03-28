// Sady Guzman Marzo 2024

// TESTS name iteration process. from '000.jpeg' to '999.jpeg'
// uso: problem set week 4 CS50X 2024: Recover.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Variables que iteran para nombrar cada nuevo archivo
    int num_nombre_uni = 0;
    int num_nombre_dec = 0;
    int num_nombre_cen = 0;
    char nombre[10] = "000.jpeg";

    // Each new JPEG file should be named in order of creation, starting at '000.jpeg'
    while (num_nombre_cen < 5) // limita centena
    {
        printf("%s\n", nombre);

        // Itera el nombre del siguiente archivo, ++
        num_nombre_uni++;
        if (num_nombre_uni == 10)
        {   
            num_nombre_uni = 0;
            num_nombre_dec++;

            if (num_nombre_dec == 10)
            {
                num_nombre_cen++;
                num_nombre_uni = 0;
                num_nombre_dec = 0;
            }
        }

        sprintf(nombre,"%i%i%i.jpeg", num_nombre_cen, num_nombre_dec, num_nombre_uni);
    }

    return 0;
}
