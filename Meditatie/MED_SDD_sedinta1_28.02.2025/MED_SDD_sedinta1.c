// Sedinta 1 - SDD - 28/02/2025

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct Student{
	unsigned int id;
	char* nume; 
	float medie;
}Student;

typedef struct nodLS {
	Student inf; // informatia 
	struct nodLS* next; // adresa urmatorului nod din lista 
}nodLS;

Student creeazaStudent(unsigned int _id, char* _nume, float _medie) {
	Student stud;
	stud.id = _id;
	stud.nume = (char*)malloc(sizeof(char) * (strlen(_nume) + 1));
	strcpy(stud.nume, _nume);
	stud.medie = _medie;
	return stud;
}

// inserare: inceput + final + interior 
nodLS* insereazaInceput(nodLS* cap, Student stud) {
	// UNDE INSEREZ? -> nod* cap
	// CE INSEREZ? -> Student inf
	
	// se formeaza/creeaza nodul -> se poate face si o functie de creeare nod (pas 1 + pas 2)
	// pas 1: Alocare de memorie (se aloca memorie pentru nodul nou care trebuie adaugat in lista)
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS)); // se retine adresa de memorie

	// pas 2: 
	// metoda1: shallow copy 
	nou->inf = stud;
	// metoda2: deep copy
	// nou->inf = creeazaStudent(stud.id, stud.nume, stud.medie);
	nou->next = NULL;

	// pas 3: Inserarea propriu-zisa in lista 
	// daca lista e goala 
	if (cap == NULL) {
		cap = nou; 
	}else{
		// este minim un nod in lista 
		nou->next = cap; 
		cap = nou; // nodul nou devine cap 
	}

	// pas 4: Returnearea nodului CAP => se returneaza adresa primului nod din lista 
	return cap; // Intotdeauna !!!!!
}

void insereazaFinal(nodLS** cap, Student stud) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf = creeazaStudent(stud.id, stud.nume, stud.medie);
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou; 
	}
	else {
		nodLS* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

// afisare 
void afiseaza(nodLS* cap) {
	nodLS* aux = cap;
	while (aux) {
		printf("ID: %u | NUME: %s | MEDIA: %5.2f \n", aux->inf.id, aux->inf.nume, aux->inf.medie);

		aux = aux->next;
	}
}

// dezalocare 
void dezaloc(nodLS* cap) {
	nodLS* aux = cap;
	while (aux) {
		free(aux->inf.nume); 
		nodLS* temp = aux->next;
		free(aux);
		aux = temp;
	}
}

// stergere 


void main() {
	Student s1 = creeazaStudent(1, "Ana", 9.1f);
	Student s2 = creeazaStudent(2, "Ileana", 10);
	Student s3 = creeazaStudent(3, "Andrei", 4.1f);
	Student s4 = creeazaStudent(4, "Stefania", 6.50f);
	Student s5 = creeazaStudent(5, "Maria", 5.25f);
	Student s6 = creeazaStudent(6, "Ionut", 4.65f);

	nodLS* cap = NULL;
	cap = insereazaInceput(cap, s1);
	cap = insereazaInceput(cap, s2);
	cap = insereazaInceput(cap, s3);
	cap = insereazaInceput(cap, s4);
	cap = insereazaInceput(cap, s5);

	insereazaFinal(&cap, s6);

	afiseaza(cap); 

	dezaloc(cap);
}