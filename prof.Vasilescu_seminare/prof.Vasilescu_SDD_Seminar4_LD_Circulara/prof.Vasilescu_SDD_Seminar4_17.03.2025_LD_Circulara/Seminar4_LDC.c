// SDD - Seminar 4 - 17/03/2025 - Lista Dubla Circulara

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#pragma Structuri_De_Baza

typedef struct Carte Carte;
typedef struct nodLD nodLD;

struct Carte
{
	int id;
	char* autor;
	int nrPagini;
	float pret;
};

struct nodLD {
	Carte info; // informatia utila 
	nodLD* next; // adresa urmatorului nod in LD
	nodLD* prev; // adresa nodului anterior in LD
};


#pragma Operatii_Carti

void afiseazaCarte(Carte crt) {
	printf("ID: %d | Autor: %s | Pret: %5.2f | Nr pagini: %d\n",
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


#pragma Operatii_De_Baza_LD_Circulara

// INSERARE LA INCEPUT 
void inserareInceputLDC(nodLD** cap, nodLD** coada, Carte info) {

	// pas1 
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	// pas2 
	nou->info = info; // shallow copy 

	// pas3 
	nou->next = *cap;

	// pas4
	nou->prev = NULL; 

		// pas5
		if ((*cap) != NULL) {
			// exista cel putin un nod in lista 
			(*cap)->prev = nou;
			(*cap) = nou; // actualizarea noului cap cu nodul nou 
		}
		else {
			// cazul in care lista este goala
			*cap = *coada = nou;
		}
}

void insereazaSfarsitLDC(nodLD** cap, nodLD** coada, Carte info) {
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	nou->info = info;
	nou->next = NULL;
	nou->prev = *coada;

	if ((*cap) == NULL) {
		*cap = *coada = nou;
	}
	else {
		(*coada)->next = nou;
		(*coada) = nou;
	}

}

void dezalocareLD(nodLD** cap, nodLD** coada) {
	while ((*cap) != NULL) {
		free((*cap)->info.autor);

		nodLD* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux);
	}
	(*coada) = NULL;
}

int numarareCartiByAutorLDCirculara(nodLD* cap, char* autor) {
	int nrCarti = 0;

	if (cap == NULL) {
		return 0;
	}

	nodLD* copie = cap;
	do {
		if (strcmp(cap->info.autor, autor) == 0) {
			nrCarti++;
		}
		cap = cap->next;

	} while (cap != copie);

	return nrCarti;
}

void traversareLDCirculara(nodLD* cap) {
	if (!cap) {
		// lista e goala cap == NULL
		return;
	}

	nodLD* copie = cap;

	do {
		afiseazaCarte(cap->info);
		cap = cap->next;

	} while (cap != copie);
}

void main() {
	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;

	citireVectorCarti(file, &vectorCarti, &nrCarti);

	printf("\n------ Inserare la inceput ------ \n");
	nodLD* cap = NULL;
	nodLD* coada = NULL;
	for (int i = 0; i < nrCarti; i++) {
		inserareInceputLDC(&cap, &coada, vectorCarti[i]);
		// insereazaSfarsitLS(&cap, &coada, vectorCarti[i]);
	}

	// LD Circulara
	coada->next = cap;
	cap->prev = coada;

	traversareLDCirculara(cap);

	printf("\n------ Numarul cartilor scrie de Nichita Stanescu este: %d",
		numarareCartiByAutorLDCirculara(cap, "Nichita Stanescu"));

	printf("\n");
	printf("\n");


	// dezalocareLD(&cap, &coada);

	free(vectorCarti);

	fclose(file);
}
