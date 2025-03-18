// Seminar 4 - SDD - 18/03/2025
// STIVA


#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct {
	int zi, luna, an;
} dataReceptionare;

typedef struct {
	dataReceptionare data;
	char* expeditor;
	float dimensiune;
} mesaj;

typedef struct {
	mesaj info; // 20 bytes
	struct nodStiva* next; // 4 bytes
} nodStiva;

// functia de inserare nod in stiva = PUSH 
void push(nodStiva** varf, mesaj msj) {

	// 1. alocarea si initializarea unui nod nou
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	nou->info.data.zi = msj.data.zi;
	nou->info.data.luna = msj.data.luna;
	nou->info.data.an = msj.data.an;

	nou->info.expeditor = (char*)malloc(sizeof(char) * (strlen(msj.expeditor) + 1));
	strcpy(nou->info.expeditor, msj.expeditor);

	nou->info.dimensiune = msj.dimensiune;

	nou->next = NULL;

	// 2. inserarea la inceput intr-o stiva 
	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

// functia de extragere nod din stiva = POP
int pop(nodStiva** varf, mesaj* msj) {
	if (*varf == NULL) {
		return -1; // stiva e goala => nu se extrage nimic 
	}
	else {
		// in variabila msj s-a retinut informatia utila al nodului care urmeaza sa fie extras 
		(*msj).data.zi = (*varf)->info.data.zi;
		(*msj).data.luna = (*varf)->info.data.luna;
		(*msj).data.an = (*varf)->info.data.an;
		(*msj).expeditor = (char*)malloc(sizeof(char) * (strlen((*varf)->info.expeditor) + 1));
		strcpy((*msj).expeditor, (*varf)->info.expeditor);
		(*msj).dimensiune = (*varf)->info.dimensiune;

		nodStiva* temp = *varf;
		(*varf) = (*varf)->next;

		free(temp->info.expeditor);
		free(temp);

		return 0;
	}
}

void afiseazaStiva(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp) {
		printf("\nData: %d, %d, %d | Expeditor: %s | Dimensiune: %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an,
			temp->info.expeditor, temp->info.dimensiune);
		temp = temp->next;
	}
}

void dezalocaStiva(nodStiva* varf) {
	mesaj msj;
	while (pop(&varf, &msj) == 0) {
		free(msj.expeditor);
	}
}

void main() {
	int nrMesaje;
	nodStiva* varf = NULL;
	mesaj m;
	char buffer[30]; // pt expeditor
	FILE* f = fopen("Stiva.txt", "r");

	fscanf(f, "%d", &nrMesaje);
	for (int i = 0; i < nrMesaje; i++) {
		fscanf(f, "%d", &m.data.zi);
		fscanf(f, "%d", &m.data.luna);
		fscanf(f, "%d", &m.data.an);

		fscanf(f, "%s", buffer);
		m.expeditor = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(m.expeditor, buffer);

		fscanf(f, "%f", &m.dimensiune);

		push(&varf, m);

		free(m.expeditor); // ca sa nu avem memory leaks
	}

	fclose(f);

	afiseazaStiva(varf);

	printf("\n");
	printf("\n");
	printf("\n");

	dezalocaStiva(varf);
}