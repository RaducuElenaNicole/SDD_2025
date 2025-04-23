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

typedef struct HashTable HashTable;
struct HashTable {
	struct nodLS** vectHashT; 
	int nrElem; 
};

void inserareSfarsitLS(nodLS** cap, Student detaliiStudent) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf = detaliiStudent;
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		nodLS* temp = (*cap);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traversareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("   NrCrt: %d | Nume: %s | Media: %5.2f \n",
			temp->inf.nrCrt, temp->inf.nume, temp->inf.media);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS** cap) {
	nodLS* temp = (*cap);
	while (temp) {
		if (temp->inf.nume != NULL) {
			free(temp->inf.nume);
		}

		nodLS* aux = temp;
		temp = temp->next;
		free(aux);
	}
}

HashTable initializareHT(int dimensiune) {
	HashTable tabela; 
	tabela.nrElem = dimensiune; 
	tabela.vectHashT = (nodLS**)malloc(sizeof(nodLS) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		tabela.vectHashT[i] = NULL;
	}
	return tabela;
}

int functieHash(HashTable tabela, char* nume) {
	return (nume[0] % tabela.nrElem);
}

void inserareHT(HashTable tabela, Student detaliiStudent) {
	if (tabela.nrElem > 0) {
		int pozitie = functieHash(tabela, detaliiStudent.nume);
		if (pozitie >= 0 && pozitie <= tabela.nrElem) {
			inserareSfarsitLS(&tabela.vectHashT[pozitie], detaliiStudent);
		}
	}
}

void traversareHT(HashTable tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vectHashT[i]) {
			printf("\nPozitia %d\n", i);
			traversareLS(tabela.vectHashT[i]);
			printf("\n");
		}
		else {
			printf("\nPozitia %d\n", i);
		}
	}
}
void dezalocareHT(HashTable tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		dezalocareLS(&tabela.vectHashT[i]);
	}
	free(tabela.vectHashT);
}


void main() {
	FILE* file = fopen("DetaliiStudenti.txt", "r");

	int nrStudentiFisier = 0;
	fscanf(file, "%d", &nrStudentiFisier);

	char buffer[40];
	Student s;

	int dim = 8;
	HashTable tabela = initializareHT(dim);
	
	for (int i = 0; i < nrStudentiFisier; i++) {
		fscanf(file, "%d", &s.nrCrt);

		fscanf(file, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);

		fscanf(file, "%f", &s.media);

		inserareHT(tabela, s);
	}
	fclose(file);

	printf("\n---------------- Hash Table ---------------- \n");
	traversareHT(tabela);

	dezalocareHT(tabela);
}