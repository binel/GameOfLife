#include <stdio.h>
#include <string.h>

#define GRIDWIDTH 80
#define GRIDHEIGHT 24
#define TRUE 1
#define FALSE 0

void printGrid(char grid[GRIDHEIGHT][GRIDWIDTH], int frameNum);

int checkAlive(char grid[GRIDHEIGHT][GRIDWIDTH], int x, int y);

void  simulate(char grid[GRIDHEIGHT][GRIDWIDTH], int frameNum);

int countNeighbors(char grid[GRIDHEIGHT][GRIDWIDTH], int x, int y); 

int main(int argc, char* argv[]) {

  char grid[GRIDHEIGHT][GRIDWIDTH];
  int frameNum = 0; 

  //initalize the grid to all spaces 
  int i, j; 

  for(i = 0; i < GRIDHEIGHT; i++){
    for(j = 0; j < GRIDWIDTH; j++){ 
      grid[i][j] = ' ';
    }
  }
  //populate the grid using command args
  for(i = 1; i < argc; i = i + 2) {
    int x = atoi(argv[i]);
    int y = atoi(argv[i + 1]);
    grid[y][x] = 'O';
  } 

  printGrid(grid, frameNum);
  usleep(83333);
  while(TRUE) {
    frameNum++; 
    simulate(grid, frameNum);
  }
}

int countNeighbors(char grid[GRIDHEIGHT][GRIDWIDTH], int x, int y) {
  int numNeighbors = 0;
  int i, j; 
  for(i = x - 1; i <= x + 1; i++) {
    for(j = y - 1; j <= y + 1; j++) {
      int xcheck = i; 
      int ycheck = j; 
      //handles wrapping 
      if(i < 0) {
	xcheck = GRIDWIDTH - 1;  
      }
      if(i >= GRIDWIDTH) {
	xcheck = 0; 
      }
      if(j < 0) { 
	ycheck = GRIDHEIGHT - 1; 
      }
      if(j >= GRIDHEIGHT) {
	ycheck = 0; 
      }
      if(!(i == x && j == y)) {
	numNeighbors += aliveCheck(grid, xcheck, ycheck); 
      }
    }
  }
  return numNeighbors; 
}


void simulate(char grid[GRIDHEIGHT][GRIDWIDTH], int frameNum) {
  //Simulate 
  char nextGrid[GRIDHEIGHT][GRIDWIDTH];
  int i, j; 
  //initalize the grid 
  for(i = 0; i < GRIDHEIGHT; i++){
    for(j = 0; j < GRIDWIDTH; j++){ 
      nextGrid[i][j] = ' ';
    }
  }
  //determine status of each cell 
  int x, y; 
  for(y = 0; y < GRIDHEIGHT; y++) {
    for(x = 0; x < GRIDWIDTH; x++) {
      //what is the status of this cell
      int isAlive = aliveCheck(grid, x, y);

      //count the number of neighbors of this cell 
      int numNeighbors = countNeighbors(grid, x, y);
      printf("%d", numNeighbors); 
      //determines if alive in the next round
      //1. If the cell is alive and has 0 or 1 live neighbors, it dies 
      if(isAlive == TRUE && numNeighbors < 2) {
	isAlive = FALSE; 
      }
      //2. If the cell is alive and has 2 or 3 live neighbors, it lives 
      else if(isAlive == TRUE && numNeighbors < 4) {
	isAlive = TRUE;
      }
      //3. If the cell is alive and has 4 live neighbors, it dies 
      else if(isAlive == TRUE && numNeighbors == 4) {
	isAlive = FALSE; 
      }
      //4. If the cell is dead and has exactly 3 live neighbors, it lives
      else if(isAlive == FALSE && numNeighbors == 3) {
	isAlive = TRUE; 
      }
      
      //add cell to next grid 
      if(isAlive == TRUE) {
	nextGrid[y][x] = 'O'; 
      } else {
	nextGrid[y][x] = ' ';
      }
    } 
    printf("\n");
  }
  //copy old grid to new grid
  for(i = 0; i < GRIDHEIGHT; i++){
    for(j = 0; j < GRIDWIDTH; j++){ 
      grid[i][j] = nextGrid[i][j];
    }
  }
  printGrid(grid, frameNum); 
  usleep(83333);
  return; 
}

int aliveCheck(char grid[GRIDHEIGHT][GRIDWIDTH], int x, int y) {
  int isAlive = FALSE; 
  if(grid[y][x] == 'O') {
      isAlive = TRUE; 
  }
  return isAlive; 
}

void printGrid(char grid[GRIDHEIGHT][GRIDWIDTH], int frameNum){
  int i,j;

  for(i = 0; i < GRIDHEIGHT; i++) {
    for(j = 0; j < GRIDWIDTH; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
  printf("FRAME %i\n", frameNum); 
}
