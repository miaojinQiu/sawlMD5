#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "allFuncVar.h"


const int constK[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const int constR[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

int gettingFileName(){
    printf("Enter the file name: ");
    scanf("%s", fileName);
    fflush(stdin);
    return 0;
}

int start(){
    for(int i = 0; i <= kernelLength; i+= 1) printf("\n");
    printf("«sawlMD5» is now Working...\n");
    printf("The length of the each string must be under 512 bytes.\n");
    gettingFileName();
    srcFile = fopen(fileName, "r");
    if(srcFile == NULL) {
        printf("An error has occuured during calling the plain text «%s».\n", fileName);
        return ERROR_CODE_NOFILE;
    } else {
        printf("The plain text «%s» has been successfully loaded.\n", fileName);
    }
    fileBody = 0;
    numLine = 0;
    printf("Parameters have been initiated.\n");
    return 0;

}

int init() {
    temp = 0;
    initA = 0x67452301;
    initB = 0xEFCDAB89;
    initC = 0x98BADCFE;
    initD = 0x10325476;
    varA = initA;
    varB = initB;
    varC = initC;
    varD = initD;
    *k = *constK;
    *r = *constR;
    f = 0, g = 0;
    for(int i = 0; i < 8; i++) endianOut[i] = 0;
    return 0;
}

int txtLoader() {
    printf("txtLoader has been successfully loaded.\n");
    division();
    while(fgets(buffLine, sizeof buffLine, srcFile) != NULL) {
        init ();
        if(buffLine[strlen(buffLine)-1]  == CL ) printf("Plain text(strlen: %lu, sizeof: %lu): %s", strlen(buffLine), sizeof(buffLine), buffLine);
        else printf("Plain text(strlen: %lu, sizeof: %lu): %s\n", strlen(buffLine), sizeof(buffLine), buffLine);
        txtPadding(buffLine);
        // printf("Padded Text\nin line %d(sizeof: %d, \nwith plain length %d, \nwith plain little endian: %x %x %x %x %x %x %x)\nas following : «%s»\n", numLine, sizeof(paddedText) + 1, strlen(buffLine), endianOut[0], endianOut[1], endianOut[2], endianOut[3], endianOut[4], endianOut[5], endianOut[6], endianOut[7], paddedText);
        // printf("Little endian: %x %x %x %x %x %x %x\n", endianOut[0], endianOut[1], endianOut[2], endianOut[3], endianOut[4], endianOut[5], endianOut[6], endianOut[7])
        process_chunk(paddedText);
        mainLoop();
        cypheration();
        division();
        sleep(5);
        numLine++;
    }
    printf("Hashing is finished.\n");
    division();
    return 0;
}

int division() {
    for(int i = 0; i < kernelLength; i += 1) {
        printf("-");
    } printf("\n");
    return 0;
}