#include <stdio.h>
#include <unistd.h>

struct c {
  int a[4];
  int b[4];
  int c[4];
};
c obj;

// struct c_elem {
//   int a;
//   int a;
//   int b;
//   int c;
// };
// c_elem arr[4];

int main()
{
  /*
  Before
  obj.a[3];
  newobj[3].a;
  */
  //printf("%d\n", obj.a[2]);
  //printf("%d", obj.a[2]);
  for(int i = 0; i < 4; ++i) {
    obj.a[i] = 1;
  }
  // for(int i = 0; i < 4; ++i) {
  //   printf("%d \n", obj.a[i]);
  //   printf("%d \n", obj.b[i]);
  //   printf("%d \n", obj.c[i]);
  // }
  

  return 1;
}