#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6
#define MAX_STACK_SIZE 100


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

void push(StackType* s, element item) //stack의 top에 item을 넣는다. 
{
   if (s->data != NULL)
   {
      if (is_full(s))
      {
         s->capacity *= 2; //stack이 이미 차있는 상태라면 용량을 2배로 늘려준다 
         s->data = (element*)realloc(s->data, s->capacity * sizeof(element));//동적 메모리 할당
      }
      s->data[++(s->top)] = item;//top의 값을 1 올려준 후 stack에 item을 top에 놓는다
   }
}

int is_empty(StackType* s)
{ 
   return (s->top == -1);
}

int is_full(StackType* s)
{
   return (s->top == (MAX_STACK_SIZE - 1));
}

char maze[MAZE_SIZE][MAZE_SIZE] =
{
   {'1','1','1','1','1','1',},
   {'e','0','1','0','0','1',},
   {'1','0','0','0','1','1',},
   {'1','0','1','0','1','1',},
   {'1','0','1','0','0','x',},
   {'1','1','1','1','1','1',},

};


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
   FILE* file;


   file = fopen("output.txt", "w");
   for (int r = 0; r < MAZE_SIZE; r++)
   {
      for (int c = 0; c < MAZE_SIZE; c++)
      {
         if (maze[r][c] == '1')
            fprintf(file, "[]");
         else if (maze[r][c] == '0')
            fprintf(file, "  ");
         else if (maze[r][c] == 'e')
            fprintf(file, "E");
         else if (maze[r][c] == '.')
            fprintf(file, ". ");
         else
            fprintf(file, "X");
      }
      fprintf(file, "\n");
   }



   init_stack(&s);
   here = entry;
   printf("시작 ->");
   while (maze[here.r][here.c] != 'x')
   {
      r = here.r;//stack의 r을 here로 우선 선언한다
      c = here.c;
      if (maze[r][c] != 'e')
         maze[r][c] = '.';
      //현재 위치에서 갈 수 있는 곳을 stack에 쌓는다, 0으로만 갈 수 있다
      push_loc(&s, r - 1, c);
      push_loc(&s, r + 1, c);
      push_loc(&s, r , c-1);
      push_loc(&s, r, c+1);
      printf("(%d, %d)-> ", r, c); // 지나간 좌표 표시
      if (is_empty(&s))//스택에 남은 갈 수 있는 경로가 남지 않았다면 실패
      {
         printf("실패\n");
         return;

      }
      else
         here = pop(&s);
      
   }
   printf("성공\n");//operation level 끝


   //output에 입력하는 부분 시작
   file = fopen("output.txt", "w");//output.txt에 입력 과정
   fprintf(file, "탐색 경로\n");
   fprintf(file,"\n");
   for (int r = 0; r < MAZE_SIZE; r++)
   {
      for (int c = 0; c < MAZE_SIZE; c++)
      {
         if (maze[r][c] == '1')
            fprintf(file, "[]");
         else if (maze[r][c] == '0')
            fprintf(file, " ");
         else if (maze[r][c] == 'e')
            fprintf(file, "E");
         else if (maze[r][c] == '.')
            fprintf(file, ". ");
         else
            fprintf(file, "X");
      }
      fprintf(file,"\n");
   }


   return 0;
}
