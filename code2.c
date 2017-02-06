// COA PROJECT PART B(ii)
/* Group Members:
	Neha Kumari 	14ucc021
	Pooja	     	14ucc024
	Vanshita	14ucc041
CONTROL SIGNALS FOR ALU ARE :-
   00 -> Addition
   01 -> Decrement
   10 -> Multiplication
   11 -> Division */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int bintodec(char c[]);
void mov1(int,int);
void mov2(int ind1,int ind2);
void add(int ind1,int ind2);
void mul(int ind1,int ind2);
void divi(int ind1,int ind2);
int cmp(int ind1,int ind2);
void dec(int ind);
void pop(int);
void push1(int);
void push2(int);
void print_reg();
float arr[10];
int pc=-1;
char flag[4], ir[50];
int stk[100];
int top=-1;
void set();
int main()
{
	FILE *f_in;
	char ch,oneword[100];
	char extracted[33];
	char op1[10],op2[10];
	int l,i,cmp_res,cn;
	int d1,d2;
	//to read value from registers.txt and store it in a array
	int j=0;
	set();
	f_in= fopen("final_output.txt","r");
	ch=fscanf(f_in,"%s",oneword);
	pc++;
	j=0;
	int k,count=20;
	while(ch!=EOF)
	{
	
		j=0;
		count=20;
		while(j<5)
		{
			for(i=0;i<count;i++) 
				extracted[i]=oneword[i];
				extracted[i]='\0';
				if(strlen(oneword)<20)     
					j=5;
				else
				{
				if(strcmp(extracted,"00000000000000000000")==0)
				{
						
						j=5;
						
						for(i=count+1;i<count+8;i++)
						{
								op1[i-count-1]=oneword[i];  
						}
						op1[i-count]='\0';
						for(k=i;k<32;k++)
						{
								op2[k-i]=oneword[k];
						}
						op2[k-i]='\0';
						d1=bintodec(op1);
						d2=bintodec(op2);
						mov1(d1,d2);
						printf("The special purpose registers are\n");
						printf("Instruction register\tmov1 r%d,r%d\n",d1,d2);
						
				}		 //move1 opcode is extracted whcih perform mov reg reg oeration...opcode and operands are send to respective function to perform oertion...
				else if(strcmp(extracted,"000000000000000000010000")==0)
				{
						
						j=5;
						for(i=count;i<count+5;i++)
						{
								op1[i-count]=oneword[i];
								op2[i-count+1]=oneword[i+5];
						}
						op1[i-count]='\0';
						op2[i-count+1]='\0';
						d1=bintodec(op1);   
						d2=bintodec(op2);
						mov2(d1,d2);
						printf("The special purpose registers are\n");
						printf("Instruction register\tmov2 %d,r%d\n",d1,d2);
						
				}		//move2 opcode is extracted and compared which perform mov reg immediate operation....opcode and operands are send to respective function to perform oertion
				else if(strcmp(extracted,"000000000000000000010001")==0)
				{
						
						j=5;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=oneword[i];
								op2[i-count+1]=oneword[i+5];
						}
						op1[i-count]='\0';
						op2[i-count+1]='\0';   
						d1=bintodec(op1);
						d2=bintodec(op2);
						mul(d1,d2);
						printf("\nthe control signal is 10\n");
						printf("The special purpose registers are\n");
						printf("Instruction register\tmul r%d,r%d\n",d1,d2);
				}		//multiply opcode is extracted and compared which perform mul reg reg operation...opcode and oprands are send to resective function to perfom operation......
				else if(strcmp(extracted,"000000000000000000010010")==0)
				{
						j=5;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=oneword[i];
								op2[i-count+1]=oneword[i+5];
						}
						op1[i-count]='\0';
						op2[i-count+1]='\0'; 
						d1=bintodec(op1);
						d2=bintodec(op2);
						add(d1,d2);
						printf("Control Signal 00\n");
						printf("The special purpose registers are\n");
						printf("Instruction register\tadd r%d,r%d\n",d1,d2);
					
				}	 //addition opcode is extracted and compared which perform mul reg reg operation...opcode and oprands are send to resective function to perfom operation...... 
				else if(strcmp(extracted,"000000000000000000010011")==0)
				{	
						j=5;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=oneword[i];
								op2[i-count+1]=oneword[i+5];
						}
						op1[i-count]='\0';
						op2[i-count+1]='\0';
						d1=bintodec(op1); 
						d2=bintodec(op2);
						divi(d1,d2);
						printf("Control Signal 11\n");
						printf("The special purpose registers are\n");
						printf("Instruction register\tdiv r%d,r%d\n",d1,d2);
				}	//division opcode is extracted and compared which perform div reg reg operation...opcode and oprands are send to resective function to perfom operation...... 
				else if(strcmp(extracted,"000000000000000000010100")==0)
				{	
						j=5;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=oneword[i];
								op2[i-count+1]=oneword[i+5];
						}
						op1[i-count]='\0';
						op2[i-count+1]='\0';
						d1=bintodec(op1); 
						d2=bintodec(op2);
						cmp_res=cmp(d1,d2);
						printf("The special purpose registers are\n");
						printf("Instruction register\tcmp r%d,r%d\n",d1,d2);
				}	//comparison opcode is extracted and compared which perform cmp reg reg operation...opcode and oprands are send to resective function to perfom operation...... 
				else if(strcmp(extracted,"000000000000000000010101")==0)
				{
						printf("push1\n");	
						j=5;
						for(i=count+1;i<count+8;i++)
						{
								op1[i-count-1]=oneword[i];
						}
						op1[i-count-1]='\0';
						d1=bintodec(op1);
						push1(d1);
						printf("The special purpose registers are\n");
						printf("Instruction register\tpsh1 %d\n",d1);
				}	//push1(); //push opcode is extracted and compared which perform push reg  operation...opcode and oprands are send to resective function to perfom operation...... 
				else if(strcmp(extracted,"0000000000000000000101100")==0)
				{	
						j=5;
						for(i=count+1;i<count+8;i++)
						{
								op1[i-count-1]=oneword[i];
						}
						op1[i-count]='\0';
						//printf("jnz %s\n",op1);
						d1=bintodec(op1);
						printf("The special purpose registers are\n");
						printf("Instruction register\t jnz label\n");
						if(cmp_res==-1)
						{
							rewind(f_in);
							ch=fseek(f_in,(d1-1)*32+7,SEEK_SET);
							pc= d1-1;
							ch=fscanf(f_in,"%s",oneword);
						}
						
				}	//opcode is extracted and compared which perform jump not equal operation.....
				else if(strcmp(extracted,"0000000000000000000101101000")==0)
				{
						j=5;
						for(i=count;i<count+5;i++)
						{
								op1[i-count]=oneword[i];
								
						}
						op1[i-count-1]='\0';
						d1=bintodec(op1);
						dec(d1);
						printf("ontrol Signal 01\n");
						printf("The special purpose registers are\n");
						printf("Instruction register\tdec r%d\n",d1);
				}
				else if(strcmp(extracted,"0000000000000000000101101001")==0)
				{
						j=5;
						for(i=count;i<count+5;i++)
						{
								op1[i-count]=oneword[i];
						}
						op1[i-count]='\0';
						d1=bintodec(op1);
						push2(d1);
						printf("The special purpose registers are\n");
						printf("Instruction register\tpsh2 r%d\n",d1);
				}   //push2(); //push opcode is extracted and compared which perform push immeediate  operation...opcode and oprands are send to resective function to perfom operation...... 
				else if(strcmp(extracted,"0000000000000000000101101010")==0)
				{
						j=5;
						for(i=count;i<count+5;i++)
						{
								op1[i-count]=oneword[i];
						}
						op1[i-count]='\0';
						d1=bintodec(op1);
						pop(d1);
						printf("The special purpose registers are\n");
						printf("Instruction register\tpop r%d\n",d1);
				}
				else if(strcmp(extracted,"00000000000000000001011010110000")==0)
				{
						j=5;
						printf("The special purpose registers are\n");
						printf("Instruction register\thlt\n");
						print_reg();
						return 0;	
				}
				}
				
			if(count==24)
				count++;
			else if(count==25)
				count=28;
			else
				count=count+4;
			j++;	
		}	
		print_reg();
		ch=fscanf(f_in,"%s",oneword);
		pc++;
	}
	fclose(f_in);
}
int bintodec(char c[])
{
	
	int sum=0,i,j;
	int *arr;
	int l=strlen(c);
	arr=(int*)malloc(l*sizeof(int));
	for(i=0;i<l;i++)
		(*(arr+i))=c[i]-'0';
	for(i=l-1,j=0;i>=0;i--,j++)         //conversion of binary to decimal take place
	{
		sum=sum+(*(arr+i))*pow(2,j);
	}
	return sum;
}
void set()
{
	int x1;
	for(x1=0;x1<10;x1++)       //array is set to zero
		arr[x1]=0;
}
void mov1(int imm,int ind)
{
	int x1;
	arr[ind]=imm;     //move reg ,immediate operation is performed
}
void mov2(int ind1,int ind2)
{
	arr[ind2]=arr[ind1];   //mov  reg,reg operation is performed
}
void add(int ind1,int ind2)
{
	arr[ind2]=arr[ind1]+arr[ind2];
	if(arr[ind2]==0)
		flag[2]=1;
	else
		flag[2]=0;
	if(arr[ind2]<0)          //add reg,reg operation is performed
		flag[1]=1;
	else
		flag[1]=0;
}
void mul(int ind1,int ind2)
{
	arr[ind2]=arr[ind1]*arr[ind2];
	if(arr[ind2]==0)
		flag[2]=1;
	else
		flag[2]=0;
	if(arr[ind2]<0)                // multiply reg reg opertaion is performed
		flag[1]=1;
	else
		flag[1]=0;
}
void divi(int ind1,int ind2)
{
	arr[ind2]=arr[ind2]/arr[ind1];
	if(arr[ind2]==0)
		flag[2]=1;
	else
		flag[2]=0;
	if(arr[ind2]<0)                               //division reg,reg operation is performed...
		flag[1]=1;
	else
		flag[1]=0;
}
int cmp(int ind1,int ind2)
{
	if(arr[ind2]!=arr[ind1])
		return -1;                         //comparision operation is performed.....
	else
		return 1;
}
void dec(int ind)
{
	arr[ind]=arr[ind]-1;
	if(arr[ind]==0)
		flag[2]=1;
	else
		flag[2]=0;                          //decrement operation
	if(arr[ind]<0)
	{
		arr[ind]=0;
		flag[1]=1;
	}
	else
		flag[1]=0;
	
}
void print_reg()
{
	int x1;
	printf("Overflow flag\t\t%d\n",flag[0]); //flag register - ONZU where O- overflow bit , N- negative bit, Z- zero bit, U- underflow bit.
	printf("Negative flag\t\t%d\n",flag[1]);
	printf("Zero flag\t\t%d\n",flag[2]);
	if(top==-1)
		flag[3]=1;
	else
		flag[3]=0;
	printf("Underflow flag\t\t%d\n",flag[3]);
	printf("Program Counter\t\t%d\n",pc);
	printf("Stack Pointer\t\t%d\n",top);
	printf("The contents of general purpose register are\n");
	for(x1=0;x1<10;x1++)
		printf("r%d\t%f\n",x1,arr[x1]);
}
void pop(int ind)
{
	int i;
	if(top!=-1)
	{
		arr[ind]=stk[top];
		top--;
		flag[3]=0;
	}
	else
		flag[3]=1;
	
}
void push1(int r)
{
	int i;
	top++;
	stk[top]=r;
	printf("elements in stack\n");       //element is pushed into stack.....
	if(top<100)
	{
		for(i=top;i>=0;i--)
			printf("%d\n",stk[i]);
		flag[0]=0;
	}
	else
		flag[0]=1;
}
void push2(int ind)
{
	int i;
	top++;
	stk[top]=arr[ind];
	printf("elements in stack\n");
	if(top<100)
	{
		for(i=top;i>=0;i--)
			printf("%d\n",stk[i]);       //immediate is pushed ......
		flag[0]=0;
	}
	else
		flag[0]=1;
}
	
		
		
