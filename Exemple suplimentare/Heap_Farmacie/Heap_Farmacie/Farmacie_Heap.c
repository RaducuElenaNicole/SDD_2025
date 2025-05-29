#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct Farmacie Farmacie; 
struct Farmacie {
	int id; 
	char* denumire; 
	float suprafata; 
	unsigned char nrAngajati;
};

Farmacie initFarmacie(int id, char* denumire, float suprafata, unsigned char nrAngajati) {
	Farmacie farm; 

	farm.id = id; 
	farm.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1)); 
	strcpy(farm.denumire, denumire); 
	farm.suprafata = suprafata; 
	farm.nrAngajati = nrAngajati;

	return farm;
}

void afiseazaFarmacie(Farmacie f) {
	printf("Id: %d | Denumire: %s | Suprafata: %5.2f | Numar angajati: %u \n",
		f.id, f.denumire, f.suprafata, f.nrAngajati);
}

typedef struct MaxHeap MaxHeap; 
struct MaxHeap {
	Farmacie* vectFarmacii; 
	int dimVect;
};

void afiseazaVectFarmacii(MaxHeap mh) {
	for (int i = 0; i < mh.dimVect; i++) {
		afiseazaFarmacie(mh.vectFarmacii[i]);
	}
}

void filtrare(MaxHeap mh, int index) {
	if (mh.dimVect > 0) {
		int pozMax = index; 
		int pozStg = 2 * index + 1; 
		int pozDrp = 2 * index + 2; 

		if (pozStg < mh.dimVect) {
			if (mh.vectFarmacii[pozMax].id < mh.vectFarmacii[pozStg].id) {
				pozMax = pozStg;
			}
		}

		if (pozDrp < mh.dimVect) {
			if (mh.vectFarmacii[pozMax].id < mh.vectFarmacii[pozDrp].id) {
				pozMax = pozDrp;
			}
		}

		if (pozMax != index) {
			Farmacie farm = mh.vectFarmacii[index];
			mh.vectFarmacii[index] = mh.vectFarmacii[pozMax];
			mh.vectFarmacii[pozMax] = farm; 

			if (pozMax <= (mh.dimVect - 1) / 2) {
				filtrare(mh, pozMax);
			}
		}
	}
}

void main() {
	MaxHeap h; 
	h.dimVect = 6; 
	h.vectFarmacii = (Farmacie*)malloc(sizeof(Farmacie) * h.dimVect); 

	h.vectFarmacii[0] = initFarmacie(1, "Farm1", 23.55, 7);
	h.vectFarmacii[1] = initFarmacie(2, "Farm2", 120, 19);
	h.vectFarmacii[2] = initFarmacie(3, "Farm3", 11.55, 2);
	h.vectFarmacii[3] = initFarmacie(4, "Farm4", 24.55, 6);
	h.vectFarmacii[4] = initFarmacie(5, "Farm5", 80, 10);
	h.vectFarmacii[5] = initFarmacie(6, "Farm6", 118.90, 15);

	for (int i = (h.dimVect - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afiseazaVectFarmacii(h);
}