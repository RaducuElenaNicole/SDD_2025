#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct Student Student; 
struct Student {
	int nrCrt; 
	char* nume; 
	float media; 
};

typedef struct nodLS nodLS;
struct nodLS {
	Student inf; 
	nodLS* next; 
};

void inserareInceputLS(nodLS** cap, Student detaliiStudent) {
	// pas1 - alocare memorie pt noul nod 
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	// pas2 - infomatia utila prin shallow copy
	nou->inf = detaliiStudent;

	// pas3 - nodul nou se leaga de capul listei simple 
	// nodul nou va deveni cap => adresa capului trebuie memorata in nou->next 
	nou->next = (*cap);

	// pas4 - se actualizeaza noul cap al listei simple 
	(*cap) = nou;
}

void inserareSfarsitLS(nodLS** cap, Student detaliiStudent) {
	// pas1 - alocare memorie pt noul nod 
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	// pas2 - infomatia utila prin shallow copy
	nou->inf = detaliiStudent;

	// pas3 - nodul nou trebuie sa fie ultimul nod din LS => nou->next trebuie sa fie null
	nou->next = NULL; 

	// pas4 - actualizarea LS prin adaugarea noului nod 
	if ((*cap) == NULL) {
		// LS este goala => nodul nou devine cap 
		(*cap) = nou;
	}
	else {
		// LS se traverseaza cu temp pana la ultimul nod din LS
		nodLS* temp = (*cap);
		while (temp->next != NULL) {
			temp = temp->next; 
		}
		// l-a sfarsit se adauga noul nod 
		temp->next = nou; 
	}
}

void traversareLS(nodLS* cap) {
	nodLS* temp = cap; 
	while (temp) {
		printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
			temp->inf.nrCrt, temp->inf.nume, temp->inf.media);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS** cap) {
	nodLS* temp = (*cap);
	while (temp) {
		// dezalocare din informatia utila a nodului curent a tuturor campurilor care sunt alocate dinamic 
		if (temp->inf.nume != NULL) {
			free(temp->inf.nume);
		}

		// initializarea unui nod nou cu nodul curent pentru a putea dezaloca nodul curent 
		// daca fac free(temp) => se pierde legatura catre urmatorul nod din LS
		nodLS* aux = temp; 
		temp = temp->next;
		free(aux);
	}
}

void stergereNodByMedie(nodLS** cap, float criteriuMedia) {
	nodLS* temp = (*cap);
	nodLS* nodPrev = NULL; 
	while (temp) {
		if (temp->inf.media == criteriuMedia){
			nodLS* nodDeSters = temp;

			if (temp == (*cap)) {
				// nodul gasit dupa criteriu este primul 
				temp = temp->next;
				(*cap) = temp;
				nodPrev = NULL; 
			}
			else if (temp->next == NULL) {
				// nodul gasit dupa criteriu este ultimul 
				nodPrev->next = NULL;
				temp = NULL; 
			}
			else {
				// nodul gasit dupa criteriu este la mijloc 
				temp = temp->next;
				nodPrev->next = temp; 
			}

			free(nodDeSters->inf.nume);
			free(nodDeSters);
		}
		else {
			// nodul curent nu indeplineste conditia => merge mai departe 
			nodPrev = temp;
			temp = temp->next;
		}
	}
}

void main() {
	FILE* file = fopen("DetaliiStudenti.txt", "r");
	int nrStudentiFisier = 0; 
	nodLS* capLS_1 = NULL; 
	nodLS* capLS_2 = NULL;
	char buffer[40];
	Student s;

	fscanf(file, "%d", &nrStudentiFisier);
	for (int i = 0; i < nrStudentiFisier; i++) {
		fscanf(file, "%d", &s.nrCrt);

		fscanf(file, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);

		fscanf(file, "%f", &s.media);

		inserareInceputLS(&capLS_1, s);
		inserareSfarsitLS(&capLS_2, s); 
	}
	fclose(file);

	printf("\n---------------- LS - inserare inceput ---------------- \n");
	traversareLS(capLS_1);

	printf("\n\n");

	printf("\n---------------- LS - inserare sfarsit ---------------- \n");
	traversareLS(capLS_2);

	printf("\n\n");

	printf("\n---------------- LS - stergere primul nod by criteriu ---------------- \n");
	float criteriuMedie = 6.9; 
	stergereNodByMedie(&capLS_2, criteriuMedie);
	traversareLS(capLS_2);

	printf("\n\n");

	printf("\n---------------- LS - stergere ultimul nod by criteriu ---------------- \n");
	criteriuMedie = 9.5;
	stergereNodByMedie(&capLS_2, criteriuMedie);
	traversareLS(capLS_2);

	printf("\n\n");

	printf("\n---------------- LS - stergere nod de la mijloc by criteriu ---------------- \n");
	criteriuMedie = 5.55;
	stergereNodByMedie(&capLS_2, criteriuMedie);
	traversareLS(capLS_2);

	printf("\n\n");


	/* 
		De la faptul ca am utilizat shallow copy, campul nume partajeaza aceeasi zona de memorie =>
		=> cand se sterge un nod, se elibereaza si zona de memorie alocata dinamic (in cazul acesta, 
		se elibereaza nume) 
	*/
	traversareLS(capLS_1); 

	dezalocareLS(&capLS_2);
}