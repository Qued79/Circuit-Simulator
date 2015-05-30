#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "circuithelp.h"
/*This is a helper method that was created just to clean up after the graycode method [since it would leave an array of malloc'd strings otherwise]*/
void freegray(char** stuff, int length){
	int i;
	for(i=0;i<length;i++){
		free(stuff[i]);
	}
	free(stuff);
}

/*This function generates a graycode sequence of the requested length.*/
char** graycode(int n){
	char ** res;
	if(n==1){
		res= malloc(2*sizeof(char*));
		res[0] = malloc(2);
		res[1] = malloc(2);
		strcpy(res[0],"0");
		strcpy(res[1],"1");
		return res;
	}
	int i;
	char** prev = graycode(n-1);
	int len = pow(2,n-1);
	int tlen = pow(2,n)-1;
	res = malloc((tlen+1)*sizeof(char*)); 
	

	for(i=0;i<len*2;i++){		/*Initialize the array with half 0s and half 1s... will be first bit in greycode*/
		res[i]=malloc(n+1);
		if(i<len){
			strcpy(res[i],"0");
		}
		else{strcpy(res[i],"1");}
	}

	for(i=0;i<len;i++){		/*same as walking the prev array forwards then backwards. First goes to first and last, second goes to second and (second to last) etc.*/
		strcat(res[i],prev[i]);
		strcat(res[tlen-i],prev[i]);
		free(prev[i]);/*Clean up after previous iteration of graycode. No longer need prev[i] so free it.*/
	}
	return res;
}

int getval(struct gate* x){
	int i,res,temp;
	switch(x->code){
		case 0: return 0;
		case 1: return 1;
		case 2:	
			res=0;
			for(i=0;i<x->numinputs;i++){
				temp = getval(x->inputs[i]);
				if(x->not[i]==1){
					if(temp==0){temp=1;}
					else{temp=0;}
						}
				res+=temp;
						   }
				if(res==0){return 0;}
				else {return 1;}
		case 3:
			res=1;
			for(i=0;i<x->numinputs;i++){
				temp = getval(x->inputs[i]);
				if(x->not[i]==1){
					if(temp==0){temp=1;}
					else{temp=0;}
						}
				res*=temp;
						   }
				if(res==0){return 0;}
				else {return 1;}
		case 4:{
			int j;
			char** gc;
			int len = pow(2,x->numinputs);
			int selects[x->numinputs];
			gc= graycode(x->numinputs);
			for(i=0;i<x->numinputs;i++){
				selects[i] = getval(x->inputs[i]);/*Thought it better to do the calls only once, so I separated it and then use it below repeatedly*/
						   }

			/*Goal is to find a graycode-input match since the select code determines which input becomes the output*/
			for(i=0;i<len;i++){/*For each graycode*/
				for(j=0;j<x->numinputs;j++){/*Walk across the first inputs [select signals] if not a match will break early, else walk through all select inputs */
					if((int)(gc[i][j]-'0')!= selects[j]){break;}
						       	   }
				if(j==x->numinputs){/*Will only be true if above walked through all of the select inputs (implies the select signal/graycode pair matched entirely])*/
					freegray(gc,len);
					res = getval(x->inputs[i+x->numinputs]); /*Return the input corresponding to the index of the matching graycode */
					return res;
						  }
		  			  }
			return 1;
			}
		case 5: 
			if(getval(x->inputs[0])==0){return 1;}
			else {return 0;}
		
		default:
			return 1;
		}/*end switch*/
}

/*This is a pseudo hash function. It takes each of the valid inputs and maps them to a unique location in the array of structs*/
int ctonum(char a){
	int res = (int)a;
	if(res==48){return 52;}/*0 and 1 each are their own type of gate that can not change, so we map them all to the same two structs that are premade for this purpose*/
	if(res==49){return 53;}
	if(res>=65&&res<=90){res-=65;}
	else if(res>=97&&res<=122){res-=71;}
	return res;
}






