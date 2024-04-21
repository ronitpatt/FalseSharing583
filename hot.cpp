#include <stdio.h>
#include <unistd.h>

// struct c {
//   int a[4];
//   int b[4];
//   int c[4];
// };
// c obj;

struct c_elem {
  int a;
  int b;
  int c;
};
c_elem hot[4];

c_elem cold[4];


int main()
{
  /*
  Before
  obj.a[3];
  newobj[3].a;
  */
  //printf("%d\n", obj.a[2]);
  //printf("%d", obj.a[2]);
  // for(int i = 0; i < 4; ++i) {
    
  // }

  for(int i = 0; i < 1000; i++){
    hot[i].a = 1;
    hot[i].b = 2;
    hot[i].c = 3;
  }

  for(int i = 0; i < 1000; i++){
    cold[i].a = 1;
    cold[i].b = 2;
    cold[i].c = 3;
  }

  // obj.b[1] = 6;
  // obj.b[2] = 7;
  // obj.b[3] = 8;
  //printf("%p %p %p\n", &arr.a[0], &obj.a[1], &obj.c[0]);
  /*
  0 1 0
  0 1 0
  0 1 0
  0 1 0
  */
  for(int ctr = 0; ctr < 10000; ctr++){
    printf("%d %d %d \n", hot[ctr % 1000].a, hot[ctr % 1000].b, hot[ctr % 1000].c );
  }

  

  return 1;
}