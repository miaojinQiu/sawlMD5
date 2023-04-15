#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "nonMD5func.h"
#include "MD5func.h"

int main() {
    fileExist = ERROR_CODE_NOFILE;
    while(1) {
        fileExist = start();
        if(fileExist != ERROR_CODE_NOFILE) txtLoader();
        else if(fileExist == ERROR_CODE_NOFILE) return 1;
        else return ERROR_CODE_UNKNOWN;
        fclose(srcFile);
        printf("Try again? (y/n): ");
        scanf("%s", getStr);
        fflush(stdin);
        if(strcmp(getStr, "N") == 0 || strcmp(getStr, "n") == 0) break;
        else continue;
    }
    printf("Bye bye.\n");
    return 0;
}