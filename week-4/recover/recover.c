// Sady Guzman Marzo 2024

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void iterar_nombre(int *uni, int *dec, int *cen);
int es_nuevo_jpeg(uint8_t buffer[]);

#define BLOCK_SIZE 512 // used for buffer

int main(int argc, char *argv[])
{

    // Program only allows a single command-line argument, (file-name)
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card (the file is specified in the command-line argument)
    // Verifies that the card is correctly opened
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // Buffer de 512 bytes para guardar para bloque de un archivo tipo JPEG
    uint8_t buffer[BLOCK_SIZE];

    // While there's still data left to read from the memory card

    // Each new JPEG file should be named in order of creation, starting at '000.jpeg'
    // Variables que iteran para nombrar cada nuevo archivo
    int num_nombre_uni = 0;
    int num_nombre_dec = 0;
    int num_nombre_cen = 0;

    char rcv_img[10] = "000.jpg"; // recovered_image
    int es_primer_jpeg = 1;

    FILE *fp = NULL;

    // lee hasta el final de card
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Comprueba los primeros 4 bytes. Busca SIGNATURE de jpeg
        if (es_nuevo_jpeg(buffer) == 1)
        {
            if (es_primer_jpeg == 1)
            {
                // Solo entra a este caso 1 vez
                es_primer_jpeg = 0;

                // Creates a new file to store the photo
                fp = fopen(rcv_img, "w"); // <--------- write en vez de append
                fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, fp);
            }
            else
            {
                // No es el primer jpg
                fclose(fp);

                // Nuevo nombre para el siguiente archivo
                iterar_nombre(&num_nombre_uni, &num_nombre_dec, &num_nombre_cen);
                sprintf(rcv_img, "%i%i%i.jpg", num_nombre_cen, num_nombre_dec, num_nombre_uni);

                // Creates a new file to store the photo
                fp = fopen(rcv_img, "w"); // <--------- write en vez de append
                fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, fp);
            }
        }
        else if (es_primer_jpeg == 0)
        {
            // El archivo JPEG usa mas de un bloque de 512 BYTES
            // Continua escribiendo en el mismo JPEG
            fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, fp);
        }
    }

    // Libera los punteros antes de terminar
    fclose(fp);
    fclose(card);
}

void iterar_nombre(int *uni, int *dec, int *cen)
{
    // Funcion que aumenta en una unidad el nombre
    // de string que es nombre de un archivo.
    // Limite 999

    // Aumenta unidad
    *uni = *uni + 1;

    if (*uni == 10)
    {
        // Aumenta decena
        *uni = 0;
        *dec = *dec + 1;

        if (*dec == 10)
        {
            // Aumenta centena
            *cen = *cen + 1;
            *dec = 0;
            *uni = 0;
        }
    }
}

int es_nuevo_jpeg(uint8_t buffer[])
{
    // Comprueba los primeros 4 bytes de un buffer
    // Busca signature de archivo JPEG

    if (buffer[0] == 0xff)
    {
        if (buffer[1] == 0xd8)
        {
            if (buffer[2] == 0xff)
            {
                if ((buffer[3] & 0xf0) == 0xe0) // bit shift arithmetic
                {
                    return 1;
                }
            }
        }
    }

    // Los primeros 4 bytes no coinciden
    return 0;
}
