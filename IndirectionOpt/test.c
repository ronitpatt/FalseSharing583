#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char word[] = "helloworldba";
char* word_two;

int main()
{
  // allocate and fill heap array
  word_two = (char *)malloc(13);
  strcpy(word_two, word);                        

  int pid = fork();

  // print heap array
  int j;
  for (j = 0; j < strlen(word_two); j++) {
    if (pid == 0 && !(j % 2)) { //evens
      fprintf(stdout,"%c", word_two[j]);
    } else if (pid > 0 && (j % 2)) { //odds
      fprintf(stdout,"%c", word_two[j]);
    }
  }
  
  fprintf(stdout,"%c", '\n');

  return 1;
}