#include "ptoc.h"


float_ b;
array<1,3,float_> a;
word n,d;

int main(int argc, const char* argv[])
{
  pio_initialize(argc, argv);
  b=2*a[n];
  b=d;
  return EXIT_SUCCESS;
}
