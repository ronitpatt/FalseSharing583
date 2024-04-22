#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char word[] = "helloworld";
char* word_two;

int main()
{
  // allocate and fill heap array
  word_two = (char *)malloc(11);
  strcpy(word_two, word);                        


  // print heap array
  int j;
  for (j = 0; j < strlen(word_two); j++) {
    fprintf(stdout,"%c", word_two[j]);
  }
  fprintf(stdout,"%c", '\n');

  return 1;
}