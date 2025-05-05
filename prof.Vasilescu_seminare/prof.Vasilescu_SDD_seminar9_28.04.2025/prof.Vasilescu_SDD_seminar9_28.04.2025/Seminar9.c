// Coada de prioritati (MaxHeap)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct Examen Examen;
struct Examen {
	int nrCredite; // prioritate
	char* disciplina; 
	float nota; 
};

typedef struct MaxHeap MaxHeap; 
struct MaxHeap {
	int dimVector; 
	Examen* vectorExamene;
};

Examen initExamen(int nrCredite, char* disciplina, float nota) {
	Examen nou; 

	nou.nrCredite = nrCredite; 

	nou.disciplina = (char*)malloc(sizeof(char) * (strlen(disciplina) + 1)); 
	strcpy(nou.disciplina, disciplina); 

	nou.nota = nota; 

	return nou; 
}

void afiseazaExamen(Examen exm) {
	printf("NrCredite: %d | Disciplina: %s | Nota: %.2f",
		exm.nrCredite, exm.disciplina, exm.nota);
}

void traversareVector(MaxHeap mh) {
	for (int i = 0; i < mh.dimVector; i++) {
		printf("Examenul %d (indexul din vector: %d) -> ", i + 1, i);
		afiseazaExamen(mh.vectorExamene[i]); 
		printf("\n");
	}
}

void filtrareMaxHeap(MaxHeap mHeap, int index) {
	if (mHeap.dimVector > 0) {

		int pozMax = index;
		int pozStg = 2 * index + 1; 
		int pozDrp = 2 * index + 2;

		// pun > pt Min Heap
		if (pozStg < mHeap.dimVector &&
			mHeap.vectorExamene[pozMax].nrCredite < mHeap.vectorExamene[pozStg].nrCredite) {
			pozMax = pozStg;
		}

		if (pozDrp < mHeap.dimVector &&
			mHeap.vectorExamene[pozMax].nrCredite < mHeap.vectorExamene[pozDrp].nrCredite) {
			pozMax = pozDrp;
		}

		if (pozMax != index) {
		// interschimbarea propriu-zisa
			Examen aux = mHeap.vectorExamene[index]; 
			mHeap.vectorExamene[index] = mHeap.vectorExamene[pozMax];
			mHeap.vectorExamene[pozMax] = aux; 

			if (pozMax <= (mHeap.dimVector / 2 - 1)) {
				filtrareMaxHeap(mHeap, pozMax);
			}
		}
	}
}

void main() {
	printf("\n");

	MaxHeap mh; 
	mh.dimVector = 6; 
	mh.vectorExamene = (Examen*)malloc(sizeof(Examen) * mh.dimVector);

	mh.vectorExamene[0] = initExamen(1, "BTI", 5.8); 
	mh.vectorExamene[1] = initExamen(2, "PAW", 9.8); 
	mh.vectorExamene[2] = initExamen(3, "SDD", 4.6); 
	mh.vectorExamene[3] = initExamen(4, "BCO", 7.4); 
	mh.vectorExamene[4] = initExamen(5, "POO", 9.5); 
	mh.vectorExamene[5] = initExamen(6, "CSE", 10); 

	printf("--------------- MaxHeap fara filtrare --------------- \n");
	traversareVector(mh);

	printf("\n\n"); 

	printf("--------------- MaxHeap valid dupa filtrare --------------- \n");
	for (int i = mh.dimVector / 2 - 1; i >= 0; i--) {
		filtrareMaxHeap(mh, i);
	}
	traversareVector(mh);
}