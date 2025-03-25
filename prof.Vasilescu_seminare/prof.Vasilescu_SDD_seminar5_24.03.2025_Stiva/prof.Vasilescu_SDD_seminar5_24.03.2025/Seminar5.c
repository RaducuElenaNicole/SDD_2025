// Seminar 5 - SDD - 24/03/2025

// STIVA


#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct nodStiva nodStiva;
typedef struct nodCoada nodCoada;
typedef struct Masina Masina;


struct Masina {
	char* marca;
	float putere;
	int anFabricatie;
};

struct nodStiva {
	Masina info;
	nodStiva* next;
};

struct nodCoada {
	Masina info;
	nodCoada* next;
};

// deep copy
Masina creeazaMasina(char* _marca, float _putere, int _anFabricatie) {
	Masina m;

	m.marca = (char*)malloc(sizeof(_marca) * (strlen(_marca) + 1));
	strcpy(m.marca, _marca);
	m.putere = _putere;
	m.anFabricatie = _anFabricatie;

	return m;
}

void afiseazaMasina(Masina m) {
	printf("Masina { Marca: %s | Putere: %.2f | An fabricatie: %d} \n", 
		m.marca, m.putere, m.anFabricatie);
}

// inserare inceput 
void push(nodStiva** varf, Masina m) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	//nou->info = creeazaMasina(m.marca, m.putere, m.anFabricatie);

	nou->next = (*varf);
	nou->info = m; // shallow copy 
	(*varf) = nou;
}

//int pop(nodStiva** varf, Masina* m) {
//	if ((*varf) == NULL) {
//		return 0;
//	}
//	else {
//		// memorez masina din nodul pe care il extrag -> dar trebuie deep copy 
//		(*m) = (*varf)->info;
//		
//		// se schimba varful stivei 
//		nodStiva* temp = *varf;
//		(*varf) = (*varf)->next;
//
//		// dezalocare 
//		free(temp->info.marca);
//		free(temp);
//
//		return 0;
//	}
//}

// extragere inceput 
Masina pop(nodStiva** varf) {
	Masina m;

	if ((*varf) == NULL) {
		return creeazaMasina("Necunoscuta", 0.0, 0);
	}
	else {
		m = (*varf)->info;

		nodStiva* temp = *varf;
		(*varf) = (*varf)->next;

		free(temp);

		return m;
	}
}

// inserare la sfarsit 
void put(nodCoada** coada, Masina m) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));

	nou->info = m;

	nou->next = NULL;

	if ((*coada) == NULL) {
		(*coada) = nou;
	}
	else {
		nodCoada* temp = (*coada);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void main() {
	Masina m1 = creeazaMasina("Audi", 130.50, 2007);
	printf("m1 = "); 
	afiseazaMasina(m1); 
	printf("\n\n");

	Masina m2 = creeazaMasina("Dacia Logan", 110.90, 2008);
	printf("m2 = ");
	afiseazaMasina(m2);
	printf("\n\n");

	Masina m3 = creeazaMasina("BMW", 210, 2023);
	printf("m3 = ");
	afiseazaMasina(m3);
	printf("\n\n");


	nodStiva* varfStiva = NULL;
	push(&varfStiva, m1);
	push(&varfStiva, m2);
	push(&varfStiva, m3);

	Masina masina;
	while (varfStiva != NULL) {
		masina = pop(&varfStiva);
		afiseazaMasina(masina);
		free(masina.marca);
	}
	// in acest moment, stiva este dezalocata (inclusiv char* marca)

	nodCoada* coada = NULL;

	Masina m4 = creeazaMasina("Audi", 130.50, 2007);
	Masina m5 = creeazaMasina("Dacia Logan", 110.90, 2008);
	Masina m6 = creeazaMasina("BMW", 210, 2023);

	put(&coada, m4);
	put(&coada, m5);
	put(&coada, m6);

	printf("\n\n");

	Masina masina2;
	while (coada != NULL) {
		masina2 = pop(&coada);
		afiseazaMasina(masina2);
		free(masina2.marca);
	}
}