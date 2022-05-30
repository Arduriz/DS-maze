#define _CRT_SECURE_NO_WARNINGS //코드의 안정성과 번거로움을 해결하기 위해 삽입
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_SIZE 100
int i, j = 0;

void main() {
    FILE* fp = fopen("input.txt", "r");//fopen이 반환하는 파일 위치를 받을 포인터 변수 file_read 선언

    char *buf[MAZE_SIZE];
    char maze[MAZE_SIZE][MAZE_SIZE];

    while (!feof(fp)) {
        j = 0;
        fgets(buf, sizeof(buf), fp);
        char *ptr = strtok(buf, " ");
        while (ptr != NULL) {
            maze[i][j] = *ptr;
            printf("%s\n", ptr);
            printf("i: %d, j: %d\n", i, j);
            ptr = strtok(NULL, " ");
            j++;
        }
        i++;
    }

    fp = fopen("output.txt", "w");
    for (int r = 0; r < j; r++)
    {
        for (int c = 0; c < i; c++)
        {
            if (maze[r][c] == '1')
                fprintf(fp, "■(%d %d)", r, c);
            else if (maze[r][c] == '0')
                fprintf(fp, "□(%d %d)", r, c);
            else if (maze[r][c] == 'E')
                fprintf(fp, "EE(%d %d)", r, c);//특수문자와 간격을 맞추기 위해 E 두 번 사용
            else if (maze[r][c] == '.')
                fprintf(fp, ".(%d %d)", r, c);
            else if (maze[r][c] == 'X')
                fprintf(fp, "XX(%d %d)", r, c);
            else
                fprintf(fp, "N(%d %d)", r, c);
        }
        fprintf(fp, "\n");
    }

    return 0;
}
