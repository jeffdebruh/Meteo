#include "tp3.h"




typedef struct dt{
	long val;            
	float Num;            
	int den;            
	

	float rest[5];  
	

}Data;

//THIS FILE IS NO LONGER USED in the program due to technicial difficulties
//Data Explained in Sort.h
//Functions Explained in Sort.c, only changes are 'greater than' comparator becoming 'Equal or greater than' in sorting fonctions: 'insert' 'insertAVL' and 'putInTabRec'


void skipline(FILE *file){
	int c;
	while (c = fgetc(file), c != '\n' && c != EOF);
}



int noNum(FILE* f){
	char c=getc(f);
	fseek(f,-1,SEEK_CUR);
	if (c==';' || c=='\n')
		return 0;
	return 1;
}

int restart(FILE *f){
	skipline(f);
	return 2;
}

void skip(FILE *f){
	char c;
	int i=0;
	
	while(c=getc(f), c!=';' && c!='\n' && i<20) {i++;}
	
}




Data takeDat(FILE* file);

void WriteThatDown(Data x, FILE *file);

Data Equal(Data x, Data y){
	return x;
	}








//========================== TAB SORT=================================

void put(Data tab[], long t, Data a, long* size){
	for(int i=*size; i>=t;i--)
		tab[i+1]=tab[i];
	
	tab[t]=a;
	*size+=1;


}
	

Data* putInTabRec(Data phead[], Data a, long start, long end, long* size){
		long mid=(start+end)/2;
		
		
		
		if(phead[start].val>a.val || (phead[start].val==a.val && phead[start].Num>a.Num)){
			put(phead, start, a, size);
			return phead;
		}
		if(phead[start].val<a.val || (phead[start].val==a.val && phead[start].Num<a.Num)){
			if(phead[start+1].val>a.val){

				put(phead, start+1, a, size);
				return phead;
			}
		}
				
			
		if(phead[end].val<a.val || (phead[end].val==a.val && phead[end].Num<a.Num)){
			put(phead, end+1, a, size);
			return phead;
		}
		if(phead[start].val==a.val || (phead[start].val==a.val && phead[start].Num==a.Num)){
			phead[start]=Equal(phead[start],a);
			return phead;
			}
		if(phead[end].val==a.val || (phead[end].val==a.val && phead[end].Num==a.Num)){
			phead[end]=Equal(phead[end],a);
			return phead;
			}
		if(phead[mid].val>a.val || (phead[mid].val==a.val && phead[mid].Num>a.Num)){
			return putInTabRec(phead, a, start, mid, size);
		}
		if(phead[mid].val<a.val || (phead[mid].val==a.val && phead[mid].Num<a.Num)){	
			return putInTabRec(phead, a, mid, end, size);
		}
		else{
			phead[mid]=Equal(phead[mid], a);
			return phead;
		}
			
			
		
}


Data* putInTab (Data phead[], Data a, long* size){
	if (phead[0].val>a.val){
		
		put(phead, 0, a, size);
		return phead;
	}
		
	return putInTabRec(phead, a, 0, *(size)-1, size);
}


//========================== AVL ==================================






int min(int a, int b){
    if (a<b)
        return a;
    else 
        return b;
}


int max(int a, int b){
    if (a>b)
        return a;
    else 
        return b;
}

typedef struct AVL{
	Data value;
	struct AVL* pleft;
	struct AVL* pright;
    int eq;

}AVLNode;



int isEmptyAVL(AVLNode* pTree){
	return (pTree==NULL);
}

int hasLeftChildAVL(AVLNode* pTree){
	if(isEmptyAVL(pTree)){
		exit(4);
	}
	return (pTree->pleft!=NULL);
}

int hasRightChildAVL(AVLNode* pTree){
	if(isEmptyAVL(pTree)){
		exit(4);
	}
	return (pTree->pright!=NULL);
}





