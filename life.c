#include <stdio.h>

#define GRIDWIDTH 80
#define GRIDHEIGHT 24

void printGrid(char grid[GRIDHEIGHT][GRIDWIDTH]);

int main(int argc, char* argv[]) {
  

  char grid[GRIDHEIGHT][GRIDWIDTH];

  //populate the grid using command args
  int i; 
  for(i = 1; i < argc; i = i + 2) {
    int x = atoi(argv[i]);
    int y = atoi(argv[i + 1]);
    grid[y][x] = 'O';
  } 

  printGrid(grid);
}

void printGrid(char grid[GRIDHEIGHT][GRIDWIDTH]){
  int i,j;

  for(i = 0; i < GRIDHEIGHT; i++) {
    for(j = 0; j < GRIDWIDTH; j++) {
      if(grid[i][j] != 'O'){
        printf(" ");
      } else {
        printf("O");
      } 
    }
    printf("\n");
  }
}
