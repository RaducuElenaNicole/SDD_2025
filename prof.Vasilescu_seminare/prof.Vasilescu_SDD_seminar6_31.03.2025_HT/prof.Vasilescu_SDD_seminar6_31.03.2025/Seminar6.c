// Seminar 6 - 31/03/2025
// Tabela de dispersie 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Carte Carte;
typedef struct nodLS nodLS;
typedef struct HashTable HashTable;

#pragma Operatii_Carte
struct Carte
{
	int id;
	char* autor;
	int nrPagini;
	float pret;
};

void afiseazaCarte(Carte crt) {
	printf("        ID: %d | Autor: %s | Pret: %5.2f | Nr pagini: %d\n",
		crt.id, crt.autor, crt.pret, crt.nrPagini);
}

Carte citireCarte(FILE* fileStream) {
	Carte carte;
	char buffer[30];

	fgets(buffer, 5, fileStream);
	carte.id = atoi(buffer);

	fgets(buffer, 30, fileStream);
	char* autor = strtok(buffer, "\n");
	carte.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
	strcpy(carte.autor, autor);

	fgets(buffer, 5, fileStream);
	carte.nrPagini = atoi(buffer);

	fgets(buffer, 5, fileStream);
	carte.pret = atof(buffer);
	return carte;
}

void citireVectorCarti(FILE* file, Carte** vectorCarti, int* nrCarti) {
	if (file == NULL) {
		return;
	}

	while (!feof(file)) {
		*vectorCarti = (Carte*)realloc(*vectorCarti, ((*nrCarti) + 1) * sizeof(Carte));
		(*vectorCarti)[*nrCarti] = citireCarte(file);
		(*nrCarti)++;
	}
}

#pragma Operatii_LS 

struct nodLS {
	Carte info;  
	nodLS* next; 
};
 
void insereazaSfarsitLS(nodLS** cap, Carte info) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = info;
	nou->next = NULL; 

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		nodLS* temp = (*cap);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traverseazaLS(nodLS* cap) {
	while (cap) {
		afiseazaCarte(cap->info);
		cap = cap->next;
	}
}

void dezalocareLS(nodLS** cap) {
	while ((*cap) != NULL) {
		if ((*cap)->info.autor != NULL) {
			free((*cap)->info.autor);
		}

		nodLS* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux);
	}
}

int numarareCartiByAutorLS(nodLS* cap, char* autor) {
	int nrCarti = 0;
	while (cap) {
		if (strcmp(cap->info.autor, autor) == 0) {
			nrCarti++;
		}
		cap = cap->next;
	}
	return nrCarti;
}

#pragma Operatii_HashTable

struct HashTable {
	int dimHashTable; 
	nodLS** vectHashT;
};

HashTable initializeazaHashTable(int dimensiune) {
	HashTable tabela; 
	tabela.dimHashTable = dimensiune;
	tabela.vectHashT = (nodLS**)malloc(sizeof(nodLS*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		tabela.vectHashT[i] = NULL;
	}
	return tabela;
}

int hash(char primaLiteraAutor, int dimensiune) {
	return primaLiteraAutor % dimensiune; 
}

void insereazaHashTabel(HashTable tabela, Carte crt) {
	if (tabela.dimHashTable > 0) {
		int pozitie = hash(crt.autor[0], tabela.dimHashTable);
		if (pozitie >= 0 && pozitie <= 6) {
			insereazaSfarsitLS(&(tabela.vectHashT[pozitie]), crt);
		}
	}
}

void traverseazaHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimHashTable; i++) {
		printf("\nPozitia: %d \n", i);
		if (tabela.vectHashT[i] == NULL) {
			printf("        Lista pe aceasta pozitie este GOALA!\n");
		}
		else {
			traverseazaLS(tabela.vectHashT[i]);
		}
	}
}

int numarareCartiByAutorHashTable(HashTable tabela, char* autor) {
	int nrCarti = 0;

	int pozitia = hash(autor[0], tabela.dimHashTable);
	nodLS* cap = tabela.vectHashT[pozitia];
	while (cap) {
		if (strcmp(cap->info.autor, autor) == 0) {
			nrCarti++;
		}
		cap = cap->next;
	}

	return nrCarti;
}

void dezalocaHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimHashTable; i++) {
		if (tabela.vectHashT[i] != NULL) {
			dezalocareLS(&(tabela.vectHashT[i]));
		}
	}
	free(tabela.vectHashT);
}

void main() {
	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;
	citireVectorCarti(file, &vectorCarti, &nrCarti);
	fclose(file);

	/*printf("\n------ LS: Inserare la sfarsit ------ \n");
	nodLS* cap = NULL;
	for (int i = 0; i < nrCarti; i++) {
		insereazaSfarsitLS(&cap, vectorCarti[i]);
	}
	traverseazaLS(cap);

	printf("\n------ Numarul cartilor scrie de Nichita Stanescu este: %d",
		numarareCartiByAutorLS(cap, "Nichita Stanescu"));

	printf("\n\n");
	dezalocareLS(&cap);*/

	printf("\n------ Hash Table ------ \n");

	HashTable tabela = initializeazaHashTable(6);

	for (int i = 0; i < nrCarti; i++) {
		insereazaHashTabel(tabela, vectorCarti[i]);
	}
	traverseazaHashTable(tabela);

	printf("\n------ Numarul cartilor scrie de Nichita Stanescu este: %d",
		numarareCartiByAutorHashTable(tabela, "Nichita Stanescu"));

	free(vectorCarti);
	dezalocaHashTable(tabela);

	printf("\n\n\n");
}