#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
char type(mode_t mode);
char *perm(mode_t mode);
void printStat(char *pathname, char *file, struct stat *st);

/* 디렉터리 내용을 자세히 리스트한다. */
int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct dirent *d;
    struct stat st;
    char path[BUFSIZ + 1];

    // 디렉터리 경로 설정 (기본: 현재 디렉터리)
    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    // 디렉터리 열기
    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    // 디렉터리 내 파일들을 하나씩 처리
    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name); // 전체 경로 생성

        if (lstat(path, &st) < 0) { // 파일 정보 가져오기
            perror(path);
            continue;
        }

        printStat(path, d->d_name, &st); // 정보 출력
        putchar('\n');
    }

    closedir(dp); // 디렉터리 닫기
    exit(0);
}

/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st) {
    printf("%5ld ", st->st_blocks);                                 // 블록 수
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));          // 파일 타입 + 권한
    printf("%3ld ", (long)st->st_nlink);                             // 링크 수
    printf("%s %s ", getpwuid(st->st_uid)->pw_name,                 // 사용자 이름
                   getgrgid(st->st_gid)->gr_name);                  // 그룹 이름
    printf("%9ld ", (long)st->st_size);                              // 파일 크기
    printf("%.12s ", ctime(&st->st_mtime) + 4);                      // 수정 시간
    printf("%s", file);                                              // 파일 이름
}

/* 파일 타입을 리턴 */
char type(mode_t mode) {
    if (S_ISREG(mode)) return '-';   // 일반 파일
    if (S_ISDIR(mode)) return 'd';   // 디렉터리
    if (S_ISCHR(mode)) return 'c';   // 문자 디바이스
    if (S_ISBLK(mode)) return 'b';   // 블록 디바이스
    if (S_ISLNK(mode)) return 'l';   // 심볼릭 링크
    if (S_ISFIFO(mode)) return 'p';  // FIFO (파이프)
    if (S_ISSOCK(mode)) return 's';  // 소켓
    return '?';                      // 알 수 없는 타입
}

/* 파일 사용 권한을 문자열로 리턴 */
char* perm(mode_t mode) {
    static char perms[10];
    int i;

    for (i = 0; i < 9; i++)
        perms[i] = '-';
    perms[9] = '\0';

    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';
    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';
    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';

    return perms;
}
