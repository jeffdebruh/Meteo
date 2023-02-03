

#include "wind.h"



Data takeDat(FILE* f){
	Data res;
	int i=0;             // 1= data taken with success, 2=Skipline and restart.

	float d;
	float v;
	while (i!=1 && getc(f)!=EOF){
		fseek(f,-1,SEEK_CUR);

		if(!noNum(f)){			// take date/station
			i=restart(f);
		}
		else{
			fscanf(f, "%li", &res.val);
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
		
	}
	
	res.Num= v*cosf(d); //x axis
	res.rest[0]= v*sinf(d); //y axis
	res.den=1;
	printf("val: %li \n", res.val);
	printf("Num: %f \n", res.Num);
	return res;

	//
}





void WriteThatDown(Data z, FILE *file){
	int x= z.Num/z.den;
	int y= z.rest[0]/z.den;
	
	fprintf(file,"%f;%f;%f,%f;\n", sqrt((x*x)+(y*y)) , atanf(y/x), z.rest[1], z.rest[2]);
}


Data Equal(Data x, Data y){
	 x.den+=1;
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
