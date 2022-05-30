#define _CRT_SECURE_NO_WARNINGS //코드의 안정성과 번거로움을 해결하기 위해 삽입
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 7
#define MAZE_SIZE 7

int i, j = 0;//지역변수 초기화에 에러가 걸려서 아예 맨처음에 선언과 초기화

typedef struct {
    short r;
    short c;
}

void main() {
    char maze[MAZE_SIZE][MAZE_SIZE];//파일에서 읽어들인 문자열을 저장하기 위한 배열

    FILE* file_read = fopen("input.txt", "r");//fopen이 반환하는 파일 위치를 받을 포인터 변수 file_read 선언

    for (int i = 0; i < MAZE_SIZE-1; i++){
        for (int j = 0; j < MAZE_SIZE-1; j++) {
            fscanf(file_read, "%s", &maze[i][j]);
        }
    }

    file_read = fopen("output.txt", "w");
    for (int r = 0; r < MAZE_SIZE-1; r++)
    {
        for (int c = 0; c < MAZE_SIZE-1; c++)
        {
            if (maze[r][c] == '1')
                fprintf(file_read, "1");
            else if (maze[r][c] == '0')
                fprintf(file_read, "0");
            else if (maze[r][c] == 'E')
                fprintf(file_read, "E");
            else if (maze[r][c] == '.')
                fprintf(file_read, ".");
            else if (maze[r][c] == 'X')
                fprintf(file_read, "X");
            else
                fprintf(file_read, "N");
        }
        fprintf(file_read, "\n");
    }
    return 0;
}
