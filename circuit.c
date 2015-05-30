#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "circuithelp.h"

struct gate* vars[54];

int main(int argc, char*argv[]){
if(argc!=3){printf("Wrong number of inputs\n");return 1;}

FILE *fd = fopen(argv[1],"r+");
FILE *in = fopen(argv[2],"r+");

struct gate* x = malloc(sizeof(struct gate));
x->code=0;
vars[52]=x;

x = malloc(sizeof(struct gate));
x->code=1;
vars[53]=x;

char gate[20];
char i[520];
int j,k,num,max;
char inputs[100];
char outputs[52];
int numinputs=0;
int numoutputs=0;

for(j=0;j<52;j++){
	vars[j]=malloc(sizeof(struct gate));
	vars[j]->code=42;
}


/*Handle first 2 scans*/
fscanf(fd,"%s",gate);
if(strcmp(gate,"INPUTVAR")!=0){
	printf("Malformed input file!\n");
	return 1;
			       }

fscanf(fd,"%d",&numinputs);
for(j=0;j<numinputs;j++){
	fscanf(fd," %c",&inputs[j]);
}


fscanf(fd,"%s",gate);
if(strcmp(gate,"OUTPUTVAR")!=0){
	printf("Malformed input file!\n");
	return 1;
			       }

fscanf(fd,"%d",&numoutputs);
for(j=0;j<numoutputs;j++){
	fscanf(fd," %c",&outputs[j]);
}



while(fscanf(fd,"%s",gate)==1){
	if(strcmp(gate,"AND")==0){
		fscanf(fd, " %c %c %c", &i[0],&i[1],&i[2]);
		x = vars[ctonum(i[2])];
		x->numinputs = 2;
		x->code = 3;
		x->inputs[0] = vars[ctonum(i[0])];
		x->inputs[1] = vars[ctonum(i[1])];
				 }	
	if(strcmp(gate,"OR")==0){
		fscanf(fd, " %c %c %c", &i[0],&i[1],&i[2]);
		x = vars[ctonum(i[2])];
		x->numinputs = 2;
		x->code = 2;
		x->inputs[0] = vars[ctonum(i[0])];
		x->inputs[1] = vars[ctonum(i[1])];	
		}
	if(strcmp(gate,"DECODER")==0){
		fscanf(fd,"%d",&num);
		max = num + pow(2,num);			
		char** gc = graycode(num);		
		
		for(j=0;j<max;j++){/*scan in inputs and outputs [in then out]*/
			fscanf(fd," %c",&i[j]);
				  }
			
		for(j=0;j<max-num;j++){ /*For each output make an and gate of the appropriate size pointing to the input signals*/
		
			x = vars[ctonum(i[j+num])];
			x->code = 3;
			x->numinputs = num;
	
			for(k=0;k<num;k++){/*Set the inputs [same for all] and the nots appropriately according to the graycode*/
				x->inputs[k] = vars[ctonum(i[k])];
				x->not[k] = gc[j][k]; 
					  }

				      }/*End of outer loop*/
			freegray(gc,(max-num));
		}	

	if(strcmp(gate,"MULTIPLEXER")==0){
		fscanf(fd,"%d",&num);
		max = (int)log2(num);
		
		for(j=0;j<(num+max+1);j++){
			fscanf(fd," %c",&i[j]);
		}
		
		x = vars[ctonum(i[num+max])];
		x->code =4;
		x->numinputs = max;
		for(j=0;j<max;j++){
			x->inputs[j]=vars[ctonum(i[j+num])];/*Put the select signals at the front of the MUX input list*/
		}
		
		for(j=0;j<num;j++){
			x->inputs[j+max]=vars[ctonum(i[j])];/*Put the input signals at the end of the list, maintaining their order*/
		}
	}
	if(strcmp(gate,"NOT")==0){
		fscanf(fd," %c %c",&i[0],&i[1]);
		x=vars[ctonum(i[1])];
		x->code = 5;
		x->inputs[0] = vars[ctonum(i[0])];
	}
}



while(fscanf(in,"%d",&j)==1){
		if(j==0){vars[ctonum(inputs[0])]->code=0;}
		else{vars[ctonum(inputs[0])]->code=1;}
	for(k=1;k<numinputs;k++){
		fscanf(in,"%d",&j);
		if(j==0){vars[ctonum(inputs[k])]->code=0;}
		else{vars[ctonum(inputs[k])]->code=1;}
	}
	
	for(j=0;j<numoutputs;j++){
		getval(vars[ctonum(outputs[j])]);
		printf("%d\t",getval(vars[ctonum(outputs[j])]));
	}
	printf("\n");
	
			  }
}

