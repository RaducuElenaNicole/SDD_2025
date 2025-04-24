#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct student student;
typedef struct nod nod;
typedef struct ht ht;

struct student {
	int id;
	char* nume;
	char* materie;
	int nrNote;
	float* nota;
};

struct nod {
	student info;
	nod* next;
};

struct ht {
	int dim;
	nod** vector;
};

student initStudent(int id, const char* nume, const char* materie, int nrNote, float* nota) {
	student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);
	s.materie = (char*)malloc(sizeof(char) * (strlen(materie) + 1));
	strcpy(s.materie, materie);
	s.nrNote = nrNote;

	s.nota = (float*)malloc(sizeof(float) * s.nrNote);
	for (int i = 0; i < s.nrNote; i++) {
		s.nota[i] = nota[i];
	}

	return s;
}

void afisareStudent(student s) {
	printf("   ID: %d | Nume: %s | Materie: %s | Nr. note: %d: ", s.id, s.nume, s.materie, s.nrNote);
	for (int i = 0; i < s.nrNote; i++) {
		printf("Nota: %.2f, ", s.nota[i]);
	}
	printf("\n");
}

void inserareFinal(nod** cap, student s) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initStudent(s.id, s.nume, s.materie, s.nrNote, s.nota);
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void afisareLs(nod* cap) {
	while (cap) {
		afisareStudent(cap->info);
		cap = cap->next;
	}
}

// HASH
int hash(int dim, const char* nume) {
	return (nume[0] + 16) % dim;
}

// INITIALIZARE HT
ht initHash(int dim) {
	ht ht;
	ht.dim = dim;
	ht.vector = (nod*)malloc(sizeof(nod) * dim);
	for (int i = 0; i < dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

// INSERARE HT
void inserareHt(ht ht, student s) {
	if (ht.dim > 0) {
		int poz = hash(ht.dim, s.nume);
		if (poz >= 0 && poz < ht.dim) {
			inserareFinal(&(ht.vector[poz]), s);
		}

	}
}

// AFISARE HT
void afisareHt(ht ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i]) {
			printf("\nPozitie: %d - Adresa: %p\n", i, ht.vector[i]);
			afisareLs(ht.vector[i]);
			printf("\n");
		}
		else {
			printf("Pozitie: %d - Adresa: %p\n", i, ht.vector[i]);
		}
	}
}

// DEZALOCARI
// LS
void dezalocareLs(nod** cap) {
	nod* aux = *cap;
	while (aux) {
		free(aux->info.nume);
		free(aux->info.materie);
		free(aux->info.nota);
		nod* temp = aux;
		aux = aux->next;
		free(temp);
	}
}
// HT
void dezalocareHt(ht ht) {
	for (int i = 0; i < ht.dim; i++) {
		dezalocareLs(&(ht.vector[i]));
	}
	free(ht.vector);
}

void citireFisier(const char* file, ht ht) { 
	FILE* f = fopen(file, "r");
	char* token;
	char buffer[100];
	char separator[] = ",\n";
	while (fgets(buffer, 100, f) != NULL) {
		student s;
		token = strtok(buffer, separator);
		s.id = atoi(token);

		token = strtok(NULL, separator);
		s.nume = (char*)malloc(strlen(token) + 1);
		strcpy(s.nume, token);

		token = strtok(NULL, separator);
		s.materie = (char*)malloc(strlen(token) + 1);
		strcpy(s.materie, token);

		token = strtok(NULL, separator);
		s.nrNote = atoi(token);

		s.nota = (float*)malloc(sizeof(float) * s.nrNote);
		for (int i = 0; i < s.nrNote; i++) {
			token = strtok(NULL, separator);
			s.nota[i] = atof(token);
		}

		inserareHt(ht, s);
	}
	fclose(f);
}

// stergere nod dupa criteriu
void stergereNodCriteriu(ht ht, const char* nume) {
	if (ht.vector) {
		for (int i = 0; i < ht.dim; i++) {
			nod* aux = ht.vector[i];
			nod* prev = NULL; // nodul de dinaintea nodului aux 
			while (aux) {
				if (aux != NULL && strcmp(aux->info.nume, nume) == 0) {
					nod* deSters = aux;

					if (prev == NULL) {
						// nodul care trebuie sters este primul din LS
						aux = aux->next;
						ht.vector[i] = aux;
					}
					else {
						// nodul care trebuie sters nu este primul 
						aux = aux->next;
						prev->next = aux->next;
					}

					free(deSters->info.nume);
					free(deSters->info.materie);
					free(deSters->info.nota);
					free(deSters);
				}
				else {
					prev = aux;
					aux = aux->next;
				}
			}
		}
	}
}

// memorare in vector a tuturor studentilor a caror nume incep cu litera A
int contor(ht ht, char* primaLitera) {
	int nr = 0; 
	if (ht.vector) {
		int poz = hash(ht.dim, primaLitera);
		nod* aux = ht.vector[poz];
		while (aux) {
			nr++; 
			aux = aux->next;
		}
	}
	return nr;
}

student* conversieLaVector(ht ht, char* primaLitera) {
	int dim = contor(ht, primaLitera);
	student* vector = (student*)malloc(sizeof(student) * dim);
	int index = 0;

	if (ht.vector) {
		int poz = hash(ht.dim, primaLitera);

		nod* aux = ht.vector[poz];
		while (aux) {
			vector[index] = aux->info;
			aux = aux->next;
			index++;
		}
	}

	return vector;
}

void main() {
	nod* cap = NULL;

	int dim = 23;
	ht ht = initHash(dim);

	citireFisier("Text.txt", ht);
	afisareHt(ht);

	printf("\n\nVector\n");
	int dimV = contor(ht, "A");
	student* vector = conversieLaVector(ht, "A");
	for (int i = 0; i < dimV; i++) {
		afisareStudent(vector[i]);
	}

	printf("\n\nStergere\n");
	stergereNodCriteriu(ht, "Ana");
	stergereNodCriteriu(ht, "Lorena");
	stergereNodCriteriu(ht, "Maria");
	afisareHt(ht);

	dezalocareHt(ht);
}