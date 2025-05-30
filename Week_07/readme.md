
# 시스템 프로그래밍 7주차 정리

## 주요 명령어 및 개념 정리

### 프로세스 관련 명령어
- `$ ps [-옵션]` : 현재 시스템의 프로세스 상태 요약 출력
- `$ sleep 초` : 지정된 시간만큼 실행 중지
- `$ fg` : 정지된 작업을 전면 실행으로 전환
- `$ fg %작업번호` : 특정 작업번호를 전면으로 전환
- `$ bg %작업번호` : 중지된 작업을 백그라운드 실행으로 전환
- `$ kill 프로세스번호` / `$ kill %작업번호` : 프로세스를 강제 종료
- `$ wait [프로세스번호]` : 자식 프로세스 종료까지 대기 (없으면 모두 대기)

### 우선순위 설정 명령어
- `$ nice [-n 조정수치] 명령어` : 조정된 우선순위로 명령 실행
- `$ renice [-n] 우선순위 [-gpu] PID` : 실행 중인 프로세스 우선순위 변경

### 사용자 정보 확인
- `$ id [사용자명]` : 실제 ID, 유효 ID, 그룹 ID 확인

### 사용자 ID 종류
- **Real User ID** : 명령을 실행한 사용자 ID
- **Effective User ID** : 현재 유효한 ID로 권한 확인에 사용됨 (특수 실행파일에 따라 변경 가능)

### 시그널
- 소프트웨어 인터럽트로 예기치 않은 사건을 알림
- `$ kill [-시그널] 프로세스번호` / `$ kill [-시그널] %작업번호` : 시그널 전송 (기본 SIGTERM)

---

### 원격 접속 및 파일 전송
- `$ sftp linux.sookmyung.ac.kr` : 원격 서버에 SFTP 접속
  - 예시: `sftp > cd test`, `sftp > ls`
- `$ ssh 사용자명@호스트명` 또는 `$ ssh -l 사용자명 호스트명` : 원격 접속

### 문자열 검색 및 출력
- `$ grep 패턴 파일*` : 문자열 검색 후 해당 줄 출력
- 명령어 > 출력파일 & : 백그라운드 작업 출력 리다이렉션

---

## 정규 표현식

| 문자 | 의미 | 예시 |
|------|------|------|
| `.` | 임의의 한 문자 | `a...b`: a로 시작, b로 끝나는 5자 문자열 |
| `*` | 앞 문자 0회 이상 반복 | `a*b`: b, ab, aab, ... |
| `[...]` | 대괄호 내 문자 중 하나 | `[abc]d`: ad, bd, cd |
| `[^...]` | 대괄호 내 문자 제외 | `[^abc]d`: ed, fd 등 |
| `^`, `$` | 줄의 시작, 끝 | `^abc`, `abc$` |

---

### 파일 처리 명령어
- `$ sort [-옵션] 파일*` : 텍스트 줄 정렬
- `$ cmp 파일1 파일2` : 파일 비교
- `$ diff [-i] 파일1 파일2` : 줄 단위 비교 (`-i`: 대소문자 무시)
- `$ split [-l n] 입력파일 [출력파일]` : 파일 분할 (-l: 줄 수 지정)
- `$ cat 파일1 파일2 > 파일3` : 파일 연결 후 새 파일 생성
- `$ paste [-s] [-d구분문자] 파일*` : 파일 합병 (`-s`: 직렬, `-d`: 구분자 지정)

---

### 작업 예약 명령어
- `$ crontab 파일` : 주기적 작업 등록
  - `$ crontab -l` : 등록된 작업 목록
  - `$ crontab -e` : 작업 수정
  - `$ crontab -r` : 작업 삭제
- `$ at [-f 파일] 시간` : 특정 시간에 1회 실행 등록

---

### 기타 유용한 명령어
- `$ gzip [옵션] 파일*` : 파일 압축 (.gz 생성)
- `$ alias 이름=문자열` : 명령어 별칭 등록
- `$ history [-rh] [번호]` : 명령어 히스토리 확인

#### History 특수 호출
| 형태 | 의미 |
|------|------|
| `!!` | 직전 명령 재실행 |
| `!n` | n번 명령 재실행 |
| `!문자열` | 해당 문자열로 시작하는 마지막 명령 재실행 |
| `!?문자열?` | 해당 문자열 포함 마지막 명령 재실행 |

- `$ gcc [-옵션] 파일` : C 프로그램 컴파일 (기본 `a.out` 생성)
- `명령어 < 입력파일 &` : 백그라운드 입력 리다이렉션

---

## 단축키
- `Ctrl + C` : 강제 종료
- `Ctrl + Z` : 실행 중지
- `Ctrl + D` : 입력 종료 / EOF

---

## 참조

<https://openai.com/index/chatgpt/>
