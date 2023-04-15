#include <stdio.h>
#include <stdint.h>
#include <string.h>

//functions
int start();
int init();
int gettingFileName();
int txtLoader();
int division();
int txtPadding(char *code);
int getNumLine();
int littleEndian();
int process_chunk();
int mainLoop();
int cypheration();

//variations
int fileBody;
int numLine;
int temp;
int varA;
int varB;
int varC;
int varD;
int initA;
int initB;
int initC;
int initD;
int fileExist;
int k[64];
int r[64];
char buffLine[64-1];
char fileName[256-1];
char getStr[256-2];
uint32_t f, g;
uint32_t chunkedText[16];
unsigned int endianOut[7];
unsigned char paddedText[64-1];
unsigned char digest[16];
FILE *srcFile;