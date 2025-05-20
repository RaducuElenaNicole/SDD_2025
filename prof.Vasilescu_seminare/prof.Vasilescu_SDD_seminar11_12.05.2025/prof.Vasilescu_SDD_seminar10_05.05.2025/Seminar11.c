// Arbore Echilibrat = Arbore AVL (particularizare a arborelui binar de cautare)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h> // pt bool

typedef struct Examen Examen;
struct Examen {
	int id; 
	char* disciplina;
	float nota;
};

typedef struct NodAVL NodAVL;
struct NodAVL {
	Examen info; 
	NodAVL* stanga; 
	NodAVL* dreapta;
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

int inaltimeArbore(NodAVL* radacina) {
	if (radacina != NULL) {
		int inaltimeStanga = inaltimeArbore(radacina->stanga); 
		int inaltimeDreapta = inaltimeArbore(radacina->dreapta);

		if (inaltimeDreapta > inaltimeStanga) {
			return 1 + inaltimeDreapta;
		}
		else {
			return 1 + inaltimeStanga;
		}
	}
	else {
		return 0; 
	}
}

int diferentaInaltimi(NodAVL* radacina) {
	if (radacina != NULL) {
		return inaltimeArbore(radacina->stanga) - inaltimeArbore(radacina->dreapta);
	}
	else {
		return 0; 
	}
}

void rotireDreapta(NodAVL** radacina) {
	NodAVL* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = (*radacina);

	(*radacina) = aux;
}

void rotireStanga(NodAVL** radacina) {
	NodAVL* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);

	(*radacina) = aux;
}

void inserareAVL(NodAVL** radacina, Examen exm) {
	if ((*radacina) == NULL) {
		NodAVL* nou = (NodAVL*)malloc(sizeof(NodAVL));
		nou->info = exm; 
		nou->stanga = NULL;
		nou->dreapta = NULL;
		(*radacina) = nou; 
	}
	else if (exm.id < (*radacina)->info.id) {
		inserareAVL(&(*radacina)->stanga, exm);
	}
	else {
		inserareAVL(&(*radacina)->dreapta, exm);
	}

	// diferente inailtimi subarbori 
	// st - dr = 2 => dezechilibru pe partea stanga 
	// st - dr = -2 => dezechilibru pe partea dreapta

	int difInaltimi = diferentaInaltimi(*radacina);
	if (difInaltimi == 2) {
		if (diferentaInaltimi((*radacina)->stanga) == -1) {
			rotireStanga(&(*radacina)->stanga);
		}
		rotireDreapta(radacina);
	}
	else if (difInaltimi == -2) {
		if (diferentaInaltimi((*radacina)->stanga) == 1) {
			rotireStanga(&(*radacina)->stanga);
		}
		rotireStanga(radacina);
	}
	else {

	}
}

void parcurgereInordineArbore(NodAVL* radacina) {
	// stanga - radacina - dreapta (SRD)
	if (radacina) {
		parcurgereInordineArbore(radacina->stanga);
		afiseazaExamen(radacina->info);
		parcurgereInordineArbore(radacina->dreapta);
	}
}

void parcurgerePostordineArbore(NodAVL* radacina) {
	// stanga - dreapta - radacina (SDR)
	if (radacina) {
		parcurgerePostordineArbore(radacina->stanga);
		parcurgerePostordineArbore(radacina->dreapta);
		afiseazaExamen(radacina->info);
	}
}

void parcurgerePreordineArbore(NodAVL* radacina) {
	// radacina - stanga - dreapta (RSD)
	if (radacina) {
		afiseazaExamen(radacina->info);
		parcurgerePreordineArbore(radacina->stanga);
		parcurgerePreordineArbore(radacina->dreapta);
	}
}

Examen cautaExamenById(NodAVL* radacina, int idCautat) {
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

void dezalocare(NodAVL** radacina) {
	if ((*radacina) != NULL) {
		dezalocare(&(*radacina)->stanga);
		dezalocare(&(*radacina)->dreapta);

		free((*radacina)->info.disciplina);
		free((*radacina));
	}
}

bool existaFrunze(NodAVL* radacina, int id) {
	if (radacina == NULL)
		return false;

	if (radacina->info.id == id && radacina->dreapta == NULL && radacina-> stanga == NULL) {
		return true;
	}

	return existaFrunze(radacina->stanga, id) || existaFrunze(radacina->dreapta, id);
}

void main() {
	printf("\n");

	NodAVL* radacinaArboreBinar = NULL; 

	inserareAVL(&radacinaArboreBinar, initExamen(7, "SDD", 5.5));
	inserareAVL(&radacinaArboreBinar, initExamen(4, "PAW", 10));
	inserareAVL(&radacinaArboreBinar, initExamen(9, "PEAG", 5));
	inserareAVL(&radacinaArboreBinar, initExamen(3, "MACRO", 8.50));
	inserareAVL(&radacinaArboreBinar, initExamen(5, "ATP", 6.90));
	inserareAVL(&radacinaArboreBinar, initExamen(8, "SGBD", 7.85));
	inserareAVL(&radacinaArboreBinar, initExamen(2, "BCO", 6.90));
	inserareAVL(&radacinaArboreBinar, initExamen(1, "MICRO", 9.90));

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

	printf("-------------------- --------------------\n");
	printf("Diferenta inaltimi: %d", diferentaInaltimi(radacinaArboreBinar));

	printf("\n\n");

	printf("-------------------- --------------------\n");
	if (existaFrunze(radacinaArboreBinar, 2)) {
		printf("Este frunza!");
	}
	else {
		printf("NU este frunza!");
	}

	printf("\n\n");

	dezalocare(&radacinaArboreBinar);
}