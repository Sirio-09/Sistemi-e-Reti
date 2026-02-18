#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "exercise.h"

#define MAX_LENGTH 100
#define MAX_STRING_LENGTH 500

/**
 * Prints an array of strings as a single line with a separator.
 *
 * @param s The array of strings to print
 * @param sep The separator to use between strings
 * @param N The number of strings in the array
 */
void printArray(const char s[MAX_LENGTH][MAX_STRING_LENGTH], const char sep[MAX_LENGTH], const int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%s", s[i]);
        if (i < N - 1)
        {
            printf("%s", sep);
        }
    }
    printf("\n");
}

int main()
{
    char choice = menu();

    // TODO: STUDENT AREA FOR TESTING
    int inputN = 1;
    float decimals[MAX_LENGTH] = {1.1f, 3.2f, 1.3f, 4.4f, 5.0f};

    int N = 6; // Number of values
    char values[MAX_LENGTH][MAX_STRING_LENGTH] = {"Aldo", "Bruno", "Carlo", "Carlotta", "Giacomo", "Alex"};

    float searchedValue = 5;
    char searchedString[MAX_STRING_LENGTH] = "Aldo";
    char temp[MAX_STRING_LENGTH];
    // END STUDENT AREA

    int semifactorial, firstIndex, searchedIndex;
    switch (choice)
    {
    case 'A':
        semifactorial = exercise1(inputN);
        printf("%d\n", semifactorial);
        break;
    case 'B':
        firstIndex = exercise2(decimals, searchedValue);
        printf("%d\n", firstIndex);
        break;
    case 'C':
        searchedIndex = exercise3(values, searchedString);
        printf("%d\n", searchedIndex);
        break;
    case 'X':
        printf("Programma terminato\n");
        break;
    default:
        printf("Scelta non valida\n");
        return -1;
    }

    return 0;
}