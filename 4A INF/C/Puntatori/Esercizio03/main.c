#include <stdio.h>

int main()
{

    int vet[5] = {10, 20, 30, 40, 50};
    int *p;

    printf("\n\nEsercizio 3: gestione Vettori con Puntatori\n\n");

    // p = vet[0]; // Versione "grezza" / "grossolana"
    p = vet;

    for(int I=0; I<5; I++) {
        printf("\n - elemento %d - valore %d - indirizzo %p", I+1, *p, p);
        p++; // FONDAMENTALE !!!!
    }

    p = vet; // Riporta il Puntatore al 1° Elemento del Vettore ovvero all'Inizio

    p = &vet[2];
    *p = 18;
    printf("\n valore %d - indirizzo %p", *p, p);

    p[2] = 12;

    printf("\n\n");

    p = vet;
    for(int I=0; I<5; I++) {
        printf("\n - elemento %d - valore %d - indirizzo %p", I+1, *p, p);
        p++; // FONDAMENTALE !!!!
    }
    
    *p = 100;
    printf("\n\n");

    p = vet;
    for(int I=0; I<6; I++) {
        printf("\n - elemento %d - valore %d - indirizzo %p", I+1, *p, p);
        p++; // FONDAMENTALE !!!!
    }

    printf("\n\n");

    return 0;

}
