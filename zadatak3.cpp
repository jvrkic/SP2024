#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osobe* p;
struct osobe {
    char ime[10], prezime[10];
    int godina_rodenja;
    p Next;
};

p UnosIza(p prvi, const char* prezime, const char* ime, const char* novoPrezime, int godina_rodenja) {
    p temp = prvi;

    while (temp != NULL && strcmp(temp->prezime, prezime) != 0) {
        temp = temp->Next;
    }

    if (temp == NULL) {
        printf("\nElement s prezimenom %s nije prona?en.", prezime);
        return prvi;
    }

    p novaOsoba = (struct osobe*)malloc(sizeof(struct osobe));
    if (novaOsoba == NULL) {
        printf("\nAlokacija memorije nije uspjela.");
        return prvi;
    }

    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, novoPrezime);
    novaOsoba->godina_rodenja = godina_rodenja;

    novaOsoba->Next = temp->Next;
    temp->Next = novaOsoba;

    return prvi;
}

p UnosIspred(p prvi, const char* prezime, const char* ime, const char* novoPrezime, int godina_rodenja) {
    p temp = prvi;
    p prethodni = NULL;

    while (temp != NULL && strcmp(temp->prezime, prezime) != 0) {
        prethodni = temp;
        temp = temp->Next;
    }

    if (temp == NULL) {
        printf("\nElement s prezimenom %s nije prona?en.", prezime);
        return prvi;
    }

    p novaOsoba = (struct osobe*)malloc(sizeof(struct osobe));
    if (novaOsoba == NULL) {
        printf("\nAlokacija memorije nije uspjela.");
        return prvi;
    }

    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, novoPrezime);
    novaOsoba->godina_rodenja = godina_rodenja;

    novaOsoba->Next = temp;
    if (prethodni == NULL) {
        prvi = novaOsoba;
    }
    else {
        prethodni->Next = novaOsoba;
    }

    return prvi;
}

p Sortiraj(p prvi) {
    if (prvi == NULL || prvi->Next == NULL)
        return prvi;

    p i, j;
    char tempIme[10], tempPrezime[10];
    int tempGodina;

    for (i = prvi; i->Next != NULL; i = i->Next) {
        for (j = i->Next; j != NULL; j = j->Next) {
            if (strcmp(i->prezime, j->prezime) > 0) {
                strcpy(tempIme, i->ime);
                strcpy(tempPrezime, i->prezime);
                tempGodina = i->godina_rodenja;

                strcpy(i->ime, j->ime);
                strcpy(i->prezime, j->prezime);
                i->godina_rodenja = j->godina_rodenja;

                strcpy(j->ime, tempIme);
                strcpy(j->prezime, tempPrezime);
                j->godina_rodenja = tempGodina;
            }
        }
    }

    return prvi;
}

void UpisiUDatoteku(p prvi, const char* imeDatoteke) {
    FILE* fp = fopen(imeDatoteke, "w");
    if (fp == NULL) {
        printf("\nGreska prilikom otvaranja datoteke.");
        return;
    }

    p temp = prvi;
    while (temp != NULL) {
        fprintf(fp, "%s %s %d\n", temp->ime, temp->prezime, temp->godina_rodenja);
        temp = temp->Next;
    }

    fclose(fp);
}

p CitanjeIzDatoteke(const char* imeDatoteke) {
    FILE* fp = fopen(imeDatoteke, "r");
    if (fp == NULL) {
        printf("\nGreska prilikom otvaranja datoteke.");
        return NULL;
    }

    p prvi = NULL, zadnji = NULL, novaOsoba = NULL;
    char ime[10], prezime[10];
    int godina_rodenja;

    while (fscanf(fp, "%s %s %d", ime, prezime, &godina_rodenja) == 3) {
        novaOsoba = (struct osobe*)malloc(sizeof(struct osobe));
        if (novaOsoba == NULL) {
            printf("\nAlokacija memorije nije uspjela.");
            fclose(fp);
            return prvi;
        }

        strcpy(novaOsoba->ime, ime);
        strcpy(novaOsoba->prezime, prezime);
        novaOsoba->godina_rodenja = godina_rodenja;
        novaOsoba->Next = NULL;

        if (prvi == NULL) {
            prvi = novaOsoba;
            zadnji = prvi;
        }
        else {
            zadnji->Next = novaOsoba;
            zadnji = novaOsoba;
        }
    }

    fclose(fp);
    return prvi;
}

void Ispis(p prvi) {
    p temp = prvi;
    if (temp == NULL) {
        printf("\nLista je prazna.");
        return;
    }
    while (temp != NULL) {
        printf("\nIme: %s, Prezime: %s, Godina rodenja: %d", temp->ime, temp->prezime, temp->godina_rodenja);
        temp = temp->Next;
    }
}

int main() {
    p lista = NULL;

    lista = UnosIza(lista, "Anic", "Luka", "Lukic", 1988);   
    lista = UnosIspred(lista, "Drazic", "Ivan", "Ivic", 1982); 

    lista = Sortiraj(lista);
    printf("\nSortirana lista:");
    Ispis(lista);

    UpisiUDatoteku(lista, "lista.txt");

    lista = CitanjeIzDatoteke("lista.txt");
    printf("\nLista iz datoteke:");
    Ispis(lista);

    return 0;
}