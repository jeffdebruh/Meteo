#include "moist.h"
#include "Sort.c"



Data takeDat(FILE* f){
	Data res;
	int i=0;             // 1= data taken with success, 2=Skipline and restart.



	while (i!=1 && getc(f)!=EOF){
		fseek(f,-1,SEEK_CUR);

		if(!noNum(f)){			// take date/station
			i=restart(f);
		}
		else{
			fscanf(f, "%f", &res.val);
			i=1;
			skip(f);
		}
		if(i!=2){              // take moist
			
			if (!noNum(f)){
				i=restart(f);
			}
			else
			{
				fscanf(f, "%f", &res.Num);
				i=1;
				skip(f);
			}
			
		}
		if(i!=2){              // take coords
			
			if (!noNum(f)){
				i=restart(f);
			}
			else
			{
				fscanf(f, "%f", &res.rest[1]);
				skipcoord(f);
				fscanf(f, "%f", &res.rest[2]);
				i=1;
				skip(f);
			}
		}


		
	}

	
	res.den=1;
	return res;
}





void WriteThatDown(Data x, FILE *file){
	
	fprintf(file,"%f;%f;%f,%f;\n", x.val, x.Num, x.rest[1], x.rest[2]);
}


Data Equal(Data x, Data y){
	if (x.Num < y.Num)
		x.Num=y.Num;
	return x;
}

void sortM(int mode, long size, FILE* input, FILE* out, int reverse){
	FILE *finter = fopen("intermoist", "w+");	
	Spe(mode,size, input, finter,reverse);
	fclose(finter);
}





/*int main() {
	FILE *fptr = fopen("filetest2","r");
   	FILE *fout = fopen("output", "w+");
   	Spe(1, 10, fptr, fout, 0);
   	fclose(fptr);
   	fclose(fout);
}*/
