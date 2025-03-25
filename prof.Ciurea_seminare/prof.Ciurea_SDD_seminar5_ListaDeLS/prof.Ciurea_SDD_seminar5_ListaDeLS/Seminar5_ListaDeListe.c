// SDD - Seminar 5 - 25/03/2025 - sapt 5

// Lista de liste simple 

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
	struct nodLS* info; // sublista 
	struct nodLP* next; // lista principala 
}nodLP;

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

void traverseazaLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp) {
		printf("    Produs { Cod: %d | Denumire: %s | Pret: %.2f } \n",
			temp->info.cod, temp->info.denumire, temp->info.pret);
		temp = temp->next;
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

void insereazaLP(nodLP** capLP, nodLS* capLS) {
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info = capLS;
	nou->next = NULL;
	if ((*capLP) == NULL) {
		(*capLP) = nou;
	}
	else {
		nodLP* temp = (*capLP);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traverseazaLP(nodLP* capLP) {
	nodLP* temp = capLP;
	int i = 1;
	
	while (temp) {
		printf("\nSublista: %d \n", i);
		traverseazaLS(temp->info);
		temp = temp->next;
		i++;
	}
}

void dezalocaLP(nodLP* capLP) {
	nodLP* temp = capLP;
	while (temp) {
		nodLP* aux = temp->next;

		dezalocaLS(temp->info);

		free(temp);

		temp = aux;
	}
}

void main()
{
	nodLP* capLP = NULL;
	nodLS* capLS_1 = NULL;
	nodLS* capLS_2 = NULL;

	Produs p;
	int nrProduse;
	char buffer[20];

	FILE* f = fopen("ListaDeListe.txt", "r");
	fscanf(f, "%d", &nrProduse);
	for (int i = 0; i < nrProduse; i++) {
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);

		if (p.pret >= 10) {
			insereazaLS(&capLS_1, p);
		}
		else {
			insereazaLS(&capLS_2, p);
		}

		free(p.denumire);
	}
	fclose(f);

	insereazaLP(&capLP, capLS_1);
	insereazaLP(&capLP, capLS_2);

	printf("------------------------------ Lista de liste ------------------------------\n");
	traverseazaLP(capLP);

	printf("\n\n\n");

	dezalocaLP(capLP);
}