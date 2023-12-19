#include <iostream>

/**
 * storage: static
 * linkage: external
 * scope: file
 *
 * (referencing declaration)
 */
extern char *a;

/**
 * storage: static
 * linkage: internal
 * scope: file
 */
const char *const e = "in file main.cpp: const char *const e -> (static,internal,file)";

extern const char *const f;

char *return_b();
const char *const return_e();
char *static_local();
char *automatic_local();

int main()
{
  std::cout << a << std::endl;
  std::cout << return_b() << std::endl;
  std::cout << static_local() << std::endl;
  std::cout << automatic_local() << std::endl;
  std::cout << e << std::endl;
  std::cout << return_e() << std::endl;
  std::cout << f << std::endl;
}
