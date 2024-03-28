#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Se lee el valor de cada BYTE de color de cada pixel (Red, Green, Blue) y se calcula
    // el promedio de los 3 valores. Luego se asigna ese valor promedio a los 3 bytes.
    // (El valor tiene que ser entero. Antes de asignar valor se tiene que redondear)

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Por cada pixel calcula promedio y redondea
            float average =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            average = round(average);

            // Asigna promedio a cada BYTE de color
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Se lee el valor de cada BYTE de color de cada pixel (Red, Green, Blue) y se calcula
    // el nuevo valor para cada BYTE. Esto se hace usando una formula (Sepia Formula) para cada
    // color Rojo: (0.393 * Rojo) + (0.769 * Verde) + (0.189 * Azul) Verde: (0.349 * Rojo) + (0.686
    // * Verde) + (0.168 * Azul) Azul: (0.272 * Rojo) + (0.534 * Verde) + (0.131 * Azul)

    // (El valor tiene que ser entero. Antes de asignar valor se tiene que redondear)
    // Si el resultado es mayor a 255. Se iguala a 255

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Aplica la formula para cada color
            float rojo = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) +
                         (.189 * image[i][j].rgbtBlue);
            float verde = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) +
                          (.168 * image[i][j].rgbtBlue);
            float azul = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) +
                         (.131 * image[i][j].rgbtBlue);

            // Redondea resultado de formla
            rojo = round(rojo);
            verde = round(verde);
            azul = round(azul);

            // Corregir el caso borde de que resultado sea > 255
            if (rojo > 255)
                rojo = 255;

            if (verde > 255)
                verde = 255;

            if (azul > 255)
                azul = 255;

            // Asigna nuevos valores a cada BYTE de color
            image[i][j].rgbtRed = rojo;
            image[i][j].rgbtGreen = verde;
            image[i][j].rgbtBlue = azul;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Lee cada ROW e invierte los pixeles de manera horizontal
    // usa 3 indices y caso borde para imagenes con ancho impar

    int swpRed = 0, swpGreen = 0, swpBlue = 0;

    for (int i = 0; i < height; i++)
    {
        // j avanza izq -> der; x avanza der -> izq
        for (int j = 0, x = (width - 1); j < (width / 2); j++, x--)
        {
            // Caso borde para imagenes de ancho impar
            if (j == x)
                break;

            // Hace Swap con cada BYTE de cada PIXEL de la img
            swpRed = image[i][j].rgbtRed;
            swpGreen = image[i][j].rgbtGreen;
            swpBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][x].rgbtRed;
            image[i][j].rgbtGreen = image[i][x].rgbtGreen;
            image[i][j].rgbtBlue = image[i][x].rgbtBlue;

            image[i][x].rgbtRed = swpRed;
            image[i][x].rgbtGreen = swpGreen;
            image[i][x].rgbtBlue = swpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Blur is archived using the 'Box-Blur' method.
    // Para calcular el los nuevos valores de cada BYTE de color de un Pixel
    // Se toman los valores RGB de todos los pixeles que rodean el pixel que se quiere modificar
    // (Incluye el pixel que se va a modificar) y se calcula el promedio de cada color
    // Finalmente se asigna el promedio de cada color a cada BYTE del pixel.
    // Se repite para todos los pixeles siempre usando los valores originales de la imagen
    // Caso borde: pixeles que estan en alguno de los extremos o esquinas usan menos pixeles para el
    // calculo

    // Variables para guardar los promedios
    float AvgRed = 0, AvgGreen = 0, AvgBlue = 0;
    int divisor = 0;
    RGBTRIPLE respaldo[height][width];

    // Recorre BitMap para hacer copia de la img original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            respaldo[i][j] = image[i][j];
        }
    }

    // Recorre BitMap para calcular efecto
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            AvgRed = 0;
            AvgGreen = 0;
            AvgBlue = 0;
            divisor = 0;

            // Sub-Matriz 3x3
            for (int x = (i - 1); x <= (i + 1); x++)
            {
                for (int y = (j - 1); y <= (j + 1); y++)
                {
                    // if asegura que los pixeles esten dentro del BitMap antes de recuperar valores
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        AvgRed = AvgRed + respaldo[x][y].rgbtRed;
                        AvgGreen = AvgGreen + respaldo[x][y].rgbtGreen;
                        AvgBlue = AvgBlue + respaldo[x][y].rgbtBlue;

                        divisor++;
                    }
                }
            }
            // Promedio de colores
            AvgRed = AvgRed / divisor;
            AvgGreen = AvgGreen / divisor;
            AvgBlue = AvgBlue / divisor;

            // Redondea el valor decimal a entero
            AvgRed = round(AvgRed);
            AvgGreen = round(AvgGreen);
            AvgBlue = round(AvgBlue);

            // Corregir el caso borde de que resultado sea > 255
            if (AvgRed > 255)
                AvgRed = 255;

            if (AvgGreen > 255)
                AvgGreen = 255;

            if (AvgBlue > 255)
                AvgBlue = 255;

            // AvgRed = (int) AvgRed;
            // AvgGreen = (int) AvgGreen;
            // AvgBlue = (int) AvgBlue;

            // Asigna promedio de cada color a bytes de pixel
            image[i][j].rgbtRed = AvgRed;
            image[i][j].rgbtGreen = AvgGreen;
            image[i][j].rgbtBlue = AvgBlue;
        }
    }

    return;
}
