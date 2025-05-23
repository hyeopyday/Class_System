#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* 부모 프로세스가 자식 프로세스를 생성하고 서로 다른 메시지를 프린트 */
int main()
{
    int pid;
    pid = fork();

    if (pid == 0) 
    { // 자식 프로세스
        printf("[Child] : Hello, world pid=%d\n", getpid());  // (변경됨)
    }
    else 
    { // 부모 프로세스
        printf("[Parent] : Hello, world pid=%d\n", getpid());
    }

    return 0;
}
