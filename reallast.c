#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 100
#define MAX_STACK_SIZE 100

int i, j = 0;
int success = 0;

char maze[MAZE_SIZE][MAZE_SIZE];

typedef struct //r은 row, c는 column을 의미한다
{
    short r;
    short c;
}element;

typedef struct { //Stacktype 구조체의 data에 maze 속 좌표를 입력할 것이다. 
    element* data;
    int capacity;
    int top;
}StackType;

element here = { 1, 0 }, entry = { 1,0 };

element pop(StackType* s) //stack에서 top data를 빼낸다
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택공백 에러\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}

int is_empty(StackType* s)
{
    return (s->top == -1);
}

int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push_loc(StackType* s, int r, int c) //위치를 스택에 삽입
{
    if (r < 0 || c < 0)
        return;


    if (maze[r][c] != '1' && maze[r][c] != '.')
    {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }

}


void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++)
    {
        for (int c = 0; c < MAZE_SIZE; c++)
        {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

void init_stack(StackType* s) //stack을 초기화
{
    s->top = -1;//stack에 아무 data도 저장되어 있지 않다
    s->capacity = 1;//stack의 용량 또한 1로 초기화
    s->data = (element*)malloc(s->capacity * (sizeof(element)));
}

int main(void)
{
    int r, c;
    StackType  s;

    FILE* fp = fopen("input.txt", "r");//fopen이 반환하는 파일 위치를 받을 포인터 변수 file_read 선언

    char* buf[MAZE_SIZE];

    while (!feof(fp)) {
        j = 0;
        fgets(buf, sizeof(buf), fp);
        char* ptr = strtok(buf, " ");
        while (ptr != NULL) {
            maze[i][j] = *ptr;
            ptr = strtok(NULL, " ");
            j++;
        }
        i++;
    }


    fp = fopen("output.txt", "w");
    for (int r = 0; r < MAZE_SIZE; r++)
    {
        for (int c = 0; c < MAZE_SIZE; c++)
        {
            if (maze[r][c] == '1')
                fprintf(fp, "■");
            else if (maze[r][c] == '0')
                fprintf(fp, "□");
            else if (maze[r][c] == 'E')
                fprintf(fp, "EE");//특수문자와 간격을 맞추기 위해 E 두 번 사용
            else if (maze[r][c] == '.')
                fprintf(fp, "☆");
            else if (maze[r][c] == 'X')
                fprintf(fp, "X");
            else
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }

    init_stack(&s);
    here = entry;
    printf("시작 ->");
    while (maze[here.r][here.c] != 'X')
    {
        r = here.r;//stack의 r을 here로 우선 선언한다
        c = here.c;
        maze[r][c] = '.';
        //현재 위치에서 갈 수 있는 곳을 stack에 쌓는다, 0으로만 갈 수 있다
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        printf("(%d, %d)-> ", r, c); // 지나간 좌표 표시
        if (is_empty(&s))//스택에 남은 갈 수 있는 경로가 남지 않았다면 실패
        {
            printf("실패\n");
            break;
        }
        else {
            here = pop(&s);
        }
        if (maze[here.r][here.c] == 'X') {
            printf("도착\n");//operation level 끝
            printf("탐색 성공\n");
            break;
        }
    }

    fprintf(fp, "\n");
    fprintf(fp, "탐색 경로\n");
    for (int r = 0; r < MAZE_SIZE; r++)
    {
        for (int c = 0; c < MAZE_SIZE; c++)
        {
            if (maze[r][c] == '1')
                fprintf(fp, "■");
            else if (maze[r][c] == '0')
                fprintf(fp, "□");
            else if (maze[r][c] == 'E')
                fprintf(fp, "EE");//특수문자와 간격을 맞추기 위해 E 두 번 사용
            else if (maze[r][c] == '.')
                fprintf(fp, "☆");
            else if (maze[r][c] == 'X')
                fprintf(fp, "X");
            else
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}
