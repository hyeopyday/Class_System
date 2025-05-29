# 12주차 시스템 프로그래밍 강의 내용 정리
---

## 프로세스 생성

fork()는 한 번 호출되면 두 번 리턴한다.
* 자식 프로세스에게는 0을 리턴하고
* 부모 프로세스에게는 자식 프로세스 ID를 리턴한다

![image](https://github.com/user-attachments/assets/038b8764-e647-4242-ab02-cafc1f7c9ff0)

---
```c
#include <stdio.h>
#include <unistd.h>
/* 자식 프로세스를 생성한다. */
int main()
{
int pid;
printf("[%d] 프로세스 시작 \n", getpid());
pid = fork();
printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
}
```
*출력 결과
```
6
$ fork1
[15065] 프로세스 시작
[15065] 프로세스 : 반환값 15066
[15066] 프로세스 : 반환값 0
```

---

## 부모 프로세스와 자식 프로세스 구분
* fork() 호출 후에 리턴값이 다르므로 이 리턴값을 이용하여
* 부모 프로세스와 자식 프로세스를 구별하고
* 서로 다른 일을 하도록 할 수 있다.

```c
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
        printf("[Child] : Hello, world pid=%d\n", getpid());  
    }
    else 
    { // 부모 프로세스
        printf("[Parent] : Hello, world pid=%d\n", getpid());
    }

    return 0;
}

```
```
$ fork2
[Parent] Hello, world! pid=15799
[Child] Hello, world! pid=15800
```

---

## 두 개의 자식 프로세스 생성: fork3.c

```c
#include <stdlib.h>
#include <stdio.h>
/* 부모 프로세스가 두 개의 자식 프로세스를 생성한다. */
int main()
{
int pid1, pid2;
pid1 = fork();
if (pid1 == 0) {
printf("[Child 1] : Hello, world ! pid=%d\n", getpid());
exit(0);
}
pid2 = fork();
if (pid2 == 0) {
printf("[Child 2] : Hello, world ! pid=%d\n", getpid());
exit(0);
}
printf("[PARENT] : Hello, world ! pid=%d\n",getpid());
}
```

```
$ fork3
[Parent] Hello, world! pid=15740
[Child 1] Hello, world! pid=15741
[Child 2] Hello, world! pid=15742
```

* 만약 exit이 없다면?
  - 자식 프로세스는 부모와 동일한 코드를 그대로 실행하게 되어, 원치 않는 추가적인 fork() 호출이 발생할 수 있습니다.

---

## 프로세스 기다리기: wait()

* 자식 프로세스 중의 하나가 끝날 때까지 기다린다
  - 끝난 자식 프로세스의 종료 코드가 status에 저장되며, 끝난 자식 프로세스의 번호를 리턴한다.
 

 ``` c
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main()
{
int pid, child, status;
printf("[%d] 부모 프로세스 시작 \n", getpid( ));
pid = fork();
if (pid == 0) {
printf("[%d] 자식 프로세스 시작 \n", getpid( ));
exit(1);
}
child = wait(&status); // 자식 프로세스가 끝나기를 기다린다.
printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);
printf("\t종료 코드 %d\n", status>>8);
}
```


## 특정 자식 프로세스 기다리기: waitpid.c

```c
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // waitpid 사용을 위해 필요함

/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main()
{
    int pid1, pid2, child, status;

    printf("[%d] 부모 프로세스 시작 \n", getpid());
    pid1 = fork();
    if (pid1 == 0) {
        printf("[%d] 자식 프로세스[1] 시작 \n", getpid());
        sleep(1);
        printf("[%d] 자식 프로세스[1] 종료 \n", getpid());
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("[%d] 자식 프로세스 #2 시작 \n", getpid());
        sleep(2);
        printf("[%d] 자식 프로세스 #2 종료 \n", getpid());
        exit(2);
    }

    // 자식 프로세스 #1의 종료를 기다린다.
    child = waitpid(pid1, &status, 0);
    printf("[%d] 자식 프로세스 #1 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);

    return 0;
}
```

```
$ waitpid
[16840] 부모 프로세스 시작
[16841] 자식 프로세스[1] 시작
[16842] 자식 프로세스[2] 시작
[16841] 자식 프로세스[1] 종료
[16840] 자식 프로세스[1] 16841 종료
종료코드 1
[16842] 자식 프로세스[2] 종료
```
