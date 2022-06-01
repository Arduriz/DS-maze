#define _CRT_SECURE_NO_WARNINGS //코드의 안정성과 번거로움을 해결하기 위해 삽입
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 101
#define MAX_STACK_SIZE 100

char maze[MAZE_SIZE][MAZE_SIZE]; //미로를 저장할 배열

int i, j = 0; //input.txt에서 미로 불러올 때 지역변수 초기화에 에러가 걸려서 아예 전역변수로 선언과 초기화

FILE* file_read;//fopen이 반환하는 파일 위치를 받을 포인터 변수 선언
FILE* file_write;

typedef struct { //stack이 구조체로 정의되며 r은 row, c는 column을 의미
    short r;
    short c;
}element;

element here;

typedef struct { //Stacktype 구조체의 data에 maze 속 좌표를 입력할 것
    element* data;
    int capacity;
    int top;
}StackType;

//공백 상태 검출 함수
int is_empty(StackType* s) {
    return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

//삭제함수, stack에서 top data를 빼냄
element pop(StackType* s) {
    if (is_empty(s)){
        fprintf(stderr, "stack공백 에러\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

//삽입함수
void push(StackType* s, element item) {
    if (is_full(s)) {
        s->capacity *= 2;//stack이 이미 차있는 상태라면 용량을 2배로 늘려줌 
        s->data = (element*)malloc(s->data, s->capacity * sizeof(element));//동적 메모리 할당
    }
    else s->data[++(s->top)] = item;
}

//위치를 stack에 삽입하는 함수
void push_loc(StackType* s, int r, int c) {
    if (r < 0 || c < 0)
        return;

    if (maze[r][c] != '1' && maze[r][c] != '.' && maze[r][c] != NULL) { //maze[r][c] != NULL 조건으로 벽으로 막히지 않는 미로도 탐색 가능
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

//stack 초기화 함수
void init_stack(StackType* s) {
    s->top = -1;//stack에 아무 data도 저장되어 있지 않음
    s->capacity = 1;//stack의 용량 1로 초기화
    s->data = (element*)malloc(s->capacity * (sizeof(element)));//동적메모리 할당
}

//output.txt에 미로와 경로를 출력하는 함수
void write() {
    for (int r = 0; r < i; r++)//미로가 존재하는 행과 열만큼만 출력
    {
        for (int c = 0; c < j; c++)
        {
            if (maze[r][c] == '1')
                fprintf(file_write, "■");
            else if (maze[r][c] == '0')
                fprintf(file_write, "□");
            else if (maze[r][c] == 'E')
                fprintf(file_write, "EE");//특수문자와 간격을 맞추기 위해 E 두 번 사용
            else if (maze[r][c] == '.')
                fprintf(file_write, "☆");
            else if (maze[r][c] == 'X')
                fprintf(file_write, "X");
            else
                fprintf(file_write, " ");
        }
        fprintf(file_write, "\n");
    }
}

int main(void) {
    memset(maze, 0, MAZE_SIZE * MAZE_SIZE);//메모리 초기화
    int r, c;
    StackType  s;

    //input.txt에서 미로를 불러와서 maze배열에 집어넣는 코드
    char* buf[MAZE_SIZE];
    file_read = fopen("input.txt", "r");
    while (!feof(file_read)) {
        j = 0;
        fgets(buf, sizeof(buf), file_read);//개행을 기준으로 한 줄씩 읽어오기 위해 fgets 사용
        char* value = strtok(buf, " ");//버퍼에 있는 것들을 공백을 기준으로 잘라서 하나씩 value에 집어넣음
        while (value != NULL) {
            maze[i][j] = *value;//value에 있는 값을 maze에 하나씩 집어넣음
            if (maze[i][j] == 'E') {//E가 있는 위치를 시작위치로 잡음
                here.r = i;
                here.c = j;
            }
            value = strtok(NULL, " ");
            j++;
        }
        i++;
    }

    file_write = fopen("output.txt", "w");
    write();//미로를 출력

    init_stack(&s);//stack 초기화
    printf("시작 ->");
    while (maze[here.r][here.c] != 'X') {
        r = here.r;//stack의 r, c를 here로 우선 선언
        c = here.c;
        maze[r][c] = '.';//지나간 길에 .넣음
        //현재 위치에서 갈 수 있는 곳을 stack에 쌓음, 0으로만 갈 수 있음
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        printf("(%d, %d)-> ", r, c);//지나간 좌표 출력
        if (is_empty(&s)) { //stack에 갈 수 있는 경로가 남지 않았다면 실패        
            printf("실패\n");
            break;
        }
        else {
            here = pop(&s);
        }
        if (maze[here.r][here.c] == 'X') { //X를 만나면 탐색에 성공
            printf("도착\n");
            printf("탐색 성공\n");
            break;
        }
    }

    fprintf(file_write, "\n");
    fprintf(file_write, "탐색 경로\n");
    write();//탐색 경로를 출력

    fclose(file_read);
    fclose(file_write);
    return 0;
}