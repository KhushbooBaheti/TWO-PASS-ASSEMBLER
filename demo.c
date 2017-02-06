/*COA Project Part B(i)
Conversion of assembly code to Binary code
GROUP Members
1 Neha Kumari 		14ucc021
2 Pooja			14ucc024
3 Vanshita Tilwani	14ucc041 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int strcopy(char *s,char *tar,char *c);
char binaryNumber[8];
char binaryNumb[7];
FILE *f_ou;
int file_open=0;
int main()
{
	FILE *fp,*fp2,*f_out,*f,*f_in;
	int nol=0,flag=0,i,k,j,l,r,quotient;
	char filename[20],*c,*extra,ch_in;
	char ch1,ch2,oneword[100],oneword2[100],label[100],oneword_in[100];
	char convert[8];
	printf("enter the file name\n");
	scanf("%s",filename);
	fp= fopen(filename,"r");  //opening the file for assembly code
	fp2=fopen("raw.txt","w"); //intermediate file in which each word is written in new line 
	ch1= fscanf(fp,"%s",oneword);
	while(ch1!=EOF)			//reading words from input file and printing in intermediate file
	{
		fprintf(fp2,"%s\n",oneword);
		ch1= fscanf(fp,"%s",oneword);
	}
	fclose(fp);
	fclose(fp2);
	f=fopen("raw.txt","r");		//opening the intermediate file and will read opcode one by one
	f_out=fopen("final_output.txt","w");	//file in which the each opcode will be converted to equivalent binary code
	ch1=fscanf(f,"%s",oneword);
	//registers.txt- file in which opcode along with its binary code is written
	//read word from the raw.txt file and compare the opcode from registers.txt file
	while(ch1!=EOF)		
	{
		fp2=fopen("registers.txt","r");		
		i= atoi(oneword);	    //atoi converts string to integer. it will be used in case of immediate constant. since imediate constant does not exit in registers.txt file so we have to convert it in binary and place it in output file.		
		ch2=fscanf(fp2,"%s",oneword2);		
		if(strcmp(oneword,":")==0);
		else if(strcmp(oneword,"0")==0) //if immediate const is 0 directly place 00000000 in output file
		{
			fprintf(f_out,"%s","00000000");
			fclose(fp2);
		}
		else if(i>0 && i<256) //if immediate const lies between 0-256 . then convert it in binary
		{
			j=7;
			quotient = i;
			for(l=0;l<8;l++)
				binaryNumber[l]=0;
			while(quotient!=0)	//piece of code for converting immediate constant into binary.
			{
				binaryNumber[j]= quotient % 2;
				quotient = quotient / 2;
				j--;
			}
			k=0;
			while(k!=8) //placing the binary equivalent of immediate constant in file
			{
				fprintf(f_out,"%d",binaryNumber[k]);
				k++;
			}	
			fclose(fp2);
		}
		else		//if word is not immediate constant then it must be an opcode
		{
			while(ch2!=EOF) //comparing opcodes from input and registers.txt file
			{
				if(strcmp(oneword,oneword2)==0) //as soon as we found opcode in registers file. move pointer by one and place its equivalent binary
				{
					ch2=fscanf(fp2,"%s",oneword2);
					if(strlen(oneword2)>=20 || strcmp(oneword,"l0:")==0 || strcmp(oneword,"l1:")==0 || strcmp(oneword,"l2:")==0 || strcmp(oneword,"l3:")==0 || strcmp(oneword,"l4:")==0 || strcmp(oneword,"l5:")==0 || strcmp(oneword,"l6:")==0 || strcmp(oneword,"l7:")==0)
					{
						fprintf(f_out,"\n%s",oneword2); //if opcode is found or label is found then put \n in front since it will be a new instruction
					}
					else
					{
						fprintf(f_out,"%s",oneword2); //else if r0 ,etc us found no need to put \n
					}
					fclose(fp2);
				}
				else
				{
					ch2=fscanf(fp2,"%s",oneword2); //if the matching opcode is not found. increment the pointer by 2
					ch2=fscanf(fp2,"%s",oneword2);
				}
			}
		}
		ch1=fscanf(f,"%s",oneword);
	}
		nol=1;
		fclose(f_out);
		fclose(f);
		f_in= fopen("final_output.txt","r"); //opening the output file.
		f_ou=fopen("output.txt","w"); //reading the label opcode from output file and converting it into ILC
		 ch_in= fscanf(f_in,"%s",oneword_in);
		while(ch_in!=EOF)
		{
			//r=strcopy(oneword_in,extra,c);
			if(strlen(oneword_in)==32 )
			{
				fprintf(f_ou,"\n%s",oneword_in);
			}
			if(strlen(oneword_in)!=32)
			{
				j=6;
				quotient = nol;
				for(l=0;l<7;l++)
					binaryNumb[l]=0;
				while(quotient!=0)
				{
					binaryNumb[j]= quotient % 2;
					quotient = quotient / 2;
					j--;
				}
				k=0;
				fprintf(f_ou,"%s","\n");
				while(k!=7)
				{
					fprintf(f_ou,"%d",binaryNumb[k]);
					k++;
				}
				if(file_open==0)
				{
					fp=fopen("symbol_table","w"); //Symbol table in which opcode and ILC value for label is stored.
					file_open=1;			//format for symbol table is
				}					//initial opcode	ILC	line number where label is declared
				else
					fp=fopen("symbol_table","a");
				fprintf(fp,"%s",oneword_in);
				fprintf(fp,"%s","\t\t\t");
				k=0;
				while(k!=7)
				{
					fprintf(fp,"%d",binaryNumb[k]);
					k++;
				}
				fprintf(fp,"%s","\t\t\t");
				fprintf(fp,"%d",nol);
				fprintf(fp,"%s","\n");
				fclose(fp);
			}
			nol++;
			ch_in= fscanf(f_in,"%s",oneword_in);
		}
		//printf("hey\n");
		fclose(f_in);
		fclose(f_ou);
		f_in= fopen("output.txt","r"); //opening the output file.
		f_ou=fopen("final_output.txt","w"); //reading the label opcode from output file and converting it into ILC
		ch_in= fscanf(f_in,"%s",oneword_in);
		while(ch_in!=EOF)
		{
			//printf("hey 1\n");
			if(strlen(oneword_in)==32)
			{
				r=strcopy(oneword_in,extra,c);
				if(r==0)
				fprintf(f_ou,"\n%s",oneword_in);
			}
			else
				fprintf(f_ou,"\n%s",oneword_in);
			
			ch_in= fscanf(f_in,"%s",oneword_in);

		}

		fclose(f_in);
		fclose(f_ou);

		printf("\nThe given assembly code file has been converted into Binary file. Please open final_output.txt to view the final binary file.\n");
}

int strcopy(char *s,char *tar,char *c)
{
	int i,flag=0;
	FILE *fs;
	char ch,oneword[100];
	c=(char*)malloc(7*sizeof(char));
	tar=(char*)malloc(25*sizeof(char));
	for(i=0;i<25;i++)
	{
		(*(tar+i))=(*(s+i));
	}
	for(i=0;i<7;i++)
	{
		(*(c+i))=(*(s+i+25));
	}
	if(strcmp(tar,"0000000000000000000101100")==0)
	{
		fprintf(f_ou,"\n%s","0000000000000000000101100");
		fs=fopen("symbol_table","r");
		ch=fscanf(fs,"%s",oneword);
		while(ch!=EOF)
		{
			if(strcmp(c,oneword)==0)
			{
				ch=fscanf(fs,"%s",oneword);
				goto lt;
			}
			else
			{
				
				ch=fscanf(fs,"%s",oneword);
				ch=fscanf(fs,"%s",oneword);
				ch=fscanf(fs,"%s",oneword);
			}
		}	
        lt:	fprintf(f_ou,"%s",oneword);
		return 1;

	}
	else
	return 0;
}
