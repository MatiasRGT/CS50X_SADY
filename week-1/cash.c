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

    // Siempre hace la primera division
    y = (cents % 25);
    x = cents / 25;

    // comprueba resultado 1ra vez
    if ((cents % 25) > 0)
    {
        y = y % 25;
        x = x + (y / 10);
        printf("%i\n", x); // Resultado

        // comprueba resultado 2da vez
        if ((y % 10) > 0)
        {
            y = y % 10;
            x = x + (y / 5);
            printf("%i\n", x); // Resultado

            // comprueba resultado 3ra vez
            if ((y % 5) > 0)
            {
                y = y % 5;
                x = x + (y / 1);
                printf("%i\n", x); // Resultado
            }
        }
    }
    else
    {
        printf("%i\n", x); // Resultado
    }

    return 0;
}
