// Seminar 4 - SDD - 18/03/2025
// STIVA + COADA


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

typedef struct {
	mesaj info; // 20 bytes
	struct nodCoada* next; // 4 bytes
} nodCoada;

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

void conversieCoadaFromStiva(nodStiva* varf, nodCoada** prim, nodCoada** ultim) {
	mesaj m;
	while (pop(&varf, &m) == 0) {
		put(prim, ultim, m);
	}
}

void conversieStivaFromCoada(nodStiva** varf, nodCoada* prim, nodCoada* ultim) {
	mesaj m;
	while (get(&prim, &ultim, &m) == 0) {
		push(varf, m);
	}
}

void main() {
	int nrMesaje;
	nodStiva* varf = NULL;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	mesaj m;
	char buffer[30]; // pt expeditor
	FILE* f = fopen("Text.txt", "r");

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
		put(&prim, &ultim, m);

		free(m.expeditor); // ca sa nu avem memory leaks
	}

	fclose(f);

	printf("---------------- Stiva -> varf: ---------------- \n");
	afiseazaStiva(varf);

	printf("\n\n\n---------------- Coada -> prim + ultim: ---------------- \n");
	afiseazaCoada(prim);

	nodCoada* primConv = NULL;
	nodCoada* ultimConv = NULL; 
	printf("\n\n\n---------------- Coada from Stiva -> primConv + ultimConv From varf ---------------- \n");
	conversieCoadaFromStiva(varf, &primConv, &ultimConv);
	afiseazaCoada(primConv);

	nodStiva* varfConv = NULL;
	printf("\n\n\n---------------- Stiva from Coada -> varfConv From prim + ultim: ---------------- \n");
	conversieStivaFromCoada(&varfConv, prim, ultim);
	afiseazaStiva(varfConv);

	printf("\n\n\n");

	//dezalocaStiva(varf);
	//dezalocaCoada(prim, ultim);
}