AVLNode* createAVL(Data val){
	AVLNode* pTree = malloc(sizeof(AVLNode));
	if(pTree == NULL){
		exit(4);
	}
	pTree->value = val;
	pTree->pleft = NULL;
	pTree->pright = NULL;
    pTree->eq=0;
	return pTree;
}


AVLNode* rotateRight(AVLNode* a){
    AVLNode* p=a->pleft;
    int eqa=a->eq, eqp=p->eq;
    
    a->pleft=p->pright;
    p->pright=a;

    a->eq= eqa-min(eqp, 0)+1;
    p->eq= max(max(eqa+2, eqa+eqp+2), eqp+1);
    a=p;
    return a;
}

AVLNode* rotateLeft(AVLNode* a){
    AVLNode* p=a->pright;
    int eqa=a->eq, eqp=p->eq;
    
    a->pright=p->pleft;
    p->pleft=a;

    a->eq= eqa-max(eqp, 0)-1;
    p->eq= min(min(eqa-2, eqa+eqp-2), eqp-1);
    a=p;
    return a;
}

AVLNode* rotateRightDouble(AVLNode* a){
    a->pleft= rotateLeft(a->pleft);
    return rotateRight(a);
}

AVLNode* rotateLeftDouble(AVLNode* a){
    a->pright= rotateRight(a->pright);
    return rotateLeft(a);
}

AVLNode* balanceAVL(AVLNode* a){
    if (a->eq>=2){

        if (a->pright->eq>=0)
            return rotateLeft(a);
        else
            return rotateLeftDouble(a);
    }
    else if(a->eq<=-2){
       
        if (a->pleft->eq<=0)
            return rotateRight(a);
        else
            return rotateRightDouble(a);
    }   
    return a;    

}






AVLNode* insertAVL(AVLNode* a, Data e, int* h){
    if(a == NULL){
		*h=1;
        return createAVL(e);
	}
    else if (e.val < a->value.val){
        a->pleft=insertAVL(a->pleft,e,h);
        *h=-(*h);
    }
    else if (e.val > a->value.val){
        a->pright=insertAVL(a->pright, e, h);
    }
    else
    {
		if (e.Num < a->value.Num){
        a->pleft=insertAVL(a->pleft,e,h);
        *h=-(*h);
    	}
    	else if (e.Num > a->value.Num){
        	a->pright=insertAVL(a->pright, e, h);
    	}
    }
    
    if (*h!=0){
        a->eq += *h;
        a=balanceAVL(a);
        if (a->eq==0)
            *h=0;
        else 
            *h=1;
    } 
    return a;
    
}

void delLeftAVL(AVLNode* pTree);
void delRightAVL(AVLNode* pTree){
	
	if (pTree==NULL)
		exit(4);
	if (hasRightChildAVL(pTree)){	
		if(hasRightChildAVL(pTree->pright)){
			delRightAVL(pTree->pright);
		}
		if(hasLeftChildAVL(pTree->pright)){
			delLeftAVL(pTree->pright);
		}
		AVLNode* pFree = pTree->pright;
		pTree->pright = NULL;
		free(pFree);
	}

}



void delLeftAVL(AVLNode* pTree){
	
	if (pTree==NULL)
		exit(4);
	if (hasLeftChildAVL(pTree)){	
		if(hasLeftChildAVL(pTree->pleft)){
			delLeftAVL(pTree->pleft);
		}
		if(hasRightChildAVL(pTree->pleft)){
			delRightAVL(pTree->pleft);
		}
		AVLNode* pFree = pTree->pleft;
		pTree->pleft = NULL;
		free(pFree);
	}

}



//============================= BST ==================================


typedef struct Tree{
	Data value;
	struct Tree* pleft;
	struct Tree* pright;

}TreeNode;

typedef TreeNode PTreeNode;

TreeNode* createTree(Data val){
	TreeNode* pTree = malloc(sizeof(TreeNode));
	if(pTree == NULL){
		exit(4);
	}
	pTree->value = val;
	pTree->pleft = NULL;
	pTree->pright = NULL;
	return pTree;
}

int isEmpty(TreeNode* pTree){
	return (pTree==NULL);
}


