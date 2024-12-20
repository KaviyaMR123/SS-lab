#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display1() 
{
    char str;
    FILE *fp1, *fp2, *fp3;

    printf("\n----------------Pass One-----------------\n\n");

    printf("\nThe contents of Input Table :\n\n");
    fp1 = fopen("input.txt", "r");
    if (!fp1) {
        perror("Error opening input.txt");
        return;
    }
    while ((str = fgetc(fp1)) != EOF) 
   {
        printf("%c", str);
    }
    fclose(fp1);

    printf("\n\nThe contents of Intermediate Table :\n\n");
    fp2 = fopen("intermediate.txt", "r");
    if (!fp2) 
    {
        perror("Error opening inter.txt");
        return;
    }
    while ((str = fgetc(fp2)) != EOF) 
    {
        printf("%c", str);
    }
    fclose(fp2);

    printf("\n\nThe contents of Symbol Table :\n\n");
    fp3 = fopen("symtab.txt", "r");
    if (!fp3) 
    {
        perror("Error opening symtab.txt");
        return;
    }
    while ((str = fgetc(fp3)) != EOF) 
    {
        printf("%c", str);
    }
    fclose(fp3);
}

void display2() 
{
    char ch;
    FILE *fp1, *fp4;

    printf("\n-----------------------------PassTwo-------------------------------\n\n");
    printf("Intermediate file is converted into object code\n");

    printf("\n\nThe contents of Assembly Listing file :\n\n");
    fp1 = fopen("assembly.txt", "r");
    if (!fp1) 
    {
        perror("Error opening list.txt");
        return;
    }
    while ((ch = fgetc(fp1)) != EOF) 
    {
        printf("%c", ch);
    }
    fclose(fp1);

    printf("\n\nThe contents of Object code file :\n\n");
    fp4 = fopen("object.txt", "r");
    if (!fp4) 
    {
        perror("Error opening object.txt");
        return;
    }
    while ((ch = fgetc(fp4)) != EOF) 
    {
        printf("%c", ch);
    }
    printf("\n");
    fclose(fp4);
}

void main() 
{
    char opcode[10], operand[10], label[10], a[10], ad[10], symbol[10], ch;
    char code[10][10], code1[10][10] = { "33", "44", "53", "57" };
    char mnemonic[10][10] = { "START", "LDA", "STA", "LDCH", "STCH", "END" };
    char mnemonic1[10][10] = { "LDA", "STA", "LDCH", "STCH" };
    int locctr, start, length, i = 0, j = 0, k, l = 0;
    int st, diff, address, add, len, actual_len, finaddr, prevaddr;

    FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7;

    fp1 = fopen("input.txt", "r");
    if (!fp1) 
    {
        perror("Error opening input.txt");
        return;
    }
    fp2 = fopen("symtab.txt", "w");
    fp3 = fopen("inter.txt", "w");

    fscanf(fp1, "%s%s%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) 
    {
        start = (int)strtol(operand, NULL, 16);
        locctr = start;
        fprintf(fp3, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s%s%s", label, opcode, operand);
    }
    else 
    {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) 
    {
        fprintf(fp3, "%x", locctr);
        if (strcmp(label, "**") != 0) 
        {
            fprintf(fp2, "%s\t%x\n", label, locctr);
        }
        strcpy(code[i], mnemonic[j]);
        while (strcmp(mnemonic[j], "END") != 0) 
        {
            if (strcmp(opcode, mnemonic[j]) == 0) 
            {
                 locctr += 0x3;
                break;
            }
            strcpy(code[i], mnemonic[j]);
            j++;
        }
        if (strcmp(opcode, "WORD") == 0) 
        {
            locctr += 0x3;
        }
        else if (strcmp(opcode, "RESW") == 0) 
        {
            locctr += (0x3 * (atoi(operand)));
        } 
        else if (strcmp(opcode, "RESB") == 0) 
        {
            locctr += (0x1) * (atoi(operand));
        } 
        else if (strcmp(opcode, "BYTE") == 0) 
        {
            locctr = locctr + 0x1;
        }
        fprintf(fp3, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s%s%s", label, opcode, operand);
    }
    fprintf(fp3, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    length = locctr - start;

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    printf("\n\nThe contents of Input file:\n\n");
    fp1 = fopen("input.txt", "r");
    while ((ch = fgetc(fp1)) != EOF) 
    {
        printf("%c", ch);
    }
    fclose(fp1);

    printf("\n\nLength of the input program is %d.", length);
    printf("\n\nThe contents of Symbol Table:\n\n");
    fp2 = fopen("symtab.txt", "r");
    while ((ch = fgetc(fp2)) != EOF) 
    {
        printf("%c", ch);
    }
    fclose(fp2);

    display1();
    display2();

    getchar();  
}
