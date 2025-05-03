// Arbore AVL

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Rezervare Rezervare;
typedef struct nodArbore nodArbore;

struct Rezervare {
	unsigned int id;
	char* hotel;
	unsigned char nrCamere;
	char* client;
	float suma; 
};

struct nodArbore {
	Rezervare info;
	nodArbore* stanga;
	nodArbore* dreapta;

	int grad;
};

Rezervare creeazaRezervare(unsigned int id, char* hotel,
	unsigned char nrCamere, char* client, float suma) {
	Rezervare rez;
	rez.id = id;
	rez.hotel = (char*)malloc(sizeof(char) * (strlen(hotel) + 1));
	strcpy(rez.hotel, hotel);
	rez.nrCamere = nrCamere;
	rez.client = (char*)malloc(sizeof(char) * (strlen(client) + 1));
	strcpy(rez.client, client);
	rez.suma = suma;

	return rez;
}

nodArbore* creeazaNodArbore(Rezervare r, nodArbore* stg, nodArbore* drp) {
	nodArbore* nou = (nodArbore*)malloc(sizeof(nodArbore));
	nou->info = creeazaRezervare(r.id, r.hotel, r.nrCamere, r.client, r.suma);

	nou->dreapta = drp;
	nou->stanga = stg;

	return nou;
}

nodArbore* insereazaNodArbore(nodArbore* radacina, Rezervare r) {
	if (radacina) {
		if (r.id < radacina->info.id) {
			radacina->stanga = insereazaNodArbore(radacina->stanga, r);
			return radacina;
		}
		else if (r.id > radacina->info.id) {
			radacina->dreapta = insereazaNodArbore(radacina->dreapta, r);
			return radacina;
		}
		else
		{
			return radacina;
		}
	}
	else {
		return creeazaNodArbore(r, NULL, NULL);
	}
}

