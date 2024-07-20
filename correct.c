#include <stdio.h>
#include <assert.h>
typedef int bool;
typedef unsigned uint;

#define x_size 10
#define y_size 10
#define size x_size * y_size

bool board[size];
bool temp[size];
char string[13 * size + 1];

char live[] = "\033[34m\u25CF\033[0m";
char dead[] = "\033[34m\u25CB\033[0m";

void my_strcpy(char* destination, char* source) {
  uint i = 0;
  while(source[i] != '\0') {
    destination[i] = source[i];
    ++i;
  }
}

uint idx(uint x, uint y) {
  return x * y_size + y;
}

void stringify() {

  uint string_idx = 0;

  for(uint y = 0; y < y_size; ++y) {
    for(uint x = 0; x < x_size; ++x) {
      
      if(board[idx(x,y)])
        my_strcpy(string + string_idx, live);
      else
        my_strcpy(string + string_idx, dead);
      string_idx += 12;
        
      string[string_idx++] = ' ';
    }
    string[string_idx - 1] = '\n';
  }

  string[string_idx] = '\0';
  
}

void init(void) {
  for(uint i = 0; i < size; ++i)
    board[i] = 0;

}

int from_stdin(void) {

  uint nof_trials;
  printf("Enter the number of cells you want to live: ");
  scanf("%d", &nof_trials);

  for(uint trial = 0; trial < nof_trials; ++trial) {
    uint x,y;
    printf("Enter the x,y coordinates of the %d/%d cell: ", trial, nof_trials);
    scanf("%d %d", &x, &y);

    uint index = idx(x,y);

    if(index < size) {

      board[index] = 1;

  printf("\033c");
      stringify();
  printf("%s", string);
    }
    else {
      printf("Indices (%d, %d) out of bounds.\n", x, y);
      return 1;
    }
  }

  return 0;
}

uint live_neighbours(uint x, uint y) {

  assert(x < x_size);
  assert(y < y_size);

  switch(x) {
    case 0: switch(y) {
              case 0:
                return 
                  board[idx(x, y + 1)] +
                  board[idx(x + 1, y)] +
                  board[idx(x + 1, y + 1)];

              case y_size - 1:
                return 
                  board[idx(x, y - 1)] +
                  board[idx(x + 1, y)] +
                  board[idx(x + 1, y - 1)];
              default:
                return 
                  board[idx(x, y + 1)] +
                  board[idx(x, y - 1)] +
                  board[idx(x + 1, y - 1)] +
                  board[idx(x + 1, y)] +
                  board[idx(x + 1, y + 1)];
            };

    case x_size - 1: switch(y) {
              case 0:
                return 
                  board[idx(x, y + 1)] +
                  board[idx(x - 1, y)] +
                  board[idx(x - 1, y + 1)];
              case y_size - 1:
                return 
                  board[idx(x, y - 1)] +
                  board[idx(x - 1, y)] +
                  board[idx(x - 1, y - 1)];
              default:
                return 
                  board[idx(x, y + 1)] +
                  board[idx(x, y - 1)] +
                  board[idx(x - 1, y - 1)] +
                  board[idx(x - 1, y)] +
                  board[idx(x - 1, y + 1)];
            };
    default: switch(y) {
              case 0:
                return 
                  board[idx(x - 1, y)] +
                  board[idx(x + 1, y)] +
                  board[idx(x - 1, y + 1)] +
                  board[idx(x, y + 1)] +
                  board[idx(x + 1, y + 1)];
              case y_size - 1:
                return 
                  board[idx(x - 1, y)] +
                  board[idx(x + 1, y)] +
                  board[idx(x - 1, y - 1)] +
                  board[idx(x, y - 1)] +
                  board[idx(x + 1, y - 1)];
              default:
                return 
                  board[idx(x - 1, y)] +
                  board[idx(x + 1, y)] +
                  board[idx(x - 1, y - 1)] +
                  board[idx(x, y - 1)] +
                  board[idx(x + 1, y - 1)] +
                  board[idx(x - 1, y + 1)] +
                  board[idx(x, y + 1)] +
                  board[idx(x + 1, y + 1)];
            };  
  }
  
}

uint next(void) {
  for(uint x = 0; x < x_size; ++x) {
    for(uint y = 0; y < y_size; ++y) {

      uint live_nb = live_neighbours(x,y);
      uint index = idx(x,y);

      if(board[index]){
        if(live_nb == 2 || live_nb == 3)
          temp[index] = 1;
        else
          temp[index] = 0;
      } else {
        if(live_nb == 3)
          temp[index] = 1;
        else
          temp[index] = 0;
      }
    }
  }

  uint done = 0;
  for(uint i = 0; i < size; ++i) {
    board[i] = temp[i];
    done = done || temp[i];
  }

  for(volatile uint i = 0; i < 200000000; ++i){}
  return done;

}

//DEBUG

void raw_print(void) {
  for(uint x = 0; x < x_size; ++x)
    for(uint y = 0; y < y_size; ++y) {
      if(y == y_size - 1)
        printf("%d\n", board[idx(x,y)]);
      else
        printf("%d ", board[idx(x,y)]);
    }
}

void raw_print_temp(void) {

  for(uint x = 0; x < x_size; ++x)
    for(uint y = 0; y < y_size; ++y) {
      /*printf("x,y: %d %d\n", x,y);*/
      if(y == y_size - 1)
        printf("%d\n", temp[idx(x,y)]);
      else
        printf("%d ", temp[idx(x,y)]);
    }
}

void raw_print_nb(void) {
  for(uint x = 0; x < x_size; ++x)
    for(uint y = 0; y < y_size; ++y) {
      /*printf("x,y: %d %d\n", x,y);*/
      if(y == y_size - 1)
        printf("%d\n", live_neighbours(x,y));
      else
        printf("%d ", live_neighbours(x,y));
    }
}

int main(void) {
  init();
  from_stdin();

  printf("\033c");
  stringify();
  printf("%s", string);

  /*raw_print();*/
  /**/
  /*printf("\n---------\n");*/
  /*raw_print_nb();*/
  /*next();*/
  /*printf("\n---------\n");*/
  /*raw_print_temp();*/


  while(next()){
  printf("NOT DONE\n");

    printf("\033c");
    /*raw_print();*/
    stringify();
    printf("%s", string);
  }

  printf("DONE\n");
  
}
