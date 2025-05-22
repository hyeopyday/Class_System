#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024  /
int main(int argc, char *argv[]) {
    char buffer[BUF_SIZE + 1];  
    int nread;

    if (argc < 2) {  
        fprintf(stderr, "사용법: %s <심볼릭링크 경로>\n", argv[0]);
        exit(1);
    }

    nread = readlink(argv[1], buffer, BUF_SIZE);
    if (nread > 0) {
        buffer[nread] = '\0'; 
        printf("%s\n", buffer);  
        exit(0);
    } else {
        perror("readlink");  
        exit(1);
    }
}
