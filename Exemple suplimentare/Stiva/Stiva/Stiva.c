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

typedef struct nodStiva nodStiva;
struct nodStiva {
	Student inf; 
	nodStiva* next;
};

// inserarare la inceput
void push(nodStiva** varf, Student detaliiStudent) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = detaliiStudent;
	nou->next = (*varf);
	(*varf) = nou;
}

// extragere de la inceput
int pop(nodStiva** varf, Student* detaliiStudentExtras) {
	if ((*varf) == NULL) {
		return -1; // nu s-a gasit nimic in stiva 
	}
	else {
		(*detaliiStudentExtras) = (*varf)->inf;

		nodStiva* nodExtras = (*varf);
		(*varf) = (*varf)->next;

		//free(nodExtras->inf.nume);
		free(nodExtras);

		return 1; // s-a extras cu succes nodul de la inceputul stivei si s-a memorat informatia utila 
	}
}

void traversareStiva(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp) {
		printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
			temp->inf.nrCrt, temp->inf.nume, temp->inf.media);
		temp = temp->next;
	}
}

void dezalocareStiva(nodStiva** varf) {
	Student stud; 
	while (pop(varf, &stud) == 1) {
		free(stud.nume);
	}
}

void main() {
	FILE* file = fopen("DetaliiStudenti.txt", "r");

	int nrStudentiFisier = 0;
	fscanf(file, "%d", &nrStudentiFisier);

	nodStiva* varfStv = NULL;

	char buffer[40];
	Student s;

	for (int i = 0; i < nrStudentiFisier; i++) {
		fscanf(file, "%d", &s.nrCrt);

		fscanf(file, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);

		fscanf(file, "%f", &s.media);

		push(&varfStv, s);
	}
	fclose(file);

	printf("\n---------------- Stiva ---------------- \n");
	traversareStiva(varfStv);

	printf("\n---------------- Nod Extras ---------------- \n");
	Student detaliiStudentExtras; 
	pop(&varfStv, &detaliiStudentExtras);
	printf("NrCrt: %d | Nume: %s | Media: %5.2f \n",
		detaliiStudentExtras.nrCrt, detaliiStudentExtras.nume, detaliiStudentExtras.media);

	dezalocareStiva(&varfStv);
}