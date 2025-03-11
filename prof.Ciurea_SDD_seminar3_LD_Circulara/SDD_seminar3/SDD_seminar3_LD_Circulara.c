// SDD - Seminar 3 - 11/03/2025 - sapt 3 
// Lista Dubla Circulara

// Lista Dubla referita printr-un singur pointer! 
// Eliminarea pointerului coadaLD -> de facut! 

// lista de liste ! 
// tabela de dispersie = vector de liste 

#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct {
	int cod;
	char* titlu;
	float* vectPreturi;
	int nrPreturi;
} Carte;

typedef struct {
	Carte info;  // inf utila 12 bytes 
	struct nodLD* next; // 2 pointeri de legatura => 2 bytes * 2 = 8 bytes 
	struct nodLD* prev;
} nodLD;

// DE MOFICIAT PT LD CIRCULARA
nodLD* initializeazaNod(Carte crt)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	nou->info.cod = crt.cod;

	nou->info.titlu = (char*)malloc(sizeof(char) * (strlen(crt.titlu) + 1));
	strcpy(nou->info.titlu, crt.titlu);

	nou->info.nrPreturi = crt.nrPreturi;
	nou->info.vectPreturi = (float*)malloc(sizeof(float) * nou->info.nrPreturi);
	for (int i = 0; i < crt.nrPreturi; i++) {
		nou->info.vectPreturi[i] = crt.vectPreturi[i];
	}

	nou->next = NULL;
	nou->prev = NULL;

	return nou;
}

// DE MOFICIAT PT LD CIRCULARA
// inserare la final 
// transfer prin pointer, apel prin adresa 
nodLD* insereazaNodFinal(nodLD* capLD, nodLD** coadaLD, Carte crt)
{
	nodLD* nou = initializeazaNod(crt);

	if (capLD == NULL) {
		capLD = nou;
		(*coadaLD) = nou;
	}
	else {
		nodLD* temp = capLD;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		(*coadaLD) = nou;
	}

	return capLD;
}

// DE MOFICIAT PT LD CIRCULARA
// inserare la inceput 
// transfer parametri prin pointeri 
void insereazaNodInceput(nodLD** capLD, nodLD** coadaLD, Carte crt)
{
	nodLD* nou = initializeazaNod(crt);

	if (*capLD == NULL) {
		*capLD = nou;
		*coadaLD = nou;
	}
	else {
		/*
		nodLD* temp = *capLD;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		*coadaLD = nou;
		*/
		(*coadaLD)->next = nou;
		nou->prev = (*coadaLD);
		(*coadaLD) = nou;
	}
}

