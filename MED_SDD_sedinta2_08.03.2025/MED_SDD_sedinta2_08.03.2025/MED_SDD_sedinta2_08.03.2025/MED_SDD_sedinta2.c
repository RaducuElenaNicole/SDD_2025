// Sedinta 2 - SDD - 08/03/2025

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

// typedef struct Client Client;
// typedef struct nodLd nodLD;

// LISTA DUBLA 
// citire din fisier cu virgula -> de facut

// structura are campuri! 
typedef struct Client {
	unsigned id; 
	char* nume;
	int nrProduse;
	float* preturiPerProdus;

	// char** -> de facut 
	// char** denumireProdue = {apa, lapte, cafea} -> vector de char* (vector de cuvinte)

}Client;

typedef struct nodLD {
	struct nodLD* prev;
	Client info;
	struct nodLD* next;
}nodLD;

typedef struct ListaDubla {
	nodLD* prim;
	nodLD* ultim;
}ListaDubla;

// functie pt creat clienti si copiat clienti cu deep copy 
Client initializeazaClient(unsigned id, char* nume, int nrProduse, float* pret) {
	Client clt;
	// deep copy -> fiecare camp in parte (cea mai sigura varianta)
	clt.id = id;
	clt.nume = (char*)malloc(sizeof(char) * (strlen(nume)+1));
	// malloc returneaza void* => trebuie facut cast la tipul de date pentru campul caruia i se face alocare de memorie 
	strcpy(clt.nume, nume);
	clt.nrProduse = nrProduse;
	clt.preturiPerProdus = (float*)malloc(sizeof(float) * nrProduse);
	for (int i = 0; i < nrProduse; i++) {
		clt.preturiPerProdus[i] = pret[i];
	}
	return clt;
}

// inserare - 2 variante: la inceput + la final 
ListaDubla insereazaNodLDInceput(ListaDubla ld, Client clt) {
	// pas1: creare nod ld 
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));
	// trebuie returnata adresa

	/*
	// shallow copy => pierdere adresele (informatiile gasite la adrese) (adica char* si float*)
	nou->info = clt;
	*/

	// deep copy 
	nou->info = initializeazaClient(clt.id, clt.nume, clt.nrProduse, clt.preturiPerProdus);
	
	// pas2: initializare adrese nod 
	nou->prev = NULL;
	nou->next = NULL;

	// pas3: inserare nod nou in ld
	if (ld.prim == NULL) {
		// lista dubla este vida => nou va deveni primul nod din lista => prim = ultim = nou 
		ld.prim = ld.ultim = nou;
		// daca este un singur nod in lista dubla, nodul este si prim si ultim 
	}
	else {
		nou->next = ld.prim;
		ld.prim->prev = nou;
		ld.prim = nou;
	}

	// pas4: returnare 
	// o functie returneaza UN SINGUR LUCRU
	return ld;
}

ListaDubla insereazaNodLDFinal(ListaDubla ld, Client clt) {
	// pas1: creare nod ld 
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	// deep copy 
	nou->info = initializeazaClient(clt.id, clt.nume, clt.nrProduse, clt.preturiPerProdus);

	// pas2: initializare adrese nod 
	nou->prev = NULL;
	nou->next = NULL;

	// pas3: inserare nod nou in ld
	if (ld.prim == NULL) {
		ld.prim = ld.ultim = nou; 
	}
	else {
		ld.ultim->next = nou;
		nou->prev = ld.ultim;
		ld.ultim = nou;
	}

	// pas4: returnare 
	return ld;
}

// afisare
void traverseazaLDInceput(ListaDubla ld) {
	nodLD* temp = ld.prim;
	while (temp) {
		printf("ID: %u | NUME: %s | NrPRODUSE: %d | Pretul per produs: ", 
				temp->info.id, temp->info.nume, temp->info.nrProduse);
		for (int i = 0; i < temp->info.nrProduse; i++) {
			printf("%5.2f | ", temp->info.preturiPerProdus[i]);
		}
		printf("\n");

		temp = temp->next;
	}
}

void traverseazaLDFinal(ListaDubla ld) {
	nodLD* temp = ld.ultim;
	while (temp) {
		printf("ID: %u | NUME: %s | NrPRODUSE: %d | Pretul per produs: ",
			temp->info.id, temp->info.nume, temp->info.nrProduse);
		for (int i = 0; i < temp->info.nrProduse; i++) {
			printf("%5.2f | ", temp->info.preturiPerProdus[i]);
		}
		printf("\n");

		temp = temp->prev;
	}
}

// dezalocare 
void dezalocareLD(ListaDubla ld) {
	nodLD* temp = ld.prim;
	while(temp){
		free(temp->info.nume);
		free(temp->info.preturiPerProdus);

		nodLD* aux = temp->next;
		free(temp);

		temp = aux;
	}
}

void main(){
	int nr; 
	Client c;
	char buffer[50];
	ListaDubla lista;

	lista.prim = NULL;
	lista.ultim = NULL;

	FILE* file = fopen("fisier.txt", "r");
	fscanf(file, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		// id
		fscanf(file, "%u", &c.id); 

		// nume 
		fscanf(file, "%s", buffer);
		c.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(c.nume, buffer);

		// nrProduse
		fscanf(file, "%d", &c.nrProduse);

		// preturiPerProdus
		c.preturiPerProdus = (float*)malloc(sizeof(float) * c.nrProduse); // alocare memorie vector
		for (int i = 0; i < c.nrProduse; i++) {
			fscanf(file, "%f", &c.preturiPerProdus[i]);
		}

		lista = insereazaNodLDFinal(lista, c);

		// dezalocari 
	}

	fclose(file);

	traverseazaLDInceput(lista);
}