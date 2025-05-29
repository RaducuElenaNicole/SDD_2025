#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Localitate Localitate;
struct Localitate {
	int nrCrt; // cheia 
	char* denumire;
	unsigned int populatie;
	char* tip;
	float bugetLocal;
};

Localitate initLocalitate(int nrCrt, char* denumire, unsigned int populatie, char* tip, float buget) {
	Localitate nou;

	nou.nrCrt = nrCrt;
	nou.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(nou.denumire, denumire);
	nou.populatie = populatie;
	nou.tip = (char*)malloc(sizeof(char) * (strlen(tip) + 1));
	strcpy(nou.tip, tip);
	nou.bugetLocal = buget;

	return nou;
}

void afiseazaLocalitate(Localitate loc) {
	printf("Id: %d | Denumire: %s | Populatie: %u | Tip: %s | Buget: %5.2f \n",
		loc.nrCrt, loc.denumire, loc.populatie, loc.tip, loc.bugetLocal);
}

typedef struct nodArbore nodArbore; 
struct nodArbore {
	Localitate info; 
	nodArbore* stanga;
	nodArbore* dreapta;
};

nodArbore* creeazaNod(Localitate loc, nodArbore* stg, nodArbore* drp) {
	nodArbore* nou = (nodArbore*)malloc(sizeof(nodArbore)); 

	nou->info = initLocalitate(loc.nrCrt, loc.denumire, 
		loc.populatie, loc.tip, loc.bugetLocal);
	nou->stanga = stg; 
	nou->dreapta = drp;

	return nou; 
}

nodArbore* insereazaNod(nodArbore* radacina, Localitate locNoua) {
	if (radacina) {
		if (locNoua.nrCrt < radacina->info.nrCrt) {
			radacina->stanga = insereazaNod(radacina->stanga, locNoua); 
			return radacina;
		}
		else if (locNoua.nrCrt > radacina->info.nrCrt) {
				radacina->dreapta = insereazaNod(radacina->dreapta, locNoua); 
				return radacina;
		}
		else {
			return radacina;
		}
	}
	else {
		return creeazaNod(locNoua, NULL, NULL);
	}
}

void inordine(nodArbore* radacina) {
	if (radacina) {
		inordine(radacina->stanga); 
		afiseazaLocalitate(radacina->info); 
		inordine(radacina->dreapta);
	}
}

int suma(nodArbore* arb) {
	int nr = 0; 
	if (arb) {
		nr += arb->info.populatie;

		nr += suma(arb->dreapta);
		nr += suma(arb->stanga);
	}
	return nr;
}

int maxim(int a, int b) {
	if (a > b) {
		return a; 
	}
	else {
		return b;
	}
}

int inaltimeArbore(nodArbore* arb) {
	if (arb) {
		return 1 + maxim(inaltimeArbore(arb->stanga), 
			inaltimeArbore(arb->dreapta));
	}
	else {
		return 0; 
	}
}
 
int numarFrunze(nodArbore* arb) {
	int nr = 0; 
	if (arb) {
		if (arb->dreapta == NULL && arb->stanga == NULL) {
			return 1;
		}
		return numarFrunze(arb->dreapta) + numarFrunze(arb->stanga);
	}
	else {
		return 0;
	}
}

Localitate cautaNodByCheie(nodArbore* arb, int idCautat) {
	if (arb == NULL) {
		return initLocalitate(-1, "N/A", 0, "N/A", 0);
	}
	else {
		if (idCautat == arb->info.nrCrt) {
			return initLocalitate(arb->info.nrCrt, arb->info.denumire,
				arb->info.populatie, arb->info.tip, arb->info.bugetLocal);
		}
		else if (idCautat < arb->info.nrCrt) {
			return cautaNodByCheie(arb->stanga, idCautat);
		}
		else if (idCautat > arb->info.nrCrt) {
			return cautaNodByCheie(arb->dreapta, idCautat);
		}
	}
}

void dezalocare(nodArbore* arb) {
	if (arb) {
		nodArbore* stanga = arb->stanga;
		nodArbore* dreapta = arb->dreapta;

		free(arb->info.denumire);
		free(arb->info.tip);
		free(arb);

		dezalocare(stanga);
		dezalocare(dreapta);
	}
}

void main() {
	nodArbore* arb = NULL;

	Localitate loc1 = initLocalitate(7, "Pitesti", 1200, "oras", 56.90);
	Localitate loc2 = initLocalitate(9, "Mioveni", 1200, "oras", 56.90);
	Localitate loc3 = initLocalitate(5, "Ploiesti", 1200, "oras", 56.90);
	Localitate loc4 = initLocalitate(10, "Craiova", 1200, "oras", 56.90);
	Localitate loc5 = initLocalitate(2, "Cluj", 1200, "oras", 56.90);
	Localitate loc6 = initLocalitate(12, "Timisoara", 1200, "oras", 56.90);
	Localitate loc7 = initLocalitate(8, "Alba Iulia", 1200, "oras", 56.90);
	Localitate loc8 = initLocalitate(6, "Campulung", 1200, "oras", 56.90);

	arb = insereazaNod(arb, loc1);
	arb = insereazaNod(arb, loc2);
	arb = insereazaNod(arb, loc3);
	arb = insereazaNod(arb, loc4);
	arb = insereazaNod(arb, loc5);
	arb = insereazaNod(arb, loc6);
	arb = insereazaNod(arb, loc7);
	arb = insereazaNod(arb, loc8);

	inordine(arb);
	printf("\n\n"); 
	printf("Suma populatie: %d", suma(arb));
	printf("\n\n");
	printf("Inaltime arbore: %d", inaltimeArbore(arb));
	printf("\n\n");
	printf("Frunze arbore: %d", numarFrunze(arb));
	printf("\n\n");
	Localitate locCautata = cautaNodByCheie(arb, 2);
	afiseazaLocalitate(locCautata);


	dezalocare(arb); 

	printf("\n\n");
}