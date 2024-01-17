import sat;

#include <iostream>
#include <ranges>

int main()
{
  const sat::CNF cnf{{1, -2, -3}, {5, 3, 123}};

  const auto sol = cnf.solve();
  if (!sol)
  {
    std::cout << "No solution.\n";
    return 1;
  }

  auto &&answer = std::views::transform(*sol, [](const auto &idVal) {
    return idVal.second ? idVal.first : -idVal.first;
  });

  std::cout << '(';
  sat::utils::joinStr(std::cout, answer, ", ");
  std::cout << ")\n";
}
