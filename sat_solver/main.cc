import sat;

#include <iostream>

int main()
{
  const sat::CNF cnf{{1, -2, -3}, {5, 3, 123}};

  const auto sol = cnf.solve();
  if (!sol)
  {
    std::cout << "No solution.\n";
    return 1;
  }
  std::cout << '(';

  for (const auto [id, val] : sol.value())
    std::cout << (val ? id : -id) << ", ";

  std::cout << ")\n";
}
