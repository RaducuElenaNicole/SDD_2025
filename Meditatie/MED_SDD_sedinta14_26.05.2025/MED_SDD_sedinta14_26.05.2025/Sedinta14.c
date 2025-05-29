// Subiect examen - CursaFeroviara

// arbore binar de cautare 

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct CursaFeroviara CursaFeroviara;
struct CursaFeroviara {
	unsigned int numarCursa; // cheia de cautare 
	char* data;
	unsigned char numarVagoane;
	unsigned short int bileteCumparate[2]; // la clasa I si II 
	float pretBilet[2];
};

typedef struct nodArbore nodArbore;
struct nodArbore {
	CursaFeroviara info;
	nodArbore* stanga;
	nodArbore* dreapta;
};

CursaFeroviara creeazaCursaFeroviara(unsigned int numarCursa, char* data, unsigned char numarVagoane,
	unsigned short int bileteCumparate[2], float pretBilet[2]) {
	CursaFeroviara cursa;

	cursa.numarCursa = numarCursa;

	cursa.data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
	strcpy(cursa.data, data);

	cursa.numarVagoane = numarVagoane;

	cursa.bileteCumparate[0] = bileteCumparate[0];
	cursa.bileteCumparate[1] = bileteCumparate[1];

	cursa.pretBilet[0] = pretBilet[0];
	cursa.pretBilet[1] = pretBilet[1];

	return cursa;
}

nodArbore* creeazaNodArbore(CursaFeroviara cursa, nodArbore* stanga, nodArbore* dreapta) {
	nodArbore* nou = (nodArbore*)malloc(sizeof(nodArbore));

	nou->info = creeazaCursaFeroviara(cursa.numarCursa, cursa.data,
		cursa.numarVagoane, cursa.bileteCumparate, cursa.pretBilet);

	nou->dreapta = dreapta;
	nou->stanga = stanga;

	return nou;
}

void afiseazaDetaliiCursa(CursaFeroviara cursa) {
	printf("Numar cursa: %u | Data: %s | numarVagoane: %u | Bilete cumparate -> clasa 1: %d - clasa 2: %d | Pret bilete -> clasa 1: %5.2f - clasa 2: %5.2f \n",
		cursa.numarCursa, cursa.data, cursa.numarVagoane,
		cursa.bileteCumparate[0], cursa.bileteCumparate[1],
		cursa.pretBilet[0], cursa.pretBilet[1]);
}

nodArbore* insereazaNodArbore(nodArbore* radacina, CursaFeroviara cursa) {
	if (radacina) {
		if (cursa.numarCursa < radacina->info.numarCursa) {
			radacina->stanga = insereazaNodArbore(radacina->stanga, cursa);
			return radacina;
		}
		else if (cursa.numarCursa > radacina->info.numarCursa) {
			radacina->dreapta = insereazaNodArbore(radacina->dreapta, cursa);
			return radacina;
		}
		else {
			return radacina;
		}
	}
	else {
		return creeazaNodArbore(cursa, NULL, NULL);
	}
}

// afisare (traversare)
void predordine(nodArbore* radacina) {
	// preordine = R - S - D
	if (radacina) {
		printf("Numar cursa: %u | Data: %s | numarVagoane: %u | Bilete cumparate -> clasa 1: %d - clasa 2: %d | Pret bilete -> clasa 1: %5.2f - clasa 2: %5.2f \n",
			radacina->info.numarCursa, radacina->info.data, radacina->info.numarVagoane,
			radacina->info.bileteCumparate[0], radacina->info.bileteCumparate[1],
			radacina->info.pretBilet[0], radacina->info.pretBilet[1]);
		predordine(radacina->stanga);
		predordine(radacina->dreapta);
	}
}

void inordine(nodArbore* radacina) {
	// inordine = S - R - D
	if (radacina) {
		inordine(radacina->stanga);
		printf("Numar cursa: %u | Data: %s | numarVagoane: %u | Bilete cumparate -> clasa 1: %d - clasa 2: %d | Pret bilete -> clasa 1: %5.2f - clasa 2: %5.2f \n",
			radacina->info.numarCursa, radacina->info.data, radacina->info.numarVagoane,
			radacina->info.bileteCumparate[0], radacina->info.bileteCumparate[1],
			radacina->info.pretBilet[0], radacina->info.pretBilet[1]);
		inordine(radacina->dreapta);
	}
}

