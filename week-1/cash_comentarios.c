// 11/01/24 sady
// Greedy Algorithm

#include <cs50.h>
#include <stdio.h>

int main()
{
    // cents = 25, 10, 5, 1
    int cents;
    int x, y;

    // Usuario ingresa monto
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // printf("Calcula con monedas de (25)\n");
    y = (cents % 25);
    x = cents / 25;

    // printf("cantidad de monedas de cambio: %i\n", x);

    if ((cents % 25) > 0)
    {
        // printf("falta cambio --> AGREGA monedas de (10)\n");

        y = y % 25;
        x = x + (y / 10);
        printf("%i\n", x);

        // printf("nuevo valor de cambio: %i\n", x);

        if ((y % 10) > 0)
        {
            // printf("falta cambio --> AGREGA monedas de (5)\n");

            y = y % 10;
            x = x + (y / 5);
            printf("%i\n", x);

            // printf("nuevo valor de cambio: %i\n", x);

            if ((y % 5) > 0)
            {
                // printf("falta cambio --> AGREGA monedas de (1)\n");

                y = y % 5;
                x = x + (y / 1);
                printf("%i\n", x);

                // printf("nuevo valor de cambio (y ultimo): %i\n", x);
            }
        }
    }
    else
    {
        // printf("NO falta cambio\n");

        // printf("se usan %i monedas\n", x);

        printf("%i\n", x);
    }

    return 0;
}
