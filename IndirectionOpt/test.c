#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char word[] = "HELLOWORLD";

int main()
{
  char *word_two = (char *)malloc(11);
  // char word_three[] = "yelloworld";
  char *word_four = (char *)malloc(11);

  // strcpy(word_two, "jelloworld");                        
  // strcpy(word_two, "belloworld");    

  int i;
  for (i = 0; i < 15; i++) {
    fprintf(stdout,"%c ", word[i]);
  }
  fprintf(stdout,"%d", '\n');

  // for (i = 0; i < strlen(word_two); i++) {
  //   fprintf(stdout,"%c", word_two[i]);
  // }
  // fprintf(stdout,"%c", '\n');

  return 1;
}