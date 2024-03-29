#include <stdio.h>
#include <stdlib.h>

typedef struct dtsr{
	float val;            // value to sort
	float Num;            //secondary value (average/secondary sorting)
	int den;            //average denominator
	

	float rest[3];  //other values needed
	

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
