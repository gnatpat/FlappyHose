#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 70
#define HEIGHT 20

// hehe I see you changed that. Good.
#define HOSE_X 4
#define PIPE_DIFF 15
#define PIPE_GAP 4

void print_board(char board[WIDTH][HEIGHT], int offset)
{
  for(int y = 0; y < HEIGHT; y++)
  {
    for(int x = 0; x < WIDTH; x++)
    {
      printf("%c", board[(x+offset)%WIDTH][y]);
    }
    printf("\n");
  }
}

int main(void)
{
system("stty cbreak -echo");
  srand(time(NULL));
  int offset = 0;
  char board[WIDTH][HEIGHT];
  int hoseY = HEIGHT/2;
  float hoseYExact = hoseY;
  float ySpeed = 0;
  int pipeCount = 0;
  
  /* Clear the board. */
  for(int x = 0; x < WIDTH; x++)
    for(int y = 0; y < HEIGHT; y++)
      board[x][y] = ' ';

  /* Start the hose. */
  board[HOSE_X][hoseY] = '>';
  for(int x = 0; x < HOSE_X; x++)
    board[x][hoseY] = '-';

  /* Fill the floor. */
  for(int x = 0; x < WIDTH; x++)
    board[x][HEIGHT - 1] = '#';

  /* Print the initial board. */
  print_board(board, offset);

  /* Main game loop. */
  while(getchar())
  {
    /* Clear the piece of the hose that's about to go off-screen. */
    for(int y = 0; y < HEIGHT; y++)
    {
      if(board[offset][y] == '|' ||
         board[offset][y] == '-' ||
         board[offset][y] == '/' ||
         board[offset][y] == '\\')
      {
        board[offset][y] = ' ';
      }
    }
    /* TODO: update the hose position. */
    board[(offset + HOSE_X)%WIDTH][hoseY] = '-';
    board[(offset + HOSE_X + 1)%WIDTH][hoseY] = '>';

    if (pipeCount % PIPE_DIFF == 0)
    {
      int pipeHeight = rand() % (HEIGHT - PIPE_GAP - 1);
      for(int y = 0; y < pipeHeight; y++)
      {
        board[offset][y] = '|';
      }
      for(int y = pipeHeight + PIPE_GAP; y < HEIGHT-1; y++)
      {
        board[offset][y] = '|';
      }
    }


    offset = (offset + 1)%WIDTH;
    pipeCount++;
    print_board(board, offset);
  }

system("stty cooked echo");
}
