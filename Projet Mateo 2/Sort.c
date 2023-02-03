

#include "Sort.h"


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

void skipcoord(FILE *f){
	char c;
	int i=0;
	
	while(c=getc(f), c!=',' && i<20) {i++;}
	
}

void skip(FILE *f){
	char c;
	int i=0;
	
	while(c=getc(f), c!=';' && c!='\n' && i<20) {i++;}
	
}



Data takeDat(FILE* file);

void WriteThatDown(Data x, FILE *file);

Data Equal(Data x, Data y);








//========================== TAB SORT=================================




void put(Data tab[], long t, Data a, long* size){
	for(int i=*size; i>=t;i--)
		tab[i+1]=tab[i];
	
	tab[t]=a;
	*size+=1;


}
	

Data* putInTabRec(Data phead[], Data a, long start, long end, long* size){
		long mid=(start+end)/2;
		if(phead[start].val>a.val){
			put(phead, start, a, size);
			return phead;
		}
		if(phead[start].val<a.val){
			if(phead[start+1].val>a.val){

				put(phead, start+1, a, size);
				return phead;
			}
		}
				
			
		if(phead[end].val<a.val){
			put(phead, end+1, a, size);
			return phead;
		}
		if(phead[start].val==a.val){
			phead[start]=Equal(phead[start],a);
			return phead;
			}
		if(phead[end].val==a.val){
			phead[end]=Equal(phead[end],a);
			return phead;
			}
		if(phead[mid].val>a.val){
			return putInTabRec(phead, a, start, mid, size);
		}
		if(phead[mid].val<a.val){	
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
		exit(1);
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
		a->value=Equal(a->value, e);
        *h=0;
        return a;
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
	
	
	if(e.val > pTree->value.val){
		if (isEmpty(pTree->pright) || e.val<pTree->pright->value.val){
			tamp= pTree->pright;
			pTree->pright=createTree(e);
			pTree->pright->pright=tamp;
		}
		else if(!isEmpty(pTree->pright))
			insert(pTree->pright, e);
	}
	
	
	if(e.val < pTree->value.val){
		if (isEmpty(pTree->pleft) || e.val>pTree->pleft->value.val){
			tamp= pTree->pleft;
			pTree->pleft=createTree(e);
			pTree->pleft->pleft=tamp;
		}
		else if(!isEmpty(pTree->pleft))
			insert(pTree->pleft, e);
	}
	else
    {
		pTree->value=Equal(pTree->value, e);
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
	puts("writing output...");
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
	puts("writing output...");
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
	
	while(getc(file) != EOF){
	fseek(file,-1,SEEK_CUR);
	insert(pRoot, takeDat(file));
	
	skipline(file);
	
	}
	puts("writing output...");
	if (mode==1)
		walkthrough_fin(pRoot, output);
	else
		walkthrough_inf(pRoot, output);
	puts("freeing memory...");
	
	delLeft(pRoot);
	delRight(pRoot);
	free(pRoot);
}

int Spe(int opt, long size, FILE* fptr, FILE* fout, int mode)
{
   

   
   switch(opt){
	   case 0:
	   		AVLsort(fptr, fout, mode);
			break;
		case 1:
			BSTsort(fptr, fout, mode);
			break;
		case 2:
			Tabsort(fptr, size, fout, mode);
			break;
		default:
			AVLsort(fptr, fout, mode);
			break;
		}
   
   
	
	return 0;
}





