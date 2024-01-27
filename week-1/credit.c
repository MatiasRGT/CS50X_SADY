// 11/01/24 sady
// Luhn’s Algorithm

#include <cs50.h>
#include <stdio.h>

int create_array(long int card, int card_arr[]);
int check_length(long int card);
int luhn(int arr[]);
int check_bank(long int card);

int main()
{
    int x;
    long int card;
    int card_arr[17];

    // Usuario ingresa numero de tarjeta.
    card = get_long("Number: ");

    // Se pasa cada digito del numero a un array
    create_array(card, card_arr);

    // Comprueba que numero sea valido con el algoritmo de Luhn
    if (luhn(card_arr) == 1)
    {
        printf("INVALID\n");
    }
    else
    {
        // Entrar a ELSE significa que el numero paso el algoritmo de Luhn correctamente.
        check_bank(card);
    }

    return 0;
}

int create_array(long int card, int card_arr[])
{
    int a;
    int i;

    // Avanza por el numero de derecha a izquierda. Pone los numeros en un array

    for (i = 15; i >= 0; i--)
    {
        a = card % 10;

        card_arr[i] = a;
        card = card / 10;
    }

    return 0;
}

int check_length(long int card)
{
    int contador = 1;
    long int num = card;

    // Calcula largo de numero ingresado como tarjeta, Retorna el largo

    while (num >= 10)
    {
        num = num / 10;
        contador++;
    }

    return contador;
}

int luhn(int arr[])
{
    int i;
    int a = 0, b, c = 0;

    // 1234 1234 1234 1234
    // 0123 4567 89AB CDEF

    for (i = 14; i >= 0; i = i - 2)
    {

        b = arr[i];
        // Multiplica numero por medio (desde el penultimo hasta el primero) por 2 y suma sus valores
        b = b * 2;
        a = a + (b % 10);
        b = b / 10;
        a = a + b;
    }

    for (i = 15; i > 0; i = i - 2)
    {

        b = arr[i];
        // Suma numero por medio (Lo que no se sumaron en el ciclo anterior)
        c = c + b;
    }

    a = a + c;

    if (a % 10 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int check_bank(long int card)
{
    long int num = card;
    int primero = 0, segundo = 0, c = 0, LARGO;

    // 1234 1234 1234 1234
    // 0123 4567 89AB CDEF

    // Genera largo de numero de tarejeta
    LARGO = check_length(num);

    // Metodo con int y ciclo
    // Se guardan los primeros 2 digitos del numero de tarjeta en PRIMERO y SEGUNDO

    while (num >= 10)
    {
        segundo = num % 10;
        num = num / 10;
    }

    primero = num;

    if (primero == 4)
    {

        if (LARGO == 13 || LARGO == 16)
        {
            printf("VISA\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else if (primero == 3)
    {
        if (segundo == 4 || segundo == 7)
        {
            if (LARGO == 15)
            {
                printf("AMEX\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else if (primero == 5)
    {
        if (segundo >= 1 && segundo <= 5)
        {
            if (LARGO == 16)
            {
                printf("MASTERCARD\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else if (primero != 4 && primero != 5 && primero != 3)
    {
        printf("INVALID\n");
        return 0;
    }

    return 0;
}
