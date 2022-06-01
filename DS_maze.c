#define _CRT_SECURE_NO_WARNINGS //�ڵ��� �������� ���ŷο��� �ذ��ϱ� ���� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 101
#define MAX_STACK_SIZE 100

char maze[MAZE_SIZE][MAZE_SIZE]; //�̷θ� ������ �迭

int i, j = 0; //input.txt���� �̷� �ҷ��� �� �������� �ʱ�ȭ�� ������ �ɷ��� �ƿ� ���������� ����� �ʱ�ȭ

FILE* file_read;//fopen�� ��ȯ�ϴ� ���� ��ġ�� ���� ������ ���� ����
FILE* file_write;

typedef struct { //stack�� ����ü�� ���ǵǸ� r�� row, c�� column�� �ǹ�
    short r;
    short c;
}element;

element here;

typedef struct { //Stacktype ����ü�� data�� maze �� ��ǥ�� �Է��� ��
    element* data;
    int capacity;
    int top;
}StackType;

//���� ���� ���� �Լ�
int is_empty(StackType* s) {
    return (s->top == -1);
}

//��ȭ ���� ���� �Լ�
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

//�����Լ�, stack���� top data�� ����
element pop(StackType* s) {
    if (is_empty(s)){
        fprintf(stderr, "stack���� ����\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

//�����Լ�
void push(StackType* s, element item) {
    if (is_full(s)) {
        s->capacity *= 2;//stack�� �̹� ���ִ� ���¶�� �뷮�� 2��� �÷��� 
        s->data = (element*)malloc(s->data, s->capacity * sizeof(element));//���� �޸� �Ҵ�
    }
    else s->data[++(s->top)] = item;
}

//��ġ�� stack�� �����ϴ� �Լ�
void push_loc(StackType* s, int r, int c) {
    if (r < 0 || c < 0)
        return;

    if (maze[r][c] != '1' && maze[r][c] != '.' && maze[r][c] != NULL) { //maze[r][c] != NULL �������� ������ ������ �ʴ� �̷ε� Ž�� ����
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

//stack �ʱ�ȭ �Լ�
void init_stack(StackType* s) {
    s->top = -1;//stack�� �ƹ� data�� ����Ǿ� ���� ����
    s->capacity = 1;//stack�� �뷮 1�� �ʱ�ȭ
    s->data = (element*)malloc(s->capacity * (sizeof(element)));//�����޸� �Ҵ�
}

//output.txt�� �̷ο� ��θ� ����ϴ� �Լ�
void write() {
    for (int r = 0; r < i; r++)//�̷ΰ� �����ϴ� ��� ����ŭ�� ���
    {
        for (int c = 0; c < j; c++)
        {
            if (maze[r][c] == '1')
                fprintf(file_write, "��");
            else if (maze[r][c] == '0')
                fprintf(file_write, "��");
            else if (maze[r][c] == 'E')
                fprintf(file_write, "EE");//Ư�����ڿ� ������ ���߱� ���� E �� �� ���
            else if (maze[r][c] == '.')
                fprintf(file_write, "��");
            else if (maze[r][c] == 'X')
                fprintf(file_write, "X");
            else
                fprintf(file_write, " ");
        }
        fprintf(file_write, "\n");
    }
}

int main(void) {
    memset(maze, 0, MAZE_SIZE * MAZE_SIZE);//�޸� �ʱ�ȭ
    int r, c;
    StackType  s;

    //input.txt���� �̷θ� �ҷ��ͼ� maze�迭�� ����ִ� �ڵ�
    char* buf[MAZE_SIZE];
    file_read = fopen("input.txt", "r");
    while (!feof(file_read)) {
        j = 0;
        fgets(buf, sizeof(buf), file_read);//������ �������� �� �پ� �о���� ���� fgets ���
        char* value = strtok(buf, " ");//���ۿ� �ִ� �͵��� ������ �������� �߶� �ϳ��� value�� �������
        while (value != NULL) {
            maze[i][j] = *value;//value�� �ִ� ���� maze�� �ϳ��� �������
            if (maze[i][j] == 'E') {//E�� �ִ� ��ġ�� ������ġ�� ����
                here.r = i;
                here.c = j;
            }
            value = strtok(NULL, " ");
            j++;
        }
        i++;
    }

    file_write = fopen("output.txt", "w");
    write();//�̷θ� ���

    init_stack(&s);//stack �ʱ�ȭ
    printf("���� ->");
    while (maze[here.r][here.c] != 'X') {
        r = here.r;//stack�� r, c�� here�� �켱 ����
        c = here.c;
        maze[r][c] = '.';//������ �濡 .����
        //���� ��ġ���� �� �� �ִ� ���� stack�� ����, 0���θ� �� �� ����
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        printf("(%d, %d)-> ", r, c);//������ ��ǥ ���
        if (is_empty(&s)) { //stack�� �� �� �ִ� ��ΰ� ���� �ʾҴٸ� ����        
            printf("����\n");
            break;
        }
        else {
            here = pop(&s);
        }
        if (maze[here.r][here.c] == 'X') { //X�� ������ Ž���� ����
            printf("����\n");
            printf("Ž�� ����\n");
            break;
        }
    }

    fprintf(file_write, "\n");
    fprintf(file_write, "Ž�� ���\n");
    write();//Ž�� ��θ� ���

    fclose(file_read);
    fclose(file_write);
    return 0;
}