// Grafuri

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct Oras Oras;
struct Oras {
	int id; 
	char* nume; 
	int nrLocuitori; 
};

typedef struct nodGrafPrincipal nodGrafPrincipal;
typedef struct nodGrafSecundar nodGrafSecundar;

struct nodGrafSecundar {
	// nodGrafSecundar* nodSecundar; // pointer catre alt oras 
	nodGrafSecundar* next; // legatura cu vecinii 
	nodGrafPrincipal* parinte; 
};

struct nodGrafPrincipal {
	Oras info; 
	nodGrafSecundar* vecini; // lista vecinilor
	nodGrafPrincipal* next; // urmatorul nod principal  
};

Oras creareOras(int id, char* nume, int nrLocuitori) {
	Oras o;
	o.id = id;
	o.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(o.nume, nume);
	o.nrLocuitori = nrLocuitori;

	return o;
}


// inserare la inceput in lista principala 
nodGrafPrincipal* inserareNodPrincipal(nodGrafPrincipal* graf, Oras o) {
	nodGrafPrincipal* nou = (nodGrafPrincipal*)malloc(sizeof(nodGrafPrincipal)); 

	nou->info = creareOras(o.id, o.nume, o.nrLocuitori); 
	nou->next = graf; 
	nou->vecini = NULL; 

	return nou; 
}

void inserareListaSecundara(nodGrafSecundar** cap, nodGrafPrincipal* nodPrincipal) {
	nodGrafSecundar* nou = (nodGrafSecundar*)malloc(sizeof(nodGrafSecundar));

	nou->parinte = nodPrincipal; 
	nou->next = NULL; 

	if ((*cap)) {
		nodGrafSecundar* nodSecundarTemporal = (nodGrafSecundar*)malloc(sizeof(nodGrafSecundar));
		nodGrafSecundar* aux = (*cap);
		while (aux->next) {
			aux = aux->next; 
		}
		aux->next = nou; 
	}
	else {
		(*cap) = nou;
	}
}

// cautare nod in graf
nodGrafPrincipal* cautareNod(nodGrafPrincipal* graf, int idCautat) {
	while (graf && graf->info.id != idCautat) {
		graf = graf->next;
	}
	return graf;
}

// inserare muchie in lista 
void inserareMuchie(nodGrafPrincipal* graf, int idStart, int idStop) {
	nodGrafPrincipal* nodStart = cautareNod(graf, idStart); 
	nodGrafPrincipal* nodStop = cautareNod(graf, idStop); 

	inserareListaSecundara(&nodStart->vecini, nodStop);
	inserareListaSecundara(&nodStop->vecini, nodStop);
}

void afisareGraf(nodGrafPrincipal* graf) {
	while (graf) {
		printf("Oras -> ID: %d | Nume: %s | NrLocuitori: %d \n",
			graf->info.id, graf->info.nume, graf->info.nrLocuitori); 
		//nodGrafSecundar* vecini = graf->vecini;
		//while (vecini) {
		//	printf("Vecini-> Id: %d, Nume: %s", vecini->nod)
		//}
		graf = graf->next;
	}
}

void afisareGrafVecini(nodGrafPrincipal* graf) {
	while (graf) {
		printf("Oras -> ID: %d | Nume: %s | NrLocuitori: %d\n",
			graf->info.id, graf->info.nume, graf->info.nrLocuitori);

		nodGrafSecundar* vecin = graf->vecini;
		if (vecin == NULL) {
			printf(" Nu are vecini.\n");
		}
		else {
			printf(" Vecini:\n");
			while (vecin) {
				printf("   -> ID: %d | Nume: %s | NrLocuitori: %d\n",
					vecin->parinte->info.id,
					vecin->parinte->info.nume,
					vecin->parinte->info.nrLocuitori);

				vecin = vecin->next;
			}
		}
		graf = graf->next;
	}
}

void main() {
	nodGrafPrincipal* graf = NULL;
	Oras o0 = creareOras(0, "Bucuresti", 1234);
	Oras o1 = creareOras(1, "Pitesti", 7788);
	Oras o2 = creareOras(2, "Oradea", 4125);
	Oras o3 = creareOras(3, "Timisoara", 3288);
	Oras o4 = creareOras(4, "Constanta", 7890);
	Oras o5 = creareOras(5, "Craiova", 1876);
	Oras o6 = creareOras(6, "Buzau", 7865);

	graf = inserareNodPrincipal(graf, o0);
	graf = inserareNodPrincipal(graf, o1);
	graf = inserareNodPrincipal(graf, o2);
	graf = inserareNodPrincipal(graf, o3);
	graf = inserareNodPrincipal(graf, o4);
	graf = inserareNodPrincipal(graf, o5);
	graf = inserareNodPrincipal(graf, o6);


	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 6);
	inserareMuchie(graf, 6, 2);
	inserareMuchie(graf, 2, 3);
	inserareMuchie(graf, 1, 5);
	inserareMuchie(graf, 3, 4);

	afisareGraf(graf);
	printf("\n----------------------------\n"); 
	afisareGrafVecini(graf);
}