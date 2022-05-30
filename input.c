#define _CRT_SECURE_NO_WARNINGS //코드의 안정성과 번거로움을 해결하기 위해 삽입
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 6
#define MAZE_SIZE 100

int i, j = 0;//지역변수 초기화에 에러가 걸려서 아예 맨처음에 선언과 초기화

void main() {
    char maze[MAZE_SIZE][MAZE_SIZE];//파일에서 읽어들인 문자열을 저장하기 위한 배열
    char* buf;//분할된 문자열의 포인터 값을 저장할 변수

    FILE* file_read = fopen("input.txt", "r");//fopen이 반환하는 파일 위치를 받을 포인터 변수 file_read 선언

    while (fgets(maze, sizeof(maze), file_read) != NULL) { //fgets 함수로 파일의 마지막 문장을 읽을 때까지 실행
        buf = strtok(maze, " ");//strtok 함수로 공백을 기준으로 문자열을 분할한 뒤 포인터 반환
        while (buf != NULL) { //자른 문자열이 나오지 않을 때까지 반복
            maze[i][j] = atoi(buf);//첫번째 값으로 계수, 두번째 값으로 차수가 배열에 저장
            i++;//while문이 실행될 때마다 1 증가
            buf = strtok(NULL, " ");//다음 문자열을 잘라서 포인터를 반환
            if (buf == "\r\n") {
                i = 0;
                j++;
            }
        }
    }
    
    return 0;
}
