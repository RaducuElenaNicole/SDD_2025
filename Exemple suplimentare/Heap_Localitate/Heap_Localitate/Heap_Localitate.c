#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Localitate Localitate; 
struct Localitate {
	int nrCrt; // prioritate 
	char* denumire; 
	unsigned int populatie; 
	char* tip;
	float bugetLocal;
};

Localitate initLocalitate(int nrCrt, char* denumire, unsigned int populatie, char* tip, float buget) {
	Localitate nou; 

	nou.nrCrt = nrCrt; 
	nou.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1)); 
	strcpy(nou.denumire, denumire); 
	nou.populatie = populatie; 
	nou.tip = (char*)malloc(sizeof(char) * (strlen(tip) + 1));
	strcpy(nou.tip, tip); 
	nou.bugetLocal = buget;

	return nou;
}

void afiseazaLocalitate(Localitate loc) {
	printf("Id: %d | Denumire: %s | Populatie: %u | Tip: %s | Buget: %5.2f \n",
		loc.nrCrt, loc.denumire, loc.populatie, loc.tip, loc.bugetLocal);
}

typedef struct MaxHeap MaxHeap; 
struct MaxHeap {
	Localitate* vectLocalitati; 
	int dimVect; 
};

void afiseazaVectorLocalitati(MaxHeap mh) {
	for (int i = 0; i < mh.dimVect; i++) {
		afiseazaLocalitate(mh.vectLocalitati[i]);
	}
}

MaxHeap filtrare(MaxHeap mh, int index) {
	if (mh.dimVect > 0) {
		int indexMax = index; 
		int indexSTG = 2 * index + 1; 
		int indexDRP = 2 * index + 2; 

		if (indexSTG < mh.dimVect) {
			if (mh.vectLocalitati[indexMax].nrCrt < mh.vectLocalitati[indexSTG].nrCrt) {
				indexMax = indexSTG;
			}
		}

		if (indexDRP < mh.dimVect) {
			if (mh.vectLocalitati[indexMax].nrCrt < mh.vectLocalitati[indexDRP].nrCrt) {
				indexMax = indexDRP;
			}
		}

		if (index != indexMax) {
			Localitate aux = mh.vectLocalitati[index];
			mh.vectLocalitati[index] = mh.vectLocalitati[indexMax];
			mh.vectLocalitati[indexMax] = aux; 

			if (indexMax <= (mh.dimVect - 1) / 2) {
				filtrare(mh, indexMax);
			}
		}
	}
}

void main() {
	MaxHeap heap; 
	heap.dimVect = 5; 
	heap.vectLocalitati = (Localitate*)malloc(sizeof(Localitate) * heap.dimVect); 

	heap.vectLocalitati[0] = initLocalitate(1, "Pitesti", 1200, "oras", 56.90);
	heap.vectLocalitati[1] = initLocalitate(2, "Mioveni", 1200, "oras", 56.90);
	heap.vectLocalitati[2] = initLocalitate(5, "Ploiesti", 1200, "oras", 56.90);
	heap.vectLocalitati[3] = initLocalitate(4, "Craiova", 1200, "oras", 56.90);
	heap.vectLocalitati[4] = initLocalitate(3, "Cluj", 1200, "oras", 56.90);

	for (int i = (heap.dimVect - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}

	afiseazaVectorLocalitati(heap);
}