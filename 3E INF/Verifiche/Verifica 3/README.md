# Esercitazione 10.2

Implementare le funzioni dichiarate in `exercise.h` per gestire una struttura `Shipping` che rappresenta una spedizione con informazioni sul mittente, destinatario, peso, volume e distanza. Le funzioni includono l'inizializzazione, la serializzazione su file, la deserializzazione da file, l'ordinamento di un array di spedizioni in base al costo e la stampa delle informazioni sulle spedizioni.

## Struttura `Shipping`

```c
typedef struct {
    char source[MAX_STR_LENGTH];
    char destination[MAX_STR_LENGTH];

    float package_weight;
    float package_volume;
    
    float distance;
} Shipping;
```

In questa esercitazione tutti i vettori di Shipping devono essere considerati con dimensione `MAX_LENGTH`. La costante `MAX_STR_LENGTH` è definita come 30, mentre `MAX_LENGTH` è definita come 100.

> Il progetto è disponibile utilizzabile con Code::Blocks, aprendo il file `codeblocks-project.cbp`. 
>
> &Egrave; possibile compilare ed eseguire i test con il comando `make test` da terminale, oppure eseguire manualmente il `main.c` con `make run` per testare le funzioni implementate.
>
> Il file `main.c` è un file che potete usare come più vi aggrada per testare le funzioni implementate, ma non è obbligatorio utilizzarlo. I test automatici sono definiti in `tests/main.c` e verificano il corretto funzionamento delle funzioni implementate.
