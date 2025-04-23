#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Student Student;
struct Student {
	int nrCrt;
	char* nume;
	float media;
};

typedef struct nodLDC nodLDC;
struct nodLDC {
	nodLDC* prev;
	Student inf;
	nodLDC* next;
};

void inserareInceputLDC(nodLDC** cap, nodLDC** coada, Student detaliiStudent) {
	// pas1 - alocare memorie pt nodul nou 
	nodLDC* nou = (nodLDC*)malloc(sizeof(nodLDC));

	// pas2 - shallow copy 
	nou->inf = detaliiStudent;

	// pas3 
	nou->prev = NULL; 
	nou->next = NULL;

	// pas5 
	if ((*cap) != NULL) {
		// exista cel putin un nod in lista 

		// pas 5.1 - adresa pointerului next al noului nod se leaga de capul listei 
		nou->next = (*cap);

		// pas 5.2 - adresa pointerului prev al noului nod se leaga de nodul coada al listei  
		nou->prev = (*coada);

		// pas 5.3 - adresa pointerului prev al capului listei se leaga nodul nou 
		(*cap)->prev = nou;

		// pas 5.4 - adresa pointerului next al nodului coadei al listei se leaga nodul nou 
		(*coada)->next = nou; 

		// pas 5.5 - se actualizeaza capul listei duble cu nodul nou 
		(*cap) = nou;
	}
	else {
		// lista este goala 
		nou->prev = nou;
		nou->next = nou;
		(*cap) = (*coada) = nou;
	}
}

void inserareSfarsitLDC(nodLDC** cap, nodLDC** coada, Student detaliiStudent) {
	// pas1 - alocare memorie pt nodul nou 
	nodLDC* nou = (nodLDC*)malloc(sizeof(nodLDC));

	// pas2 - shallow copy 
	nou->inf = detaliiStudent;

	// pas3 
	nou->prev = NULL;
	nou->next = NULL;

	// pas4
	if ((*cap) != NULL) {
		// exista cel putin un nod in lista 

		// pas 4.1. - adresa pointerului prev al noului nod se leaga de nodul coada al listei 
		nou->prev = (*coada);

		// pas 4.2 - adresa pointerului next al noului nod se leaga de capul listei 
		nou->next = (*cap);

		// pas 4.3 - adresa pointerului next al nodului coada al listei se leaga de noul nod 
		(*coada)->next = nou; 

		//  pas 4.4 - adresa pointerului prev al nodului cap al listei se leaga de noul nod 
		(*cap)->prev = nou; 

		// pas 4.5 - se actualizeaza nodul coada al listei 
		(*coada) = nou;
	}
	else {
		// lista este goala 
		nou->prev = nou;
		nou->next = nou;
		(*cap) = (*coada) = nou;
	}
}

void traversareInceputLDC(nodLDC* cap) {
	nodLDC* start = cap;
	while (start->next != cap) {
		printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
			start->inf.nrCrt, start->inf.nume, start->inf.media);

		start = start->next;
	}
	printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
		start->inf.nrCrt, start->inf.nume, start->inf.media);
}

void traversareSfarsitLDC(nodLDC* coada) {
	nodLDC* final = coada;
	while (final->prev != coada) {
		printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
			final->inf.nrCrt, final->inf.nume, final->inf.media);

		final = final->prev;
	}
	printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
		final->inf.nrCrt, final->inf.nume, final->inf.media);
}

void dezalocareLDC(nodLDC** cap, nodLDC** coada) {
	nodLDC* temp = (*cap);
	while (temp->next != (*cap)) {
		free(temp->inf.nume);

		nodLDC* aux = temp;
		temp = temp->next;
		free(aux);
	}

	free(temp->inf.nume);
	free(temp);

	(*coada) = NULL;
}

void main() {
	FILE* file = fopen("DetaliiStudenti.txt", "r");

	int nrStudentiFisier = 0;
	fscanf(file, "%d", &nrStudentiFisier);

	nodLDC* capLDC_1 = NULL;
	nodLDC* coadaLDC_1 = NULL;

	nodLDC* capLDC_2 = NULL;
	nodLDC* coadaLDC_2 = NULL;

	char buffer[40];
	Student s;

	for (int i = 0; i < nrStudentiFisier; i++) {
		fscanf(file, "%d", &s.nrCrt);

		fscanf(file, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);

		fscanf(file, "%f", &s.media);

		inserareInceputLDC(&capLDC_1, &coadaLDC_1, s);
		inserareSfarsitLDC(&capLDC_2, &coadaLDC_2, s);
	}
	fclose(file);

	printf("\n---------------- LD - inserare inceput + traversare inceput ---------------- \n");
	traversareInceputLDC(capLDC_1);

	printf("\n---------------- LD - inserare inceput + traversare sfarsit ---------------- \n");
	traversareSfarsitLDC(coadaLDC_1);

	printf("\n---------------- LD - inserare sfarsit + traversare inceput ---------------- \n");
	traversareInceputLDC(capLDC_2);

	printf("\n---------------- LD - inserare sfarsit + traversare sfarsit ---------------- \n");
	traversareSfarsitLDC(coadaLDC_2);

	dezalocareLDC(&capLDC_1, &coadaLDC_1);
}