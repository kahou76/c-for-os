#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printfEx() {
  char c = 'a';
  char *str = "Kris Kool";
  int i = 10;
  double pi = 3.1415926;
  printf("character: %c, string: %s, int: %d, double: %f\n", c, str, i, pi);
  // cannot modify str
  // segmentation fault: str[3] = '\0';
  char *dest = (char *)malloc(80 * sizeof(char));
  strcpy(dest, str);
  dest[3] = '\0';
  printf("shorter string: %s\n", dest);
  free(dest);
}

void fopenEx() {
  FILE *fp = fopen("main.c", "r");
  assert(fp != NULL);
  char *buffer = NULL;
  size_t buffer_size = 0; // unsigned long
  ssize_t read;           // long
  while ((read = getline(&buffer, &buffer_size, fp)) != EOF) {
    // z - for size_t, u - for unsigned
    printf("Retrieved line of length %zu:\n", read);
    printf("%s", buffer);
  }
  free(buffer);
  fclose(fp);
}

void getlineEx() {
  char *temp;
  char *original;
  size_t buffer_size; // unsigned long
  char *buffer = NULL;
  ssize_t read; // long
  while ((read = getline(&buffer, &buffer_size, stdin)) != EOF) {
    printf("line: %s", buffer);
    // strdup makes a copy
    temp = original = strdup(buffer);
    // temp is modified
    char *name = strsep(&temp, ";");
    assert(name != NULL && temp != NULL);
    int length = atoi(strsep(&temp, ";"));
    assert(name != NULL && temp != NULL);
    int height = atoi(strsep(&temp, ";"));
    printf("Name: %s, length: %d, height: %d\n", name, length, height);
    assert(temp == NULL);
    // duplicated from strdup
    free(original);
  }
  // resized by getline
  free(buffer);
}

void memsetEx() {
  char str[20] = "Hello World";
  // Fill 3 characters starting from str[5] with '.'
  memset(str + 5, '.', 3 * sizeof(char));
  printf("Modified: %s\n", str);
  // change all to x
  memset(str, 'x', strlen(str) * sizeof(char));
  printf("x'ed: %s\n", str);
  char *world = "World";
  char *hello = "Hello";
  memcpy(str, world, strlen(world));
  memcpy(str + 6, hello, strlen(hello));
  printf("Recreated: %s\n", str);
}

// must use strcmp to compare char*
// common mistake is to use
// a < b or a == b
// which compares address of a and address of b
bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

void sortCharArray(char *arr[], int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (comesBefore(arr[j], arr[i])) {
        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void strSortEx() {
  printf("Enter 5 strings\n");
  size_t buffer_size = 80;
  char *buffer = (char *)malloc(buffer_size * sizeof(char));
  ssize_t read; // long
  char *strArray[5];
  for (int i = 0; i < 5; ++i) {
    read = getline(&buffer, &buffer_size, stdin);
    buffer[read - 1] = '\0'; // get rid of \n
    strArray[i] = (char *)malloc(read * sizeof(char));
    strcpy(strArray[i], buffer);
  }
  free(buffer);
  sortCharArray(strArray, 5);
  for (int i = 0; i < 5; ++i) {
    printf("%s ", strArray[i]);
    free(strArray[i]);
  }
  printf("\n");
}

void tokenizeEx() {
  char line[80] = "A sentence with spaces";
  char *tokens[20];
  char *pch;

  pch = strtok(line, " ");
  int num = 0;
  while (pch != NULL) {
    printf("Token %d: %s\n", num, pch);
    tokens[num] = pch;
    ++num;
    pch = strtok(NULL, " ");
  }
}

int mainEx(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    printf("argument %d: %s\n", i, argv[i]);
  }
  fprintf(stderr, "printing to standard error\n");
  exit(EXIT_SUCCESS);
}

void memleakEx() {
  char *str = (char *)malloc(100 * sizeof(char));
  char *buffer = NULL;
  size_t buffer_size;
  getline(&buffer, &buffer_size, stdin);
  printf("String: %s\n", buffer);
}
int main() {
  memleakEx();
  exit(0);
  tokenizeEx();
  printfEx();
  fopenEx();
  getlineEx();
  memsetEx();
  strSortEx();

  exit(EXIT_SUCCESS);
}
