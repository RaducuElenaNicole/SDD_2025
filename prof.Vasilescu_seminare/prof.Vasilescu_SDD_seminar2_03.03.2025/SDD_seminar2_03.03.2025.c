// SDD - seminar 2 - 03/03/2025
// alocare de memorie + vectori + fisier + struct 

/*
	cand se citeste => adresa varabilei (&)
	cand se afiseara => valoarea variabilei 
*/

#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Carte Carte;

struct Carte {
	char* autor;
	int nrPagini;
	float pret;
};

// FisierDetaliiCarte
Carte citesteCarte(FILE* fileStream) {
	Carte crt;

	char buffer[30];

	fgets(buffer, 30, fileStream);
	char* autor = strtok(buffer, "\n");
	crt.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
	strcpy(crt.autor, autor);


	fgets(buffer, 5, fileStream);
	// nr de caractere + \n + \0
	// fgets pune \n 
	int nrPag = atoi(buffer);
	crt.nrPagini = nrPag;
	fgets(buffer, 5, fileStream);
	int pret = atof(buffer);
	crt.pret = pret;

	return crt;
}

void citireVectorFisier(char* fileName, int* lungimeV, int** vector) {
	FILE* fisier;
	fisier = fopen(fileName, "r");
	if (fisier == NULL) {
		return;
	}
	fscanf(fisier, "%d", lungimeV);
	*vector = (int*)malloc(sizeof(int) * (*lungimeV));
	for (int i = 0; i < (*lungimeV); i++) {
		fscanf(fisier, "%d", &(*vector)[i]);
	}
	fclose(fisier);
}

void afiseazaVector(int lungime, int* vector){
	printf("\n%d", lungime);
	printf("\n");
	for (int i = 0; i < lungime; i++) {
		printf("%d | ", vector[i]);
	}
}

void main() {
	int nrIntreg1;
	int nrIntreg2;

	FILE* fisier; // declarare fisier 
	// deschidere fisier
	fisier = fopen("FisierNumereIntregi.txt", "r");
	// preluare date din fisier
	if (fisier != NULL) {
		fscanf(fisier, "%d", &nrIntreg1);
		fscanf(fisier, "%d", &nrIntreg2);
		//fgets
	}
	// inchidere fisier 
	fclose(fisier);
	printf("\nNr1 = %d | Nr2 = %d", nrIntreg1, nrIntreg2);

	int nrElem;
	int vector[10];
	FILE* fisierV;  
	fisierV = fopen("FisierVectorNumereIntregi.txt", "r");

	if (fisierV != NULL) {
		fscanf(fisierV, "%d", &nrElem);
		for(int i = 0; i < nrElem; i++){
			fscanf(fisierV, "%d", &vector[i]);
		}
	}
	fclose(fisierV);
	printf("\n%d", nrElem);
	printf("\n");
	for (int i = 0; i < nrElem; i++) {
		printf("%d | ", vector[i]);
	}

	int* vector2;
	int lungimeV2;
	citireVectorFisier("FisierVectorNumereIntregi2.txt", &lungimeV2, &vector2);
	// transmis catre functie prin ADRESA (functiile in C nu returneaza 2 valori, returneaza o valoare) 
	afiseazaVector(lungimeV2, vector2);

	FILE* fileStream = fopen("FisierDetaliiCarte.txt", "r");
	Carte c = citesteCarte(fileStream);
	fclose(fileStream);
	printf("\nAutor = %s | Nr pagini = %d | Pret = %5.2f", c.autor, c.nrPagini, c.pret);

	free(c.autor);

	printf("\n\n");
}