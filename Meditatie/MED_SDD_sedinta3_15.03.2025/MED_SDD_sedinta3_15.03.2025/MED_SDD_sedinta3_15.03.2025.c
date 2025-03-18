// Sedinta 3 - 15/03/2025
// Lista Dubla Circulara

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct nodLD nodLD;
typedef struct Student Student;
typedef struct LD LD;

struct Student {
	unsigned int id;
	char* nume;
	int nrMaterii;
	float* note;
};

struct nodLD {
	nodLD* prev;
	Student info;
	nodLD* next;
};

struct LD
{
	nodLD* prim; 
	nodLD* ultim;
};

Student creeazaStudent(unsigned int id, const char* nume, 
						int nrMaterii, float* note){
	Student stud;
	stud.id = id;
	stud.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy_s(stud.nume, strlen(nume) + 1, nume);
	stud.nrMaterii = nrMaterii;
	stud.note = malloc(sizeof(float) * nrMaterii);
	for (int i = 0; i < nrMaterii; i++) {
		stud.note[i] = note[i];
	}
	return stud;
}

LD insereazaNodLDCircularaFinal(LD lista, Student stud) {
	nodLD* nou = malloc(sizeof(nodLD));

	nou->info = creeazaStudent(stud.id, stud.nume, stud.nrMaterii, stud.note);

	nou->prev = NULL;
	nou->next = NULL;

	if (lista.prim == NULL) {
		lista.prim = lista.ultim = nou;
		nou->next = lista.prim;
		nou->prev = lista.prim;
	}
	else {
		lista.ultim->next = nou;
		nou->prev = lista.ultim;
		lista.prim->prev = nou;
		nou->next = lista.prim;
		lista.ultim = nou;
	}
	return lista;
}

void afiseaza(LD lista) {
	nodLD* aux = lista.prim;
	while (aux->next != lista.prim) {
		printf("Student -> Id: %d | Nume: %s | NrMAterii: %d | Note:",
			aux->info.id, aux->info.nume, aux->info.nrMaterii);
		for (int i = 0; i < aux->info.nrMaterii; i++) {
			printf("\n  Nota %d: %.2f", i + 1, aux->info.note[i]);
		}
		printf("\n");
		aux = aux->next;
	}

	// pentru ultimul nod din lista
	printf("Student -> Id: %d | Nume: %s | NrMAterii: %d | Note:",
		aux->info.id, aux->info.nume, aux->info.nrMaterii);
	for (int i = 0; i < aux->info.nrMaterii; i++) {
		printf("\n  Nota %d: %.2f", i + 1, aux->info.note[i]);
	}
	printf("\n");
}

void dezalocaLista(LD lista) {
	nodLD* aux = lista.prim;
	while (aux->next != lista.prim) {
		free(aux->info.nume);
		free(aux->info.note);
		nodLD* temp = aux->next;
		free(aux);
		aux = temp;
	}
	free(aux->info.nume);
	free(aux->info.note);
	free(aux);
}

void main() {
	Student s;
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	char linieBuffer[100];
	char* token;
	char separator[] = ",";

	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (fgets(linieBuffer, sizeof(linieBuffer), f)) {
			token = strtok(linieBuffer, separator);
			s.id = atoi(token);

			token = strtok(NULL, separator);
			s.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy_s(s.nume, sizeof(char) * (strlen(token) + 1), token);

			token = strtok(NULL, separator);
			s.nrMaterii = atoi(token);

			s.note = malloc(sizeof(float) * s.nrMaterii);
			for (int i = 0; i < s.nrMaterii; i++) {
				token = strtok(NULL, separator);
				s.note[i] = atof(token);
			}

			lista = insereazaNodLDCircularaFinal(lista, s);

			free(s.note);
			free(s.nume);
		}
	}
	fclose(f);

	afiseaza(lista);

	dezalocaLista(lista);
}