#include <stdio.h>

#define GRIDWIDTH 80
#define GRIDHEIGHT 24
#define TRUE 1
#define FALSE 0

void printGrid(char grid[GRIDHEIGHT][GRIDWIDTH]);

int checkAlive(char grid[GRIDHEIGHT][GRIDWIDTH], int x, int y);

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

  //simulate 
  int x, y; 
  for(y = 0; y < GRIDHEIGHT; y++) {
    for(x = 0; x < GRIDWIDTH; x++) {
      //what is the status of this cell
      int isAlive aliveCheck(grid, x, y);

      //count the number of neighbors of this cell 
      int numNeighbors = 0; 
      
      //count above
      if(y == GRIDHEIGHT) {
        numNeighbors += aliveCheck(grid, x, 0);
      } else {
        numNeighbors += aliveCheck(grid, x, y + 1);
      }
      //count right
      if(x == GRIDWIDTH) {
        numNeighbors += aliveCheck(grid, 0, y);
      } else {
        numNeighbors += aliveCheck(grid, x + 1, y);
      }
      //count down 
      if(y == 0){
        numNeighbors += aliveCheck(grid, x, GRIDHEIGHT);
      } else {
        numNeighbors += aliveCheck(grid, x, y - 1);
      }
      //count left
      if(x == 0) {
        numNeighbors += aliveCheck(grid, GRIDWIDTH, y);
      } else {
        numNeighbors += aliveCheck(grid, x - 1, y);
      }
      //count upper left 
      if(x == 0 && y == 0) {
        numNeighbors += aliveCheck(grid, GRIDWIDTH, GRIDHEIGHT);
      } else {
        numNeighbors += aliveCheck(grid, x - 1, y - 1); 
      }
      //count upper right
      if(x == GRIDWIDTH && y == 0) {
	numNeighbors += aliveCheck(grid, 0, GRIDHEIGHT); 
      } else {
	numNeighbors += aliveCheck(grid, x - 1, y - 1);
      }
    } 
  }
}

int aliveCheck(char grid[GRIDHEIGHT][GRIDWIDTH], int x, int y) {
  int isAlive = FALSE; 
    if(grid[y][x] == 'O') {
      isAlive = TRUE; 
  }
  return isAlive; 
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
