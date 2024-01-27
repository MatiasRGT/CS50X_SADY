// Sady Guzman 26/01/24
// encryption of message

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    string input, str_argv;
    char str_cifrado[25] = " ";
    char input_arr[25] = " ";
    int i, argv_len = 0;
    int k; // KEY
    int arr_num[4];

    // Comprueba que el usuario solo ingrese un argumento al ejecutar comando
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./caesar key\n"); // Error si hay menos o mas de 1 argumento
        return 1;
    }

    // Comprueba que el argumento sea un numero
    // Calcula largo del argumento
    str_argv = argv[1];
    for (i = 0; str_argv[i] != '\0'; i++)
    {
        argv_len++;
    }

    // Cantidad de digitos en argumento
    // printf("len det de argv %i\n", argv_len);

    // Usa largo del argumento para iterar por el array, preguntando si cada caracter es un DIGITO valido
    for (i = 0; i < argv_len; i++)
    {
        if (isdigit(str_argv[i]) == 0)
        {
            printf("Usage: ./caesar key\n"); // Error si argumento NO es un numero
            return 1;
        }
    }

    // Se controla caso en que usuario ingresa numero > 26 para K
    k = atoi(str_argv);
    k = k % 26;

    // User writes text
    input = get_string("plaintext: ");

    for (i = 0; i < strlen(input); i++)
    {
        input_arr[i] = input[i];
    }

    // Se cifra el input del usuario
    for (i = 0; i < strlen(input); i++)
    {
        // CASO MINUSCULAS
        if ((((input_arr[i])) >= 97) && (((input_arr[i])) <= 122))
        {
            if (((input_arr[i]) + k) > 122)
            {
                str_cifrado[i] = 96 + (k - (122 - input_arr[i]));
            }
            else
            {
                str_cifrado[i] = ((input_arr[i]) + k);
            }
        }
        // CASO MAYUSCULAS
        else if ((((input_arr[i])) >= 65) && (((input_arr[i])) <= 90))
        {
            if (((input_arr[i]) + k) > 90)
            {
                str_cifrado[i] = 64 + (k - (90 - input_arr[i]));
            }
            else
            {
                str_cifrado[i] = ((input_arr[i]) + k);
            }
        }
        // CASO SIMBOLOS
        else
        {
            str_cifrado[i] = (input_arr[i]);
        }
    }

    // Resultado del cifrado
    printf("ciphertext: %s\n", str_cifrado);

    return 0;
}
