# 🐧 시스템 프로그래밍 6주차 강의 내용 정리

## 📌 모드 구분 (Vim 기준)
- **명령 모드 (Command Mode)**  
  → 기본 모드, 복사/붙여넣기/삭제/이동 등 수행 가능

- **편집 모드 (Edit Mode)**  
  → `i` 또는 `a`로 진입하여 텍스트 입력 가능

- **입력 모드 (Insert Mode)**  
  → 편집모드와 거의 동일하게 사용

---

## 💾 자주 쓰는 단축키/명령어

| 키 조합 / 명령어 | 설명 |
|------------------|------|
| `Shift + ZZ`     | 저장하고 나가기 |
| `Ctrl + Z`       | 쉘에서 작업 중지 (백그라운드로 보내기) |
| `Esc`            | 편집 모드 종료 |
| `!g`             | 최근에 실행한 g로 시작하는 명령 실행 |
| `echo $?`        | 직전 명령어의 종료 상태 (exit status) 확인 |
| `$0, $1, $2`     | 스크립트 실행 시 전달한 인자 (예: `./script.sh arg1 arg2`) |
| `>`              | 출력 결과를 파일에 **덮어쓰기** |
| `>>`             | 출력 결과를 파일에 **추가 (append)** |

---

# 강의 중 사용된 예시

## 🧮 변수 및 연산

```bash
expr 1 + 5       # 띄어쓰기 필수! (1 + 5)
var1=$[1 + 5]    # 변수 대입 시 = 앞뒤 공백 없이, 연산식 내부는 공백 필요
echo $var1

value1=10
value2=$value1
echo The resulting value is $value2
```
---

## 📅 날짜 출력 예시
```bash
testing=`date`  # 역따옴표 (`) 사용 주의
echo "The date and time are: $testing"
```
---  

## ➗ 연산 예시
```bash
# 기본 연산
var1=100
var2=50
var3=45
var4=$[$var1 * ($var2 - $var3)]
echo "The final result is $var4"
```

# 나누기
```bash
var1=100
var2=45
var3=$[$var1 / $var2]
echo "The final result is $var3"
```
# 덧셈
```bash
var1=10
var2=30
var3=$[$var1 + $var2]
echo "The answer is $var3"
exit 5
```

---

## ✅ 조건문 예시
```bash
if date
then
    echo "It worked"
fi
```
## 👤 사용자 정보 예시
```text
hyeop:x:1000:1000:,,,:/home/hyeop:/bin/bash
```
* x는 패스워드 필드

---

##🧪 샘플 스크립트
```bash
days=10
guest="Katie"
echo "$guest checked in $days days ago"
```
```bash
days=5
guest="Jessica"
echo "$guest checked in $days days ago"
```
---
🛠️ 파일 실행 및 관리
```bash
vi $1             # 스크립트 파일 열기
chmod u+x $1      # 실행 권한 부여
./$1              # 실행
mv test st        # 자주 쓰는 명령어에 별칭 부여
```
## 🧰 유용한 명령어

| 명령어 | 설명 |
|--------|------|
| jobs | 현재 백그라운드에서 실행 중인 작업 확인 |
| echo "문자열" | 문자열 그대로 출력 |
| echo $? | 직전 명령어의 종료 코드 출력 (127 = command not found 등) |

---

## 참조 
<https://chatgpt.com/>
