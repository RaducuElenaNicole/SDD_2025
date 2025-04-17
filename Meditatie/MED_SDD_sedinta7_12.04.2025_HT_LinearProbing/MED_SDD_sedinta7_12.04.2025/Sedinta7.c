// Sedinta 7 - 12/04/2025
// HashTable - Linear Probing 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct nodLS nodLS;
typedef struct Student Student;
typedef struct HashTable HashTable;

struct Student {
	unsigned id;
	char* nume;
	int nrMaterii;
	float* note;
};

struct HashTable {
	int dim; 
	Student** vectHT;
};

Student* creareStudent(unsigned id, const char* nume, int nrMaterii, float* note) {
	Student* s;
	s = (Student*)malloc(sizeof(Student));

	s->id = id;
	s->nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy_s(s->nume, sizeof(char) * (strlen(nume) + 1), nume);
	s->nrMaterii = nrMaterii;
	s->note = (float*)malloc(sizeof(float) * nrMaterii);
	for (int i = 0; i < nrMaterii; i++) {
		s->note[i] = note[i];
	}
	return s;
}

void afisareStudent(Student s) {
	printf("    Student { Id: %u | Nume: %s | NrMaterii: %d | Note: ", s.id, s.nume, s.nrMaterii);
	for (int i = 0; i < s.nrMaterii; i++) {
		printf("\n        Nota %d: %.2f", i + 1, s.note[i]);
	}
	printf("}");
	printf("\n\n");
}

int functieHash(HashTable tabela, unsigned int id) {
	return id % tabela.dim;
}

void inserareHashT(HashTable tabela, Student* stud) {
	int pozitie = 0;
	if(tabela.vectHT) {
		pozitie = functieHash(tabela, stud->id);
		if (tabela.vectHT[pozitie] == NULL) {
			tabela.vectHT[pozitie] = stud;
		}
		else {
			int index = 1; 
			while (pozitie + index < tabela.dim) {
				if (tabela.vectHT[pozitie + index] == NULL) {
					tabela.vectHT[pozitie + index] = stud;
					pozitie = pozitie + index;
				}
				index++;
			}
		}
	}
}

void afisareHashTable(HashTable tabela) {
	if (tabela.vectHT) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vectHT[i] != NULL) {
				printf("Pozitia %d -> Student { Id: %u | Nume: %s | NrMaterii: %d | Note: ",
					i,
					tabela.vectHT[i]->id,
					tabela.vectHT[i]->nume,
					tabela.vectHT[i]->nrMaterii);
				for (int j = 0; j < tabela.vectHT[i]->nrMaterii; j++) {
					printf("%.2f", tabela.vectHT[i]->note[j]);
				}
				printf(" }\n");
			}
		}
	}
}

void dezalocareHashT(HashTable tabela) {
	if (tabela.vectHT) {
		for (int i = 0; i < tabela.dim; i++) {
			free(tabela.vectHT[i]->nume);
			free(tabela.vectHT[i]->note);
			free(tabela.vectHT[i]);
		}
		free(tabela.vectHT);
	}
}

void main() {

	Student s;

	char liniebuffer[100];
	char* aux;
	char sep[4] = ",\n";

	HashTable tabela; 
	tabela.dim = 10; 
	tabela.vectHT = (Student**)malloc(sizeof(Student*) * tabela.dim);
	for (int i = 0; i < tabela.dim; i++) {
		tabela.vectHT[i] = NULL;
	}

	FILE* f = fopen("studenti.txt", "r");
	if (f) {
		while (fgets(liniebuffer, sizeof(liniebuffer), f)) { 

			aux = strtok(liniebuffer, sep);

			s.id = atoi(aux);

			aux = strtok(NULL, sep);
			s.nume = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
			strcpy_s(s.nume, (strlen(aux) + 1), aux);

			aux = strtok(NULL, sep);
			s.nrMaterii = atoi(aux);

			s.note = (float*)malloc(sizeof(float) * s.nrMaterii);
			for (int i = 0; i < s.nrMaterii; i++) {
				aux = strtok(NULL, sep);
				s.note[i] = atof(aux);
			}

			Student* copie = creareStudent(s.id, s.nume, s.nrMaterii, s.note);
			inserareHashT(tabela, copie);

			free(s.note);
			free(s.nume);
		}
	}
	fclose(f);
	afisareHashTable(tabela);
}