// traversare - preordine - RSD
void preordine(nodArbore* rad) {
	if (rad) {
		printf("Id: %3u | Hotel: %-10s | NrCamere: %2u | NumeClient: %-10s | Pret: %8.2f | Grad arbore: %2d\n",
			rad->info.id, rad->info.hotel, rad->info.nrCamere, rad->info.client, rad->info.suma, rad->grad);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

// traversare - inordine - SRD
void inordine(nodArbore* rad) {
	if (rad) {
		inordine(rad->stanga);
		printf("Id: %3u | Hotel: %-10s | NrCamere: %2u | NumeClient: %-10s | Pret: %8.2f | Grad arbore: %2d\n",
			rad->info.id, rad->info.hotel, rad->info.nrCamere, rad->info.client, rad->info.suma, rad->grad);
		inordine(rad->dreapta);
	}
}

// traversare - postordine - SDR
void postordine(nodArbore* rad) {
	if (rad) {
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("Id: %3u | Hotel: %-10s | NrCamere: %2u | NumeClient: %-10s | Pret: %8.2f | Grad arbore: %2d\n",
			rad->info.id, rad->info.hotel, rad->info.nrCamere, rad->info.client, rad->info.suma, rad->grad);
	}
}

void afisareArboreNivel(nodArbore* radacina, int nivel) {
	if (radacina == NULL)
		return;

	afisareArboreNivel(radacina->dreapta, nivel + 1);

	printf("Nivel: %d     ", nivel);
	for (int i = 0; i < nivel; i++)
		printf("    ");

	printf("%d (%s)\n", radacina->info.id, radacina->info.hotel);

	afisareArboreNivel(radacina->stanga, nivel + 1);
}

void dezalocareArbore(nodArbore* radacina) {
	if (radacina) {
		nodArbore* arboreStg = radacina->stanga;
		nodArbore* arboreDrp = radacina->dreapta;

		free(radacina->info.hotel);
		free(radacina->info.client);
		free(radacina);

		dezalocareArbore(arboreStg);
		dezalocareArbore(arboreDrp);
	}
}

int maxim(int a, int b) {
	if (a > b)
		return a;
	else return b;

	//return a > b ? a : b;
}

int nrNiveluriArbore(nodArbore* radacina) { // Da cu 1 in plus!!!!
	if (radacina == NULL) {
		return 0;
	}

	if (radacina) {
		int nrNivelStanga = nrNiveluriArbore(radacina->stanga);
		int nrNivelDreapta = nrNiveluriArbore(radacina->dreapta);

		return 1 + maxim(nrNivelStanga, nrNivelDreapta);
	}
}

// nr total de camere rezervate din arbore 
int nrTotalCamere(nodArbore* rad, int* nrTotal) {
	if (rad) {
		(*nrTotal) += rad->info.nrCamere;
		nrTotalCamere(rad->stanga, nrTotal);
		nrTotalCamere(rad->dreapta, nrTotal);

		return (*nrTotal);
	}
}

void calculGrad(nodArbore* radacina) {
	if (radacina) {
		radacina->grad = (nrNiveluriArbore(radacina->stanga) - nrNiveluriArbore(radacina->dreapta)); 
		
		calculGrad(radacina->stanga); 
		calculGrad(radacina->dreapta); 
	}
}

nodArbore* rotatieDreapta(nodArbore* rad) {
	nodArbore* x = rad->stanga; 
	rad->stanga = x->dreapta; 
	x->dreapta = rad; 
	return x;
}

nodArbore* rotatieStanga(nodArbore* rad) {
	nodArbore* x = rad->dreapta;
	rad->dreapta = x->stanga; 
	x->stanga = rad;
	return x;
}

nodArbore* rotatieStangaDreapta(nodArbore* rad) {
	rad->stanga = rotatieStanga(rad->stanga);
	return rotatieDreapta(rad);
}



void main() {
	Rezervare r;

	nodArbore* radacina = NULL;

	char linieBuffer[100];
	char sep[] = ",\n";
	char* token;

	FILE* f = fopen("rezervari.txt", "r");

	if (f) {
		while (fgets(linieBuffer, 100, f)) {
			token = strtok(linieBuffer, sep);
			r.id = atoi(token);

			token = strtok(NULL, sep);
			r.hotel = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(r.hotel, token);

			token = strtok(NULL, sep);
			r.nrCamere = atoi(token);

			token = strtok(NULL, sep);
			r.client = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(r.client, token);

			token = strtok(NULL, sep);
			r.suma = atof(token);

			radacina = insereazaNodArbore(radacina, r);

			free(r.client);
			free(r.hotel);
		}
	}
	else {
		printf("Fisier invalid!");
	}

	calculGrad(radacina);

	printf("\n");

	printf("--------------- Postordine ---------------\n");
	postordine(radacina);

	printf("\n\n");

	printf("--------------- Inordine ---------------\n");
	inordine(radacina);

	printf("\n\n");

	printf("--------------- Preordine ---------------\n");
	preordine(radacina);

	printf("\n\n");

	printf("--------------- Afisare arbore nivel - inordine ---------------\n");
	afisareArboreNivel(radacina, 0);

	printf("\n\n");

	printf("--------------- Preordine dupa rotatie la dreapta ---------------\n");
	radacina = rotatieDreapta(radacina); 
	calculGrad(radacina);
	preordine(radacina);

	printf("\n\n");

	printf("--------------- Preordine dupa rotatie la stanga ---------------\n");
	radacina = rotatieStanga(radacina);
	calculGrad(radacina);
	preordine(radacina);

	printf("\n\n");

	printf("--------------- Niveluri ---------------\n");
	int nrNiveluri = nrNiveluriArbore(radacina);
	printf("  Numarul de niveluri este: %d", nrNiveluri);

	printf("\n\n");

	printf("--------------- Numarul de camere rezervate ---------------\n");
	int nrCamereRezervate = 0;
	nrCamereRezervate = nrTotalCamere(radacina, &nrCamereRezervate);
	printf("  Numarul de camere rezervate este: %d", nrCamereRezervate);

	printf("\n\n");
}