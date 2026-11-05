#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{

    FILE *fp;
    char nome[30+1];
    char materia[20+1];

    /**
    /// Controllo File Testo.txt
    fp = fopen("Testo.txt","r");
    if (fp == NULL) {
        fclose(fp);
        fp = fopen("Testo.txt","w");
        printf("\nFile creato con successo !!!");
    }
    else
        printf("\nFile e' esiste !!!");
    fclose(fp);

    /// INSERT
    fp = fopen("Testo.txt","w");

    printf("\nInserisci il Nome ==> ");
    /// scanf("%s",nome);
    gets(nome);

    fprintf(fp, "%s", nome);

    fclose(fp);

    /// READ - 1
    fp = fopen("Testo.txt","r");
    fscanf(fp, "%s", nome);
    fclose(fp);
    printf("\nREAD (1) => Nome : \"%s\" ", nome);

    printf("\n\n");

    /// READ - 2
    fp = fopen("Testo.txt","r");
    while(fgets(nome, 30, fp) != NULL)
        printf("\nREAD (2) => Nome : \"%s\" ", nome);
    fclose(fp);

    printf("\n\n");

    /// READ - 3
    fp = fopen("Testo.txt","r");
    fscanf(fp, "%s", nome);
    while(! feof(fp)){
        printf("\nREAD (3) => Nome : \"%s\" ", nome);
        fscanf(fp, "%s", nome);
    }
    fclose(fp);
    **/

    /// Controllo File Elenco.txt
    fp = fopen("Elenco.txt","r");
    if (fp == NULL) {
        fclose(fp);
        fp = fopen("Elenco.txt","w");
    }
    fclose(fp);


    /// Visualizzo le eventuali MATERIE
    printf("\nElenco Materie [fscanf]:\n");
    fp = fopen("Elenco.txt","r");
    fscanf(fp, "%s", materia);
    while(! feof(fp)){
        printf("- %s \n", materia);
        fscanf(fp, "%s", materia);
    }
    fclose(fp);

    printf("\n\nElenco Materie [fgets]:\n");
    fp = fopen("Elenco.txt","r");
    while(fgets(materia, 22, fp) != NULL)
        printf("- %s", materia);
    fclose(fp);

    /// Append
    fp = fopen("Elenco.txt","a");
    do
    {
        printf("\nInserisci una Materia [FINE per concludere] ==> ");
        fflush(stdin); /// Pulisce il Buffer di Input
        gets(materia);
        ///fgets(materia, sizeof(materia), stdin);

        /// if (materia != "FINE") /// ERRORE !!!
        if (strcmp(materia, "FINE") != 0)
        {
           fputs(materia, fp);
           fputs("\n", fp);
        }

    }
    while(strcmp(materia, "FINE") != 0);
    fclose(fp);


    printf("\n\n");

}
