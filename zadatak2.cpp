#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct osobe* p;
struct osobe {
	char ime[10], prezime[10];
	int godina_rodenja;
	p Next;
};
p prvi = NULL;
p zadnji = NULL;
p UnosP(p prvi, const char* ime, const char* prezime, int godina_rodenja) {
	p novaOsoba = (struct osobe*)malloc(sizeof(struct osobe));
	if (novaOsoba == NULL) {
		printf("\nAlokacija memorije nije uspjesna.");
		return NULL;
	}
	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godina_rodenja = godina_rodenja;

	novaOsoba->Next = prvi;
	prvi = novaOsoba;
	return prvi;
}
void Ispis(p prvi){
	p temp=prvi;
	if (temp == 0) {
		printf("\nLista je prazna.");
		return;
	}
	while(temp != NULL) {
		printf("\nIme %s, Prezime %s, Godina rodenja %d", temp->ime, temp->prezime, temp->godina_rodenja);
		temp = temp->Next;
	}
}
p UnosK(p prvi, const char* ime, const char* prezime, int godina_rodenja) {
	p temp = prvi;
	p ZadnjiElement = (struct osobe*)malloc(sizeof(struct osobe));
	if (ZadnjiElement == NULL) {
		printf("\nAlokacija memorije nije uspjela.");
		return NULL;
	}

	strcpy(ZadnjiElement->ime, ime);
	strcpy(ZadnjiElement->prezime, prezime);
	ZadnjiElement->godina_rodenja = godina_rodenja;
	ZadnjiElement->Next = NULL;

	if (temp == NULL) {
		printf("\nLista je prazna");
		return ZadnjiElement;
	}
	while (temp->Next != NULL) {
		temp = temp->Next;
	}
	temp->Next = ZadnjiElement;
	return prvi;
}
p Trazi(p prvi, const char* prezime) {
	p temp=prvi;
	if (temp == 0) {
		printf("\nLista je prazna.");
		return NULL;
	}
	while (temp != 0) {
		if (strcmp(temp->prezime, prezime) == 0) {
			return temp;
		}
		temp = temp->Next;
	}
	printf("\nElement nije pronaden.");
	return NULL;
}
p Brisi(p prvi, const char* ime, const char* prezime, int godina_rodenja) {
	p prethodni = NULL;
	p temp = prvi;
	if (temp == 0) {
		printf("\nLista je prazna.");
		return NULL;
	}
	while(temp!=0){
	if (strcmp(temp->ime, ime) == 0 && strcmp(temp->prezime, prezime) == 0 && temp->godina_rodenja == godina_rodenja) {
		if (prethodni == NULL) {
			prvi = temp->Next;
		}
		else {
			prethodni->Next = temp->Next;
		}
		free(temp);
		printf("\nElement je obrisan!");
		return prvi;
	}
	prethodni = temp;
	temp = temp->Next;
	return NULL;
}
printf("Element nije pronaden");
return prvi;
}
int main() {
	p lista = NULL;

	lista = UnosP(lista, "Drazen", "Drazic", 1990);
	lista = UnosP(lista, "Ana", "Anic", 1985);

	lista = UnosK(lista, "Refko", "Refkic", 1995);

	Ispis(lista);

	p pronadjen = Trazi(lista, "Drazic");
	if (pronadjen != NULL) {
		printf("\nPronaden: %s %s, %d", pronadjen->ime, pronadjen->prezime, pronadjen->godina_rodenja);
	}

	lista = Brisi(lista, "Ana", "Anic", 1985);
	Ispis(lista);

	return 0;
}