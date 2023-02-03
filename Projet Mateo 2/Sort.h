#include <stdio.h>
#include <stdlib.h>

typedef struct dtsr{
	long val;            // Valeur a trier
	float Num;            //Valeur a sortir
	int den;            //denominateur Moyenne
	

	float rest[3];  //autre valeur a sortir
	

}Data;

void skipline(FILE *file);

int noNum(FILE* f);

int restart(FILE *f);

void skipcoord(FILE *f);

void skip(FILE *f);

Data takeDat(FILE* file);

void WriteThatDown(Data x, FILE *file);

Data Equal(Data x, Data y);

int Spe(int opt, long size, FILE* fptr, FILE* fout, int mode);
