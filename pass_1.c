#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char label[10],opcode[10],operand[10],code[10],mnemonic[3];
int length;

void pass1()
{
 int locctr=0x0,str;
 int start;
 FILE *f1,*f2,*f3,*f4,*f5;
 f1 = fopen("input.txt","r");
 f2 = fopen("optab.txt","r");
 f3 = fopen("intermediate.txt","w");
 f4 = fopen("symtab.txt","w");
 f5 = fopen("length.txt","w");
 fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
 if(strcmp(opcode,"START")==0)
 {
  start = strtol(operand,NULL,16);
  locctr=(0x1)*start;
  printf("%x\n",locctr);
  fprintf(f3,"\t%s\t%s\t%s\n",label,opcode,operand);
  fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
 }
 else
 {
  locctr=0x0;
 }
 while(strcmp(opcode,"END")!=0)
{
 fprintf(f3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
 if(strcmp(label,"**")!=0)
 {
  fprintf(f4,"%s\t%x\n",label,locctr);
 }
 fscanf(f2,"%s\t%s",code,mnemonic);
 while(strcmp(code,"END")!=0)
 {
 if(strcmp(opcode,code)==0)
 {
  locctr+=0x3;
  break;
 }
 fscanf(f2,"%s\t%s",code,mnemonic);
 }
 if(strcmp(opcode,"WORD")==0)
 {
   locctr+=0x3;
 }
 else if(strcmp(opcode,"RESW")==0)
 {
   locctr+=((0x3)*atoi(operand));
 }
 else if(strcmp(opcode,"RESB")==0)
 {
  locctr+=(0x1)*atoi(operand);
 }
 else if(strcmp(opcode,"BYTE")==0)
 {
  locctr+=strlen(operand)*(0x1);
 }
 fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
 }
fprintf(f3,"%x\t%s\t%s\t%s",locctr,label,opcode,operand);
length = locctr-start;
fprintf(f5,"%x",length);
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
fclose(f5);
}
void display()
{
char ch;
FILE *f1;
printf("---INPUT CODE---\n");
f1 = fopen("input.txt","r");
ch = fgetc(f1);
while(ch!=EOF)
{
 printf("%c",ch);
 ch = fgetc(f1);
}
fclose(f1);
printf("\n\n");
printf("---INTERMEDIATE FILE---\n");
f1 = fopen("intermediate.txt","r");
ch = fgetc(f1);
while(ch!=EOF)
{
  printf("%c",ch);
  ch = fgetc(f1);
}
fclose(f1);
printf("\n\n");
printf("---SYMTAB---\n");
f1 = fopen("symtab.txt","r");
ch = fgetc(f1);
while(ch!=EOF)
{
printf("%c",ch);
ch = fgetc(f1);
}
fclose(f1);
}
int main()
{
pass1();
display();
printf("\n");
return 0;
}
