// Arbore Binar = BST

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct Examen Examen;
struct Examen {
	int id; 
	char* disciplina;
	float nota;
};

typedef struct Nod Nod;
struct Nod {
	Examen info; 
	Nod* stanga; 
	Nod* dreapta;
};

Examen initExamen(int id, char* disciplina, float nota) {
	Examen nou;

	nou.id = id;

	nou.disciplina = (char*)malloc(sizeof(char) * (strlen(disciplina) + 1));
	strcpy(nou.disciplina, disciplina);

	nou.nota = nota;

	return nou;
}

void afiseazaExamen(Examen exm) {
	printf("Id: %d | Disciplina: %s | Nota: %.2f \n",
		exm.id, exm.disciplina, exm.nota);
}

void inserareBST(Nod** radacina, Examen exm) {
	if ((*radacina) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = exm; 
		nou->stanga = NULL;
		nou->dreapta = NULL;
		(*radacina) = nou; 
	}
	else if (exm.id < (*radacina)->info.id) {
		inserareBST(&(*radacina)->stanga, exm);
	}
	else {
		inserareBST(&(*radacina)->dreapta, exm);
	}
}

void parcurgereInordineArbore(Nod* radacina) {
	// stanga - radacina - dreapta (SRD)
	if (radacina) {
		parcurgereInordineArbore(radacina->stanga);
		afiseazaExamen(radacina->info);
		parcurgereInordineArbore(radacina->dreapta);
	}
}

void parcurgerePostordineArbore(Nod* radacina) {
	// stanga - dreapta - radacina (SDR)
	if (radacina) {
		parcurgerePostordineArbore(radacina->stanga);
		parcurgerePostordineArbore(radacina->dreapta);
		afiseazaExamen(radacina->info);
	}
}

void parcurgerePreordineArbore(Nod* radacina) {
	// radacina - stanga - dreapta (RSD)
	if (radacina) {
		afiseazaExamen(radacina->info);
		parcurgerePreordineArbore(radacina->stanga);
		parcurgerePreordineArbore(radacina->dreapta);
	}
}

Examen cautaExamenById(Nod* radacina, int idCautat) {
	if (radacina == NULL) {
		return initExamen(-1, "Necunoscuta", 0);
	}
	else if (idCautat == radacina->info.id) {
		return initExamen(radacina->info.id, radacina->info.disciplina, radacina->info.nota);
	}
	else if (idCautat < radacina->info.id) {
		return cautaExamenById(radacina->stanga, idCautat);
	}
	else {
		return cautaExamenById(radacina->dreapta, idCautat);
	}
}

void dezalocare(Nod** radacina) {
	if ((*radacina) != NULL) {
		dezalocare(&(*radacina)->stanga);
		dezalocare(&(*radacina)->dreapta);

		free((*radacina)->info.disciplina);
		free((*radacina));
	}
}

void main() {
	printf("\n");

	Nod* radacinaArboreBinar = NULL; 

	inserareBST(&radacinaArboreBinar, initExamen(7, "SDD", 5.5));
	inserareBST(&radacinaArboreBinar, initExamen(4, "PAW", 10));
	inserareBST(&radacinaArboreBinar, initExamen(9, "PEAG", 5));
	inserareBST(&radacinaArboreBinar, initExamen(3, "MACRO", 8.50));
	inserareBST(&radacinaArboreBinar, initExamen(5, "ATP", 6.90));
	inserareBST(&radacinaArboreBinar, initExamen(8, "SGBD", 7.85));
	inserareBST(&radacinaArboreBinar, initExamen(2, "BCO", 6.90));
	inserareBST(&radacinaArboreBinar, initExamen(1, "MICRO", 9.90));

	printf("-------------------- Parcurgere arbore - INORDINE --------------------\n");
	parcurgereInordineArbore(radacinaArboreBinar);

	printf("\n\n");

	printf("-------------------- Parcurgere arbore - POSTORDINE --------------------\n");
	parcurgerePostordineArbore(radacinaArboreBinar);

	printf("\n\n");

	printf("-------------------- Parcurgere arbore - PREORDINE --------------------\n");
	parcurgerePreordineArbore(radacinaArboreBinar);

	printf("\n\n");

	printf("-------------------- Cautare examen By ID --------------------\n");
	Examen examenCautat = cautaExamenById(radacinaArboreBinar, 5);
	afiseazaExamen(examenCautat);
	free(examenCautat.disciplina);

	printf("\n\n");

	dezalocare(&radacinaArboreBinar);

}