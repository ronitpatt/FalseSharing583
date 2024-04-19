#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char word[] = "helloworld";

// char word[] = {1,2,3,4,5};

int main()
{
  // char *word_two = (char *)malloc(11);
  // char word_three[] = "yelloworld";
  // char *word_four = (char *)malloc(11);

  // strcpy(word_two, "jelloworld");                        
  // strcpy(word_two, "belloworld");    

  // char num = word[1];

  // fprintf(stdout, "%d", num);

  int i;
  for (i = 0; i < sizeof(word); i++) {
    fprintf(stdout,"%c", word[i]);
  }
  fprintf(stdout,"%c", '\n');



  // for (i = 0; i < strlen(word_two); i++) {
  //   fprintf(stdout,"%c", word_two[i]);
  // }
  // fprintf(stdout,"%c", '\n');

  return 1;
}