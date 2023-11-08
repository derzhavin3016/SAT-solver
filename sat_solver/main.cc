import sat;

#include <ios>
#include <iostream>

int main()
{
  sat::CNF cnf{{1, -2, -3}, {5, 3, 123}};
  auto sol = cnf.solve();
  std::cout << std::boolalpha << sol.has_value() << '\n';
  if (!sol)
    return 1;
  for (const auto [id, val] : sol.value())
    std::cout << id << ':' << std::boolalpha << val << std::endl;

  std::cout << cnf << std::endl;
}
