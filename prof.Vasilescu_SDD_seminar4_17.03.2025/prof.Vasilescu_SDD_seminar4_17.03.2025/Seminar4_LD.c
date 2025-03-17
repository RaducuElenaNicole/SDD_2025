// SDD - Seminar 4 - 17/03/2025 - Lista Dubla 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#pragma Structurile_De_Baza

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


#pragma Carti

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

// functie de copiere -> deep copy pentru fiecare camp din structura Carte
Carte initializeazaCarte(int id, char* autor, int nrPagini, float pret) {
	Carte crt;

	crt.id = id;

	crt.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
	strcpy(crt.autor, autor);

	crt.nrPagini = nrPagini;
	crt.pret = pret;

	return crt;
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

void afiseazaCarte(Carte crt) {
	printf("ID: %d | Autor: %s | Pret: %5.2f | Nr pagini: %d\n",
		crt.id, crt.autor, crt.pret, crt.nrPagini);
}


#pragma Operatii_De_Baza_Lista_Dublu_Inlantuita

// INSERARE LA INCEPUT 
// 1. creare nod nou -> alocarea noului nod 
// 2. setarea informatiei utile 
// 3. setarea adresa noului nod ca fiind vechiul cap 
// 4. setarea pointerului prev cu NULL
// 5. se actualizeaza noul cap al listei 
//		5.1. exista cel putin un nod in lista 
//		5.2. lista este goala/vida
void inserareInceputLD(nodLD** cap, nodLD** coada, Carte info) {

	// pas1 
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	// pas2 
	// nou->info = info; -> shallow copy 
	nou->info = initializeazaCarte(info.id, info.autor, info.nrPagini, info.pret); // deep copy 

	// pas3 
	nou->next = *cap;

	// pas4
	nou->prev = NULL;\

	// pas5
	if((*cap) != NULL){
		// exista cel putin un nod in lista 
		(*cap)->prev = nou; 
		(*cap) = nou; // actualizarea noului cap cu nodul nou 
	}
	else {
		// cazul in care lista este goala
		*cap = *coada = nou;
	}

}

void insereazaSfarsitLD(nodLD** cap, nodLD** coada, Carte info) {
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	// nou->info = info; -> shallow copy 
	nou->info = initializeazaCarte(info.id, info.autor, info.nrPagini, info.pret); // deep copy 

	nou->next = NULL; 
	nou->prev = NULL; 

	if ((*cap) == NULL) {
		*cap = *coada = nou;
	}
	else {
		(*coada)->next = nou;
		nou->prev = (*coada);
		(*coada) = nou;
	}

}

void traverseazaLD(nodLD* cap) {
	while (cap) {
		afiseazaCarte(cap->info);
		cap = cap->next;
	}
}

void traverseazaLDInvers(nodLD* coada) {
	while (coada) {
		afiseazaCarte(coada->info);
		coada = coada->prev;
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


#pragma Operatii_Lista_Dublu_Inlantuita

int numarareCartiByAutor(nodLD* cap, const char* autor) {
	int nrCarti = 0;
	while (cap) {
		if (strcmp(cap->info.autor, autor) == 0) {
			nrCarti++;
		}
		cap = cap->next;
	}
	return nrCarti;
}

void main() {
	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;

	citireVectorCarti(file, &vectorCarti, &nrCarti);

	printf("\n------ Inserare la inceput ------");
	nodLD* cap = NULL;
	nodLD* coada = NULL;
	for (int i = 0; i < nrCarti; i++) {
		inserareInceputLD(&cap, &coada, vectorCarti[i]);
	} 
	printf("\n------ Traversare ------ \n");
	traverseazaLD(cap);
	printf("\n------ Traversare inversa ------ \n");
	traverseazaLDInvers(coada);

	printf("\n");

	printf("\n------ Inserare la final ------");
	nodLD* cap1 = NULL;
	nodLD* coada1 = NULL;
	for (int i = 0; i < nrCarti; i++) {
		insereazaSfarsitLD(&cap1, &coada1, vectorCarti[i]);
	}
	printf("\n------ Traversare ------ \n");
	traverseazaLD(cap1);
	printf("\n------ Traversare inversa ------ \n");
	traverseazaLDInvers(coada1);

	printf("\n");

	printf("\n------ Numarul cartilor scrie de Nichita Stanescu este: %d",
		numarareCartiByAutor(cap, "Nichita Stanescu"));

	printf("\n");
	printf("\n");

	dezalocareLD(&cap, &coada);
	dezalocareLD(&cap1, &coada1);

	free(vectorCarti);

	fclose(file);
}
