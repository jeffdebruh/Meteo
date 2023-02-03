

#include "wind.h"
#include "Sort.c"


Data takeDat(FILE* f){
	Data res;
	int i=0;             // 1= data taken with success, 2=Skipline and restart.

	float d;
	float v;
	while (i!=1 && getc(f)!=EOF){
		fseek(f,-1,SEEK_CUR);

		if(!noNum(f)){			// station
			i=restart(f);
		}
		else{
			fscanf(f, "%f", &res.val);
			i=1;
			skip(f);
		}
			
		
		if(i!=2){              // take wind dir
			
			if (!noNum(f)){
				i=restart(f);
			}
			else
			{
				fscanf(f, "%f", &d);
				i=1;
				skip(f);
			}
			
		}
		if(i!=2){              // take wind speed
			
			if (!noNum(f)){
				i=restart(f);
			}
			else
			{
				fscanf(f, "%f", &v);
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
	
	res.Num= v*cosf(d); //x axis
	res.rest[0]= v*sinf(d); //y axis
	res.den=1;
	return res;

	//
}





void WriteThatDown(Data z, FILE *file){
	float x= z.Num/z.den; //X axis average
	float y= z.rest[0]/z.den;  //X axis average
	float e=atanf(y/x); //wind direction
	float s=sqrtf((x*x)+(y*y)); //wind speed
	if (isnanf(e))
		e=0;
	if (isnanf(s))
		s=0;
	
	fprintf(file,"%f;%f;%f;%f;%f;\n", z.val, s, e, z.rest[1], z.rest[2]);
}


Data Equal(Data x, Data y){
	 x.den+=1; //prepare for average calculation in WriteThatDown
	 x.Num=x.Num+y.Num;
	 x.rest[0]=x.rest[0]+y.rest[0];
	return x;
}




void sortW(int mode,long size, FILE* input, FILE* out, int reverse){
	Spe(mode,size,input,out,reverse);
}

/*int main() {
	FILE *fptr = fopen("filetest2","r");
   FILE *fout = fopen("output", "w+");
   Spe(2, 10, fptr, fout, 0);
   fclose(fptr);
   fclose(fout);
}*/
