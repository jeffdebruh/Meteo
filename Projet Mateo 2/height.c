

#include "height.h"



Data takeDat(FILE* f){
	Data res;
	int i=0;             // 1= data taken with success, 2=Skipline and restart.



	while (i!=1 && getc(f)!=EOF){
		fseek(f,-1,SEEK_CUR);

		if(!noNum(f)){			// take date/station
			i=restart(f);
		}
		else{
			fscanf(f, "%f", &res.Num);
			i=1;
			skip(f);
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

		if(i!=2){              // take height
			
			if (!noNum(f)){
				i=restart(f);
			}
			else
			{
				fscanf(f, "%li", &res.val);
				i=1;
				skip(f);
			}
			
		}
		
	}

	
	res.den=1;
	return res;
}





void WriteThatDown(Data x, FILE *file){
	
	fprintf(file,"%li;%f;%f,%f;\n", x.val, x.Num, x.rest[1], x.rest[2]);
}


Data Equal(Data x, Data y){

	return x;
}




void sortH(int mode, long size, FILE* input, FILE* out, int reverse){
	Spe(mode,size,input,out,reverse);
}

/*int main() {
	FILE *fptr = fopen("filetest2","r");
   FILE *fout = fopen("output", "w+");
   Spe(2, 10, fptr, fout, 0);
   fclose(fptr);
   fclose(fout);
}*/
