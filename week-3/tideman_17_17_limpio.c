#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;


// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

void swap(int *i, int *j);           // Usado en sort_pairs -- Sady
int encuentra(int col, int obj);              // Usado en lock_pairs -- Sady

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n"); // Salta linea entre cada papeleta
    }



    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    /*
        * Checks if users name is VALID
        * Must collect voters preferences into array 'ranks[]'.
            ranks[i] is the index of the candidate who is the *i'th* preference for the voter
        * int rank -> j
        * looks for the [i] candidate in the array of candidates, And uses their POS to update the arr RANKS[].
    */

    // busca en array de candidatos si el nombre ingresado es valido.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Nombre existe -> Se agrega a arreglo RANKS[] en pos j->(rank)
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    /*
     * Updates GLOBAL PREFERENCES[][] with the information in RANKS[] for each voter
     * preferences[i][j] represents the number of voters who prefer cand [i] over cand [j]
     */

    for (int i = 0; i < ((candidate_count) -1); i++)
    {
        for (int k = (i + 1); k < (candidate_count); k++)
        {
            int temp_crs_row = ranks[i];
            int temp_crs_col = ranks[k];

            preferences[temp_crs_row][temp_crs_col]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    /*
        - Uses Struct Pairs
        - Checks PREFERED matrix and makes comparisons for each pair of candidates.
        - Only adds winners and losers, a TIE between two candidates is not added.
        - For each new pair added to the array, The global value Pairs is incremented.
    */

    int flag = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

            if (flag == 0) // PRIMER PAR
            {
                if ((preferences[i][j] > preferences[j][i]) || (preferences[i][j] < preferences[j][i]))
                {

                    // s_pair new_pair;
                    pair new_pair;
                    if (preferences[i][j] > preferences[j][i])
                    {
                        new_pair.winner = i;
                        new_pair.loser = j;
                    }
                    else
                    {
                        new_pair.winner = j;
                        new_pair.loser = i;
                    }

                    pair_count++;
                    pairs[(pair_count - 1)] = new_pair;


                    flag = 1;
                }
            }
            else if (flag == 1) // Segundo par en adelante
            {

                if (preferences[i][j] > preferences[j][i])
                {
                    pair new_pair;
                    new_pair.winner = i;
                    new_pair.loser = j;

                    int foe = pair_count;
                    int existe = 0;
                    for (int foo = 0; foo < foe; foo++)
                    {
                        if ((new_pair.winner != pairs[foo].winner) || (new_pair.loser != pairs[foo].loser))
                        {
                            existe = 1;
                            break;
                        }
                    }
                    if (existe == 0)
                    {
                        pair_count++;
                        pairs[(pair_count - 1)] = new_pair;
                    }
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pair new_pair;
                    new_pair.winner = j;
                    new_pair.loser = i;

                    int foe = pair_count;
                    int existe = 0;
                    for (int foo = 0; foo < foe; foo++)
                    {
                        if ((new_pair.winner == pairs[foo].winner) && (new_pair.loser == pairs[foo].loser))
                        {
                            existe = 1;
                            break;
                        }
                    }
                    if (existe == 0)
                    {
                        pair_count++;
                        pairs[(pair_count - 1)] = new_pair;
                    }
                }
                else if (preferences[i][j] == preferences[j][i])
                {
                }
            }
        }
    }


    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    // Ordena array s_pais[] por Stength y luego pasa winner y loser de cada pos a arreglo pairs[]



   // metodo usando arreglo, PAIRS[]
   // Usa simple ordenamiento BUBBLE SORT, Porque el numero maximo de candidatos es 9
   int i, j;
    for (i = 0; i < pair_count - 1; i++)
    {
        for (j = 0; j < pair_count - i - 1; j++)
        {
            int str1, str2;
            str1 = (preferences[pairs[j].winner][pairs[j].loser]) - preferences[pairs[j].loser][pairs[j].winner];
            str2 = (preferences[pairs[j+1].winner][pairs[j+1].loser]) - preferences[pairs[j+1].loser][pairs[j+1].winner];
            if (str1 < str2)
            {
                swap(&pairs[j].winner, &pairs[j + 1].winner);
                swap(&pairs[j].loser, &pairs[j + 1].loser);
            }
        }
    }


}

void swap(int *i, int *j) // Sady
{
    int swap = *i;
    *i = *j;
    *j = swap;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /*
        - Recorre pairs[] y agrega en coordenadas winner = i, loser = j, valor TRUE.
        - Antes de cambiar estado a TRUE, Comprueba que las coordenadas j,i sean FALSE
   */

    // Manejo de ciclos con recursividad
    int primero = 1;

    for (int i = 0; i < candidate_count; i++)
    {
        int row = pairs[i].winner;
        int col = pairs[i].loser;

        if (primero == 1) // Agrega primer enlace antes de usar metodo recursivo
        {
            locked[row][col] = true;
            primero = 0;
        }
        else // Comprueba si hace ciclo con metodo recursivo 'encuentra(col);'
        {
            if (encuentra(row, col) == col) // Busca quien es el ultimo en la secuencia, Si es el mismo al que se intenta apuntar... NO se hace el vinculo.
            {
                locked[row][col] = false;
            }
            else
            {
                locked[row][col] = true; // No se hace ciclo, todo OK
            }
        }
    }


    return;
}

int encuentra(int col, int obj)
{
    // funcion para detectar ciclos en matriz locked antes de agregar enlace entre vertices
    /*
        encuentra recibe col: row de par a comprobar. obj: col de par a comprobar
        - Busca en la columna que sea igual a la fila, Si hay algun enlace apuntando al ganador.
            -- En caso de estar siendo apuntado, Busca en la columna del que esta apuntando.
        - En caso de no encontrar a nadie apuntando a ese nodo (en la columna no hay ningun true), Retorna
                    el valor de esa columna. El cual luego se compara con el valor de columna(El perdedor del par),
                    Si es igual significa que se produce un ciclo. Por lo que no se crea el enlace (Se deja como FALSE en vez de TRUE).
    */



    int retorno;
    retorno = col; // En caso de que no se cumpla la condicion, Se retorna valor del ganador, El cual no va a ser igual al perdedor en ningun caso.

    if (col == obj)
    {
        return retorno;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][col] == true)
        {
            return encuentra(i, obj);
        }
    }

    return retorno;
}


// Print the winner of the election
void print_winner(void)
{
    // Revisa cada columna buscando un valor TRUE. Si no encuentra ninguno, Ese es el candidato SOURCE, osea el ganador

    for (int col = 0; col < candidate_count; col++)
    {
        int count = 0;
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col] == false)
            {
                count++;
                if (count == candidate_count)
                {
                    printf("%s\n", candidates[col]);
                    break;
                }
            }
        }
    }

    return;
}
