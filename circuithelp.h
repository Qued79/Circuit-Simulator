struct gate{
	int code,numinputs;
	int not[52];
	struct gate* inputs[52];
};
void freegray(char** stuff, int length);/*Clean up a graycode created with graycode(int n)*/
char** graycode(int n);/*Create a graycode sequence of length n*/
int getval(struct gate* x);/*Get the current state of gate 'x'*/
int ctonum(char a);/*Map a character to a particular gate*/
