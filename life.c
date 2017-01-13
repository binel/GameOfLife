#include <stdio.h>
#include <string.h>

#define GRIDWIDTH 80
#define GRIDHEIGHT 24
#define TRUE 1
#define FALSE 0

void printGrid(char grid[GRIDHEIGHT][GRIDWIDTH], int frameNum);

int checkAlive(char grid[GRIDHEIGHT][GRIDWIDTH], int x, int y);

int simulate(char grid[GRIDHEIGHT][GRIDWIDTH], int frameNum);

int main(int argc, char* argv[]) {
  

  char grid[GRIDHEIGHT][GRIDWIDTH];
  int frameNum = 0; 
  //populate the grid using command args
  int i; 
  for(i = 1; i < argc; i = i + 2) {
    int x = atoi(argv[i]);
    int y = atoi(argv[i + 1]);
    grid[y][x] = 'O';
  } 

  printGrid(grid, frameNum);
  while(TRUE) {
    frameNum = simulate(grid, frameNum);
  }
}

int simulate(char grid[GRIDHEIGHT][GRIDWIDTH], int frameNum) {
    //Simulate 
    char nextGrid[GRIDHEIGHT][GRIDWIDTH]; 
    int x, y; 
    for(y = 0; y < GRIDHEIGHT; y++) {
      for(x = 0; x < GRIDWIDTH; x++) {
	//what is the status of this cell
	int isAlive = aliveCheck(grid, x, y);

	//count the number of neighbors of this cell 
	int numNeighbors = 0; 

	//count in circle 
	int i, j; 
	for(i = x - 1; i < x + 1; i++) {
	  for(j = y - 1; j < y + 1; j++) {
	    //handles wrapping
	    if(i < 0) {
	      i = GRIDWIDTH - 1;  
	    }
	    if(i > GRIDWIDTH) {
	      i = 0; 
	    }
	    if(j < 0) { 
	      j = GRIDHEIGHT - 1; 
	    }
	    if(j > GRIDHEIGHT) {
	      j = 0; 
	    }

	    numNeighbors += aliveCheck(grid, i, j); 

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
	    }
	  }
	}
      } 
    }
    grid = nextGrid; 
    frameNum++;
    printGrid(grid, frameNum); 
    usleep(1000000);
    return frameNum; 
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
      if(grid[i][j] != 'O'){
        printf(" ");
      } else {
        printf("O");
      } 
    }
    printf("\n");
  }
  printf("FRAME %i", frameNum); 
}
