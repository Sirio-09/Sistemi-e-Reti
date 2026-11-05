#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LIBRI "Libri.txt"
#define FILE_GENERI "Generi.txt"
#define FILE_PRESTITI "Prestiti.txt"

typedef struct {
    int codice;
    char titolo[100];
    char autore[100];
    int cod_genere;
    int pagine;
} Libro;

typedef struct {
    int codice;
    char descrizione[50];
} Genere;

typedef struct {
    int progressivo;
    char data_prestito[11];
    char data_restituzione[11];
    int cod_libro;
} Prestito;

// Restituisce il prossimo ID disponibile per un dato file leggendo il primo campo (intero)
int getNextId(const char* filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 1;
    
    int maxId = 0, currentId;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), f)) {
        if (sscanf(buffer, "%d;", &currentId) == 1) {
            if (currentId > maxId) maxId = currentId;
        }
    }
    fclose(f);
    return maxId + 1;
}

// --- GESTIONE GENERI ---

void inserisciGenere() {
    FILE *f = fopen(FILE_GENERI, "a");
    Genere g;
    g.codice = getNextId(FILE_GENERI);
    
    printf("Inserisci descrizione genere: ");
    scanf(" %[^\n]", g.descrizione);
    
    fprintf(f, "%d;%s\n", g.codice, g.descrizione);
    fclose(f);
    printf("Genere inserito con codice %d\n", g.codice);
}

void modificaGenere() {
    FILE *f = fopen(FILE_GENERI, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) return;
    
    int idDaModificare, trovato = 0;
    Genere g;
    char buffer[256];
    
    printf("Inserisci codice genere da modificare: ");
    scanf("%d", &idDaModificare);
    
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^\n]", &g.codice, g.descrizione);
        if (g.codice == idDaModificare) {
            printf("Nuova descrizione: ");
            scanf(" %[^\n]", g.descrizione);
            trovato = 1;
        }
        fprintf(temp, "%d;%s\n", g.codice, g.descrizione);
    }
    
    fclose(f);
    fclose(temp);
    remove(FILE_GENERI);
    rename("temp.txt", FILE_GENERI);
    
    if (trovato) printf("Genere modificato.\n");
    else printf("Genere non trovato.\n");
}

void visualizzaGeneri() {
    FILE *f = fopen(FILE_GENERI, "r");
    if (!f) { printf("Nessun genere presente.\n"); return; }
    
    char buffer[256];
    printf("\n--- ELENCO GENERI ---\n");
    while (fgets(buffer, sizeof(buffer), f)) {
        Genere g;
        sscanf(buffer, "%d;%[^\n]", &g.codice, g.descrizione);
        printf("Codice: %d | Descrizione: %s\n", g.codice, g.descrizione);
    }
    fclose(f);
}

// --- GESTIONE LIBRI ---

void inserisciLibro() {
    FILE *f = fopen(FILE_LIBRI, "a");
    Libro l;
    l.codice = getNextId(FILE_LIBRI);
    
    printf("Titolo: "); scanf(" %[^\n]", l.titolo);
    printf("Autore: "); scanf(" %[^\n]", l.autore);
    printf("Codice Genere: "); scanf("%d", &l.cod_genere);
    printf("Numero Pagine: "); scanf("%d", &l.pagine);
    
    fprintf(f, "%d;%s;%s;%d;%d\n", l.codice, l.titolo, l.autore, l.cod_genere, l.pagine);
    fclose(f);
    printf("Libro inserito con matricola %d\n", l.codice);
}

void modificaLibro() {
    FILE *f = fopen(FILE_LIBRI, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) return;
    
    int idDaModificare, trovato = 0;
    Libro l;
    char buffer[512];
    
    printf("Inserisci matricola libro da modificare: ");
    scanf("%d", &idDaModificare);
    
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d;%d", &l.codice, l.titolo, l.autore, &l.cod_genere, &l.pagine);
        if (l.codice == idDaModificare) {
            printf("Nuovo Titolo: "); scanf(" %[^\n]", l.titolo);
            printf("Nuovo Autore: "); scanf(" %[^\n]", l.autore);
            printf("Nuovo Codice Genere: "); scanf("%d", &l.cod_genere);
            printf("Nuovo N. Pagine: "); scanf("%d", &l.pagine);
            trovato = 1;
        }
        fprintf(temp, "%d;%s;%s;%d;%d\n", l.codice, l.titolo, l.autore, l.cod_genere, l.pagine);
    }
    
    fclose(f);
    fclose(temp);
    remove(FILE_LIBRI);
    rename("temp.txt", FILE_LIBRI);
    
    if (trovato) printf("Libro modificato.\n");
    else printf("Libro non trovato.\n");
}

void visualizzaLibriPerGenere() {
    FILE *f = fopen(FILE_LIBRI, "r");
    if (!f) return;
    
    int codGenere;
    printf("Inserisci Codice Genere: ");
    scanf("%d", &codGenere);
    
    char buffer[512];
    Libro l;
    printf("\n--- LIBRI GENERE %d ---\n", codGenere);
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d;%d", &l.codice, l.titolo, l.autore, &l.cod_genere, &l.pagine);
        if (l.cod_genere == codGenere) {
            printf("[%d] %s di %s (%d pag)\n", l.codice, l.titolo, l.autore, l.pagine);
        }
    }
    fclose(f);
}

// --- GESTIONE PRESTITI ---

