#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PAZIENTI "Pazienti.txt"
#define FILE_VISITE "Visite.txt"

typedef struct {
    int codice;
    char cognome[50];
    char nome[50];
    char citta[50];
    char reparto[50];
    int letto;
} Paziente;

typedef struct {
    int progressivo;
    char data[11];
    char tipo[50];
    char dottore[50];
    int cod_paziente;
} Visita;

// Ottiene il prossimo ID (progressivo) disponibile leggendo il primo campo
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

// --- GESTIONE INSERIMENTI ---

void inserisciPaziente() {
    FILE *f = fopen(FILE_PAZIENTI, "a");
    Paziente p;
    p.codice = getNextId(FILE_PAZIENTI);
    
    printf("Cognome: "); scanf(" %[^\n]", p.cognome);
    printf("Nome: "); scanf(" %[^\n]", p.nome);
    printf("Citta': "); scanf(" %[^\n]", p.citta);
    printf("Reparto: "); scanf(" %[^\n]", p.reparto);
    printf("N. Letto: "); scanf("%d", &p.letto);
    
    fprintf(f, "%d;%s;%s;%s;%s;%d\n", p.codice, p.cognome, p.nome, p.citta, p.reparto, p.letto);
    fclose(f);
    printf("Paziente inserito con matricola %d\n", p.codice);
}

void inserisciVisita() {
    FILE *f = fopen(FILE_VISITE, "a");
    Visita v;
    v.progressivo = getNextId(FILE_VISITE);
    
    printf("Data visita (gg/MM/aaaa): "); scanf(" %[^\n]", v.data);
    printf("Tipo visita: "); scanf(" %[^\n]", v.tipo);
    printf("Dottore: "); scanf(" %[^\n]", v.dottore);
    printf("Codice Paziente: "); scanf("%d", &v.cod_paziente);
    
    fprintf(f, "%d;%s;%s;%s;%d\n", v.progressivo, v.data, v.tipo, v.dottore, v.cod_paziente);
    fclose(f);
    printf("Visita inserita con progressivo %d\n", v.progressivo);
}

// --- GESTIONE RICERCHE ---

void ricercaCognomeNome() {
    FILE *f = fopen(FILE_PAZIENTI, "r");
    if (!f) return;
    
    char cognomeReq[50], nomeReq[50], buffer[256];
    Paziente p;
    int trovati = 0;
    
    printf("Inserisci Cognome: "); scanf(" %[^\n]", cognomeReq);
    printf("Inserisci Nome: "); scanf(" %[^\n]", nomeReq);
    
    printf("\nReparti in cui e' stato ricoverato:\n");
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%[^;];%d", &p.codice, p.cognome, p.nome, p.citta, p.reparto, &p.letto);
        if (strcmp(p.cognome, cognomeReq) == 0 && strcmp(p.nome, nomeReq) == 0) {
            printf("- %s (Letto: %d)\n", p.reparto, p.letto);
            trovati++;
        }
    }
    if (trovati == 0) printf("Nessun paziente trovato.\n");
    fclose(f);
}

void ricercaPerReparto() {
    FILE *f = fopen(FILE_PAZIENTI, "r");
    if (!f) return;
    
    char repartoReq[50], buffer[256];
    Paziente p;
    
    printf("Inserisci Reparto: "); scanf(" %[^\n]", repartoReq);
    
    printf("\nPazienti nel reparto %s:\n", repartoReq);
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%[^;];%d", &p.codice, p.cognome, p.nome, p.citta, p.reparto, &p.letto);
        if (strcmp(p.reparto, repartoReq) == 0) {
            printf("[%d] %s %s - Letto: %d\n", p.codice, p.cognome, p.nome, p.letto);
        }
    }
    fclose(f);
}

