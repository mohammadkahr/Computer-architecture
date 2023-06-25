#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqoai.h>
#include <stdbool.h>
#include <windows.h>
#define NORTYPE 5
#define NOITYPE 8
#define NOJTYPE 2
//the number of R, I and J type instructions
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2
#define TABLE_SIZE 1000

/* this structure is defined to hold ever entity of symbol table    *
 * which, after finding the length, will become an array of symbols */
struct symbolTable{
    int value;//no. line
    char *symbol; // lable
};
/* every time an instruction is read, it will be tokenized and each   *
 * token will reside in one element of this structure               */
struct instruction{
    size_t instType; // 0 means r type, 1 means i type and 2 means j type
    size_t intInst; // Answer
    char *mnemonic; //names of instruction
    char inst[9]; //convert to hex
    int rs;
    int rt;
    int rd;
    int imm;
    int PC;
};
/* the follwing function, findSymTabLen, will scan the assembly    *
 * code and count the number of symbols and return it              */
int findSymTabLen(FILE *);
/* this function fills up the symbol table                         */
int fillSymTab(struct symbolTable *,FILE *);
/* and the following functions are other ancillary functions        */
void formInst(struct instruction *,FILE *);
int hex2int(char *);
void int2hex16(char *,int);
int findOpCode(char *token2, char *instructions[]);
void change(int op, struct instruction *currentInstruction, struct symbolTable *symbolTable,
            const char hexTable[16], char lower[5], char *token2, int symbolTabLength,
            int programCounter, int line);
