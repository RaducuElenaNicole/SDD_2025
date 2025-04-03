// HashTable

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct nodLS nodLS;
typedef struct Student Student;
typedef struct HashTable HashTable;

struct Student {
	unsigned id;
	char* nume;
	int nrMaterii;
	float* note;
};

struct nodLS {
	Student info;
	nodLS* next;
};

struct HashTable {
	int dim; // nr de elemente  
	nodLS** vectorHashT;
};

Student creareStudent(unsigned id, const char* nume, int nrMaterii, float* note) {
	Student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy_s(s.nume, sizeof(char) * (strlen(nume) + 1), nume);
	s.nrMaterii = nrMaterii;
	s.note = (float*)malloc(sizeof(float) * nrMaterii);
	for (int i = 0; i < nrMaterii; i++) {
		s.note[i] = note[i];
	}
	return s;
}

void afisareStudent(Student s) {
	printf("    Student { Id: %u | Nume: %s | NrMaterii: %d | Note: ", s.id, s.nume, s.nrMaterii);
	for (int i = 0; i < s.nrMaterii; i++) {
		printf("\n        Nota %d: %.2f", i + 1,  s.note[i]);
	}
	printf("}");
	printf("\n\n");
}

// functie hash (2 variante)
int functieHash1(HashTable tabela, unsigned id) {
	return id % tabela.dim;
}

int functieHash2(HashTable tabela, const char* nume) {
	return strlen(nume) % tabela.dim;
}

int inserareHash1(HashTable tabela, Student stud) {
	int pozitie = functieHash1(tabela, stud.id);
	if (tabela.vectorHashT)
	{
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info = creareStudent(stud.id, stud.nume, stud.nrMaterii, stud.note);
		nou->next = NULL;

		if (tabela.vectorHashT[pozitie] == NULL) {
			tabela.vectorHashT[pozitie] = nou;
		}
		else {
			nodLS* temp = tabela.vectorHashT[pozitie]; // inceputul listei = capul listei
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = nou;
		}
	} 
	return pozitie;
}

int inserareHash2(HashTable tabela, Student stud) {
	int pozitie = functieHash2(tabela, stud.nume);
	if (tabela.vectorHashT)
	{
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info = creareStudent(stud.id, stud.nume, stud.nrMaterii, stud.note);
		nou->next = NULL;

		if (tabela.vectorHashT[pozitie] == NULL) {
			tabela.vectorHashT[pozitie] = nou;
		}
		else {
			nodLS* temp = tabela.vectorHashT[pozitie]; // inceputul listei = capul listei
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
	return pozitie;
}

void traversareHash(HashTable tabela) {
	if (tabela.vectorHashT != NULL) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vectorHashT[i] == NULL) {
				printf("Pozitia %d: NULL \n", i);
			}
			else {
				printf("Pozitia %d: \n", i);
				nodLS* aux = tabela.vectorHashT[i];
				while (aux) {
					afisareStudent(aux->info);
					aux = aux->next;
				}
			}
		}
	}
}

void dezalocaLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp) {
		nodLS* aux = temp->next;

		free(temp->info.nume);
		free(temp->info.note);
		free(temp);

		temp = aux;
	}
}

void dezalocaHashTable(HashTable tabela) {
	if (tabela.vectorHashT) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vectorHashT[i] != NULL) {
				nodLS* aux = tabela.vectorHashT[i];
				while (aux) {
					free(aux->info.nume);
					free(aux->info.note);

					nodLS* temp = aux->next;
					free(aux);

					aux = temp;
				}
			}
		}
		free(tabela.vectorHashT);
	}
}

nodLS* inserareNodLS(nodLS* capLS, Student s) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = creareStudent(s.id, s.nume, s.nrMaterii, s.note);
	nou->next = NULL;

	if (capLS == NULL) {
		capLS = nou;
	}
	else {
		nou->next = capLS;
		capLS = nou;
	}
	return capLS;
}

void traversareLS(nodLS* capLS) {
	nodLS* aux = capLS;
	while (aux) {
		afisareStudent(aux->info);
		aux = aux->next;
	}
}

// conversie din hash in LS
void coversieHashTableToLS(HashTable tabela, nodLS** capLS) {
	if (tabela.vectorHashT) {
		for (int i = 0; i < tabela.dim; i++) {
			nodLS* aux = tabela.vectorHashT[i];
			while (aux) {
				(*capLS) = inserareNodLS(*capLS, aux->info);
				aux = aux->next;
			}
		}
	}
}

void main() {

	Student s;

	HashTable tabela1;
	tabela1.dim = 10;
	tabela1.vectorHashT = (nodLS**)malloc(sizeof(nodLS*) * tabela1.dim);
	for (int i = 0; i < tabela1.dim; i++) {
		tabela1.vectorHashT[i] = NULL;
	}

	HashTable tabela2;
	tabela2.dim = 10;
	tabela2.vectorHashT = (nodLS**)malloc(sizeof(nodLS*) * tabela2.dim);
	for (int i = 0; i < tabela2.dim; i++) {
		tabela2.vectorHashT[i] = NULL;
	}

	char liniebuffer[100];
	char* aux;
	char sep[4] = ",\n";

	FILE* f = fopen("studenti.txt", "r");
	if (f) {
		while (fgets(liniebuffer, sizeof(liniebuffer), f)) { // liniebuffer="111,Popescu Alin,2,10,9"

			aux = strtok(liniebuffer, sep);

			s.id = atoi(aux);

			aux = strtok(NULL, sep);
			s.nume = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
			strcpy_s(s.nume, (strlen(aux) + 1), aux);

			aux = strtok(NULL, sep);
			s.nrMaterii = atoi(aux);

			s.note = (float*)malloc(sizeof(float) * s.nrMaterii);
			for (int i = 0; i < s.nrMaterii; i++) {
				aux = strtok(NULL, sep);
				s.note[i] = atof(aux);
			}

			inserareHash1(tabela1, s);
			inserareHash2(tabela2, s);

			free(s.note);
			free(s.nume);
		}
	}
	fclose(f);

	printf("\n------------------------------ Tabela de dispersie By ID ------------------------------\n");
	traversareHash(tabela1);

	printf("\n\n\n");

	printf("\n------------------------------ Tabela de dispersie By NUME ------------------------------\n");
	traversareHash(tabela2);

	printf("\n\n\n");

	printf("\n------------------------------ Conversie ------------------------------\n");
	nodLS* listaStud = NULL;
	coversieHashTableToLS(tabela1, &listaStud);
	traversareLS(listaStud);

	dezalocaHashTable(tabela1);
	dezalocaHashTable(tabela2);

	dezalocaLS(listaStud);
}