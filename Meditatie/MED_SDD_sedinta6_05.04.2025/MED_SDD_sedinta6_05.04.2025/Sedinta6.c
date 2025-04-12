#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct reteta reteta;
typedef struct nodLS nodLS;
typedef struct HashTable HashTable;
typedef struct Pacient Pacient;

struct reteta {
	unsigned int nr;
	unsigned char medicamPrescrise;
	char* numePacient;
	char* numeMedic;
	float valoareReteta;
};

struct Pacient
{
	char* numePacient; 
	int nrMedicamente; 
};

reteta initializareReteta(unsigned int nr, unsigned char medicamPrescrise, const char* numePacient, const char* numeMedic, float valoareReteta) {
	reteta r;
	r.nr = nr;
	r.medicamPrescrise = medicamPrescrise;
	r.numePacient = malloc(sizeof(char) * strlen(numePacient) + 1);
	strcpy_s(r.numePacient, sizeof(char) * strlen(numePacient) + 1, numePacient);
	r.numeMedic = malloc(sizeof(char) * strlen(numeMedic) + 1);
	strcpy_s(r.numeMedic, sizeof(char) * strlen(numeMedic) + 1, numeMedic);
	r.valoareReteta = valoareReteta;
	return r;
}

void afisareReteta(reteta r) {
	printf("  Nr: %-2d | MedicamPrescrise: %-2u | Nume pacient: %-10s | Nume medic: %-10s | Valoare reteta: %5.2f\n",
		r.nr, r.medicamPrescrise, r.numePacient, r.numeMedic, r.valoareReteta);
}


struct nodLS {
	nodLS* next; 
	reteta info; 
};

struct HashTable {
	int dim; 
	nodLS** vectHash;
};

int functieHash(HashTable tabela, unsigned char medicamPrescrise) {
	return medicamPrescrise % tabela.dim;
}

int inserareTable(HashTable tabela, reteta r) {
	int pozitie = 0; 
	if (tabela.vectHash) {
		pozitie = functieHash(tabela, r.medicamPrescrise);

		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info = initializareReteta(r.nr, r.medicamPrescrise, r.numePacient, r.numeMedic, r.valoareReteta);
		nou->next = NULL; 

		if (tabela.vectHash[pozitie] == NULL) {
			tabela.vectHash[pozitie] = nou; 
		}
		else {
			nodLS* aux = tabela.vectHash[pozitie];
			while (aux->next) {
				aux = aux->next;
			}
			aux->next = nou; 
		}
	}
	return pozitie;
}

void traversareHT(HashTable tabela) {
	if (tabela.vectHash) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vectHash[i]) {
				printf("Pozitie: %d \n", i);
				nodLS* aux = tabela.vectHash[i];
				while (aux) {
					afisareReteta(aux->info);
					aux = aux->next;
				}
			}
		}
	}
}

void dezalocareHT(HashTable tabela) {
	if (tabela.vectHash) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vectHash) {
				nodLS* aux = tabela.vectHash[i];
				while (aux) {
					free(aux->info.numeMedic);
					free(aux->info.numePacient);
					nodLS* temp = aux->next;
					free(aux);
					aux = temp;
				}
			}
		}
	}
	free(tabela.vectHash);
}

double valoareTotalaReteta(HashTable tabela, char* numePacient) {
	float valoare = 0;
	if (tabela.vectHash) {
		for (int i = 0; i < tabela.dim; i++) {
			nodLS* aux = tabela.vectHash[i];
			while (aux) {
				if (strcmp(aux->info.numePacient, numePacient) == 1) {
					valoare = valoare + aux->info.valoareReteta;
				}
				aux = aux->next;
			}
		}
	}
	return valoare;
}

int nrMedicamenteMedic(HashTable tabela, char* numeMedic) {
	int count = 0;
	if (tabela.vectHash) {
		for (int i = 0; i < tabela.dim; i++) {
			nodLS* aux = tabela.vectHash[i];
			while (aux) {
				if (strcmp(aux->info.numeMedic, numeMedic) == 1) {
					count = count + aux->info.nr;
				}
				aux = aux->next;
			}
		}
	}
	return count;
}

Pacient crearePacient(char* numePacient, unsigned char nrMedPrescrise) {
	Pacient p;
	p.nrMedicamente = nrMedicamenteMedic;
	p.numePacient = (char*)malloc(sizeof(char) * (strlen(numePacient) + 1));
	strcpy(p.numePacient, numePacient);
	return p; 
}

Pacient* evidentaPacienti(HashTable tabela, unsigned char nrMed,int* dim) {
	int poz = functieHash(tabela, nrMed);
	//int count = 0;
	if (poz) {
		nodLS* aux = tabela.vectHash[poz];
		while (aux) {
			if (aux->info.medicamPrescrise == nrMed) {
				(*dim)++;
			}
			aux = aux->next;
		}
		aux = tabela.vectHash[poz];

		Pacient* vectorP = (Pacient*)malloc(sizeof(Pacient) * (*dim));
		int index = 0;
		while (aux) {
			if (aux->info.medicamPrescrise == nrMed) {
					vectorP[index++] = crearePacient(aux->info.numePacient, aux->info.medicamPrescrise);
			}
			aux = aux->next;
		}
		return vectorP;
	}
}

void main() {
	reteta r; 
	HashTable tabela; 
	tabela.dim = 10; 
	tabela.vectHash = (nodLS**)malloc(sizeof(nodLS*) * tabela.dim);
	for (int i = 0; i < tabela.dim; i++) {
		tabela.vectHash[i] = NULL;
	}

	char linieBuffer[100];
	char* aux;
	char sep[] = ",";
	FILE* f = fopen("reteta.txt", "r");
	if (f) {
		while (fgets(linieBuffer, 100, f)) {
			aux = strtok(linieBuffer, sep);
			r.nr = atoi(aux);

			aux = strtok(NULL, sep);
			r.medicamPrescrise = atoi(aux);

			aux = strtok(NULL, sep);
			r.numePacient = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
			strcpy(r.numePacient, aux);

			aux = strtok(NULL, sep);
			r.numeMedic = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
			strcpy(r.numeMedic, aux);

			aux = strtok(NULL, sep);
			r.valoareReteta = atof(aux);

			inserareTable(tabela, r);
		}
	}
	fclose(f);

	traversareHT(tabela);
	printf("\n\n");

	printf("Valoare totala a retetelor: %f\n", valoareTotalaReteta(tabela, "Ana"));
	printf("\n\n\n");
	printf("Valoare totala a medicamentelor: %d\n", nrMedicamenteMedic(tabela, "George"));
	printf("\n\n");


	int dim2 = 0; 
	Pacient* vectorP = evidentaPacienti(tabela,3, &dim2);
	printf("\n %d \n",dim2);
	for (int i = 0; i < dim2; i++) {
		printf("Nume pacienti: %s \n", vectorP[i].numePacient);
	}

	printf("\n\n");

	dezalocareHT(tabela);
}