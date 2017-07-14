/* Example to call various multiple functions at will */
#include <stdio.h>

void func1() {
  printf("This is function 1\n");
}

void func2() { 
  printf("This if function 2 \n"); 
}

void func3(int num) {
  printf("This if func3 and char argument is: %d\n", num);
}

int main(int argc, char **argv) {
 printf("This APP has acces to void func1(), void func2(), void func3(char c)\n");
 printf("Calling func1() in main() \n");
 func1();

 return 0;
}
