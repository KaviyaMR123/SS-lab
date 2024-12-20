#include <stdio.h>
#include <string.h>
#include <ctype.h>

void main() 
{
    FILE *f1, *f2, *f3, *f4, *f5;
    int i, len, j = 0;
    char ch;
    char l[10], address[10], label[10], opcode[10], op[10], operand[10], code[10], mne[10], sym[10], add[10], start[10];

    f1 = fopen("intermediate.txt", "r");
    f2 = fopen("length.txt", "r");
    f3 = fopen("symtab.txt", "r");
    f4 = fopen("optab.txt", "r");
    f5 = fopen("assembly.txt", "w");
    if (!f1 || !f2 || !f3 || !f4 || !f5) 
    {
        printf("Error opening one of the files.\n");
        return;
    }

    fscanf(f1, "%s%s%s", label, opcode, operand);
    fprintf(f5, "\t%s\t%s\t%s\n", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) 
    {
        strcpy(start, operand);
        fscanf(f2, "%s", l);
    }

    printf("H%s^%s%s\nT00%s09^", label, start, l, start);
    fscanf(f1, "%s%s%s%s", address, label, op, operand);

    while (strcmp(op, "END") != 0) 
    {
        if (j == 3) 
        {
            printf("\nT00%s09^", address);
            j = 0;
        }

        rewind(f4); 
        fscanf(f4, "%s%s", code, mne);
        while (strcmp(code, "END") != 0) 
        {
            if (strcmp(code, op) == 0) 
            {
                rewind(f3); 
                fscanf(f3, "%s%s", sym, add);
                while (strcmp(sym, "END") != 0) 
                {
                    if (strcmp(sym, operand) == 0) 
                    {
                        printf("%s%s^", mne, add);
                        fprintf(f5, "%s\t%s\t%s\t%s\t%s%s\n", address, label, op, operand, mne, add);
                        break;
                    }
                    else
                    {
                        fscanf(f3, "%s%s", sym, add);
                    }
                }
                break;
            }
            else 
            {
                fscanf(f4, "%s%s", code, mne);
            }
        }

        if (strcmp(op, "BYTE") == 0 || strcmp(op, "WORD") == 0) 
        {
            if (strcmp(op, "WORD") == 0)
            {
                printf("0000%s^", operand);
                fprintf(f5, "%s\t%s\t%s\t%s\t0000%s\n", address, label, op, operand, operand);
            }
            else
            {
                len = strlen(operand);
                for (i = 2; i < len; i++)
                {
                    printf("%c", operand[i]);
                }
                printf("^");
                fprintf(f5, "%s\t%s\t%s\t%s\t0000%s\n", address, label, op, operand, operand);
            }
        }

        if (strcmp(op, "RESW") == 0 || strcmp(op, "RESB") == 0) 
        {
            fprintf(f5, "%s\t%s\t%s\t%s\n", address, label, op, operand);
        }

        fscanf(f1, "%s%s%s%s", address, label, op, operand);
        j++;
    }

    printf("\nE00%s\n", start);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);

    printf("---ASSEMBLY LISTING---\n");
    f1 = fopen("intermediate.txt", "r");
    if (!f1) 
    {
        printf("Error reopening intermediate.txt for reading.\n");
        return;
    }

    ch = fgetc(f1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(f1);
    }
    fclose(f1);
    printf("\n");
}
