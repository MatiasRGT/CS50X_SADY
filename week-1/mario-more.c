// 11/01/24 sady

#include <cs50.h>
#include <stdio.h>

int main()
{
    int a, i, x, y, flag = 0;
    int height;

    // Elige altura
    while (flag != 1)
    {
        // usuario ingresa altura
        height = get_int("Height: ");

        // comprueba altura correcta
        if (height > 0 && height < 9)
        {
            flag = 1;
        }
    }

    // Dibuja piramide
    for (i = 0; i < height; i++)
    {
        // separa de la izquierda los ladrillos
        for (x = (height - (i + 1)); x > 0; x--)
        {
            printf(" ");
        }

        // imprime ladrillos izquierda
        for (y = (i + 1); y > 0; y--)
        {
            printf("#");
        }

        // Espacio entre triangulos
        printf("  ");

        // imprime ladrillos derecha
        for (y = (height - (height - (i + 1))); y > 0; y--)
        {
            printf("#");
        }

        printf("\n");
    }

    return 0;
}
