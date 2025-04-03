```c
#include <stdio.h>

int main() {
  
    char ch;

    while (1) {
        printf("문자 입력 : ");
        scanf(" %c", &ch);  // 공백을 추가하여 이전 입력 버퍼를 비움
        
        if (ch == '0') {
            break;  // 0을 입력하면 종료
        }

        if (ch >= 'A' && ch <= 'Z') {
            // 대문자 입력 시 소문자로 변환
            printf("%c의 소문자는 %c입니다.\n", ch, ch + 32);
        } else if (ch >= 'a' && ch <= 'z') {
            // 소문자 입력 시 대문자로 변환
            printf("%c의 대문자는 %c입니다.\n", ch, ch - 32);
        } else {
            printf("알파벳을 입력하세요.\n");
        }
    }

    return 0;
}
```
