import sat;

import <iostream>;
import <array>;

int main()
{
  sat::CNF cnf{{1, 2, 3}};
  std::cout << cnf << std::endl;
}
