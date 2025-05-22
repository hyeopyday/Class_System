#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int main(int argc, char *argv[])
{
    int fd, id;
    char c;
    struct student record;
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }
    do {
        printf("\n검색할 학생의 학번 입력:");
        if (scanf("%d", &id) == 1) {
            lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
            if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0))
                printf("이름:%s\t 학번:%d\t 점수:%d\n", record.name, record.id, 
                    record.score);
            else 
                printf("레코드 %d 없음\n", id);
        } else 
            printf("입력 오류");
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c=='Y');
    close(fd);
    exit(0);
}
