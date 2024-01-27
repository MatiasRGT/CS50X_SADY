// 11/01/24 sady

#include <cs50.h>
#include <stdio.h>

int main()
{
    int i, x, y, flag = 0;
    int height;

    while (flag != 1)
    {
        // usuario ingresa altura
        height = get_int("Height: ");

        // comprueba altura correcta
        if (height > 0)
        {
            flag = 1;
        }
    }

    for (i = 0; i < height; i++)
    {
        // separa de la izquierda
        for (x = (height - (i + 1)); x > 0; x--)
        {
            printf(" ");
        }

        // imprime ladrillos
        for (y = (i + 1); y > 0; y--)
        {
            printf("#");
        }

        // pasa a siguiente linea
        printf("\n");
    }

    return 0;
}
