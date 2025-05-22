
# 11주차 시스템 프로그래밍 강의내용 정리
---

## 6장: 파일 시스템 구조 및 파일 입출력 구현

### 6.1 파일 시스템 구조

#### 유닉스 파일 시스템 구성 요소

* **Boot block**: 부팅 시 사용되는 코드 저장 (파일 시스템의 첫 번째 섹터)
* **Super block**: 파일 시스템 정보 저장

  * 총 블록 수, 사용 가능한 i-node 수
  * 블록 비트맵, 블록 크기 등
* **i-list**: 모든 i-node 리스트
* **Data block**: 실제 파일 데이터 저장 영역

> 💡 **ext4 파일 시스템**
>
> * 최대 1EB(엑사바이트) 볼륨
> * 최대 16TB 파일 지원

### 6.2 i-node (i-노드) 구조

* 한 파일당 하나의 i-node
* 파일 메타데이터 저장

  * 타입, 크기, 권한, 소유자, 접근/수정 시간, 데이터 블록 포인터 등

#### 블록 포인터 구조

* 직접 포인터: 12개
* 간접 포인터: 1개
* 이중 간접 포인터: 1개
* 삼중 간접 포인터: 1개

### 6.3 파일 입출력 구현

#### 주요 커널 자료구조

* **Fd Array**: 프로세스별 파일 디스크립터 배열
* **Open File Table**: 열린 파일 목록, 위치/플래그/i-node 포인터 포함
* **Active i-node Table**: 메모리에 있는 i-node 정보

```c
int fd = open("file", O_RDONLY);      // 파일 열기
int new_fd = dup(fd);                  // fd 복제
int new_fd2 = dup2(fd, 4);             // fd를 4번 디스크립터에 복제
```

### 6.4 파일 상태 정보

#### 상태 확인 함수

```c
#include <sys/types.h>
#include <sys/stat.h>

int stat(const char *filename, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *filename, struct stat *buf);
```

#### `struct stat`

```c
struct stat {
  mode_t st_mode;
  ino_t st_ino;
  dev_t st_dev;
  nlink_t st_nlink;
  uid_t st_uid;
  gid_t st_gid;
  off_t st_size;
  time_t st_atime, st_mtime, st_ctime;
  long st_blksize, st_blocks;
};
```

### 6.5 파일 타입

| 타입       | 설명             | 매크로         |
| -------- | -------------- | ----------- |
| 일반 파일    | 텍스트, 바이너리      | S\_ISREG()  |
| 디렉터리     | 파일 이름 및 포인터 포함 | S\_ISDIR()  |
| 문자 장치 파일 | 문자 단위 전송 장치    | S\_ISCHR()  |
| 블록 장치 파일 | 블록 단위 전송 장치    | S\_ISBLK()  |
| FIFO     | 이름 있는 파이프      | S\_ISFIFO() |
| 소켓       | 네트워크 통신        | S\_ISSOCK() |
| 심볼릭 링크   | 다른 파일을 가리킴     | S\_ISLNK()  |

### 6.6 접근 권한 및 시간 변경

```c
#include <sys/stat.h>
int chmod(const char *path, mode_t mode);
int fchmod(int fd, mode_t mode);

#include <utime.h>
int utime(const char *filename, const struct utimbuf *times);
```

```c
struct utimbuf {
  time_t actime;
  time_t modtime;
};
```

### 6.7 파일 소유자 변경

```c
#include <unistd.h>
int chown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group);
```

### 6.8 디렉터리 관련 함수

```c
#include <dirent.h>

struct dirent {
  ino_t d_ino;
  char d_name[NAME_MAX + 1];
};

DIR *opendir(const char *path);
struct dirent *readdir(DIR *dp);
int closedir(DIR *dp);
```

```c
while ((d = readdir(dp)) != NULL) {
  printf("%s %lu\n", d->d_name, d->d_ino);
}
```

---

## 7장: 파일 및 레코드 잠금

### 7.1 파일 잠금 개요

#### 문제점

* 여러 프로세스가 동시에 파일을 읽거나 쓰면 데이터 무결성 문제 발생

#### 잠금의 필요성

* 하나의 프로세스만 특정 파일/영역을 접근하도록 제한

#### flock() 함수

```c
#include <sys/file.h>
int flock(int fd, int operation);
```

| 옵션       | 설명     |
| -------- | ------ |
| LOCK\_SH | 공유 잠금  |
| LOCK\_EX | 배타 잠금  |
| LOCK\_UN | 잠금 해제  |
| LOCK\_NB | 비차단 방식 |

### 7.2 레코드 잠금 (fcntl)

```c
#include <fcntl.h>
int fcntl(int fd, int cmd, struct flock *lock);

struct flock {
  short l_type;     // F_RDLCK, F_WRLCK, F_UNLCK
  off_t l_start;
  short l_whence;
  off_t l_len;
  pid_t l_pid;
};
```

### 7.3 lockf() 함수

```c
#include <unistd.h>
int lockf(int fd, int cmd, off_t len);
```

| 명령어      | 설명          |
| -------- | ----------- |
| F\_LOCK  | 잠금, 대기함     |
| F\_TLOCK | 잠금, 대기하지 않음 |
| F\_ULOCK | 잠금 해제       |
| F\_TEST  | 잠금 여부 검사    |

### 7.4 권고 vs 강제 잠금

* **권고 잠금**: 규칙 자발적 적용, 시스템 강제 X (Linux 기본)
* **강제 잠금**: 시스템이 강제 적용

```sh
$ chmod 2644 file.txt
$ ls -l
-rw-r-Sr-- 1 user group ... file.txt
```

---

## 8장: 프로세스

### 8.1 쉘과 프로세스

* **쉘(Shell)**: 사용자 ↔ 커널 간 명령어 처리기
* 쉘의 실행: 명령 입력 → fork → exec → wait
* 복합 명령어: `cmd1; cmd2`, `(cmd1; cmd2)`
* 전면 실행 / 후면 실행: `sleep 10 &`

### 8.2 프로그램 실행

* `exec()` 계열: 현재 프로세스를 다른 프로그램으로 대체

```c
int main(int argc, char *argv[]);
```

### 8.3 프로그램 종료

| 함수       | 특징               |
| -------- | ---------------- |
| return   | main 함수에서 정상 종료  |
| exit()   | 종료 처리기 실행 후 종료   |
| \_exit() | 즉시 종료, flush 안 함 |
| abort()  | 비정상 종료 (시그널)     |

#### atexit

```c
void handler();
atexit(handler);  // 종료 직전에 실행
```

### 8.4 PID 및 UID

```c
getpid(), getppid();
getuid(), geteuid();
getgid(), getegid();
```

* SUID 설정: `chmod 4755 filename`

---

## 9장: 프로세스 제어

### 9.1 fork()

* 부모를 복제해 자식 프로세스 생성
* 부모는 자식 PID 반환, 자식은 0 반환

```c
pid_t pid = fork();
```

### 9.2 exec() 계열 함수

* 자식 프로세스에서 새 프로그램 실행
* `execl()`, `execv()`, `execvp()` 등 다양

### 9.3 입출력 재지정

* `dup()`, `dup2()`로 디스크립터 복제 가능

### 9.4 프로세스 그룹

* PGID로 그룹화 가능
* `kill -pgid ...` 형태로 그룹에 시그널 전송
