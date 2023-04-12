#include "assemble.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqoai.h>
#include <stdbool.h>

#define TABLE_SIZE 1000

// methods:

int fillSymTab(struct symbolTable *symT,FILE *inputFile);
int hex2int( char* hex);
void int2hex16(char *lower,int a);
int findSymbolTableLength(FILE *file);
void duplicatedLabel(struct symbolTable *symbolTable, int symbolTabLength);
void duplicatedLabel2(struct symbolTable *symbolTable, int symbolTabLength);

int main(int argc, char **argv){
    // Written by Mohammad._.hr
    // https://t.me/Mohammadk_hr
    // 4003623039
    FILE *assp, *machp, *fopen();
    struct symbolTable *pSymTab;
    int symTabLen;
    int i, j, found, noInsts;
    struct instruction *currInst;
    size_t lineSize;
    char *line;
    char *token;
    char *instructions[] = {"add", "sub", "slt", "or", "nand",
                            "addi", "slti", "ori", "lui", "lw", "sw", "beq", "jalr",
                            "j", "halt"};
    int instCnt = 0;
    char hexTable[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char lower[5];
    i = 0;
    j = 0;
    line = (char *) malloc(72);
    currInst = (struct instruction *) malloc(sizeof(struct instruction));
    // malloc returns a pointer to the beginning of the allocated block of memory.
    if (argc < 3) {
        printf("***** Please run this program as follows:\n");
        printf("***** %s assprog.as machprog.m\n", argv[0]);
        printf("***** where assprog.as is your assembly program\n");
        printf("***** and machprog.m will be your machine code.\n");
        exit(1);
    }
    if ((assp = fopen(argv[1], "r")) == NULL) {
        printf("%s cannot be opened argv n1 \n", argv[1]);
        exit(1);
    }
    if ((machp = fopen(argv[2], "w+")) == NULL) {
        printf("%s cannot be opened argv n2 \n", argv[2]);
        exit(1);
    }

    /*************************************************
    * ********************************************* *
    * ********************************************* *
    here, you can place your code for the assembler
    * ********************************************* *
    * ********************************************* *
    *************************************************/


    symTabLen = findSymTabLen(assp);
//    printf("%d",symTabLen);
    pSymTab = (struct symbolTable *) malloc(symTabLen * sizeof(struct symbolTable));
    // malloc returns a pointer to the beginning of the allocated block of memory.
    for (int k = 0; k < symTabLen; k++) {
        pSymTab[k].symbol = (char *) malloc(7);
    }
    //check duplicated labels
    //duplicatedLabel2(symbolTable, symbolTabLength);
    noInsts = fillSymTab(pSymTab,assp);
//    printf("%d : " , noInsts);



//here





    fclose(assp);
    fclose(machp);

    printf("done!");
    return 0;
}
int findSymTabLen(FILE *inputFile) {
    int count = 0;
    int lineSize = 72;
    char *line;
    line = (char *) malloc(72);
    while (fgets(line, lineSize, inputFile) != NULL) {
        if ((line[0] == ' ') || (line[0] == '\t'));
        else
            count++;
    }
    rewind(inputFile);
    free(line);
    return count;
}
int fillSymTab(struct symbolTable *symT,FILE *inputFile) {
    int lineNo = 0;
    int lineSize = 72;
    char *line;
    int i = 0;
    char *token;
    line = (char *) malloc(72);
    while (fgets(line, lineSize, inputFile) != NULL) {
        if ((line[0] == ' ') || (line[0] == '\t'));
        else {
            token = strtok(line, "\t, ");
            for (int j = 0; j < i; ++j) {
                if (strcmp(token,symT[j].symbol)==0){
                    puts("ERROR! exit(1) : Duplicated Label");
                    printf("LINE ERROR : ");
                    printf("%d ",lineNo+1);
                    exit(1);
                }
            }
            strcpy(symT[i].symbol, token);
            symT[i].value = lineNo;
            i++;
        }
        lineNo++;
    }
    rewind(inputFile);
    free(line);
    return lineNo;
}
int hex2int( char* hex) {
    int result = 0;
    while ((*hex) != '\0') {
        if (('0' <= (*hex)) && ((*hex) <= '9'))
            result = result * 16 + (*hex) - '0';
        else if (('a' <= (*hex)) && ((*hex) <= 'f'))
            result = result * 16 + (*hex) - 'a' + 10;
        else if (('A' <= (*hex)) && ((*hex) <= 'F'))
            result = result * 16 + (*hex) - 'A' + 10;
        hex++;
    }
    return (result);
}
void int2hex16(char *lower,int a) {
    sprintf(lower, "%X", a);
    if (a < 0x10) {
        lower[4] = '\0';
        lower[3] = lower[0];
        lower[2] = '0';
        lower[1] = '0';
        lower[0] = '0';
    } else if (a < 0x100) {
        lower[4] = '\0';
        lower[3] = lower[1];
        lower[2] = lower[0];
        lower[1] = '0';
        lower[0] = '0';
    } else if (a < 0x1000) {
        lower[4] = '\0';
        lower[3] = lower[2];
        lower[2] = lower[1];
        lower[1] = lower[0];
        lower[0] = '0';
    }
}

//add by myself ->  );
int findSymbolTableLength(FILE *file) {
    int count = 0;
    char *line = (char *) malloc(72);
    while (fgets(line, 600, file) != NULL) {
        if (line[0] != ' ' && line[0] != '\t')
            count++;
    }
    free(line);
    rewind(file); // add by myself
    return count;
//    rewind(file);
}
void duplicatedLabel(struct symbolTable *symbolTable, int symbolTabLength) {
    //this method checks for duplicated labels in a symbol table
    Boolean duplicated = FALSE;
    for (int i = 0; i < symbolTabLength; ++i) {
        for (int j = i + 1; j < symbolTabLength; ++j) {
            if (strcmp(symbolTable[i].symbol, symbolTable[j].symbol) == 0) {
                duplicated = TRUE;
                break;
            }
        }
    }
    if (duplicated) {
        puts("ERROR! exit(1) : Duplicated Label\n");
        exit(1);
    }
}
int hashFunction(char *symbol) {
    int hash = 0 ;
    for (int i = 0; symbol[i] != '\0'; ++i) {
        hash = (hash * 31 + symbol[i]) % TABLE_SIZE;
    }
    return hash;
}
void duplicatedLabel2(struct symbolTable *symbolTable, int symbolTabLength) {
    // Create a hash table to store symbols

    bool table[TABLE_SIZE] = {false};
    bool duplicated = false;

    for (int i = 0; i < symbolTabLength; ++i) {
        int hash = hashFunction(symbolTable[i].symbol);

        // Check if the symbol is already in the hash table
        if (table[hash]) {
            duplicated = true;
            break;
        }

        // Add the symbol to the hash table
        table[hash] = true;
    }

    // Print an error message if duplicates were found
    if (duplicated) {
        puts("ERROR! exit(1) : Duplicated Label\n");
        exit(1);
    }
}