int hasLeftChild(TreeNode* pTree){
	if(isEmpty(pTree)){
		exit(4);
	}
	return (pTree->pleft!=NULL);
}

int hasRightChild(TreeNode* pTree){
	if(isEmpty(pTree)){
		exit(4);
	}
	return (pTree->pright!=NULL);
}

int isLeaf(TreeNode* pTree){
	int res=0;
	if(!isEmpty(pTree)){
		res=(pTree->pleft==NULL && pTree->pright==NULL);
	}
	return res;
}



void insert(TreeNode* pTree, Data e){
	TreeNode* tamp;
	
	if(isEmpty(pTree)){
		
		exit(4);
	}
	printf("%f/%f\n", e.val, e.Num);
	puts("hehe");
	
	if(e.val > pTree->value.val || (e.val==pTree->value.val && e.Num > pTree->value.Num)){
		puts("heh");
		if (isEmpty(pTree->pright) || (e.val<pTree->pright->value.val || (e.val==pTree->pright->value.val && e.Num < pTree->pleft->value.Num))){
			tamp= pTree->pright;
			pTree->pright=createTree(e);
			pTree->pright->pright=tamp;
		}
		else if(!isEmpty(pTree->pright))
			insert(pTree->pright, e);
	}
	
	
	if(e.val < pTree->value.val || (e.val==pTree->value.val && e.Num < pTree->value.Num)){
		if (isEmpty(pTree->pleft) || (e.val>pTree->pleft->value.val || (e.val==pTree->pleft->value.val && e.Num > pTree->pleft->value.Num))){
			tamp= pTree->pleft;
			pTree->pleft=createTree(e);
			pTree->pleft->pleft=tamp;
		}
		else if(!isEmpty(pTree->pleft))
			insert(pTree->pleft, e);
	}

    
}




void delLeft(TreeNode* pTree);
void delRight(TreeNode* pTree){
	
	if (pTree==NULL)
		exit(4);
	if (hasRightChild(pTree)){	
		if(hasRightChild(pTree->pright)){
			delRight(pTree->pright);
		}
		if(hasLeftChild(pTree->pright)){
			delLeft(pTree->pright);
		}
		TreeNode* pFree = pTree->pright;
		pTree->pright = NULL;
		free(pFree);
	}

}



void delLeft(TreeNode* pTree){
	
	if (pTree==NULL)
		exit(4);
	if (hasLeftChild(pTree)){	
		if(hasLeftChild(pTree->pleft)){
			delLeft(pTree->pleft);
		}
		if(hasRightChild(pTree->pleft)){
			delRight(pTree->pleft);
		}
		TreeNode* pFree = pTree->pleft;
		pTree->pleft = NULL;
		free(pFree);
	}

}
	

	









//============================= SORT FONCTIONS ==========================================







void walkthrough_infAVL(AVLNode* pTree, FILE *out){  //Writing file in ascending order
	if (pTree != NULL){
		
		walkthrough_infAVL(pTree->pleft, out);
		WriteThatDown(pTree->value, out);
		walkthrough_infAVL(pTree->pright, out);
		
	}

} 
void walkthrough_finAVL(AVLNode* pTree, FILE *out){ //Writing file in descending order
	if (pTree != NULL){
		
		walkthrough_finAVL(pTree->pright, out);
		WriteThatDown(pTree->value, out);
		walkthrough_finAVL(pTree->pleft, out);
		
	}

} 

void walkthrough_inf(TreeNode* pTree, FILE *out){ //Writing file in ascending order
	if (pTree != NULL){
		
		walkthrough_inf(pTree->pleft, out);
		WriteThatDown(pTree->value, out);
		walkthrough_inf(pTree->pright, out);
		
	}

}
void walkthrough_fin(TreeNode* pTree, FILE *out){ //Writing file in descending order
	if (pTree != NULL){
		
		walkthrough_fin(pTree->pright, out);
		WriteThatDown(pTree->value, out);
		walkthrough_fin(pTree->pleft, out);
		
	}

}




