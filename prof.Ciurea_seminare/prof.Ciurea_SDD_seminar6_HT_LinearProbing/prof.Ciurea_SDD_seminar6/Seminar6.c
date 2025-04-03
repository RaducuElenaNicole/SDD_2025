// Seminar 6 - SDD - 01/04/2025
// Tabela de dispersie - Linear Probing 
// HashTable (HT)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* nume;
	float medie;
}Student;

typedef struct {
	Student** vectHashT;
	int nrElem;
}HashTable;

int functieHash(HashTable tabela, int cheie) {
	return cheie % tabela.nrElem;
}

void inserareHash(HashTable tabela, Student* stud) {
	int poz = functieHash(tabela, (*stud).cod);
	if (tabela.vectHashT[poz] == NULL) {
		tabela.vectHashT[poz] = stud; // shallow copy intre cei doi ponteri 
	}
	else {
		// coliziune 
		int index = 1;
		while (poz + index < tabela.nrElem) {
			if (tabela.vectHashT[poz + index] == NULL) {
				poz += index;
				tabela.vectHashT[poz] = stud;
				break;
			}
			else {
				index++;
			}
		}
	}
}

void traversareHashT(HashTable tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vectHashT[i] != NULL) {
			printf("Pozitia = %d", i);
			printf("	Student { Cod: %d | Medie: %.2f | Nume: %s} \n",
								tabela.vectHashT[i]->cod, 
								tabela.vectHashT[i]->medie, 
								tabela.vectHashT[i]->nume);
		}
	}
}

void dezalocareHashT(HashTable tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vectHashT[i] != NULL) {
			free(tabela.vectHashT[i]->nume);
			free(tabela.vectHashT[i]);
		}
	}
	free(tabela.vectHashT);
}

int stergereHashT(HashTable tabela, int codDeSters) {
	int poz = functieHash(tabela, codDeSters);
	if (tabela.vectHashT[poz] == NULL) {
		return -1;
	}else
		if (tabela.vectHashT[poz]->cod == codDeSters) {
			free(tabela.vectHashT[poz]->nume);
			free(tabela.vectHashT[poz]);

			tabela.vectHashT[poz] = NULL;
		}
		else {
			int index = 1; 
			while (poz + index < tabela.nrElem) {
				if (tabela.vectHashT[poz + index]->cod == codDeSters) {
					poz += index;

					free(tabela.vectHashT[poz]->nume);
					free(tabela.vectHashT[poz]);

					tabela.vectHashT[poz] = NULL;
					break;
				}
				else
					index++;
			}
		}
	return poz;
}

// sa se determine din tabela de dispersie 
// studentii cu mediile intre 7 si 9 
void salvareStudentiByMedie(HashTable tabela, Student*** vectStudenti, int* dimensiune, 
	int limitaMica, int limitaMare) {
	*dimensiune = 0;
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vectHashT[i] != NULL && 
			tabela.vectHashT[i]->medie <= limitaMare && 
			tabela.vectHashT[i]->medie >= limitaMica) {
			(*vectStudenti)[*dimensiune] = tabela.vectHashT[i];
			(*dimensiune)++;
		}
	}
}

void main() {
	HashTable tabela; 
	tabela.nrElem = 23;
	tabela.vectHashT = (Student**)malloc(sizeof(Student*) * tabela.nrElem);
	for (int i = 0; i < tabela.nrElem; i++) {
		tabela.vectHashT[i] = NULL;
	}

	int nrStud;
	Student* s;
	char buffer[30];
	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++) {
		s = (Student*)malloc(sizeof(Student));
		fscanf(f, "%d", &s->cod);

		fscanf(f, "%s", buffer);
		s->nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s->nume, buffer);

		fscanf(f, "%f", &s->medie);


		inserareHash(tabela, s);
	}
	fclose(f);

	printf("--------------- HashTable ---------------\n");
	traversareHashT(tabela);

	printf("\n\n\n");

	printf("--------------- Stergere ---------------\n");
	int poz = stergereHashT(tabela, 48);
	printf("Pozitia care s-a sters este: %d\n", poz);
	traversareHashT(tabela);

	printf("\n\n\n");

	printf("--------------- Studenti By Medie ---------------\n");
	Student** vectStudenti;
	vectStudenti = (Student**)malloc(sizeof(Student*) * nrStud); 
	int dim = 0;
	int limitaMica = 7;
	int limitaMare = 9;
	salvareStudentiByMedie(tabela, &vectStudenti, &dim, limitaMica, limitaMare);
	for (int i = 0; i < dim; i++) {
		printf("	Student { Cod: %d | Medie: %.2f | Nume: %s} \n",
			vectStudenti[i]->cod,
			vectStudenti[i]->medie,
			vectStudenti[i]->nume);
	}

	dezalocareHashT(tabela);
}