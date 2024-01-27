// 11/01/24 sady
// Luhn’s Algorithm

#include <cs50.h>
#include <stdio.h>

int create_array(long int card, int card_arr[]);
void print_arr(int arr[]);
void ini_arr(int arr[]);
int check_length(long int card);
void test();
int luhn(int arr[]);
int check_bank(long int card);

int main()
{
    int x;
    long int card;
    int card_arr[17];

  //  printf("\n\n\n --------------> START <------------------- \n\n\n");


  //  test();


    ini_arr(card_arr);
   // printf("[*] MOSTRANDO ARRAY EN MAIN (Ante-INPUT): \n");
    //print_arr(card_arr);

    // Usuario ingresa numero de tarjeta.
    card = get_long("Number: ");
    // Se pasa cada digito del numero a un array
    create_array(card, card_arr);

   // printf("[*] MOSTRANDO ARRAY EN MAIN (Post-INPUT): \n");
    //print_arr(card_arr);

    // Comprueba que el numero sea valido en longitud
    // Por ahora no se comprueba longitud de numero



    // Comprueba que numero sea valido con el algoritmo de Luhn
    // func Luhn
    if (luhn(card_arr) == 1)
    {
        printf("INVALID\n");
    }
    else
    {
        //printf("VALID POR AHORA\n");
        // Comprueba de que banco es la tarjeta. Si no es de ninguno retorna INVALID
        //check_bank(card_arr);
       // printf("[MAIN] El valor de CARD es: %li \n",  card);
        check_bank(card);


    }



    // Retorna resultado de programa
   // printf("---FIN---\n");

    return 0;
}


int create_array(long int card, int card_arr[]){
    int a;
    int i;

    //printf("card ingresada: %li \n", card);

    for (i = 15; i >= 0; i--)
    {
       // printf("[*] Entra en for\n");
        a = card % 10;

       // printf("num actual en a: %i \n", a);
        //if (a == 0)
       // {
        //    break;
        //}

        card_arr[i] = a;
        //print_arr(card_arr);
        card = card / 10;
    }

    //printf("[*] SALE FOR");

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

int check_length(long int card){
    int contador = 1;
    long int num = card;

  // printf("[*] Comprobando largo de numero ingresado...\n");
    // Calcula largo de numero ingresado como tarjeta, Retorna el largo

    while(num >= 10)
    {
        num = num / 10;
        contador++;
    }

    return contador;
}


int luhn(int arr[]){
    int i;
    int a = 0, b, c = 0;

   //printf("\n[*] START LUHN'S...\n");

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

    //printf("[*] El valor de la suma de cada digito por medio * 2 es: %i \n", a);


    for (i = 15; i > 0; i = i - 2)
    {

        b = arr[i];
        // Suma numero por medio (Lo que no se sumaron en el ciclo anterior)
        c = c + b;
    }

    a = a + c;

   // printf("[*] El valor de la suma de TODOS los digitos restantes es: %i \n", a);

    if (a % 10 == 0)
    {
       // printf("[*] El modulo 10 del resultado es 0. Por lo tanto el algoritmo de Luhn se cumple.\n");
        return 0;
    }
    else
    {
        //printf("[*] El modulo 10 del resultado es != 0. Por lo tanto el algoritmo de Luhn NO se cumple.\n");
        return 1;
    }

}


int check_bank(long int card){
    long int num = card;
    int primero = 0, segundo = 0, c = 0, LARGO;

   //printf("\n[*] CHECK BANK...\n");

    // 1234 1234 1234 1234
    // 0123 4567 89AB CDEF

   // printf("[*checkbank*] El valor de num es: %li \n", num);

   // Genera largo de numero de tarejeta
   LARGO = check_length(num);
  // printf("[*Checkbank*] El valor de LARGO es: %i \n", LARGO);

    // Metodo con int y ciclo

    while(num >= 10)
    {
        segundo = num % 10;
        num = num / 10;
    }

    primero = num;

   // printf("[*CheckBank*] El primer y segundo digito son: %i %i \n", primero, segundo);
   // printf("[*CheckBank*] El numero de card es: %li \n", card);



    if (primero == 4){

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
        if (segundo == 4 || segundo == 7){
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
        if (segundo >= 1 && segundo <= 5){
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
