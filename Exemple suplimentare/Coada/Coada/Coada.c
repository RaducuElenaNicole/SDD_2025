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

typedef struct nodCoada nodCoada;
struct nodCoada {
	Student inf; 
	nodCoada* next; 
};

// inserare la sfarsit 
void put(nodCoada** prim, Student detaliiStudent) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = detaliiStudent;
	nou->next = NULL; 
	if ((*prim) == NULL) {
		(*prim) = nou;
	}
	else {
		nodCoada* temp = (*prim);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou; 
	}
}

// extragere de la inceput
int get(nodCoada** prim, nodCoada** ultim, Student* detaliiStudentExtras) {
	if ((*prim) != NULL && (*ultim) != NULL) {
		(*detaliiStudentExtras) = (*prim)->inf;

		nodCoada* nodExtras = (*prim);
		(*prim) = (*prim)->next;

		free(nodExtras);

		return 1;
	}
	else {
		if ((*prim) == NULL) {
			(*ultim) = NULL;
		}

		return -1;
	}
}

void traversareCoada(nodCoada* prim) {
	nodCoada* temp = prim; 
	while (temp) {
		printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
			temp->inf.nrCrt, temp->inf.nume, temp->inf.media);
		temp = temp->next;
	}
}

void dezalocaCoada(nodCoada** prim, nodCoada** ultim) {
	Student stud; 
	while (get(prim, ultim, &stud) == 1) {
		free(stud.nume);
	}
}

void main() {
	FILE* file = fopen("DetaliiStudenti.txt", "r");

	int nrStudentiFisier = 0;
	fscanf(file, "%d", &nrStudentiFisier);

	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;

	char buffer[40];
	Student s;

	for (int i = 0; i < nrStudentiFisier; i++) {
		fscanf(file, "%d", &s.nrCrt);

		fscanf(file, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);

		fscanf(file, "%f", &s.media);

		put(&prim, s);
	}
	fclose(file);

	printf("\n---------------- Coada ---------------- \n");
	traversareCoada(prim);

	dezalocaCoada(&prim, &ultim);
}