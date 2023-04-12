#include "assemble.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqoai.h>
#include <stdbool.h>
//defines:
#define TABLE_SIZE 1000
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2
// methods:
int findOpCode(char *token2, char *instructions[]);
void change(int op, struct instruction *currentInstruction, struct symbolTable *symbolTable,
            const char hexTable[16], char lower[5], char *token2, int symbolTabLength,
            int programCounter, int line);

int main(int argc, char **argv){
    // Written by Mohammad._.hr
    // https://t.me/Mohammadk_hr or harandi.mohamma@gmail.com

    //vars:
    FILE *assp, *machp, *fopen();
    struct symbolTable *pSymTab;
    int symTabLen;
    int noInsts, programCounter = 0, instCnt = 0;
    struct instruction *currInst;
    size_t lineSize;
    char *line;
    char *token;
    char *instructions[] = {"add", "sub", "slt", "or", "nand",
                            "addi", "slti", "ori", "lui", "lw", "sw"
                            , "beq", "jalr","j", "halt"};
    char hexTable[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char lower[5];
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
    here, you can place your code for the assembler
    *************************************************/

    symTabLen = findSymTabLen(assp);
    pSymTab = (struct symbolTable *) malloc(symTabLen * sizeof(struct symbolTable));
    for (int k = 0; k < symTabLen; k++) {
        pSymTab[k].symbol = (char *) malloc(7);
        // 6 + 1 / one for 0 in the last of chars
    }
    noInsts = fillSymTab(pSymTab,assp);
    // why we need noInsts?
    char *line2 = (char *) malloc(72);
    int lineCounterInWhile = 0 ;
    while (fgets(line2, 1000, assp) != NULL) {
        programCounter++;
        //lines without label
        if (line2[0] == ' ' || line2[0] == '\t') {
            token = strtok(line2, "\t,\n ");
            //    strtok() : is a C library function that is used to tokenize (split) a string
            //    into smaller tokens or substrings based on a delimiter.
            //    It is defined in the string.h header file.
            //    The function takes two arguments:
            //    str -> The string to be tokenized.
            //    delim -> A string that contains one or more delimiter characters.
            int op = findOpCode(token, instructions);
            if (op != -1) {
                // do the change and write in the file
                change(op, currInst, pSymTab,
                       hexTable, lower, token, symTabLen,
                       programCounter, lineCounterInWhile);
                //printf("%d\n", pSymTab->value);
                fprintf(machp, "%zu\n", currInst->intInst);
                //We should use “%zu” to print the variables of size_t length.
            }
            else {
                printf("Invalid Opcode, LINE ERROR : ");
                printf("%d ", lineCounterInWhile + 1);
                exit(1);
            }
        }
        // line with label
        else {
            Boolean isInst = FALSE;
            token = strtok(line2, "\t ");
            // its just help to code be ok :)
            token = strtok(NULL, "\t\n ");
            for (int op = 0; op < 15; op++) {
                if (strcmp(instructions[op], token) == 0) {
                    isInst = TRUE;
                    // do the change and write in the file

//                    change(op, currentInstruction, symbolTable, hex_table, lower, token, symbolTabLength,
//                           programCounter);
//                    printf("%d\n", currentInstruction->intValueInstruction);
//                    fprintf(machp, "%d\n", currentInstruction->intValueInstruction);
                    change(op, currInst, pSymTab,
                           hexTable, lower, token, symTabLen,
                           programCounter , lineCounterInWhile);
                    //printf("%d\n", pSymTab->value);
                    fprintf(machp, "%d\n", currInst->intInst);
                }
            }
            if (isInst == FALSE) {
                if (strcmp(token, ".fill") == 0) {
                    token = strtok(NULL, "\t\n ");
                    int found2 = 0;
                    int count = 0;
                    for (int i = 0; i < symTabLen; i++) {
                        if (strcmp(pSymTab[i].symbol, token) == 0) {
                            found2 = 1;
                            count = i;
                        }
                    }
                    if (found2) {
                        currInst->imm = pSymTab[count].value;
                    } else if (isalpha(token[0])) {
                        printf("Undefined Label, LINE ERROR : ");
                        printf("%d ", lineCounterInWhile + 1);
                        exit(1);
                    } else {
                        currInst->imm = atoi(token);
                    }
                    currInst->intInst = currInst->imm;
                    //printf("%d\n", currInst->intInst);
                    fprintf(machp, "%d\n", currInst->intInst);

                } else {
                    printf("Invalid Opcode, LINE ERROR : ");
                    printf("%d ", lineCounterInWhile + 1);
                    exit(1);
                }
            }
        }
        lineCounterInWhile++;
    }
    fclose(assp);
    fclose(machp);
    printf("The received file lines : ");
    printf("%d ",lineCounterInWhile);
    printf("\ndone!");
    return 0;
}

//methods:
/*//int findSymTabLen(FILE *inputFile) {
//    int count = 0;
//    int lineSize = 72;
//    char *line;
//    line = (char *) malloc(72);
//    while (fgets(line, lineSize, inputFile) != NULL) {
//        if ((line[0] == ' ') || (line[0] == '\t'));
//        else
//            count++;
//    }
//    rewind(inputFile);
//    free(line);
//    return count;
//}*/
int findSymTabLen(FILE *inputFile) {
    int count = 0;
    char line[BUFSIZ];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        if (line[0] != ' ' && line[0] != '\t') {
            count++;
        }
    }
    rewind(inputFile);
    return count;
    // This code was written by chatgpt

}
int fillSymTab(struct symbolTable *symT,FILE *inputFile) {
    // this method can find the duplicated error too
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
                    printf("Duplicated Label, LINE ERROR : ");
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
void int2hex16(char* str, int num) {
    snprintf(str, 5, "%04X", (signed int)num);
    // This code was written by chatgpt
}
/*/void int2hex16(char *lower,int a) {
//    sprintf(lower, "%X", a);
//    if (a < 0x10) {
//        lower[4] = '\0';
//        lower[3] = lower[0];
//        lower[2] = '0';
//        lower[1] = '0';
//        lower[0] = '0';
//    } else if (a < 0x100) {
//        lower[4] = '\0';
//        lower[3] = lower[1];
//        lower[2] = lower[0];
//        lower[1] = '0';
//        lower[0] = '0';
//    } else if (a < 0x1000) {
//        lower[4] = '\0';
//        lower[3] = lower[2];
//        lower[2] = lower[1];
//        lower[1] = lower[0];
//        lower[0] = '0';
//    }
//}*/
int findOpCode(char *token2, char *instructions[]) {
    int opcode = -1;
//    strcmp() is a C library function that is used to compare two strings lexicographically.
//    It is defined in the string.h header file.
//    The function takes two arguments:
//
//    s1 -> The first string to be compared.
//    s2 -> The second string to be compared.
//
//    The function returns an integer value that indicates the change of the comparison:
//
//    If s1 is less than s2, the function returns a negative integer.
//    If s1 is greater than s2, the function returns a positive integer.
//    If s1 is equal to s2, the function returns zero.

    for (int op = 0; op < 15; op++) {
        if (strcmp(instructions[op], token2) == 0) {
            opcode = op;
            break;
        }
    }
    return opcode;
}
int findSymbol(int symbolTabLength, struct symbolTable *symbolTable, char *token2) {
    int count = -1;
    for (int i = 0; i < symbolTabLength; i++) {
        if (strcmp(symbolTable[i].symbol, token2) == 0) {
            count = i;
        }
    }
    return count;
}
void change(int op, struct instruction *currentInstruction, struct symbolTable *symbolTable,
            const char hexTable[16], char lower[5], char *token2,
            int symbolTabLength, int programCounter, int line) {
    if (op >= 0 && op <= 4) {//R format instruction
        currentInstruction->instType = RTYPE;
        currentInstruction->mnemonic = (char*) malloc(5);
        strcpy(currentInstruction->mnemonic, token2);
        token2 = strtok(NULL, ",\t\n ");
        currentInstruction->rd = atoi(token2);
        token2 = strtok(NULL, ",\t\n ");
        currentInstruction->rs = atoi(token2);
        token2 = strtok(NULL, ",\t\n ");
        currentInstruction->rt = atoi(token2);
        currentInstruction->PC = currentInstruction->PC + 1;
        currentInstruction->inst[0] = '0';
        currentInstruction->inst[1] = hexTable[op];
        currentInstruction->inst[2] = hexTable[currentInstruction->rs];
        currentInstruction->inst[3] = hexTable[currentInstruction->rt];
        currentInstruction->inst[4] = hexTable[currentInstruction->rd];
        currentInstruction->inst[5] = '0';
        currentInstruction->inst[6] = '0';
        currentInstruction->inst[7] = '0';
        currentInstruction->inst[8] = '\0';
        int res = hex2int(currentInstruction->inst);
        currentInstruction->intInst = res;
    }
    else if (op >= 5 && op <= 12) {//I format instruction
        currentInstruction->instType = ITYPE;
        currentInstruction->mnemonic = (char*) malloc(5);
        strcpy(currentInstruction->mnemonic, token2);
        if (strcmp(currentInstruction->mnemonic, "jalr") == 0) {
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->rt = atoi(token2);
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->rs = atoi(token2);
            currentInstruction->imm = 0;
        }
        else if (strcmp(currentInstruction->mnemonic, "lui") == 0) {
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->rt = atoi(token2);
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->imm = atoi(token2);
            currentInstruction->rs = 0;
        }
        else if (strcmp(currentInstruction->mnemonic, "beq") == 0) {
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->rs = atoi(token2);
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->rt = atoi(token2);
            token2 = strtok(NULL, ",\t\n ");
            int count = findSymbol(symbolTabLength, symbolTable, token2);
            if (count != -1) {
                currentInstruction->imm = symbolTable[count].value - (programCounter);
            }
            else if (isalpha((token2[0]))) {
                puts("Undefined Label, LINE ERROR : ");
                printf("%d ", line + 1);

                exit(1);
            }
            else {
                long num = atol(token2);
                if (num < 65536 && num > -65536) {
                    num = num - (programCounter);
                    if (num < 0) {
                        num += 65536;
                    }
                    currentInstruction->imm = num;
                }
                else {
                    printf("invalid Offset, LINE ERROR : ");
                    printf("%d ", line + 1);
                    exit(1);//invalid offset
                }
            }
        }
        else {
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->rt = atoi(token2);
            token2 = strtok(NULL, ",\t\n ");
            currentInstruction->rs = atoi(token2);
            token2 = strtok(NULL, ",\t\n ");
            int count = findSymbol(symbolTabLength, symbolTable, token2);
            if (count != -1) {
                currentInstruction->imm = symbolTable[count].value;
            }
            else if (isalpha((token2[0]))) {
                puts("Undefined Label, LINE ERROR :");
                printf("%d ", line + 1);
                exit(1);
            }
            else {
                long num = atol(token2);
                if (num < 65536 && num > -65536) {
                    if (num < 0 && op != 7) {//op ori is 7
                        num += 65536;
                    }
                    currentInstruction->imm = num;
                }
                else {
                    puts("ERROR! exit(1) : invalid Offset\n");
                    exit(1);//invalid offset
                }
            }
        }
        currentInstruction->PC = currentInstruction->PC + 1;
        currentInstruction->inst[0] = '0';
        currentInstruction->inst[1] = hexTable[op];
        currentInstruction->inst[2] = hexTable[currentInstruction->rs];
        currentInstruction->inst[3] = hexTable[currentInstruction->rt];
        int2hex16(lower, currentInstruction->imm);
        currentInstruction->inst[4] = lower[0];
        currentInstruction->inst[5] = lower[1];
        currentInstruction->inst[6] = lower[2];
        currentInstruction->inst[7] = lower[3];
        currentInstruction->inst[8] = '\0';
        int res = hex2int(currentInstruction->inst);
        currentInstruction->intInst = res;
    }
    else if (op == 13 || op == 14) {
        //J format
        currentInstruction->instType = JTYPE;
        currentInstruction->mnemonic = (char*) malloc(5);
        strcpy(currentInstruction->mnemonic, token2);
        if (strcmp(currentInstruction->mnemonic, "halt") == 0) {
            currentInstruction->imm = 0;
        }
        else {
            //j
            token2 = strtok(NULL, ",\t\n ");
            int count = findSymbol(symbolTabLength, symbolTable, token2);
            if (count != -1) {
                currentInstruction->imm = symbolTable[count].value;
            }
            else if (isalpha((token2[0]))) {
                printf("Undefined Label, LINE ERROR : ");
                printf("%d ", line + 1);
                exit(1);
            }
            else {
                long num = atol(token2);
                if (num < 65536 && num > -65536) {
                    currentInstruction->imm = num;
                }
                else {
                    puts("invalid Offset, LINE ERROR : ");
                    printf("%d ", line + 1);
                    exit(1);//invalid offset
                }
            }
        }
        currentInstruction->PC = currentInstruction->PC + 1;
        currentInstruction->inst[0] = '0';
        currentInstruction->inst[1] = hexTable[op];
        currentInstruction->inst[2] = '0';
        currentInstruction->inst[3] = '0';
        int2hex16(lower, currentInstruction->imm);
        currentInstruction->inst[4] = lower[0];
        currentInstruction->inst[5] = lower[1];
        currentInstruction->inst[6] = lower[2];
        currentInstruction->inst[7] = lower[3];
        currentInstruction->inst[8] = '\0';
        int res = hex2int(currentInstruction->inst);
        currentInstruction->intInst = res;
    }

}
// useless
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
int hashFunction(const char *symbol) {
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


