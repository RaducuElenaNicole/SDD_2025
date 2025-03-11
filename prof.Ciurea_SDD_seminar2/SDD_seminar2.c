// SDD - seminar 2 - 04/03/2025 - prof. CIUREA
// Lista simpla 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

// 12 bytes 
typedef struct {
	int cod; // 4 bytes 
	char* titlu;// 4 bytes
	float pret; // 4 bytes
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
	nou->info.titlu = (char*)malloc(sizeof(char) * (strlen(crt.titlu) + 1));
	strcpy(nou->info.titlu, crt.titlu);
	nou->info.pret = crt.pret;
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
		while (temp->next != NULL) {
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
		printf("\nCod = %d | Titlu = %s | Pret = %5.2f",
			temp->info.cod, temp->info.titlu, temp->info.pret);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp != NULL) // se prelucreaza INCLUSIV ultimul nod 
	{
		nodLS* aux = temp->next;
		free(temp->info.titlu);
		free(temp);
		temp = aux;
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

		fscanf(f, "%f", &c.pret);

		capLS = insereazaNod(capLS, c);

		free(c.titlu);
	}

	fclose(f);

	traverseazaLS(capLS);
	dezalocareLS(capLS);

	printf("\n\n\n");
}