

#include "main.h"


int readArg(char * p){
	if (p[0]=='-' && p[1]=='f')
		return 1;
	if (p[0]=='-' && p[1]=='o')
		return 2;
	if (strcmp(p, "-r")==0)
		return 3;
	if (strcmp(p, "--avl")==0)
		return 4;
	if (strcmp(p, "--abr")==0)
		return 5;
	if (strcmp(p, "--tab")==0)
		return 6;
	if (strcmp(p, "-h")==0)
		return 7;
	if (strcmp(p, "-m")==0)
		return 8;
	if (strcmp(p, "-w")==0)
		return 9;
	if (p[0]=='-' && p[1]=='p' && p[2]>48 && p[2]<52)
		return 11;
	if (p[0]=='-' && p[1]=='t' && p[2]>48 && p[2]<52)
		return 10;
	return -1;
}


int main(int argc, char** argv) {
	int reverse=0;
	int sort=0;
	int y=0, mode=0;
	int in=0, out=0, init=0;
	char *infile;
	char *outfile;
	if (argc>5){
		puts("too much arguments! must be 3 to 5:\n exemple:-f<input file> -o<output file> -mode -r(optionnal) --avl/abr/tab(default=AVL) \n""");
		exit(1);
	}
	if (argc<3){
		puts("too few arguments! must be 3 to 5:\n exemple:-f<input file> -o<output file> -mode -r(optionnal) --avl/abr/tab(defaul=AVL) \n""");
		exit(1);
	}
	
	for(int i=1; i<argc; i++){
		y=readArg(argv[i]);
		
		switch(y){
			case -1:
				printf("did not recognize argument: \"%s\" n°%d\n", argv[i], i);
				exit(1);
				break;
			case 1:
				printf("input file: %s \n", argv[i]+2);
				infile=argv[i]+2;
				in++;
				break;
			case 2:
				printf("output file: %s \n", argv[i]+2);
				outfile=argv[i]+2;
				out++;
				break;
			case 3:
				reverse=1;
				puts("sorting reversed!");
				break;
			case 4:
				
				puts("sorting mode: avl");
				break;
			case 5:
				sort=1;
				puts("sorting mode: bst");
				break;
			case 6:
				sort=2;
				puts("sorting mode: tab");
				break;
			case 7:
				mode=1;
				puts("sorting height");
				init++;
				break;
			case 8:
				mode=2;
				puts("sorting moisture");
				init++;
				break;
			case 9:
				mode=3;
				printf("sorting wind");
				init++;
				break;
			case 10:
				mode=3+(argv[i][2]-48);
				printf("sorting temperature mode: %d\n", (argv[i][2]-48));
				init++;
				break;
			case 11:
				mode=6+(argv[i][2]-48);
				printf("sorting pressure mode: %d\n", (argv[i][2]-48));
				init++;
				break;
			default:
				sort=y-4;
				printf("sorting mode: %d\n", argv[i][2]);
				break;


		}
	}
	if (init!=1){
		puts("input mode error");
		exit(1);
	}
	if (in==0){
		puts("———————————No Input File?——————————— \n⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝\n⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇\n⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀\n⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀\n⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀\n⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n—————————————————————————————");
		exit(2);
	}

	if (in==0){
		puts("———————————No Output File?——————————— \n⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝\n⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇\n⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀\n⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀\n⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀\n⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n—————————————————————————————");
		exit(3);
	}
	
   	FILE *fptr = fopen(infile,"r");
  	if (fptr==NULL){
		puts("failed to open input file");
		exit(2);
	  }
		
   	FILE *fout = fopen(outfile, "w+");
	if (fout==NULL){
		puts("failed to open output file");
		exit(3);
	  }

	switch(mode) {
		case 1:
			puts("height");
			sortH(sort, 70, fptr,fout,reverse);

			break;
		case 2:
			puts("moist");
			sortM(sort, 70, fptr,fout,reverse);
			sortM2(sort, 70, fptr,fout,reverse);

			break;
		case 3:
			puts("wind");
			sortW(sort, 70, fptr,fout,reverse);

			break;
		case 4:
			puts("t1");
			sortT1(sort,70,fptr,fout,reverse);
			break;
		case 5:
			puts("t2");
			sortTP2(sort,5000*8,fptr,fout,reverse);
			break;
		case 6:
			puts("t3");
			sortTP3(sort,5000*8*70,fptr,fout,reverse);
			break;
		case 7:
			puts("p1");
			sortP1(sort,70,fptr,fout,reverse);
			break;
		case 8:
			puts("p2");
			sortTP2(sort,5000*8,fptr,fout,reverse);
			break;
		case 9:
			puts("p3");
			sortTP3(sort,5000*8*70,fptr,fout,reverse);
			break;
	}



	puts("sorting finished");

 	fclose(fptr);
    fclose(fout);
	return 0;
}









