#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학생 정보를 입력받아 데이터베이스 파일에 저장한다. */
int main(int argc, char *argv[])
{
  int fd;
  struct student record;
  if (argc < 2) {
    fprintf(stderr, "사용법 : %s file\n", argv[0]);
    exit(1);
  }
  if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
    perror(argv[1]);
    exit(2);
  }
  printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");
  while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3) {
    lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
    write(fd, (char *) &record, sizeof(record) );
  }
  close(fd);
  exit(0);
}
