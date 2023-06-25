#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#define Rtype 0
#define Itype 1
#define Jtype 2

struct instruction {
    int rs;
    int rt;
    int rd;
    int imm;
    char mnemonic[12];
    char hexValueInstruction[9];
    size_t intValueInstruction ;
    size_t instructionType; // R-type * I-type * J-type
};
struct registers{
    char name[12];
    long value;
    int usedNumber;
};

void intToHex16(char *lower, int a);
void printInfo(int pc,struct registers *regs[16],int no);


int main() {
    // Written by Mohammad._.hr
    // https://t.me/Mohammadk_hr or harandi.mohamma@gmail.com

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // colors :)
    int pc=0;
    int numberOfInstructions=0;
    int amountOfMemoryUsed=0;
    long memory[100];
    for (int i = 0; i < 100; ++i) {
        memory[i]=0;
    }
    char *instructions[] = {"add", "sub", "slt", "or", "nand", "addi", "slti", "ori",
                            "lui", "lw", "sw", "beq", "jalr","j", "halt"};


    FILE *input;
    input = fopen(".\\tests\\testcase0.mc", "r");
    if (input == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }


    struct instruction *currentInstruction = (struct instruction *) malloc(sizeof(struct instruction));
    struct registers *R0 = (struct registers *) malloc(sizeof(struct registers));strcpy(R0->name,"R0");R0->value=0;R0->usedNumber=0;
    struct registers *R1 = (struct registers *) malloc(sizeof(struct registers));strcpy(R1->name,"R1");R1->value=0;R1->usedNumber=0;
    struct registers *R2 = (struct registers *) malloc(sizeof(struct registers));strcpy(R2->name,"R2");R2->value=0;R2->usedNumber=0;
    struct registers *R3 = (struct registers *) malloc(sizeof(struct registers));strcpy(R3->name,"R3");R3->value=0;R3->usedNumber=0;
    struct registers *R4 = (struct registers *) malloc(sizeof(struct registers));strcpy(R4->name,"R4");R4->value=0;R4->usedNumber=0;
    struct registers *R5 = (struct registers *) malloc(sizeof(struct registers));strcpy(R5->name,"R5");R5->value=0;R5->usedNumber=0;
    struct registers *R6 = (struct registers *) malloc(sizeof(struct registers));strcpy(R6->name,"R6");R6->value=0;R6->usedNumber=0;
    struct registers *R7 = (struct registers *) malloc(sizeof(struct registers));strcpy(R7->name,"R7");R7->value=0;R7->usedNumber=0;
    struct registers *R8 = (struct registers *) malloc(sizeof(struct registers));strcpy(R8->name,"R8");R8->value=0;R8->usedNumber=0;
    struct registers *R9 = (struct registers *) malloc(sizeof(struct registers));strcpy(R9->name,"R9");R9->value=0;R9->usedNumber=0;
    struct registers *R10 = (struct registers *) malloc(sizeof(struct registers));strcpy(R10->name,"R10");R10->value=0;R10->usedNumber=0;
    struct registers *R11 = (struct registers *) malloc(sizeof(struct registers));strcpy(R11->name,"R11");R11->value=0;R11->usedNumber=0;
    struct registers *R12 = (struct registers *) malloc(sizeof(struct registers));strcpy(R12->name,"R12");R12->value=0;R12->usedNumber=0;
    struct registers *R13 = (struct registers *) malloc(sizeof(struct registers));strcpy(R13->name,"R13");R13->value=0;R13->usedNumber=0;
    struct registers *R14 = (struct registers *) malloc(sizeof(struct registers));strcpy(R14->name,"R14");R14->value=0;R14->usedNumber=0;
    struct registers *R15 = (struct registers *) malloc(sizeof(struct registers));strcpy(R15->name,"R15");R15->value=0;R15->usedNumber=0;
    struct registers *regs[16]={R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15};


    printInfo(pc,regs,1);


    size_t lineSize = 500;
    int count1 = 0;
    char fileInstructions[500][500];
    char *word = malloc(sizeof(char) * lineSize);

    while(fgets(word, lineSize, input) != NULL){
        strcpy(fileInstructions[count1], word );
        count1++;
    }
    free(word);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("The number of lines in this file is: %d\n" , count1);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);


    bool isHalt = false;
    for (int i = 0; i < count1; ++i) {
        long number = strtol(fileInstructions[i], NULL, 10);
        int opcode = (number&0b00001111000000000000000000000000) >> 24;
        if(isHalt){
            memory[i]=number;
            amountOfMemoryUsed++;
        }
        if(opcode==14){//halt
            isHalt=true;
        }
    }


    int i = 0;
    while (pc < count1){
        char lower[9];
        long number = strtol(fileInstructions[pc], NULL, 10);
        int opcode = (number&0b00001111000000000000000000000000) >> 24;
        currentInstruction -> intValueInstruction = number;
        strcpy(currentInstruction->mnemonic,instructions[opcode]);
        intToHex16(lower,number);
        strcpy(currentInstruction->hexValueInstruction,lower);
        if (opcode >= 0 && opcode <= 4){//R type
            currentInstruction -> instructionType = Rtype;
            currentInstruction -> rs = (number&0b00000000111100000000000000000000) >> 20;
            currentInstruction -> rt = (number&0b00000000000011110000000000000000) >> 16;
            currentInstruction -> rd = (number&0b00000000000000001111000000000000) >> 12;
            if(opcode==0){//add
                regs[currentInstruction->rd]->value = regs[currentInstruction->rs]->value + regs[currentInstruction->rt]->value;
                regs[currentInstruction->rd]->usedNumber = 1;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                pc+=1;
            } else if(opcode==1){//sub
                regs[currentInstruction->rd]->value = regs[currentInstruction->rs]->value - regs[currentInstruction->rt]->value;
                regs[currentInstruction->rd]->usedNumber = 1;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                pc+=1;
            }else if(opcode==2){//slt
                if(regs[currentInstruction->rs]->value < regs[currentInstruction->rt]->value) {
                    regs[currentInstruction->rd]->value = 1;
                }
                else
                    regs[currentInstruction->rd]->value=0;
                regs[currentInstruction->rd]->usedNumber = 1;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                pc++;
                break;
            }else if(opcode==3){//or
                regs[currentInstruction->rd]->value = regs[currentInstruction->rs]->value | regs[currentInstruction->rt]->value;
                regs[currentInstruction->rd]->usedNumber=1;
                regs[currentInstruction->rs]->usedNumber=1;
                regs[currentInstruction->rt]->usedNumber=1;
                pc+=1;
            }else if(opcode==4){//nand
                int and = regs[currentInstruction->rs]->value & regs[currentInstruction->rt]->value;
                regs[currentInstruction->rd]->value =~and;
                regs[currentInstruction->rd]->usedNumber = 1;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                pc+=1;
            }
        }
        else if (opcode >= 5 && opcode <= 12){//I type
            currentInstruction->instructionType = Itype;
            currentInstruction->rs = (number&0b00000000111100000000000000000000)>>20;
            currentInstruction->rt = (number&0b00000000000011110000000000000000)>>16;
            currentInstruction->imm = (number&0b00000000000000001111111111111111);
            int num = (currentInstruction->imm & 0b00000000000000001000000000000000)>>15;
            int signExtension;
            if(num == 1){//sign extension
                signExtension=(currentInstruction->imm | 0b11111111111111110000000000000000);
            }
            else if(num == 0){
                signExtension = currentInstruction->imm;
            }
            if(opcode == 5){//addi
                currentInstruction->imm = signExtension;
                regs[currentInstruction->rt]->value = regs[currentInstruction->rs]->value + currentInstruction->imm;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                pc+=1;
            }else if(opcode == 6){//slti
                currentInstruction->imm = signExtension;
                if(regs[currentInstruction->rs]->value < currentInstruction->imm)
                    regs[currentInstruction->rt]->value = 1;
                else
                    regs[currentInstruction->rt]->value = 0;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                pc+=1;
            }else if(opcode == 7){//ori
                currentInstruction->imm = currentInstruction->imm & 0b00000000000000001111111111111111;//zero extension
                regs[currentInstruction->rt]->value = regs[currentInstruction->rs]->value | currentInstruction->imm;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                pc+=1;
            }else if(opcode == 8){//lui
                regs[currentInstruction->rt]->value = (currentInstruction->imm<<16);
                regs[currentInstruction->rt]->usedNumber = 1;
                pc+=1;
            } else if(opcode==9){//lw
                currentInstruction->imm = signExtension;
                regs[currentInstruction->rt]->value = memory[currentInstruction->imm + regs[currentInstruction->rs]->value];
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                amountOfMemoryUsed++;
                pc+=1;
            } else if(opcode==10){//sw
                currentInstruction->imm = signExtension;
                memory[currentInstruction->imm + regs[currentInstruction->rs]->value] = regs[currentInstruction->rt]->value;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
                amountOfMemoryUsed++;
                pc+=1;
            } else if(opcode==11){//beq
                currentInstruction->imm = signExtension;
                if(regs[currentInstruction->rs]->value == regs[currentInstruction->rt]->value){
                    pc+=currentInstruction->imm+1;
                }
                else
                    pc+=1;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
            } else if(opcode==12){//jalr
                regs[currentInstruction->rt]->value = pc + 1;
                pc = regs[currentInstruction->rs]->value;
                regs[currentInstruction->rs]->usedNumber = 1;
                regs[currentInstruction->rt]->usedNumber = 1;
            }
        }
        else if (opcode == 13 || opcode == 14){//J type
            currentInstruction->instructionType = Jtype;
            currentInstruction->imm = (number&0b00000000000000001111111111111111);//zero extension
            if(opcode==13){//j
                pc = currentInstruction->imm;
            }
            if(opcode==14){//halt
                pc+=1;
                break;
            }
        }





        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("%d:\n",i);
        printInfo(pc,regs,2);
        i++;
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);

    }
    double percentOfUsedRegisters;
    int sumOfUsedRegisters = 0;
    for(int k = 0 ; k < 16 ; k++){
        if(regs[k]->usedNumber == 1){
            sumOfUsedRegisters++;
        }
    }
    numberOfInstructions = i;
    percentOfUsedRegisters = ((double)sumOfUsedRegisters/16) * 100;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\nPercent Of Used Registers = %f % \n",percentOfUsedRegisters);
    printf("Number Of Instructions = %d\n",numberOfInstructions);
    printf("Amount Of Memory Used = %d\n",amountOfMemoryUsed);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
    return 0;
}


