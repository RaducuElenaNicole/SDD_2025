// Coada de prioritati = HEAP

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student Student; 
struct Student {
	int nrCrt; // prioritatea => dupa acest atribut se filtreaza 
	char* nume; 
	float medie;
};

typedef struct MaxHeap MaxHeap; 
struct MaxHeap {
	Student* vectorStudenti; 
	int dimVector;
};

Student initStudent(int nrCrt, char* nume, float medie) {
	Student studNou; 

	studNou.nrCrt = nrCrt;

	studNou.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(studNou.nume, nume);

	studNou.medie = medie;

	return studNou;
}

void afiseazaStudent(Student stud) {
	printf("NrCrt: %d | Nume: %s | Medie: %5.2f \n", stud.nrCrt, stud.nume, stud.medie);
}

void afiseazaVectorStudenti(MaxHeap mh) {
	for (int i = 0; i < mh.dimVector; i++) {
		printf("Index = %d -> ", i); 
		afiseazaStudent(mh.vectorStudenti[i]);
	}
}

void filtrareMaxHeap(MaxHeap mh, int index) {
	if (mh.dimVector > 0) {
		int pozMax = index; 
		int pozStg = 2 * index + 1; 
		int pozDrp = 2 * index + 2; 

		if (pozStg < mh.dimVector) {
			if(mh.vectorStudenti[pozMax].nrCrt < mh.vectorStudenti[pozStg].nrCrt) {
				pozMax = pozStg;
			}
		}

		if (pozDrp < mh.dimVector) {
			if (mh.vectorStudenti[pozMax].nrCrt < mh.vectorStudenti[pozDrp].nrCrt) {
				pozMax = pozDrp;
			}
		}

		if (pozMax != index) {
			Student aux = mh.vectorStudenti[index]; 
			mh.vectorStudenti[index] = mh.vectorStudenti[pozMax];
			mh.vectorStudenti[pozMax] = aux;

			/*if (pozMax <= (mh.dimVector / 2) - 1) {
				filtrareMaxHeap(mh, pozMax);
			}*/

			filtrareMaxHeap(mh, pozMax);
		}
	}
}

MaxHeap inserare(MaxHeap mh, Student studNou) {
	// +1 ptc se aduga un nou student in vector
	Student* vectorCopie = (Student*)malloc(sizeof(Student) * (mh.dimVector + 1));  
	
	for (int i = 0; i < mh.dimVector; i++) {
		vectorCopie[i] = mh.vectorStudenti[i];
	}

	// se adauga la finalul vectorul noul student
	vectorCopie[mh.dimVector] = studNou;

	// se elibereaza memoria pentru vectorul initial 
	free(mh.vectorStudenti); 

	// se creste dimensiunea vectorului 
	mh.dimVector++;

	mh.vectorStudenti = vectorCopie;

	for (int i = (mh.dimVector - 1) / 2; i > 0; i--) {
		filtrareMaxHeap(mh, i);
	}

	return mh;
}

void dezalocare(MaxHeap mh) {
	for (int i = 0; i < mh.dimVector; i++) {
		free(mh.vectorStudenti[i].nume);
	}
	free(mh.vectorStudenti); 
}

void main() {
	printf("\n"); 

	MaxHeap heap; 

	heap.dimVector = 6; 
	heap.vectorStudenti = (Student*)malloc(sizeof(Student) * heap.dimVector);

	heap.vectorStudenti[0] = initStudent(1, "Ana", 10);
	heap.vectorStudenti[1] = initStudent(2, "Ioana", 9.50);
	heap.vectorStudenti[2] = initStudent(3, "Marian", 5.50);
	heap.vectorStudenti[3] = initStudent(4, "Andrei", 8.50);
	heap.vectorStudenti[4] = initStudent(5, "Catalin", 5.80);
	heap.vectorStudenti[5] = initStudent(6, "Ionut", 8.80);

	printf("--------------- MaxHeap fara filtrare --------------- \n");
	afiseazaVectorStudenti(heap);

	printf("\n\n");

	printf("--------------- MaxHeap dupa filtrare --------------- \n");
	for(int i = (heap.dimVector - 1) / 2; i > 0; i--) {
		filtrareMaxHeap(heap, i);
	}
	afiseazaVectorStudenti(heap);

	dezalocare(heap); // nu stiu cat de corecta este !!!!!

	printf("\n\n --------------------------- \n\n");

	MaxHeap heap2; 
	heap2.dimVector = 0; 
	heap2.vectorStudenti = NULL; 

	Student stud1 = initStudent(1, "Ana", 10);
	Student stud2 = initStudent(2, "Ioana", 9.50);
	Student stud3 = initStudent(3, "Marian", 5.50);
	Student stud4 = initStudent(4, "Andrei", 8.50);
	Student stud5 = initStudent(5, "Catalin", 5.80);
	Student stud6 = initStudent(6, "Ionut", 8.80);

	heap2 = inserare(heap2, stud1);
	heap2 = inserare(heap2, stud2);
	heap2 = inserare(heap2, stud3);
	heap2 = inserare(heap2, stud4);
	heap2 = inserare(heap2, stud5);
	heap2 = inserare(heap2, stud6);

	printf("--------------- MaxHeap varianta 2 --------------- \n");
	afiseazaVectorStudenti(heap2);

	printf("\n\n");
}