#include <iostream>

void (yeet::*func)(int) const = NULL;

class yeet
{
public:
  void my_int_func(int x)
  {
    printf("%d\n", x);
  }
};

int main()
{
  func = &yeet::my_int_func;
  /* call my_int_func (note that you do not need to write (*foo)(2) ) */
  (*func)(1);
  /* but if you want to, you may */
  return 0;
}
