// SDD - seminar 2 - 04/03/2025 - prof. CIUREA
// Lista simpla 
// structura Carte are un vector alocat dinamic 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

// 12 bytes 
typedef struct {
	int cod; // 4 bytes -> int* ce se intampla si ce trebuie modificat??
	char* titlu;// 4 bytes
	float* vectPreturi ; 
	int nrPreturi; // 4 bytes 
} Carte;

// 16 bytes 
typedef struct {
	Carte info; // informatie utila 12 bytes
	struct nodLS* next; //  pointer de legatura 4 bytes
} nodLS;

nodLS* initializeazaNod(Carte crt) 
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS)); // se aloca spatiul de 16 bytes pt un nod 
	// nou->info = crt; // shallow copy 
	// recomandat este DEEP COPY 
	// este mai sigur, dar mai greu de implementat  
	nou->info.cod = crt.cod;

	nou->info.titlu = (char*)malloc( sizeof(char) * (strlen(crt.titlu) + 1) );
	strcpy(nou->info.titlu, crt.titlu);
	
	nou->info.nrPreturi = crt.nrPreturi;
	nou->info.vectPreturi = (float*)malloc(sizeof(float) * nou->info.nrPreturi);
	for (int i = 0; i < crt.nrPreturi; i++) {
		nou->info.vectPreturi[i] = crt.vectPreturi[i];
	}
	
	nou->next = NULL;

	return nou;
}

nodLS* insereazaNod(nodLS* capLS, Carte crt) 
{
	nodLS* nou = initializeazaNod(crt);

	if (capLS == NULL) {
		// situatia in care lista este vida/goala => nu exista elemente(noduri) in lista simpla 
		// => nodul nou devine cap (primul nod din lista)
		capLS = nou; 
	}
	else {
		// situatia in care lista NU este goala 
		nodLS* temp = capLS; 
		while (temp->next != NULL){
			temp = temp->next;
		} // la finalul structurii repetitive, temp este pozitionat pe ultimul nod din lista simpla 
		temp->next = nou; // se insereaza nodul nou la finalul listei 
	}

	return capLS;
}

void insereazaNod2(nodLS** capLS, Carte crt) 
{
	nodLS* nou = initializeazaNod(crt);

	if (*capLS == NULL) {		
		*capLS = nou;
	}
	else { 
		nodLS* temp = *capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		} 
		temp->next = nou;  
	}
}

void traverseazaLS(nodLS* capLS) 
{
	nodLS* temp = capLS;
	while (temp != NULL) // se prelucreaza INCLUSIV ultimul nod 
	{
		printf("\nCod = %d | Titlu = %s | Nr Preturi = %d | Preturile: \n",
				temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
		for (int i = 0; i < temp->info.nrPreturi; i++) {
			printf("Pretul %d = %5.2f | ", i + 1,  temp->info.vectPreturi[i]);
		}
		printf("\n");
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp != NULL) // se prelucreaza INCLUSIV ultimul nod 
	{
		nodLS* aux = temp->next;
		free(temp->info.titlu);
		free(temp->info.vectPreturi);
		free(temp);
		temp = aux;
	}
}

void salveazaCartiVector(nodLS* capLS, Carte* vect, int* nrElemente, int prag) 
{
	nodLS* temp = capLS;
	while (temp != NULL) {
		if (temp->info.nrPreturi >= prag) {
			vect[*nrElemente] = temp->info;
			(*nrElemente)++;
			// se vor partaja zonele de memorie intre lista si vectorul de carti ptc s-a facut shallow copy 
			// de facut deep copy
		}

		temp = temp->next;
	}
}

void main() {
	int nrCarti;
	Carte c;
	nodLS* capLS = NULL;
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

		capLS = insereazaNod(capLS, c);

		free(c.titlu);
	}

	fclose(f);

	traverseazaLS(capLS);

	// salvarea intr-un vector a preturile care au minim 3 preturi 
	printf("\n------------------------- vector de carti -------------------------");
	Carte* vect = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int nrElem = 0;
	salveazaCartiVector(capLS, vect, &nrElem, 3);
	for (int i = 0; i < nrElem; i++) {
		printf("\nCod = %d | Titlu = %s | Nr Preturi = %d | Preturile: \n",
			vect[i].cod, vect[i].titlu, vect[i].nrPreturi);
		for (int j = 0; j < vect[i].nrPreturi; j++) {
			printf("Pretul %d = %5.2f | ", j + 1, vect[i].vectPreturi[j]);
		}
		printf("\n");
	}
	free(vect);


	dezalocareLS(capLS);

	printf("\n\n\n");
}

// data viitoare -> LS sa va transforma in lista dubla 
// functie de stergere a unui nod 
// apoi LD se transforma in lista dubla circulara 