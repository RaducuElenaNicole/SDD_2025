#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Student Student; 
struct Student {
	int id; 
	char* nume; 
	float medie; 
};

Student initStudent(int id, char* nume, float medie) {
	Student studNou; 

	studNou.id = id; 
	studNou.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1)); 
	strcpy(studNou.nume, nume); 
	studNou.medie = medie;

	return studNou;
}

void afisareStudent(Student stud) {
	printf("Id: %d | Nume: %s | Medie: %5.2f \n", stud.id, stud.nume, stud.medie); 
}

typedef struct nodArbore nodArbore; 
struct nodArbore {
	Student info; 
	nodArbore* stanga; 
	nodArbore* dreapta;
};

nodArbore* creeazaNodArbore(Student stud, nodArbore* stg, nodArbore* drp) {
	nodArbore* nod = (nodArbore*)malloc(sizeof(nodArbore)); 

	nod->info = initStudent(stud.id, stud.nume, stud.medie); 
	nod->stanga = stg; 
	nod->dreapta = drp; 

	return nod;
}

nodArbore* insereazaNodABC(nodArbore* radacina, Student studNou) {
	if (radacina) {
		if (studNou.id < radacina->info.id) {
			// subarborele stang contine nodurile cu valorile mai mici decat radacina 
			radacina->stanga = insereazaNodABC(radacina->stanga, studNou); 
			return radacina;
		}
		else if (studNou.id > radacina->info.id) {
			// subarborele drept contine nodurile cu valorile mai mare decat radacina 
			radacina->dreapta = insereazaNodABC(radacina->dreapta, studNou); 
			return radacina;
		}
		else {
			// NU SE INSEREAZA NIMIC 
			// id - ul deja exista in arbore 
			return radacina;
		}
	}
	else {
		return creeazaNodArbore(studNou, NULL, NULL);
	}
}

void inordine(nodArbore* arbore) {
	// INordine -> IN => radacina este in mijloc 
	// stanga - radacina - dreapta (SRD)
	if (arbore) {
		inordine(arbore->stanga);
		afisareStudent(arbore->info); 
		inordine(arbore->dreapta);
	}
}

void postordine(nodArbore* arbore) {
	// POSTordine -> POST => radacina este la final
	// stanga - dreapta - radacina (SDR)
	if (arbore) {
		postordine(arbore->stanga);
		postordine(arbore->dreapta);
		afisareStudent(arbore->info);
	}
}

void preordine(nodArbore* arbore) {
	// PREordine -> PRE => radacina este la inceput 
	// radacina - stanga - dreapta (RSD)
	if (arbore) {
		afisareStudent(arbore->info); 
		preordine(arbore->stanga);
		preordine(arbore->dreapta);
	}
}

void main() {
	nodArbore* arbore = NULL;

	Student stud1 = initStudent(7, "Ana", 5.90);
	Student stud2 = initStudent(6, "Ioana", 9.99);
	Student stud3 = initStudent(1, "Mihai", 3.70);
	Student stud4 = initStudent(9, "Andrei", 10);
	Student stud5 = initStudent(10, "Laurentiu", 4.99);
	Student stud6 = initStudent(2, "Ilinca", 9.99);

	arbore = insereazaNodABC(arbore, stud1);
	arbore = insereazaNodABC(arbore, stud2);
	arbore = insereazaNodABC(arbore, stud3);
	arbore = insereazaNodABC(arbore, stud4);
	arbore = insereazaNodABC(arbore, stud5);
	arbore = insereazaNodABC(arbore, stud6);

	printf("--------------- Preordine ---------------\n");
	preordine(arbore);

	printf("\n\n");

	printf("--------------- Postordine ---------------\n");
	postordine(arbore);

	printf("\n\n");

	printf("--------------- Inordine ---------------\n");
	inordine(arbore);

	printf("\n\n");
}