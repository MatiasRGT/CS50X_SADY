// Sady Guzman 23/01/24
// Scrabble

#include <cs50.h>
#include <stdio.h>
#include <string.h>

void check_score(char *, char *, int abc_minus[], int abc_mayus[], int abc_score[]);
void ini_mayus(int arr[]);
void ini_minus(int arr[]);
void print_arr(int arr[]);
void ini_score(int arr[]);

int main(void)
{
    int abc_mayus[25];
    int abc_minus[25];
    int abc_score[25];

    string player1_word;
    string player2_word;

    // Llena los abecedarios mayuscula y miniscula. Tambien el array de Pts.
    ini_mayus(abc_mayus);
    ini_minus(abc_minus);
    ini_score(abc_score);

    // Visualiza los contenidos de los arreglos
    // print_arr(abc_mayus);
    // print_arr(abc_minus);
    // print_arr(abc_score);


    player1_word = get_string("Player 1: ");
    player2_word = get_string("Player 2: ");

    check_score(player1_word, player2_word, abc_minus, abc_mayus, abc_score);


    return 0;
}


void check_score(char *p1, char *p2, int abc_minus[], int abc_mayus[], int abc_score[])
{
    int i,j, flag = 0;
    int score_p1 = 0, score_p2 = 0;
    int len1, len2;

    len1 = strlen(p1);
    len2 = strlen(p2);


    // Calcula los pts de Player1
    for(i = 0; i <= len1; i++)
    {
        for(j = 0; j <= 25; j++)
        {
            // DEBUG
            // printf("p1.i = %i - %c\n", p1[i], p1[i]);
            // printf("abc minus = %i - %c\n", abc_minus[i], abc_minus[j]);
            // printf("abc mayus = %i - %c\n", abc_mayus[i], abc_mayus[j]);
            // printf("<---------------------->\n\n");
            // DEBUG

            if (p1[i] == abc_minus[j] || p1[i] == abc_mayus[j])
            {
                score_p1 += abc_score[j];
            }
        }

    }


    // Calcula los pts de Player2
    for(i = 0; i <= len2; i++)
    {
        for(j = 0; j <= 25; j++)
        {
            // DEBUG
            // printf("p2.i = %i - %c\n", p2[i], p2[i]);
            // printf("abc minus = %i - %c\n", abc_minus[i], abc_minus[j]);
            // printf("abc mayus = %i - %c\n", abc_mayus[i], abc_mayus[j]);
            // printf("<---------------------->\n\n");
            // DEBUG

            if (p2[i] == abc_minus[j] || p2[i] == abc_mayus[j])
            {
                score_p2 += abc_score[j];
            }
        }
    }


  //  printf("Valor de P1: %i \n", score_p1);
  //  printf("Valor de P2: %i \n", score_p2);

    // Decide si gana Player 1 o Player 2. Si no gana nadie hay empate
    if(score_p1 > score_p2)
    {
        printf("Player 1 wins!\n");
    }
    else if(score_p1 < score_p2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
    printf("Tie!\n");
    }

}

void ini_mayus(int arr[])
{
    arr[0] = 'A';
    arr[1] = 'B';
    arr[2] = 'C';
    arr[3] = 'D';
    arr[4] = 'E';
    arr[5] = 'F';
    arr[6] = 'G';
    arr[7] = 'H';
    arr[8] = 'I';
    arr[9] = 'J';
    arr[10] = 'K';
    arr[11] = 'L';
    arr[12] = 'M';
    arr[13] = 'N';
    arr[14] = 'O';
    arr[15] = 'P';
    arr[16] = 'Q';
    arr[17] = 'R';
    arr[18] = 'S';
    arr[19] = 'T';
    arr[20] = 'U';
    arr[21] = 'V';
    arr[22] = 'W';
    arr[23] = 'X';
    arr[24] = 'Y';
    arr[25] = 'Z';

}


void ini_minus(int arr[])
{
    arr[0] = 'a';
    arr[1] = 'b';
    arr[2] = 'c';
    arr[3] = 'd';
    arr[4] = 'e';
    arr[5] = 'f';
    arr[6] = 'g';
    arr[7] = 'h';
    arr[8] = 'i';
    arr[9] = 'j';
    arr[10] = 'k';
    arr[11] = 'l';
    arr[12] = 'm';
    arr[13] = 'n';
    arr[14] = 'o';
    arr[15] = 'p';
    arr[16] = 'q';
    arr[17] = 'r';
    arr[18] = 's';
    arr[19] = 't';
    arr[20] = 'u';
    arr[21] = 'v';
    arr[22] = 'w';
    arr[23] = 'x';
    arr[24] = 'y';
    arr[25] = 'z';

}


void ini_score(int arr[])
{
    arr[0] = 1;
    arr[1] = 3;
    arr[2] = 3;
    arr[3] = 2;
    arr[4] = 1;
    arr[5] = 4;
    arr[6] = 2;
    arr[7] = 4;
    arr[8] = 1;
    arr[9] = 8;
    arr[10] = 5;
    arr[11] = 1;
    arr[12] = 3;
    arr[13] = 1;
    arr[14] = 1;
    arr[15] = 3;
    arr[16] = 10;
    arr[17] = 1;
    arr[18] = 1;
    arr[19] = 1;
    arr[20] = 1;
    arr[21] = 4;
    arr[22] = 4;
    arr[23] = 8;
    arr[24] = 4;
    arr[25] = 10;

}

void print_arr(int arr[])
{

    int i;

    printf("[* Print Array *] ... \n");

    for(i = 0; i < 26; i++)
    {
        printf("%i   ", arr[i]);
    }
    printf("\n");

    for(i = 0; i < 26; i++)
    {
        printf("%c   ", arr[i]);
    }
    printf("\n");

}
