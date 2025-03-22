# 🤓시스템 프로그래밍 3주차 강의내용🤓

---

## 디렉터리와 각 명령어의 쓰임새

  * 파일의 종류
  * ? 와 *
  * which 명령어
  * pwd 명령어
  * mkdir 명령어
  * rm / rmdir 명령어

---

## 파일의 종류

 * ll을 쳤을때 앞에 나오는 d~ , l~ ~~는 각각의 파일의 종류를 나타낸다
   - 일반 파일( - )
   - 디렉터리 ( d )
   - 장치파일 ( c )

![예시](https://github.com/user-attachments/assets/b64d467d-0327-49c7-aca1-02c203763f47)

---

## ?와 *의 차이점

 ```ls /usr/bin/l?``` 와 ```ls /sur/bin/l*```을 명령했을 때 보이는 디렉토리가 다르다

 - ?는 임의의 한 글자를 의미
 - *는 0개 이상의 모든 문자를 의미

* ```ls /usr/bin/l?```의 경우
   ```/usr/bin/ld  /usr/bin/ln  /usr/bin/ls```

* ```ls /sur/bin/l*```의 경우

```
/usr/bin/landscape-broker            /usr/bin/less          /usr/bin/localedef    /usr/bin/lsmod
/usr/bin/landscape-client            /usr/bin/lessecho      /usr/bin/logger       /usr/bin/lsns
/usr/bin/landscape-config            /usr/bin/lessfile      /usr/bin/login        /usr/bin/lsof
/usr/bin/landscape-manager           /usr/bin/lesskey       /usr/bin/loginctl     /usr/bin/lspci
/usr/bin/landscape-monitor           /usr/bin/lesspipe      /usr/bin/logname      /usr/bin/lspgpot
/usr/bin/landscape-package-changer   /usr/bin/lexgrog       /usr/bin/look         /usr/bin/lsusb
/usr/bin/landscape-package-reporter  /usr/bin/libnetcfg     /usr/bin/lowntfs-3g   /usr/bin/lto-dump-11
/usr/bin/landscape-release-upgrader  /usr/bin/link          /usr/bin/ls           /usr/bin/lzcat
/usr/bin/landscape-sysinfo           /usr/bin/linux32       /usr/bin/lsattr       /usr/bin/lzcmp
/usr/bin/last                        /usr/bin/linux64       /usr/bin/lsb_release  /usr/bin/lzdiff
/usr/bin/lastb                       /usr/bin/ln            /usr/bin/lsblk        /usr/bin/lzegrep
/usr/bin/lastlog                     /usr/bin/lnstat        /usr/bin/lscpu        /usr/bin/lzfgrep
/usr/bin/lcf                         /usr/bin/loadkeys      /usr/bin/lshw         /usr/bin/lzgrep
/usr/bin/ld                          /usr/bin/loadunimap    /usr/bin/lsipc        /usr/bin/lzless
/usr/bin/ld.bfd                      /usr/bin/locale        /usr/bin/lslocks      /usr/bin/lzma
/usr/bin/ld.gold                     /usr/bin/locale-check  /usr/bin/lslogins     /usr/bin/lzmainfo
/usr/bin/ldd                         /usr/bin/localectl     /usr/bin/lsmem        /usr/bin/lzmore 
```

---

## -p의 쓰임

* 하위 디렉터리까지 한 번에 생성

> ex)mkdir /a/b/c는 a디렉터리에 b디렉터리가 있어야 c디렉터리가 만들어지지만, -p를 사용하면 a디렉터리 부터 없어도 b디렉터리가 만들어지고 그 안에 c디렉터리가 만들어진다.

---

## 명령어 정리

##### which : 명령어의 절대 경로 보여줌


##### pwd : 현재 작업 디렉터리의 절대 경로를 보여줌
> which와 pwd의 차이점▽
>> which는 주로 프로그램의 실제 실행 파일위치를 찾는 데 사용, pwd는 현재 실행 파일위치를 찾는데 사용된다.


##### redir : 디렉터리 삭제 명령어
>***빈 디렉터리만 삭제가 가능하다***
>>본래는 /a/b/c/d/f ... 가 있다면 앞 디렉터리에 들어가 하위 디렉터리를 삭제하는 과정이 정석이지만 ***rm -r 디렉터리이름***을 한다면 지정한 디렉터리부터 하위 디렉터리 모두 삭제가 된다
>>>ex) rm 00? -r => 00으로 시작하여 3자리수 디렉터리 모두 삭제


##### touch : 파일 크기가 0인 이름만 있는 빈 파일을 만들어 준다
> ex) touch hello.c -> cat으로 읽을려고 해도 아무 내용이 없는 파일이다
>> hello.c파일을 42분에 touch로 만들고 43분에 같은 이름으로 touch명령어로 만들면 타임스탬프만이 최신화 되어 만들어진다
>>> 빈 파일과 같은 이름의 파일을 cat > 명령어로 작성을 한다면 touch명령어로 만든 빈 파일에 작성이 되고 타임스탬프가 최신화 된다.



##### more : 파일(들)의 내용을 페이지 단위로 화면에 출력한다.


##### head + 파일 : 파일(들)의 앞부분을 화면에 출력한다. 
> 파일을 지정하지 않으면 표준입력 내용을 대상으로 한다.



##### tail + 파일 : 파일(들)의 ***뒷부분을 화면에 출력***한다. 
> 파일을 지정하지 않으면 표준입력 내용을 대상으로 한다.


##### gcc : 언어 프로그램을 컴파일 하는 데 사용하는 명령어
> ```gcc source.c```은 a.out(실행 파일) 생성
>> ```./a.out```       실행 ( GCC로 컴파일된 기본 실행 파일을 실행하는 명령어 )


---
    
## 실습

 * gcc를 이용하여 내 학번과 이름을 입력하고 출력되는 파일 만들어 실행하기

* 방법
1.```gcc name.c```명령어를 실행하여 실행 파일을 생성한다
2.```cat > name.c```명령어로 실행 파일 안 내용을 기입한다(c언어)
3.```./a.out```명령어를 실행하여 실행 파일 안 내용을 실행시킨다.
  

* 실행 결과
![KakaoTalk_20250321_113822304](https://github.com/user-attachments/assets/4c12f6bf-a49f-4ecb-9cf7-a94e8f07d2ba)


* name.c 소스코드


```
#include <stdio.h>

int main() {
    char name[50];
    int student_id;

    // 학번과 이름 입력 받기
    printf("학번을 입력하세요: ");
    scanf("%d", &student_id);

    printf("이름을 입력하세요: ");
    scanf("%s", name);

    // 출력
    printf("\n[입력한 정보]\n");
    printf("학번: %d\n", student_id);
    printf("이름: %s\n", name);

    return 0;
}
```

---
## 📖참조📖

* <https://chatgpt.com/>