void printInfo(int pc,struct registers *regs[16],int no){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (no == 1) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("********************************************************************************************************** \n"
               "PC = %-5d \nR0 = %-5ld | R1 = %-5ld | R2 = %-5ld  | R3 = %-5ld  | R4 = %-5ld  | R5 = %-5ld  | R6 = %-5ld  "
               "| R7 = %-5ld\nR8 = %-5ld | R9 = %-5ld | R10 = %-5ld | R11 = %-5ld | R12 = %-5ld | R13 = %-5ld "
               "| R14 = %-5ld | R15 = %-5ld \n"
               "********************************************************************************************************** \n",
               pc, regs[0]->value, regs[1]->value, regs[2]->value, regs[3]->value, regs[4]->value, regs[5]->value,
               regs[6]->value, regs[7]->value, regs[8]->value, regs[9]->value, regs[10]->value, regs[11]->value,
               regs[12]->value, regs[13]->value, regs[14]->value, regs[15]->value);
    }
    if (no == 2) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("PC = %-5d \nR0 = %-5ld | R1 = %-5ld | R2 = %-5ld  | R3 = %-5ld  | R4 = %-5ld  | R5 = %-5ld  | R6 = %-5ld  "
               "| R7 = %-5ld\nR8 = %-5ld | R9 = %-5ld | R10 = %-5ld | R11 = %-5ld | R12 = %-5ld | R13 = %-5ld "
               "| R14 = %-5ld | R15 = %-5ld \n"
               "********************************************************************************************************** \n",
               pc, regs[0]->value, regs[1]->value, regs[2]->value, regs[3]->value, regs[4]->value, regs[5]->value,
               regs[6]->value, regs[7]->value, regs[8]->value, regs[9]->value, regs[10]->value, regs[11]->value,
               regs[12]->value, regs[13]->value, regs[14]->value, regs[15]->value);
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
}
void intToHex16(char *lower, int a) {
    int result = snprintf(lower, 5, "%04X", a);
    if (result < 0) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Error occurred during conversion int to Hex.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
    }
}