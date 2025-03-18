// Seminar 4 - SDD - 18/03/2025
// COADA

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
	struct nodCoada* next; // 4 bytes
} nodCoada;

// functie de inserare nod in coada => PUT
void put(nodCoada** prim, nodCoada** ultim, mesaj msj) {
	// 1. alocarea si initializarea unui nod nou
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));

	nou->info.data.zi = msj.data.zi;
	nou->info.data.luna = msj.data.luna;
	nou->info.data.an = msj.data.an;

	nou->info.expeditor = (char*)malloc(sizeof(char) * (strlen(msj.expeditor) + 1));
	strcpy(nou->info.expeditor, msj.expeditor);

	nou->info.dimensiune = msj.dimensiune;

	nou->next = NULL;

	if (*prim == NULL || *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	else {
		// inserare la final 
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

// functia de extragere nod din coada = GET
int get(nodCoada** prim, nodCoada** ultim, mesaj* msj) {
	if (*prim != NULL && *ultim != NULL) {
		// in variabila msj s-a retinut informatia utila al nodului care urmeaza sa fie extras 
		(*msj).data.zi = (*prim)->info.data.zi;
		(*msj).data.luna = (*prim)->info.data.luna;
		(*msj).data.an = (*prim)->info.data.an;
		(*msj).expeditor = (char*)malloc(sizeof(char) * (strlen((*prim)->info.expeditor) + 1));
		strcpy((*msj).expeditor, (*prim)->info.expeditor);
		(*msj).dimensiune = (*prim)->info.dimensiune;

		nodCoada* temp = *prim;
		(*prim) = (*prim)->next;

		free(temp->info.expeditor);
		free(temp);

		return 0; // extragerea cu succes a nodului
	}

	if ((*prim) == NULL) {
		(*ultim) = NULL;

		return -1;
	}
}

void afiseazaCoada(nodCoada* prim) {
	nodCoada* temp = prim;
	while (temp) {
		printf("\nData: %d, %d, %d | Expeditor: %s | Dimensiune: %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an,
			temp->info.expeditor, temp->info.dimensiune);
		temp = temp->next;
	}
}

void dezalocaCoada(nodCoada* prim, nodCoada* ultim) {
	mesaj msj;
	while (get(&prim, &ultim, &msj) == 0) {
		free(msj.expeditor);
	}
}

void determinaMesajeByDimensiune(nodCoada* prim, nodCoada* ultim, 
	mesaj* vect, int* nr, float prag) {
	mesaj m;
	while (get(&prim, &ultim, &m) == 0) {
		if (m.dimensiune >= prag) {
			vect[*nr] = m;
			(*nr)++;
		}
	}
}

void main() {
	int nrMesaje;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	mesaj m;
	char buffer[30]; // pt expeditor
	FILE* f = fopen("Coada.txt", "r");

	fscanf(f, "%d", &nrMesaje);
	for (int i = 0; i < nrMesaje; i++) {
		fscanf(f, "%d", &m.data.zi);
		fscanf(f, "%d", &m.data.luna);
		fscanf(f, "%d", &m.data.an);

		fscanf(f, "%s", buffer);
		m.expeditor = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(m.expeditor, buffer);

		fscanf(f, "%f", &m.dimensiune);

		// inserare in coada
		put(&prim, &ultim, m);

		free(m.expeditor); 
	}
	fclose(f);

	printf("\n---------------- Coada ---------------- \n");
	afiseazaCoada(prim);

	printf("\n");

	// dezalocaCoada(prim, ultim);

	mesaj* vect = (mesaj*)malloc(sizeof(mesaj) * nrMesaje);
	int nr = 0;
	determinaMesajeByDimensiune(prim, ultim, vect, &nr, 200);
	printf("\n---------------- Vect din coada by dimensiune ---------------- \n");
	for (int i = 0; i < nr; i++) {
		printf("\nData: %d, %d, %d | Expeditor: %s | Dimensiune: %5.2f",
			vect[i].data.zi, vect[i].data.luna, vect[i].data.an,
			vect[i].expeditor, vect[i].dimensiune);
	}

	// dezalovcare memorie
	for (int i = 0; i < nr; i++) {
		free(vect[i].expeditor);
	}
	free(vect);

	printf("\n\n\n");
}