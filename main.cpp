#include <iostream>

void ex() { char *c = (char *) malloc(100 * sizeof(char)); }

int main() {

  ex();
  return 0;
}