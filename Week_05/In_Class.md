## 문제
* 0-255의 정수를 입력받아  2진수로 출력하고, 1의 개수가 몇개인지 출력하고 상위 4비트 2진수로 출력하는  c프로그램


---

```c

#include <stdio.h>

int main() {
    int num;
    int count = 0;
    int binary[8]; // 8비트(0-255) 정수를 저장할 배열
    
    // 사용자로부터 0-255 사이의 정수 입력 받기
    printf("0부터 255 사이의 정수를 입력하세요: ");
    scanf("%d", &num);
    
    // 입력값 검증
    if (num < 0 || num > 255) {
        printf("오류: 0부터 255 사이의 정수를 입력해야 합니다.\n");
        return 1;
    }
    
    // 10진수를 2진수로 변환
    for (int i = 7; i >= 0; i--) {
        binary[i] = num % 2;
        num /= 2;
    }
    
    // 2진수 출력
    printf("2진수: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", binary[i]);
        if (binary[i] == 1) {
            count++; // 1의 개수 세기
        }
    }
    printf("\n");
    
    // 1의 개수 출력
    printf("1의 개수: %d\n", count);
    
    // 상위 4비트 출력
    printf("상위 4비트: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
    
    return 0;
```
}
