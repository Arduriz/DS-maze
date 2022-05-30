#define _CRT_SECURE_NO_WARNINGS //코드의 안정성과 번거로움을 해결하기 위해 삽입
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void main() {
    FILE* fp = fopen("input.txt", "r");//fopen이 반환하는 파일 위치를 받을 포인터 변수 file_read 선언
    int line = 1;
    char buf[SIZE];

    while (!feof(fp)) {
        fgets(buf, sizeof(buf), fp);
        printf("[ %d번째 라인 ]\n", line++);
        char* ptr = strtok(buf, " ");
        while (ptr != NULL) {
            printf("단어: %s\n", ptr);
            ptr = strtok(NULL, " ");
        }
    }

    return 0;
}
