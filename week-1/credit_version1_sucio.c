// 11/01/24 sady
// Luhn’s Algorithm

#include <cs50.h>
#include <stdio.h>

int create_array(long int card, int card_arr[]);
void print_arr(int arr[]);
void ini_arr(int arr[]);
int check_length(int arr[]);
void test();
int luhn(int arr[]);
void check_bank(int arr[]);

int main()
{
    int x;
    long int card;
    int card_arr[17];

    printf("\n\n\n --------------> START <------------------- \n\n\n");


  //  test();


    ini_arr(card_arr);
    printf("[*] MOSTRANDO ARRAY EN MAIN (Ante-INPUT): \n");
    print_arr(card_arr);

    // Usuario ingresa numero de tarjeta.
    card = get_long("Number: ");
    // Se pasa cada digito del numero a un array
    create_array(card, card_arr);

    printf("[*] MOSTRANDO ARRAY EN MAIN (Post-INPUT): \n");
    print_arr(card_arr);

    // Comprueba que el numero sea valido en longitud
    // Por ahora no se comprueba longitud de numero
/*
    if (check_length(card_arr) == 1)
    {
        printf("INVALID\n");
    }
*/


    // Comprueba que numero sea valido con el algoritmo de Luhn
    // func Luhn
    if (luhn(card_arr) == 1)
    {
        printf("INVALID MAIN LUHN\n");
    }
    else
    {
        printf("VALID POR AHORA\n");
        // Comprueba de que banco es la tarjeta. Si no es de ninguno retorna INVALID
        check_bank(card_arr);


    }


    // Detecta de que tipo es la tarjeta usando primeros digitos
    // func first-two-digits

    // Retorna resultado de programa
    printf("---FIN---\n");

    return 0;
}


int create_array(long int card, int card_arr[]){
    int a;
    int i;

    printf("card ingresada: %li \n", card);

    for (i = 15; i >= 0; i--)
    {
        printf("[*] Entra en for\n");
        a = card % 10;

        printf("num actual en a: %i \n", a);
        //if (a == 0)
       // {
        //    break;
        //}

        card_arr[i] = a;
        print_arr(card_arr);
        card = card / 10;
    }

    printf("[*] SALE FOR");

    return 0;
}

void print_arr(int arr[]){
    int i;

    printf("[*] Nums almacenados en ARRAY: ");

    for (i = 0; i < 16; i++)
    {
        printf("%i", arr[i]);
    }

    printf("\n\n\n");
}

void ini_arr(int arr[]){
    int i;

    //printf("[*] INICIA ARRAY\n: ");

    // Llena array de '-1' para poder saber cual espacios estan vacios
    // Se usa para saber si el numero ingresado por el usuario cumple con el largo necesario
    // Pero eso no se comprueba aqui. Se comprueba en 'check_length()'.
    for (i = 0; i < 16; i++)
    {
        arr[i] = -1;
    }
}

int check_length(int arr[]){
    int i;

   printf("[*] Comprobando largo de numero ingresado...\n");

   // Busca '-1' en alguna pos del array para saber si todos los espacios se usaron correctamente o no.
   // TODO ver que hacer en caso de que el numero ingresado sea mas largo de lo que debe ser... (Esta funcion solo comprueba que no sea mas corto).
    for (i = 0; i < 16; i++)
    {
        if (arr[i] == -1)
        {
            // num es mas corto que 16 digitos.
            return 1;
        }
    }
    // Todo OK
    return 0;
}


int luhn(int arr[]){
    int i;
    int a = 0, b, c = 0;

   printf("\n[*] START LUHN'S...\n");

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

    printf("[*] El valor de la suma de cada digito por medio * 2 es: %i \n", a);


    for (i = 15; i > 0; i = i - 2)
    {

        b = arr[i];
        // Suma numero por medio (Lo que no se sumaron en el ciclo anterior)
        c = c + b;
    }

    a = a + c;

    printf("[*] El valor de la suma de TODOS los digitos restantes es: %i \n", a);

    if (a % 10 == 0)
    {
        printf("[*] El modulo 10 del resultado es 0. Por lo tanto el algoritmo de Luhn se cumple.\n");
        return 0;
    }
    else
    {
        printf("[*] El modulo 10 del resultado es != 0. Por lo tanto el algoritmo de Luhn NO se cumple.\n");
        return 1;
    }

}


void check_bank(int arr[]){
    int i;
    int a = 0, b, c = 0;

   printf("\n[*] CHECK BANK...\n");

    // 1234 1234 1234 1234
    // 0123 4567 89AB CDEF

    if (arr[0] == 4){
        printf("VISA\n");
    }
    else if (arr[0] == 3)
    {
        if (arr[1] == 4 || arr[1] == 7)
            printf("AMEX\n");
    }
    else if (arr[0] == 5)
    {
        if (arr[1] >= 1 && arr[1] <= 5)
            printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID CHECK BANK\n");
    }

}

void test(){


    printf(" Todos los numeros separados son: ");

    int i = 4;
    int j = 18;
    int a = 0;
    int b = 0;

    a = i % 10;
    i = i / 10;
    a = a + i;

    printf("valor de los digitos de i: %i \n", a);

    b = j % 10;
    j = j / 10;
    b = b + j;

    printf("valor de los digitos de j: %i \n", b);


    printf(" FIN \n\n\n");

}
