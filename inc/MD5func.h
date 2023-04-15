#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "allFuncVar.h"

int left_rotate(uint32_t value, uint32_t count) {
    return (value << count) | (value >> (32 - count));
};

int txtPadding(char plain[64-1]) {
    temp = 0;
    for (int i = 0; i < 64; i += 1) {
        if((plain[i] == CL || plain[i] == 0) && temp == 0) {
            temp = i;
            // printf("padding 0x80");
            paddedText[i] = 0x80; // 0x31(="1") for testing
        } else if((plain[i] != CL && plain[i] != 0) && temp == 0) {
            // printf("padding ditto");
            paddedText[i] = plain[i];
        } else if(temp != 0) {
            // printf("padding 0x00");
            paddedText[i] = 0x00; // 0x30(="0") for testing
        } else {
            printf("An error occured on translating the plain text.");
        }
    }
    littleEndian(temp, endianOut);
    for (int i = 0; i < 8; i += 1) {
        paddedText[(64-1) - i] = endianOut[i];
        // printf("[ endianOut: %d | padded like %d ] ", endianOut[i], paddedText[(64-1) - i]);
    }
    printf("Padding is finished.\n");
    printf("Padded text: ");
        for(int i = 0; i < 64; i++) {
        printf("%x ", paddedText[i]);
    } printf("\n");
    return 0;
}

int littleEndian(uint64_t n, uint8_t *out) {
    for (int i = 0; i < 8; i++) {
        out[i] = (n >> (i * 8)) & 0xFF;
    }
    return 0;
}

int process_chunk(uint8_t *chunk) {
    // Break the 512-bit chunk into sixteen 32-bit little-endian words
    for (int i = 0; i < sizeof(chunkedText); i += 1) chunkedText[i] = 0;
    for (int i = 0; i < 16; i++) chunkedText[i] = (uint32_t)chunk[i*4] | ((uint32_t)chunk[i*4+1] << 8) | ((uint32_t)chunk[i*4+2] << 16) | ((uint32_t)chunk[i*4+3] << 24);
    printf("Chunked according to 32-bit bits: ");
    for(int i = 0; i < 16; i++) {
        printf("%x ", chunkedText[i]);
    } printf("\n");
    return 0;
    // Process the 16 words...
}

int mainLoop() {
    init();
    // printf("varA: %x, varB: %x, varC: %x, varD: %x\n", varA, varB, varC, varD);
    for (int i = 0; i < 64; i++) {
        if (i >= 0 && i <= 15) {
            f = (varB & varC) | ((~varB) & varD);
            g = i;
        } else if (i >= 16 && i <= 31) {
            f = (varD & varB) | ((~varD) & varC);
            g = (5 * i + 1) % 16;
        } else if (i >= 32 && i <= 47) {
            f = varB ^ varC ^ varD;
            g = (3 * i + 5) % 16;
        } else {
            f = varC ^ (varB | (~varD));
            g = (7 * i) % 16;
        }
        temp = varD;
        varD = varC;
        varC = varB;
        varB = left_rotate((varA + f + k[i] + chunkedText[g]), r[i]) + varB;
        varA = temp;
    }
    // printf("varA: %x, varB: %x, varC: %x, varD: %x\n", varA, varB, varC, varD);
    return 0;
}

int cypheration() {
    for (int i = 0; i < 4; i++) {
        digest[i] = ((initA + varA) >> (i * 8)) & 0xff;
        digest[4*1 + i] = ((initB + varB) >> (i * 8)) & 0xff;
        digest[4*2 + i] = ((initC + varC) >> (i * 8)) & 0xff;
        digest[4*3 + i] = ((initD + varD) >> (i * 8)) & 0xff;
    }
    printf("sawlMD5 hash with SP: ");
    for (int i = 0; i < 16; i++) {
        if(digest[i] < 0x10) printf("0%x ", digest[i]);
        else printf("%x ", digest[i]);
    } printf("\n");
    printf("sawlMD5 hash without SP: ");
    for (int i = 0; i < 16; i++) {
        if(digest[i] < 0x10) printf("0%x", digest[i]);
        else printf("%x", digest[i]);
    } printf("\n");
    return 0;
}