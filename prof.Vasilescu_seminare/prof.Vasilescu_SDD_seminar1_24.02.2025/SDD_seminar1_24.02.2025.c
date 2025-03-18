// seminar 1 - 24/02/2025

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

// transmitere prin pointeri 
void interschimbareValori(int* a, int* b) {
	// dereferentiere
	int aux = *a; 
	*a = *b;
	*b = aux;
}

void main() {
	int numarTeme = 5;
	float medieFinala = 10.0f;
	char litera = 'a';

	printf("\nNumar teme: %d | Media finala: %.2f | Litera: %c | Litera ca numar intreg(codul ASCII): %d", 
					numarTeme, medieFinala, litera, litera);
	// %.2f -> float cu maxim 2 zecimale 

	// sir de caractere: abcd dar definit ca valori de tip int (valorile din tabela Ascii)
	// alocare statica 
	char sirCaractere[5]; // abcd + "\0" 
	// ! crtl + D
	sirCaractere[0] = 97;
	sirCaractere[1] = 98;
	sirCaractere[2] = 99;
	sirCaractere[3] = 100;
	sirCaractere[4] = '\0';
	printf("\nSir = %s", sirCaractere);

	// sir de caractere alocat dinamic 
	char* nume = (char*)malloc(sizeof(char) * 6);
	// 6 = strlen("Mihai") + 1
	strcpy(nume, "Mihai");
	printf("\nNumele este %s", nume);
	// pointer = adresa de memorie HEAP 
	// stiva lui main
	

	// transmiterea parametrilor - prin referinta, valoare, pointer (in c++)
	// in c -> prin pointer sau prin valoare 
	// transmiterea prin valoare => valori locale, se pierd modificarile 
	// transmiterea prin pointer 

	int nr1 = 7; 
	int nr2 = 9;
	printf("\nNr1 = %d, Nr2 = %d", nr1, nr2);

	// interschimbareValori(nr1, nr2); // prin valoare
	
	interschimbareValori(&nr1, &nr2); // prin adrese (pointeri)
	printf("\nvalori interschimbate -> Nr1 = %d, Nr2 = %d", nr1, nr2);
	// valoarea de la o adresa  => dereferentiere 

	// dezalocare 
	free(nume);

	printf("\n");
}