import sat;

#include <iostream>

int main()
{
  sat::CNF cnf{{1, 2, -3}, {5, 3, 123}};
  std::cout << cnf << std::endl;
}
