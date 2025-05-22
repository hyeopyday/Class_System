# 시스템 프로그래밍 10주차 강의 내용 정리
---
## 📁 파일 디스크립터 복제

### 🔹 dup() / dup2()

* 기존의 파일 디스크립터를 복제함
* oldfd와 복제된 디스크립터(newfd)는 동일한 파일을 가리킴

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

* `dup()` : oldfd의 복제 디스크립터를 반환, 실패 시 -1
* `dup2()` : oldfd를 newfd로 복제, 실패 시 -1

---

## 📍 파일 위치 포인터 (File Position Pointer)

* 파일 내에서 읽거나 쓸 위치를 지정

### 🔀 이동 함수: lseek()

```c
off_t lseek(int fd, off_t offset, int whence);
```

* 성공 시 현재 위치 반환, 실패 시 -1 반환

### ✅ 사용 예시

```c
lseek(fd, 0L, SEEK_SET);         // 파일 시작으로 이동
lseek(fd, 100L, SEEK_SET);       // 시작에서 100바이트 위치로
lseek(fd, 0L, SEEK_END);         // 파일 끝으로 이동
lseek(fd, n * sizeof(record), SEEK_SET); // n+1번째 레코드로 이동
lseek(fd, sizeof(record), SEEK_CUR);     // 다음 레코드로
lseek(fd, -sizeof(record), SEEK_CUR);    // 이전 레코드로
```

---

## 📝 레코드 저장 예시

* 순차 저장: record1 → record2 → 파일 끝으로 이동 후 record3

```c
#define MAX 24
#define START_ID 1401001

struct student {
  char name[MAX];
  int id;
  int score;
};
```

---

## 📦 dbcreate.c

* 학생 정보를 파일에 저장
* `O_WRONLY | O_CREAT | O_EXCL` 모드로 파일 열기
* 학번 기준 위치 계산 후 `write()`로 저장

---

## 🔍 dbquery.c

* 학번 입력 → 해당 레코드 검색/출력
* `O_RDONLY` 모드로 열기
* 위치 계산 후 `read()`로 레코드 출력
* 학번 없으면 "레코드 없음" 출력

---

## ✏️ 레코드 수정 방식

1. 레코드 읽기
2. 수정
3. 파일 내 원래 위치에 다시 쓰기

---

## 🛠️ dbupdate.c

* 학번 입력 → 점수 수정
* `O_RDWR` 모드로 열기
* 위치 계산 후 `read()` → `lseek()`으로 위치 복원 후 `write()`

---

# 📂 파일 시스템 정리

## 1. 파일 시스템 구조

* 저장 장치 위에서 파일을 관리하는 구조
* 디스크 → 섹터 → 블록 단위로 구성

### 주요 개념

* **블록(Block)** : 데이터 저장 최소 단위
* **슈퍼블록(Superblock)** : 파일 시스템 전체 구조 정보 보유

  * 파일 시스템 크기
  * 사용된 블록 수
  * i-node 정보 등

---

## 2. i-node (Index Node)

* 파일 메타데이터 저장 구조

### i-node 저장 정보

* 파일 유형
* 권한 (Permission)
* UID / GID
* 파일 크기
* 데이터 블록 주소 (포인터)
* 생성/수정/접근 시간 등

### 블록 포인터 종류

* 직접(Direct), 단일/이중/삼중 간접 포인터 등

---

## 3. 파일 입출력 구현 (C 예제)

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer[128];
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("read");
        return 1;
    }
    buffer[n] = '\0';
    printf("읽은 내용: %s\n", buffer);

    close(fd);
    return 0;
}
```

* `open()`: 파일 열기
* `read()`: 데이터 읽기
* `close()`: 파일 닫기

---

## 4. 파일 상태 확인 (stat, fstat)

```c
#include <sys/stat.h>
#include <stdio.h>

int main() {
    struct stat st;
    if (stat("sample.txt", &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("파일 크기: %ld bytes\n", st.st_size);
    printf("파일 유형: ");
    if (S_ISREG(st.st_mode)) printf("일반 파일\n");
    else if (S_ISDIR(st.st_mode)) printf("디렉터리\n");

    return 0;
}
```

* `stat()`: 경로 기반 정보 조회
* `fstat()`: 파일 디스크립터 기반 정보 조회

### 주요 필드

* `st_size`: 파일 크기
* `st_mode`: 파일 유형 및 권한

---

## 5. 디렉터리 처리 (opendir, readdir, closedir)

```c
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("파일 이름: %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
```

* `opendir()`: 디렉터리 열기
* `readdir()`: 디렉터리 내용 순회
* `closedir()`: 디렉터리 닫기

---

## ✅ 요약 테이블

| 항목              | 설명                  |
| --------------- | ------------------- |
| i-node          | 파일 메타데이터 저장 구조      |
| 블록 포인터          | 직접/간접 포인터로 크기 확장 지원 |
| open/read/close | 파일 입출력 함수           |
| stat/fstat      | 파일 상태 정보 확인 함수      |
| opendir/readdir | 디렉터리 탐색 함수          |


디렉터리 탐색 함수