// traversare de la stanga la dreapta, adica de la inceput
void traverseazaLD(nodLD* capLD)
{
	nodLD* temp = capLD;
	while (temp->next != capLD)
	{
		printf("\nCod = %d | Titlu = %s | Nr Preturi = %d | Preturile: \n",
			temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
		for (int i = 0; i < temp->info.nrPreturi; i++) {
			printf("Pretul %d = %5.2f | ", i + 1, temp->info.vectPreturi[i]);
		}
		printf("\n");
		temp = temp->next;
	}

	printf("\nCod = %d | Titlu = %s | Nr Preturi = %d | Preturile: \n",
		temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
	for (int i = 0; i < temp->info.nrPreturi; i++) {
		printf("Pretul %d = %5.2f | ", i + 1, temp->info.vectPreturi[i]);
	}
}

// traversare de la dreapta la stanga, adica de la coada 
void traverseazaLDInvers(nodLD* coadaLD)
{
	nodLD* temp = coadaLD;
	while (temp->prev != coadaLD)
	{
		printf("\nCod = %d | Titlu = %s | Nr Preturi = %d | Preturile: \n",
			temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
		for (int i = 0; i < temp->info.nrPreturi; i++) {
			printf("Pretul %d = %5.2f | ", i + 1, temp->info.vectPreturi[i]);
		}
		printf("\n");
		temp = temp->prev;
	}
	printf("\nCod = %d | Titlu = %s | Nr Preturi = %d | Preturile: \n",
		temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
	for (int i = 0; i < temp->info.nrPreturi; i++) {
		printf("Pretul %d = %5.2f | ", i + 1, temp->info.vectPreturi[i]);
	}
}

void dezalocareLD(nodLD* capLD) {
	nodLD* temp = capLD;
	while (temp->next != capLD)
	{
		nodLD* aux = temp->next;
		free(temp->info.titlu);
		free(temp->info.vectPreturi);
		free(temp);
		temp = aux;
	}

	free(temp->info.titlu);
	free(temp->info.vectPreturi);
	free(temp);
}

void salveazaCartiVector(nodLD* capLD, Carte* vect, int* nrElemente, int prag)
{
	nodLD* temp = capLD;
	while (temp->next != capLD) {
		if (temp->info.nrPreturi >= prag) {
			vect[*nrElemente] = temp->info;
			(*nrElemente)++;
		}
		temp = temp->next;
	}
	if (temp->info.nrPreturi >= prag) {
		vect[*nrElemente] = temp->info;

	}
}

	// stergere nod 
	// 3 posibilitati -> stergere la final, la inceput si in celelalte cazuri 
	// apel prin adresa 
void stergereCarteByTitlu(nodLD** capLD, nodLD** coadaLD, char* titlu) {
		// caz 1: stergere la inceput
		if (strcmp((*capLD)->info.titlu, titlu) == 0) {
			nodLD* temp = *capLD;
			*capLD = (*capLD)->next;

			(*capLD)->prev = *coadaLD;
			(*coadaLD)->next = *capLD;

			free(temp->info.titlu);
			free(temp->info.vectPreturi);
			free(temp);

			return;
		}
		else {
			//caz 2: stergere la final
			nodLD* temp = *coadaLD;

			if (strcmp((*coadaLD)->info.titlu, titlu) == 0) {
				*coadaLD = (*coadaLD)->prev;
				(*coadaLD)->next = *capLD;
				(*capLD)->prev = NULL;

				free(temp->info.titlu);
				free(temp->info.vectPreturi);
				free(temp);

				return;
			}
			else {
				// caz 3: stergere in celelalte cazuri, nu la inceput sau la final
				nodLD* temp = *capLD;

				while (temp != NULL) {
					if (strcmp(temp->info.titlu, titlu) == 0) {
						nodLD* anterior = temp->prev;
						nodLD* urmator = temp->next;

						anterior->next = urmator;
						anterior->prev = anterior;

						free(temp->info.titlu);
						free(temp->info.vectPreturi);
						free(temp);

						return;
					}
					else {
						temp = temp->next;
					}
				}
			}
		}
	}

void main() {
	int nrCarti;
	Carte c;

	nodLD* capLD = NULL;
	nodLD* coadaLD = NULL;

	char buffer[20];

	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &nrCarti);
	for (int i = 0; i < nrCarti; i++) {
		fscanf(f, "%d", &c.cod);

		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(c.titlu, buffer);

		fscanf(f, "%d", &c.nrPreturi);

		c.vectPreturi = (float*)malloc(sizeof(float) * c.nrPreturi);
		for (int i = 0; i < c.nrPreturi; i++) {
			fscanf(f, "%f", &c.vectPreturi[i]);
		}

		capLD = insereazaNodFinal(&capLD, &coadaLD, c);

		free(c.titlu);
	}

	fclose(f);

	printf("\n------------------------- traversare de la inceput -------------------------");

	traverseazaLD(capLD);

	printf("\n------------------------- traversare inversa -------------------------");
	traverseazaLDInvers(coadaLD);


	// salvarea intr-un vector a preturile care au minim 3 preturi 
	printf("\n------------------------- vector de carti -------------------------");
	Carte* vect = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int nrElem = 0;
	salveazaCartiVector(capLD, vect, &nrElem, 3);
	for (int i = 0; i < nrElem; i++) {
		printf("\nCod = %d | Titlu = %s | Nr Preturi = %d | Preturile: \n",
			vect[i].cod, vect[i].titlu, vect[i].nrPreturi);
		for (int j = 0; j < vect[i].nrPreturi; j++) {
			printf("Pretul %d = %5.2f | ", j + 1, vect[i].vectPreturi[j]);
		}
		printf("\n");
	}
	free(vect);

	dezalocareLD(capLD);

	printf("\n\n\n");
}