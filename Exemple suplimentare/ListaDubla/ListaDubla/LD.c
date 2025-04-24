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

typedef struct nodLD nodLD; 
struct nodLD {
	nodLD* prev; 
	Student inf; 
	nodLD* next; 
};

void inserareInceputLD(nodLD** cap, nodLD** coada, Student detaliiStudent) {
	// pas1 - alocare memorie pt nodul nou 
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	// pas2 - shallow copy 
	nou->inf = detaliiStudent;

	// pas3 
	// pas 3.1 - nou va deveni capul listei duble => adresa pointerului prev trebuie sa fie NULL 
	// (conditia ca nodul sa fie primul, sa fie capul listei duble)
	nou->prev = NULL;
	// pas 3.2 
	nou->next = NULL;

	// pas5 
	if ((*cap) != NULL) {
		// exista cel putin un nod in lista 
		
		// pas 5.1 - adresa pointerului next al noului nod se leaga de capul listei 
		nou->next = (*cap);

		// pas 5.2 - adresa pointerului prev al capului listei se leaga nodul nou 
		(*cap)->prev = nou; 

		// pas 5.3 - se actualizeaza capul listei duble cu nodul nou 
		(*cap) = nou; 
	}
	else {
		// lista este goala 
		(*cap) = (*coada) = nou; 
	}
}

void inserareSfarsitLD(nodLD** cap, nodLD** coada, Student detaliiStudent) {
	// pas1 - alocare memorie pt nodul nou 
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	// pas2 - shallow copy 
	nou->inf = detaliiStudent;

	// pas3 
	nou->prev = NULL; 
	nou->next = NULL; 

	// pas4
	if ((*cap) != NULL) {
		// exista cel putin un nod in lista 

		// pas 4.1 - adresa pointerului next al nodului coada al listei se leaga de nodul nou 
		(*coada)->next = nou; 

		// pas 4.2 - adresa pointerului prev al noului nod se leaga de nodul coada al listei 
		nou->prev = (*coada);

		// pas 4.3 - se actualizeaza nodul coada al listei cu noul nod 
		(*coada) = nou;
	}
	else {
		// lista este goala 
		(*cap) = (*coada) = nou;
	}
}

void traversareInceputLD(nodLD* cap) {
	nodLD* temp = cap;
	while (temp) {
		printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
			temp->inf.nrCrt, temp->inf.nume, temp->inf.media);
		temp = temp->next; 
	}
}

void traversareSfarsitLD(nodLD* coada) {
	nodLD* temp = coada;
	while (temp) {
		printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
			temp->inf.nrCrt, temp->inf.nume, temp->inf.media);
		temp = temp->prev;
	}
}

void dezalocareLD(nodLD** cap, nodLD** coada) {
	nodLD* temp = (*cap);
	while (temp) {
		free(temp->inf.nume);

		nodLD* aux = temp;
		temp = temp->next;
		free(aux);
	}
	(*coada) = NULL;
}

void stergereNodByMedie(nodLD** cap, nodLD** coada, float criteriuMedie) {
	nodLD* nodDeTraversare = (*cap);
	while (nodDeTraversare) {
		if (nodDeTraversare->inf.media == criteriuMedie) {
			nodLD* nodDeSters = nodDeTraversare;
			if (nodDeTraversare->prev == NULL) {
				// nodul gasit este primul
				nodDeTraversare = nodDeTraversare->next; 
				nodDeTraversare->prev = NULL; 
				(*cap) = nodDeTraversare;
			}
			else if (nodDeTraversare->next == NULL) {
				// nodul gasit este ultimul 
				(nodDeTraversare->prev)->next = NULL;
				(*coada) = (nodDeTraversare->prev);
				nodDeTraversare = NULL; 
			}
			else {
				(nodDeTraversare->prev)->next = nodDeTraversare->next;
				(nodDeTraversare->next)->prev = nodDeTraversare->prev;
				nodDeTraversare = nodDeTraversare->next;
			}
			free(nodDeSters->inf.nume);
			free(nodDeSters);
		}
		else {
			nodDeTraversare = nodDeTraversare->next;
		}
	}
}

void main() {
	FILE* file = fopen("DetaliiStudenti.txt", "r");

	int nrStudentiFisier = 0;
	fscanf(file, "%d", &nrStudentiFisier);

	nodLD* capLD_1 = NULL; 
	nodLD* coadaLD_1 = NULL; 

	nodLD* capLD_2 = NULL;
	nodLD* coadaLD_2 = NULL;

	char buffer[40];
	Student s;

	for (int i = 0; i < nrStudentiFisier; i++) {
		fscanf(file, "%d", &s.nrCrt);

		fscanf(file, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);

		fscanf(file, "%f", &s.media);

		inserareInceputLD(&capLD_1, &coadaLD_1, s);
		inserareSfarsitLD(&capLD_2, &coadaLD_2, s);
	}
	fclose(file);

	printf("\n---------------- LD - inserare inceput + traversare inceput ---------------- \n");
	traversareInceputLD(capLD_1);

	printf("\n---------------- LD - inserare inceput + traversare sfarsit ---------------- \n");
	traversareSfarsitLD(coadaLD_1);

	printf("\n---------------- LD - inserare sfarsit + traversare inceput ---------------- \n");
	traversareInceputLD(capLD_2);

	printf("\n---------------- LD - inserare sfarsit + traversare sfarsit ---------------- \n");
	traversareSfarsitLD(coadaLD_2);

	printf("\n\n"); 

	printf("\n---------------- LD - stergere primul nod ---------------- \n");
	float criteriuMedie = 6.9; 
	stergereNodByMedie(&capLD_2, &coadaLD_2, criteriuMedie);
	traversareInceputLD(capLD_2);

	printf("\n\n");

	printf("\n---------------- LD - stergere primul nod ---------------- \n");
	criteriuMedie = 9.50;
	stergereNodByMedie(&capLD_2, &coadaLD_2, criteriuMedie);
	traversareInceputLD(capLD_2);

	printf("\n\n");

	printf("\n---------------- LD - stergere nod de la mijloc ---------------- \n");
	criteriuMedie = 5.55;
	stergereNodByMedie(&capLD_2, &coadaLD_2, criteriuMedie);
	traversareInceputLD(capLD_2);

	printf("\n\n");

	traversareSfarsitLD(coadaLD_1);

	dezalocareLD(&capLD_2, &coadaLD_2);
}