void ricercaPerCitta() {
    FILE *f = fopen(FILE_PAZIENTI, "r");
    if (!f) return;
    
    char cittaReq[50], buffer[256];
    Paziente p;
    
    printf("Inserisci Citta': "); scanf(" %[^\n]", cittaReq);
    
    printf("\nPazienti di %s:\n", cittaReq);
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%[^;];%d", &p.codice, p.cognome, p.nome, p.citta, p.reparto, &p.letto);
        if (strcmp(p.citta, cittaReq) == 0) {
            printf("[%d] %s %s (Reparto: %s)\n", p.codice, p.cognome, p.nome, p.reparto);
        }
    }
    fclose(f);
}

void ricercaVisitePaziente() {
    FILE *f = fopen(FILE_VISITE, "r");
    if (!f) return;
    
    int codReq;
    char buffer[256];
    Visita v;
    
    printf("Inserisci Codice Paziente: "); scanf("%d", &codReq);
    
    printf("\nVisite effettuate dal paziente [%d]:\n", codReq);
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%d", &v.progressivo, v.data, v.tipo, v.dottore, &v.cod_paziente);
        if (v.cod_paziente == codReq) {
            printf("- Data: %s | Tipo: %s | Dott. %s\n", v.data, v.tipo, v.dottore);
        }
    }
    fclose(f);
}

void pazientiVisitatiInData() {
    FILE *fv = fopen(FILE_VISITE, "r");
    FILE *fp = fopen(FILE_PAZIENTI, "r");
    if (!fv || !fp) {
        if(fv) fclose(fv);
        if(fp) fclose(fp);
        return;
    }
    
    char dataReq[11], bufferVis[256], bufferPaz[256];
    Visita v;
    Paziente p;
    int trovato;
    
    printf("Inserisci Data (gg/MM/aaaa): "); scanf(" %[^\n]", dataReq);
    
    printf("\nPazienti visitati il %s:\n", dataReq);
    while (fgets(bufferVis, sizeof(bufferVis), fv)) {
        sscanf(bufferVis, "%d;%[^;];%[^;];%[^;];%d", &v.progressivo, v.data, v.tipo, v.dottore, &v.cod_paziente);
        if (strcmp(v.data, dataReq) == 0) {
            rewind(fp);
            trovato = 0;
            while (fgets(bufferPaz, sizeof(bufferPaz), fp)) {
                sscanf(bufferPaz, "%d;%[^;];%[^;];%[^;];%[^;];%d", &p.codice, p.cognome, p.nome, p.citta, p.reparto, &p.letto);
                if (p.codice == v.cod_paziente) {
                    printf("- %s %s [%d] (Tipo visita: %s, Dott. %s)\n", p.cognome, p.nome, p.codice, v.tipo, v.dottore);
                    trovato = 1;
                    break;
                }
            }
            if(!trovato) {
                printf("- Paziente ID %d (Dati anagrafici non trovati)\n", v.cod_paziente);
            }
        }
    }
    fclose(fv);
    fclose(fp);
}

void menuRicerche() {
    int scelta;
    do {
        printf("\n--- MENU RICERCHE ---\n");
        printf("1) Ricerca per Cognome e Nome\n2) Ricerca pazienti di un reparto\n");
        printf("3) Ricerca paziente per citta'\n4) Ricerca visite di un paziente\n");
        printf("5) Pazienti visitati in una data\n6) Ritorna al menu principale\nScelta: ");
        scanf("%d", &scelta);
        
        switch(scelta) {
            case 1: ricercaCognomeNome(); break;
            case 2: ricercaPerReparto(); break;
            case 3: ricercaPerCitta(); break;
            case 4: ricercaVisitePaziente(); break;
            case 5: pazientiVisitatiInData(); break;
        }
    } while (scelta != 6);
}

// --- MAIN LOOP ---
int main() {
    int scelta;
    do {
        printf("\n--- GESTIONE OSPEDALE ---\n");
        printf("1) Inserimento paziente\n2) Ricerca paziente\n3) Inserimento visita\n0) Esci\nScelta: ");
        scanf("%d", &scelta);
        
        switch(scelta) {
            case 1: inserisciPaziente(); break;
            case 2: menuRicerche(); break;
            case 3: inserisciVisita(); break;
        }
    } while (scelta != 0);
    
    printf("Chiusura in corso...\n");
    return 0;
}