void Tabsort(FILE* file, long nb, FILE* output, int mode){
	Data* tab;
	tab=malloc(nb*sizeof(Data));
	tab[0]=takeDat(file);
	long i=0, size=1;
	
	while(getc(file) != EOF){
	fseek(file,-1,SEEK_CUR);
	putInTab(tab, takeDat(file), &size);
	
	skipline(file);
	
	}
	puts("writing output");
	if(mode==1){
		i=size-1;
		while(i>=0){
			WriteThatDown(tab[i], output);
			i--;
		}
			
	}
	else{
		while(i<size){
			WriteThatDown(tab[i], output);
			i++;
		}
	}
	puts("freeing memory...");
	free(tab);
	
}


void AVLsort(FILE* file, FILE* output, int mode){
	AVLNode* pRoot=createAVL(takeDat(file));
	int *h;
	int k=0;
	h=&k;
	
	while(getc(file) != EOF){
	fseek(file,-1,SEEK_CUR);
	pRoot=insertAVL(pRoot, takeDat(file), h);
	
	skipline(file);
	
	}
	puts("wrinting output...");
	if (mode==1)
		walkthrough_finAVL(pRoot, output);
	else
		walkthrough_infAVL(pRoot, output);
	puts("freeing memory...");

	delLeftAVL(pRoot);
	delRightAVL(pRoot);
	free(pRoot);



}

void BSTsort(FILE* file, FILE* output, int mode){
	TreeNode* pRoot=createTree(takeDat(file));
	if (isEmpty(pRoot))
		exit(4);

	while(getc(file) != EOF){
	fseek(file,-1,SEEK_CUR);
	insert(pRoot, takeDat(file));
	
	skipline(file);
	
	}
	puts("wrinting output...");
	if (mode==1)
		walkthrough_fin(pRoot, output);
	else
		walkthrough_inf(pRoot, output);
	puts("freeing memory...");
	delLeft(pRoot);
	delRight(pRoot);
	free(pRoot);

}

int Spe(int opt, long taille, FILE* fptr, FILE* fout, int mode)
{
   

   
   switch(opt){
	   case 0:
	   		AVLsort(fptr, fout, mode);
			break;
		case 1:
			BSTsort(fptr, fout, mode);
			break;
		case 2:
			Tabsort(fptr, taille, fout, mode);
			break;
		default:
			AVLsort(fptr, fout, mode);
			break;
		}
   
   
	
	return 0;
}





//========================================== TP3 MODE SPECIFICS =========================================================


Data takeDat(FILE* f){
	Data res;
	int i=0;             // 1= data taken with success, 2=Skipline and restart.



	while (i!=1 && getc(f)!=EOF){
		fseek(f,-1,SEEK_CUR);

		if(!noNum(f)){			// take station
			i=restart(f);
		}
		else{
			fscanf(f, "%f", &res.Num);
			i=1;
			skip(f);
		}
		if(i!=2){              // take Date
			
			if (!noNum(f)){
				i=restart(f);
			}
			else
			{
				fscanf(f, "%f", &res.val);
				i=1;
				skip(f);
			}
			
		}
		if(i!=2){              // take temp
			
			if (!noNum(f)){
				i=restart(f);
			}
			else
			{
				fscanf(f, "%f", &res.rest[0]);
				i=1;
				skip(f);
			}
		}


		
	}
	printf("%f/%f/%f\n", res.Num, res.val, res.rest[0]);
	
	res.den=1;
	return res;
}





void WriteThatDown(Data x, FILE *file){
	fprintf(file,"%f;%f;%f\n", x.val, x.Num, x.rest[0]);
}




void sortTP3(int mode, long size, FILE* input, FILE* out, int reverse){
	Spe(mode,size,input,out,reverse);
}




/*int main() {
	FILE *fptr = fopen("filetest2","r");
   	FILE *fout = fopen("output", "w+");
   	Spe(1, 10, fptr, fout, 0);
   	fclose(fptr);
   	fclose(fout);
}*/
