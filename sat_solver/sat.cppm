module;

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

export module sat;

namespace sat
{

template <std::input_iterator It>
[[nodiscard]] std::string joinStr(It beg, It end, std::string_view sep)
{
  if (beg == end)
    return {};
  std::ostringstream ss;
  ss << *beg;
  ++beg;

  std::for_each(beg, end, [&](const auto &elem) {
    ss << sep;
    ss << elem;
  });

  return ss.str();
}

class Variable final
{
  int m_id{};

public:
  Variable() = default;
  Variable(int idx) noexcept : m_id{idx}
  {}

  [[nodiscard]] auto getId() const noexcept
  {
    return std::abs(m_id);
  }

  [[nodiscard]] auto getVal() const
  {
    if (m_id == 0)
      throw std::runtime_error{"Trying to access unset variable"};
    return m_id > 0;
  }

  [[nodiscard]] bool empty() const noexcept
  {
    return m_id == 0;
  }

  void set() noexcept
  {
    m_id = getId();
  }

  void reset() noexcept
  {
    set();
    negate();
  }

  void negate() noexcept
  {
    m_id = -m_id;
  }

  [[nodiscard]] bool eval(bool val) const noexcept
  {
    return m_id > 0 ? val : !val;
  }

  [[nodiscard]] auto operator!() const
  {
    return !getVal();
  }

  void print(std::ostream &ost) const
  {
    ost << (m_id > 0 ? "" : "~") << 'v' << getId();
  }
};

auto &operator<<(std::ostream &ost, const Variable &var)
{
  var.print(ost);
  return ost;
}

class Clause final
{
  static constexpr std::size_t kSize = 3;
  using LiteralsTy = std::array<Variable, kSize>;
  LiteralsTy m_literals{};

public:
  Clause(std::initializer_list<Variable> ilist)
  {
    std::ranges::move(ilist, m_literals.begin());
  }

  [[nodiscard]] auto eval() const noexcept
  {
    return std::ranges::any_of(
      m_literals | std::views::transform([](auto val) { return val.getVal(); }),
      std::identity{});
  }

  void print(std::ostream &ost) const
  {
    ost << '(';
    ost << joinStr(m_literals.begin(), m_literals.end(), " | ");

    ost << ')';
  }

  [[nodiscard]] auto begin() const noexcept
  {
    return m_literals.begin();
  }

  [[nodiscard]] auto end() const noexcept
  {
    return m_literals.end();
  }
};

auto &operator<<(std::ostream &ost, const Clause &conj)
{
  conj.print(ost);
  return ost;
}

export class CNF final
{
  std::vector<Clause> m_clauses{};
  std::unordered_set<int> m_vars{};
  using AnswerTy = std::unordered_map<int, bool>;

public:
  CNF() = default;
  CNF(std::initializer_list<Clause> ilist)
    : m_clauses(ilist), m_vars{findVars()}
  {}

  [[nodiscard]] auto eval() const noexcept
  {
    return std::ranges::all_of(
      m_clauses | std::views::transform([](auto val) { return val.eval(); }),
      std::identity{});
  }

  void print(std::ostream &ost) const
  {
    ost << joinStr(m_clauses.begin(), m_clauses.end(), " &\n");
  }

  [[nodiscard]] std::optional<AnswerTy> solve() const
  {
    AnswerTy assignments;
    if (!solveImpl(m_vars.begin(), assignments))
      return std::nullopt;

    return assignments;
  }

private:
  [[nodiscard]] std::unordered_set<int> findVars() const noexcept
  {
    std::unordered_set<int> ids;
    for (const auto &clause : m_clauses)
      for (const auto &var : clause)
        ids.insert(var.getId());

    return ids;
  }

  [[nodiscard]] bool eval(const AnswerTy &assigns) const
  {
    bool res{true};
    for (const auto &clause : m_clauses)
    {
      bool resClause{false};
      for (const auto &var : clause)
        resClause = resClause || var.eval(assigns.at(var.getId()));

      res = res && resClause;
    }
    return res;
  }

  [[nodiscard]] bool solveImpl(std::unordered_set<int>::const_iterator curId,
                               AnswerTy &assignments) const
  {
    if (curId == m_vars.end())
      return eval(assignments);

    assignments[*curId] = true;
    if (solveImpl(std::next(curId), assignments))
      return true;

    assignments[*curId] = false;
    return solveImpl(std::next(curId), assignments);
  }
};

export auto &operator<<(std::ostream &ost, const CNF &cnf)
{
  cnf.print(ost);
  return ost;
}
} // namespace sat
