// Sady Guzman 23/01/24
// readability
// Coleman-Liau formula -> index = 0.0588 * L - 0.296 * S - 15.8
// where L is the average number of letters per 100 words in the text.
// and S is the average number of sentences per 100 words in the text.

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void print_arr(int arr[]);
int count_letters(string input);
int count_spaces(string input);
int count_punctuations(string input);

int main(void)
{
    /*
        FIND: ammount of letters, words, sentences.
        letters -> ctype.h
        words -> spaces + 1
        sentences -> '.' '!'
    */

    float spaces, punctuations, sentences, words, letters;
    float index = 0, L = 0, S = 0; // Coleman-Liau formula
    string input;

    // User writes text
    input = get_string("Text: ");

    // Obtiene letras
    letters = count_letters(input);

    // Obtiene espacios
    spaces = count_spaces(input);

    // Obtiene puntuaciones
    punctuations = count_punctuations(input);

    // Obtiene palabras
    words = spaces + 1;

    // Obtiene sentencias
    sentences = punctuations;

    // Reglas de 3 para L y S
    L = (letters / words) * 100;
    S = (sentences / words) * 100;

    // Coleman-Liau formula
    index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);

    // printf("[****] Grado antes de redondeo: %f\n", index);

    if (index < 1)
    {
        // Resultado. String es menos complejo que grado 1
        index = 1;
        printf("Before Grade %0.f\n", index);
    }
    else if (index > 16)
    {
        // Resultado. String es mas complejo que grado 16
        index = 16;
        printf("Grade %0.f+\n", index);
    }
    else
    {
        // Resultado esta entre grado 1 y 16
        printf("Grade %0.f\n", index);
    }

    return 0;
}

int count_letters(string input)
{
    int letters = 0;
    int i;

    for (i = 0; i <= strlen(input); i++)
    {
        if (isalpha(input[i]) != 0)
        {
            letters++;
        }
    }

    return letters;
}

int count_spaces(string input)
{
    int spaces = 0;
    int i;

    for (i = 0; i <= strlen(input); i++)
    {
        if (input[i] == ' ')
        {
            spaces++;
        }
    }

    return spaces;
}

int count_punctuations(string input)
{
    int punctuation = 0;
    int i, bluff = 0;

    for (i = 0; i <= strlen(input); i++)
    {
        if ((input[i] == '!' || input[i] == '.' || input[i] == '?') && (input[i + 1] != '.'))
        {

            punctuation++;
        }
        else
        {
            bluff++;
        }
    }

    return punctuation;
}
