// SDD - Seminar 5 - 25/03/2025 - sapt 5

// Tabela de dispersie = vector de pointeri la LS
// fiecare element este un pointer la o lista simpla
// Chaining

#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct {
	int cod;
	char* denumire;
	float pret;
}Produs;

typedef struct {
	Produs info;
	struct nodLS* next;
}nodLS;

typedef struct {
	struct nodLS** vectHashT;
	int nrElem;
}HashTable;

int functieHash1(HashTable tabela, int cheie) {
	return (cheie % tabela.nrElem);
}

int functieHash2(HashTable tabela, char* denumire) {
	return (denumire[0] % tabela.nrElem);
}

void insereazaLS(nodLS** capLS, Produs prod) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.cod = prod.cod;
	nou->info.denumire = (char*)malloc(sizeof(char) * (strlen(prod.denumire) + 1));
	strcpy(nou->info.denumire, prod.denumire);
	nou->info.pret = prod.pret;
	nou->next = NULL;

	if ((*capLS) == NULL) {
		(*capLS) = nou;
	}
	else {
		nodLS* temp = (*capLS);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void insereazaHash1(HashTable tabela, Produs prod) {
	int poz = functieHash1(tabela, prod.cod);
	insereazaLS(&tabela.vectHashT[poz], prod);
}

void insereazaHash2(HashTable tabela, Produs prod) {
	int poz = functieHash2(tabela, prod.denumire);
	insereazaLS(&tabela.vectHashT[poz], prod);
}

void traverseazaLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp) {
		printf("    Produs { Cod: %d | Denumire: %s | Pret: %.2f } \n",
			temp->info.cod, temp->info.denumire, temp->info.pret);
		temp = temp->next;
	}
}

void traverseazaHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vectHashT[i] != NULL) {
			printf("\nPozitia: %d \n", i);
			traverseazaLS(tabela.vectHashT[i]);
		}
		/*else {
			printf("\nPozitia: %d -> NULL\n", i + 1);
		}*/
	}
}

void dezalocaLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp) {
		nodLS* aux = temp->next;

		free(temp->info.denumire);
		free(temp);

		temp = aux;
	}
}

void dezalocaHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vectHashT[i] != NULL) {
			dezalocaLS(tabela.vectHashT[i]);
		}
	}
	free(tabela.vectHashT);
}

void main()
{
	HashTable tabela1;
	tabela1.nrElem = 23;
	tabela1.vectHashT = (nodLS**)malloc(sizeof(nodLS*) * tabela1.nrElem);
	for (int i = 0; i < tabela1.nrElem; i++) {
		tabela1.vectHashT[i] = NULL;
	}

	HashTable tabela2;
	tabela2.nrElem = 23;
	tabela2.vectHashT = (nodLS**)malloc(sizeof(nodLS*) * tabela2.nrElem);
	for (int i = 0; i < tabela2.nrElem; i++) {
		tabela2.vectHashT[i] = NULL;
	}

	Produs p;
	int nrProduse;
	char buffer[20];

	FILE* f = fopen("HashTable.txt", "r");
	fscanf(f, "%d", &nrProduse);
	for (int i = 0; i < nrProduse; i++) {
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);

		insereazaHash1(tabela1, p);
		insereazaHash2(tabela2, p);

		free(p.denumire);
	}
	fclose(f);

	printf("------------------------------ Tabela de dispersie by cod ------------------------------");
	traverseazaHashTable(tabela1);

	printf("\n\n\n");

	printf("------------------------------ Tabela de dispersie by denumire ------------------------------");
	traverseazaHashTable(tabela2);

	dezalocaHashTable(tabela1);
	dezalocaHashTable(tabela2);
}

// stergere hash table 