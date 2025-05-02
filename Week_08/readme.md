
# 8주차 시스템 프로그래밍 강의 내용 정리

---

## 컴퓨터 시스템 구조

* 유닉스 커널(kernel)
✅ 하드웨어를 운영 관리하여 다음과 같은 서비스를 제공
✅ 파일 관리(File management)
✅ 프로세스 관리(Process management)
✅ 메모리 관리(Memory management)
✅ 통신 관리(Communication management)
✅ 주변장치 관리(Device management)

![image](https://github.com/user-attachments/assets/cec29143-eee4-4dcd-a106-74f3e33ef320)

## 시스템 호출(system call)

 시스템 호출은 커널에 서비스 요청을 위한 프로그래밍 인터페이스
 응용 프로그램은 시스템 호출을 통해서 커널에 서비스를 요청한다

---

## 파일 열기: open()

 파일을 사용하기 위해서는 먼저 open() 시스템 호출을 이용하여
파일을 열어야 한다. 

---

## creat() 시스템 호출

 path가 나타내는 파일을 생성하고 쓰기 전용으로 연다.
 생성된 파일의 사용권한은 mode로 정한다.
 기존 파일이 있는 경우에는 그 내용을 삭제하고 연다.
 다음 시스템 호출과 동일
open(path, WRONLY | O_CREAT | O_TRUNC, mode);

---

## 데이터 읽기: read() // 리턴 타입은 int이다.

 fd가 나타내는 파일에서
 nbytes 만큼의 데이터를 읽고
 읽은 데이터는 buf에 저장한다.

```cpp
ssize_t read ( int fd, void *buf, size_t nbytes ); // void *는 어떠한 데이터 타입이든 받겠다는 의미의 포인터이다.

```

```cpp
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open (const char *path, int oflag, [ mode_t mode ]);
파일 열기에 성공하면 파일 디스크립터를, 실패하면 -1을 리턴

```

```cpp
/* 파일의 끝에 도달할 때까지 반복해서 읽으면서 파일 크기 계산 */
while( (nread = read(fd, buffer, BUFSIZE)) > 0)
total += nread;
close(fd);
printf ("%s 파일 크기 : %ld 바이트 \n", argv[1], total);
exit(0);
}
```

---

* 시스템 데이터 타입 size_t . mode_t
  - size_t
     -> 주로 메모리 크기나 배열의 인덱스 등을 나타낼 때 사용하는 부호 없는 정수형 타입.

  - mode_t
     -> 파일의 권한을 나타내는 데 사용되는 데이터 타입.

---

* fd = open(argv[1], O_RDWR); 에서 argv는 명령줄 인수(argument)**를 저장하는 배열입니다.
  - 프로그램을 실행할 때 사용자가 입력한 인수를 받아서 배열로 저장해두고, 이를 코드 내에서 활용할 수 있습니다.

---

* 확장자 없이 파일의 종류를 구분 하려면 매직 넘버로 구분 할 수 있다.

✅ ELF 파일 (리눅스 실행 파일): 7f 45 4c 46 (ASCII로 \x7f ELF)

✅ Windows 실행 파일 (MZ 포맷): 4D 5A (ASCII로 MZ)

✅ JPEG 이미지 파일: FF D8 FF (JPEG 시작 시그니처)

✅ PNG 이미지 파일: 89 50 4E 47 (ASCII로 \x89 PNG)

✅ ZIP 파일: 50 4B 03 04 (ASCII로 PK)

***-> 파일 헤더는 파일의 첫 부분에 위치하며, 파일 형식을 식별하는 매직 넘버와 메타데이터를 포함하고 있습니다***
---

## 참조
<https://chatgpt.com/>

