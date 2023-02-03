
#include "p1.h"
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
		

		if(i!=2){              // take pressure
			
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

	if (i!=2 && !noNum(f)){                     //Take variation
				res.rest[0]=res.rest[1]=res.Num;     
			}
			else
			{
				fscanf(f, "%f", &res.rest[0]);
				res.rest[1]=res.Num-(res.rest[0]/2);  //calculate MIN 
				res.rest[0]=res.Num+(res.rest[0]/2); //calculate MAX
				i=1;
				skip(f);
			}


	
	res.den=1;
	return res;
}





void WriteThatDown(Data x, FILE *file){
	
	fprintf(file,"%f;%f;%f;%f\n", x.val, (x.Num/x.den), x.rest[0],x.rest[1]);
}


Data Equal(Data x, Data y){
	 x.den+=1;
	 x.Num=x.Num+y.Num;

	 if (x.rest[0]<y.rest[0])
		x.rest[0]=y.rest[0];
	 if (x.rest[1]>y.rest[1])
		x.rest[1]=y.rest[1];
	
	
	return x;
}


void sortP1(int mode, long size, FILE* input, FILE* out, int reverse){
	Spe(mode,size,input,out,reverse);
}



/*int main() {
	FILE *fptr = fopen("filetest","r");
   FILE *fout = fopen("output", "w+");
   Spe(2, 10, fptr, fout, 0);
   fclose(fptr);
   fclose(fout);
}*/