void postordine(nodArbore* radacina) {
	// postordine = S - D - R
	if (radacina) {
		postordine(radacina->stanga);
		postordine(radacina->dreapta);
		printf("Numar cursa: %u | Data: %s | numarVagoane: %u | Bilete cumparate -> clasa 1: %d - clasa 2: %d | Pret bilete -> clasa 1: %5.2f - clasa 2: %5.2f \n",
			radacina->info.numarCursa, radacina->info.data, radacina->info.numarVagoane,
			radacina->info.bileteCumparate[0], radacina->info.bileteCumparate[1],
			radacina->info.pretBilet[0], radacina->info.pretBilet[1]);
	}
}

void numarBileteCumparateClasa2(nodArbore* radacina, int* nrBilete) {
	if (radacina) {
		(*nrBilete) += radacina->info.bileteCumparate[1];

		numarBileteCumparateClasa2(radacina->stanga, nrBilete);
		numarBileteCumparateClasa2(radacina->dreapta, nrBilete);
	}
}

int numarBileteCumparateClasa2_varianta2(nodArbore* radacina) {
	int nrBilete = 0;

	if (radacina) {
		nrBilete += radacina->info.bileteCumparate[1];

		nrBilete += numarBileteCumparateClasa2_varianta2(radacina->stanga);
		nrBilete += numarBileteCumparateClasa2_varianta2(radacina->dreapta);
	}

	return nrBilete;
}

void modificarePretBiletClasa1(char* data, float procentModficare, nodArbore* radacina) {
	if (radacina) {
		// trebuie sa gaseasca 0 diferente !
		if (strcmp(radacina->info.data, data) == 0) {
			radacina->info.pretBilet[0] = radacina->info.pretBilet[0] * (1 + procentModficare);
		}
		modificarePretBiletClasa1(data, procentModficare, radacina->dreapta);
		modificarePretBiletClasa1(data, procentModficare, radacina->stanga);
	}
}

// cautarea unui obiect pe baza cheii date ca parametru
nodArbore* cautareCursaByCheie(unsigned int numarCursaCautata, nodArbore* radacina) {
	if (radacina) {
		if (numarCursaCautata == radacina->info.numarCursa) {
			return radacina;
		}
		else if (numarCursaCautata < radacina->info.numarCursa) { // subarbore stanga
			printf("subarbore stanga\n");
			return cautareCursaByCheie(numarCursaCautata, radacina->stanga);
		}
		else if (numarCursaCautata > radacina->info.numarCursa) { // subarbore dreapta
			printf("subarbore stanga\n");
			return cautareCursaByCheie(numarCursaCautata, radacina->dreapta);
		}
	}
	else {
		return NULL;
	}
}

CursaFeroviara cautareCursaByCheie_DeepCopy(unsigned int numarCursaCautata, nodArbore* radacina) {
	CursaFeroviara cursaCautata;
	if (radacina) {
		if (numarCursaCautata == radacina->info.numarCursa) {
			cursaCautata = creeazaCursaFeroviara(radacina->info.numarCursa,
				radacina->info.data, radacina->info.numarVagoane, radacina->info.bileteCumparate,
				radacina->info.pretBilet);

			return cursaCautata;
		}
		else if (numarCursaCautata < radacina->info.numarCursa) { // subarbore stanga
			printf("subarbore stanga\n");
			return cautareCursaByCheie_DeepCopy(numarCursaCautata, radacina->stanga);
		}
		else if (numarCursaCautata > radacina->info.numarCursa) { // subarbore dreapta
			printf("subarbore stanga\n");
			return cautareCursaByCheie_DeepCopy(numarCursaCautata, radacina->dreapta);
		}
	}
	else {
		unsigned short int bileteCumparate[2] = { 0, 0 };
		float pretBilet[2] = { 0, 0 };
		return creeazaCursaFeroviara(0, "Necunoscuta", 1, bileteCumparate, pretBilet);
	}
}

// convertie arbore -> stiva (salvare intr-o alta structura)
typedef struct nodStiva nodStiva;
struct nodStiva {
	nodStiva* next; 
	CursaFeroviara info;
};
void push(nodStiva** varf, CursaFeroviara detaliiCursaNoua) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info = creeazaCursaFeroviara(detaliiCursaNoua.numarCursa, detaliiCursaNoua.data,
		detaliiCursaNoua.numarVagoane, detaliiCursaNoua.bileteCumparate, detaliiCursaNoua.pretBilet);
	nou->next = NULL;
	if ((*varf) == NULL) {
		(*varf) = nou;
	}
	else {
		nou->next = (*varf);
		(*varf) = nou;
	}
}

