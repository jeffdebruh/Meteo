
#include "tp2.h"
#include "Sort.c"


Data takeDat(FILE* f){
	Data res;
	int i=0;             // 1= data taken with success, 2=Skipline and restart.



	while (i!=1 && getc(f)!=EOF){
		fseek(f,-1,SEEK_CUR);

		if(!noNum(f)){			// take date
			i=restart(f);
		}
		else{
			fscanf(f, "%f", &res.val);
			i=1;
			skip(f);
		}
		

		if(i!=2){              // take temperature or pressure
			
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
		
	}

	res.den=1;

	return res;
}





void WriteThatDown(Data x, FILE *file){
	
	fprintf(file,"%f;%f;\n", x.val, (x.Num/x.den));
}


Data Equal(Data x, Data y){
	 x.den+=1;
	 x.Num=x.Num+y.Num;
	return x;
}



void sortTP2(int mode, long size, FILE* input, FILE* out, int reverse){
	Spe(mode,size,input,out,reverse);
}


/*int main() {
	FILE *fptr = fopen("filetest","r");
   FILE *fout = fopen("output", "w+");
   Spe(2, 10, fptr, fout, 0);
   fclose(fptr);
   fclose(fout);
}*/
