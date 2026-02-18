#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_STRING_LENGTH 500

/** (1 punto) Crea un menù con le seguenti voci:
 * A -> exercise 1
 * B -> exercise 2
 * C -> exercise 3
 * X -> Esci dal programma
 * @returns La voce scelta, se corretta.
 *          Se la scelta non è valida, riproporre
 *          nuovamente il menù finché non si sceglie
 *          correttamente.
 */
char menu()
{
    char choice;
    bool isCorrect = false;;

    do{
        printf("A -> exercise 1");
        printf("\nB -> exercise 2");
        printf("\nC -> exercise 3");
        printf("\nX -> Esci dal programma\n");

        scanf("%c", &choice);

        if(choice == 'A' || choice == 'B' || choice == 'C' || choice == 'X'){
            isCorrect = true;
        }

    }while(!isCorrect);

    return choice;;
}

/** (2 punti) Dato un numero in ingresso, restituirne il fattoriale
 * doppio.
 *
 * Si ricorda che il fattoriale doppio di un numero intero non negativo è definito come prodotto tra:
 * il numero stesso e tutti gli interi pari positivi che lo precedono, se esso è pari;
 * se il numero è dispari, il suo fattoriale doppio è il prodotto tra il numero e tutti gli interi
 * dispari che lo precedono;
 * Infine, il fattoriale doppio di zero vale 1 per definizione.
 * @param numbers L'array di numeri da considerare
 * @returns Il fattoriale doppio del numero specificato
 * @example
 * printf("%d\n", exercise1(7));  // 105
 * printf("%d\n", exercise1(12)); // 46080
 */
int exercise1(int number)
{
    if (number < 0){
        return -1;
    }

    int factorial = 1;

    for(int i = number; i >= 2; i -=2){

        factorial *= i;
    }

    return factorial;
}


/** (2 punti) Ricerca l'indice della prima occorrenza in un array fornito come
 * parametro di una numero decimale fornito.
 * @param numbers L'array di valori in cui ricercare
 * @param value Il numero da ricercare
 * @returns L'indice della prima occorrenza che rispetta il requisito, -1 se non vi è
 *          nessun elemento che rispetti il requisito.
 * @example
 * float[] numbers = { 1, 4, 2, 3, 5 };
 *
 * printf("%d\n", exercise2(numbers, 1)); // 0;
 * printf("%d\n", exercise2(numbers, 4)); // 1;
 * printf("%d\n", exercise2(numbers, 9)); // -1;
 */
int exercise2(float numbers[MAX_LENGTH], float value)
{
    for(int i = 0; i < MAX_LENGTH; i++){

        if(numbers[i] == value){
            return i;
        }
    }
    return -1;
}

/** (2 punti) Ricerca l'indice della prima occorrenza di una stringa in un array ORDINATO e SENZA RIPETIZIONI fornito come parametro.
 * @param values L'array di valori in cui ricercare
 * @param value Il valore da ricercare
 * @returns L'indice della prima occorrenza che rispetta il requisito, -1 se non vi è
 *          nessun elemento che rispetti il requisito.
 * @example
 * char values[MAX_LENGTH][MAX_STRING_LENGTH] = { "Aldo", "Bruno", "Carlo" };
 *
 * printf("%d\n", exercise3(values, "Aldo")); // 0;
 * printf("%d\n", exercise3(values, "Bruno")); // 1;
 * printf("%d\n", exercise3(values, "Dario")); // -1;
 */
int exercise3(char values[MAX_LENGTH][MAX_STRING_LENGTH], char value[MAX_STRING_LENGTH])
{
    int inf = 0;
    int sup = MAX_LENGTH;

    while(inf < sup){
        int mid = (inf + sup) /2;

        if(strcmp(values[mid], value) == 0){
            return mid;
        }
        else if(strcmp(values[mid], value) > 0){
            inf = mid + 1;
        }
        else{
            sup = mid - 1;
        }
    }
}