int pop(nodStiva** varf, CursaFeroviara* detaliiCursaExtras) {
	if ((*varf) == NULL) {
		return -1;  
	}
	else {
		(*detaliiCursaExtras) = creeazaCursaFeroviara((*varf)->info.numarCursa, (*varf)->info.data, 
			(*varf)->info.numarVagoane, (*varf)->info.bileteCumparate, (*varf)->info.pretBilet);

		nodStiva* nodExtras = (*varf);
		(*varf) = (*varf)->next;

		free(nodExtras);

		return 1; 
	}
}

void traversareStiva(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp) {
		afiseazaDetaliiCursa(temp->info);
		temp = temp->next;
	}
}

void dezalocareStiva(nodStiva** varf) {
	CursaFeroviara cursa;
	while (pop(varf, &cursa) == 1) {
		free(cursa.data);
	}
}

// functia de conversie din arbore in stiva
void conversieToStiva(nodArbore* arbore, nodStiva** stiva) {
	if (arbore) {
		push(stiva, arbore->info);
		conversieToStiva(arbore->stanga, stiva);
		conversieToStiva(arbore->dreapta, stiva);
	}
}

void main() {
	FILE* file = fopen("DetaliiCursaFeroviara.txt", "r");

	int nrCurse;
	fscanf(file, "%d", &nrCurse);

	nodArbore* rad = NULL;
	char buffer[40];
	CursaFeroviara cursa;

	for (int i = 0; i < nrCurse; i++) {
		fscanf(file, "%d", &cursa.numarCursa);

		fscanf(file, "%s", buffer);
		cursa.data = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(cursa.data, buffer);

		fscanf(file, "%u", &cursa.numarVagoane);

		fscanf(file, "%d", &cursa.bileteCumparate[0]);
		fscanf(file, "%d", &cursa.bileteCumparate[1]);

		fscanf(file, "%f", &cursa.pretBilet[0]);
		fscanf(file, "%f", &cursa.pretBilet[1]);

		rad = insereazaNodArbore(rad, cursa);

		free(cursa.data);
	}
	fclose(file);

	printf("\n--------------- Traversare PREORDINE ---------------\n");
	predordine(rad);

	printf("\n");

	printf("\n--------------- Traversare INORDINE ---------------\n");
	inordine(rad);

	printf("\n");

	printf("\n--------------- Traversare POSTORDINE ---------------\n");
	postordine(rad);

	printf("\n");

	printf("\n--------------- Numarul de bilete cumparate la clasa2 ---------------\n");
	int nrBileteCumparate = 0;
	numarBileteCumparateClasa2(rad, &nrBileteCumparate);
	printf("%d ", nrBileteCumparate);

	printf("\n");

	int nrBileteCumparate2 = 0;
	nrBileteCumparate2 = numarBileteCumparateClasa2_varianta2(rad);
	printf("%d ", nrBileteCumparate2);

	printf("\n");

	printf("\n--------------- Numarul de bilete cumparate la clasa2 ---------------\n");
	modificarePretBiletClasa1("26/12/2024", 0.3f, rad);
	postordine(rad);

	printf("\n");

	// cerinta 4 si 5 -----> de facut! 

	printf("\n--------------- Functia de cautare ---------------\n");
	nodArbore* nodCautat = NULL;
	nodCautat = cautareCursaByCheie(5, rad);
	if (nodCautat != NULL) {
		afiseazaDetaliiCursa(nodCautat->info);
	}
	else {
		printf("Cursa nu s-a gasit!");
	}

	printf("\n");

	printf("\n--------------- Functia de cautare - Varianta cu deep copy ---------------\n");
	CursaFeroviara cursaCautata;
	cursaCautata = cautareCursaByCheie_DeepCopy(6, rad);
	afiseazaDetaliiCursa(cursaCautata);

	printf("\n");

	printf("\n--------------- Conversie arbore TO stiva ---------------\n");
	nodStiva* stiva = NULL; 
	conversieToStiva(rad, &stiva); 
	traversareStiva(stiva);
}