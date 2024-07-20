#include <stdio.h>

int main(void) {
  char mode;
  scanf("Input mode: %c",&mode);
  if(mode) {
    printf("Entered 0 mode");
  } else {
    printf("Entered other mode");
  }
}
