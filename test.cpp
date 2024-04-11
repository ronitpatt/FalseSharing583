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
c_elem arr[3];

int main()
{
  /*
  Before
  obj.a[3];
  newobj[3].a;
  */
  int a = arr[2].b;
  return 1;
}