void effettuaPrestito() {
    FILE *f = fopen(FILE_PRESTITI, "a");
    Prestito p;
    p.progressivo = getNextId(FILE_PRESTITI);
    strcpy(p.data_restituzione, "-");
    
    printf("Codice Libro da prestare: "); scanf("%d", &p.cod_libro);
    printf("Data prestito (gg/MM/aaaa): "); scanf("%s", p.data_prestito);
    
    fprintf(f, "%d;%s;%s;%d\n", p.progressivo, p.data_prestito, p.data_restituzione, p.cod_libro);
    fclose(f);
    printf("Prestito registrato con ID %d\n", p.progressivo);
}

void effettuaRestituzione() {
    FILE *f = fopen(FILE_PRESTITI, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) return;
    
    int codLibro, trovato = 0;
    Prestito p;
    char buffer[256];
    
    printf("Codice libro da restituire: ");
    scanf("%d", &codLibro);
    
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d", &p.progressivo, p.data_prestito, p.data_restituzione, &p.cod_libro);
        if (p.cod_libro == codLibro && strcmp(p.data_restituzione, "-") == 0) {
            printf("Data restituzione (gg/MM/aaaa): ");
            scanf("%s", p.data_restituzione);
            trovato = 1;
        }
        fprintf(temp, "%d;%s;%s;%d\n", p.progressivo, p.data_prestito, p.data_restituzione, p.cod_libro);
    }
    
    fclose(f);
    fclose(temp);
    remove(FILE_PRESTITI);
    rename("temp.txt", FILE_PRESTITI);
    
    if (trovato) printf("Restituzione registrata.\n");
    else printf("Prestito attivo non trovato per questo libro.\n");
}

void ricercaSingoloInPrestito() {
    FILE *f = fopen(FILE_PRESTITI, "r");
    if (!f) return;
    
    int codLibro, trovato = 0;
    Prestito p;
    char buffer[256];
    
    printf("Inserisci Codice Libro: ");
    scanf("%d", &codLibro);
    
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d", &p.progressivo, p.data_prestito, p.data_restituzione, &p.cod_libro);
        if (p.cod_libro == codLibro && strcmp(p.data_restituzione, "-") == 0) {
            printf("Libro in prestito dal: %s (Prog: %d)\n", p.data_prestito, p.progressivo);
            trovato = 1;
        }
    }
    fclose(f);
    if (!trovato) printf("Il libro non e' attualmente in prestito.\n");
}

void ricercaTuttiInPrestito() {
    FILE *f = fopen(FILE_PRESTITI, "r");
    if (!f) return;
    
    Prestito p;
    char buffer[256];
    printf("\n--- LIBRI ATTUALMENTE IN PRESTITO ---\n");
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d", &p.progressivo, p.data_prestito, p.data_restituzione, &p.cod_libro);
        if (strcmp(p.data_restituzione, "-") == 0) {
            printf("Codice Libro: %d | Data prestito: %s\n", p.cod_libro, p.data_prestito);
        }
    }
    fclose(f);
}

void ricercaTuttiRestituiti() {
    FILE *f = fopen(FILE_PRESTITI, "r");
    if (!f) return;
    
    Prestito p;
    char buffer[256];
    printf("\n--- LIBRI RESTITUITI ---\n");
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d", &p.progressivo, p.data_prestito, p.data_restituzione, &p.cod_libro);
        if (strcmp(p.data_restituzione, "-") != 0) {
            printf("Codice Libro: %d | Dal %s al %s\n", p.cod_libro, p.data_prestito, p.data_restituzione);
        }
    }
    fclose(f);
}

// --- MENU SOTTO-SEZIONI ---

void menuLibri() {
    int scelta;
    do {
        printf("\n--- MENU GESTIONE LIBRI ---\n");
        printf("1) Inserimento Libro\n2) Modifica Libro\n3) Visualizza tutti i libri di un certo Genere\n4) Ritorna\nScelta: ");
        scanf("%d", &scelta);
        switch(scelta) {
            case 1: inserisciLibro(); break;
            case 2: modificaLibro(); break;
            case 3: visualizzaLibriPerGenere(); break;
        }
    } while (scelta != 4);
}

void menuGeneri() {
    int scelta;
    do {
        printf("\n--- MENU GESTIONE GENERI ---\n");
        printf("1) Inserimento Genere\n2) Modifica Genere\n3) Visualizza tutti i Generi\n4) Ritorna\nScelta: ");
        scanf("%d", &scelta);
        switch(scelta) {
            case 1: inserisciGenere(); break;
            case 2: modificaGenere(); break;
            case 3: visualizzaGeneri(); break;
        }
    } while (scelta != 4);
}

void menuPrestiti() {
    int scelta;
    do {
        printf("\n--- MENU GESTIONE PRESTITI ---\n");
        printf("1) Effettua un prestito\n2) Effettua una restituzione\n3) Ricerca singolo libro dato in prestito\n");
        printf("4) Ricerca tutti i libri in prestito\n5) Ricerca tutti i libri restituiti\n6) Ritorna\nScelta: ");
        scanf("%d", &scelta);
        switch(scelta) {
            case 1: effettuaPrestito(); break;
            case 2: effettuaRestituzione(); break;
            case 3: ricercaSingoloInPrestito(); break;
            case 4: ricercaTuttiInPrestito(); break;
            case 5: ricercaTuttiRestituiti(); break;
        }
    } while (scelta != 6);
}

// --- MAIN LOOP ---
int main() {
    int scelta;
    do {
        printf("\n--- BIBLIOTECA SCOLASTICA ---\n");
        printf("1) Gestione Libri\n2) Gestione Generi\n3) Gestione Prestiti\n0) Esci\nScelta: ");
        scanf("%d", &scelta);
        switch(scelta) {
            case 1: menuLibri(); break;
            case 2: menuGeneri(); break;
            case 3: menuPrestiti(); break;
        }
    } while (scelta != 0);
    
    printf("Chiusura in corso...\n");
    return 0;
}