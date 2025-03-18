// SDD - Seminar 3 - 10/03/2025 - LISTA SIMPLA 

/*
Informatia utila este omogena => acelasi tip de info! 
Ficare nod va stoca info, nu exista nod fara info! 
Structura de date care nu este contigua in memorie! 

OPERATII LS:
	1. parcurgere, afisare, traversare 
	2. inserare nod in lista: la inceput, la final, oriunde altundeva in lista 
	3. inserare nod dupa un anumit criteriu 
	4. dezalocare 
	5. alte operatii 
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Carte Carte;
typedef struct nodLS nodLS;

struct Carte
{
	int id;
	char* autor;
	int nrPagini;
	float pret;
};

struct nodLS {
	Carte info; // informatia utila 
	nodLS* next; // adresa urmatorului nod in lista simpla
};

// INSERARE LA INCEPUT 
// 1. creare nod nou -> alocarea noului nod 
// 2. setarea informatiei utile 
// 3. setarea adresa noului nod ca fiind vechiul cap 
// 4. se actualizeaza noul cap al listei 
void inserareInceputLS(nodLS** cap, Carte info) {
	// nodLS** cap -> transmitere prin pointer ptc se modifica capul/valoarea 
	// Carte info -> nu se modifica => transmitere prin valoarea

	// pas1 
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS)); 

	// pas2 
	nou->info = info;

	// pas3 
	nou->next = *cap;

	// pas4 
	*cap = nou;
}

// transmitere prin adresa, in cazul in care LS este vida 
void insereazaSfarsitLS(nodLS** cap, Carte info) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = info;
	nou->next = NULL; // ultimul nod din lista pointeaza catre null

	// varianta in care lista e vida si noul nod devine cap
	if ((*cap) == NULL) {
		*cap = nou;
	}else{
		// deplasare cu temp pana la ultimul nod din lista 
		nodLS* temp = (*cap);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void afiseazaCarte(Carte crt) {
	printf("ID: %d | Autor: %s | Pret: %5.2f | Nr pagini: %d\n", 
		crt.id, crt.autor, crt.pret, crt.nrPagini);
}

// transmitere prin valoare 
// afisarea listei cu cap, care e transmis prin valoare => nu se modifica lista 
// cand transmiterea este prin ponteri, se pierde lista daca se va folosi cap
void traverseazaLS(nodLS* cap) {
	while (cap) {
		afiseazaCarte(cap->info);
		cap = cap->next;
	}
}

void afisare_vector_fisier(int length, int* vector) {
	for (int i = 0; i < (length); i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");
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

// dimensiunea vectorului de carti se calculeaza dinamic -> nrCarti 
// vectorCarti si nrCarti sunt transmise prin pointeri => in functie se dereferentiaza 
void citireVectorCarti(FILE* file, Carte** vectorCarti, int* nrCarti) {
	if (file == NULL) {
		return;
	}
	// cat timp nu am ajuns la finalul fisierului 
	while (!feof(file)) {
		// initializare + alocare de memorie 
		// realloc() -> realoca vectorul de fiecare data cand se mai adauga o carte din fisier 
 		*vectorCarti = (Carte*)realloc(*vectorCarti, ((*nrCarti) + 1) * sizeof(Carte));
		// adauga la finalul vectorului inca o carte citita din fisier 
		(*vectorCarti)[*nrCarti] = citireCarte(file);
		// se modifica numarul de carti din vector 
		(*nrCarti)++;
	}
}

void dezalocareLS(nodLS** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.autor);

		nodLS* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux);
	}
}

// functie pentru numararea numarului de carti din LS scrie de un anumit autor 
// transmitere prin valoare, NU avem nevoie de referinta ptc valorile nu se modifica 
int numarareCartiByAutor(nodLS* cap, char* autor) {
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
	// fisier din care se citeste -> READ
	//FILE* fileStream = fopen("Carte.txt", "r"); 
	//Carte carte = citireCarte(fileStream);
	//fclose(fileStream);
	//printf("\nAutorul este: %s.", carte.autor);
	//printf("\n");
	//free(carte.autor);

	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;
	// transmitere prin pointeri
	citireVectorCarti(file, &vectorCarti, &nrCarti);

	//
	//printf("\nAfisare vector:");
	//for (int i = 0; i < nrCarti; i++) {
	//	/*
	//	printf("\nAutorul este: %s. --- ", vectorCarti[i].autor);
	//	printf("Autor: %s | Pret: %5.2f | Nr pagini: %d", 
	//					vectorCarti[i].autor, vectorCarti[i].pret, vectorCarti[i].nrPagini);
	//	*/
	//	afiseazaCarte(vectorCarti[i]);
	//	free(vectorCarti[i].autor);
	//}
	//

	printf("\n------ Inserare la inceput ------ \n");
	nodLS* cap = NULL;
	for (int i = 0; i < nrCarti; i++) {
		inserareInceputLS(&cap, vectorCarti[i]);
	}
	traverseazaLS(cap);

	printf("\n------ Inserare la sfarsit ------ \n");
	nodLS* cap2 = NULL;
	for (int i = 0; i < nrCarti; i++) {
		insereazaSfarsitLS(&cap2, vectorCarti[i]);
	}
	traverseazaLS(cap2);

	printf("\n------ Numarul cartilor scrie de Nichita Stanescu este: %d", 
			numarareCartiByAutor(cap, "Nichita Stanescu"));

	printf("\n");
	printf("\n");

	dezalocareLS(&cap);
	free(vectorCarti);

	fclose(file);
}
