module;

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <optional>
#include <ostream>
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

export namespace utils
{
template <std::ranges::input_range R>
void joinStr(std::ostream &ost, R &&rng, std::string_view sep)
{
  if (std::ranges::empty(rng))
    return;

  ost << *std::ranges::begin(rng);

  for (const auto &el : std::forward<R>(rng) | std::views::drop(1))
    ost << sep << el;
}

template <std::ranges::input_range R>
[[nodiscard]] std::string joinStr(R &&rng, std::string_view sep)
{
  if (std::ranges::empty(rng))
    return {};

  std::ostringstream ss;
  joinStr(ss, std::forward<R>(rng), sep);

  return ss.str();
}
} // namespace utils

using AnswerTy = std::unordered_map<int, bool>;

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

  [[nodiscard]] auto isNeg() const
  {
    if (m_id == 0)
      throw std::runtime_error{"Trying to access unset variable"};
    return m_id > 0;
  }

  [[nodiscard]] bool empty() const noexcept
  {
    return m_id == 0;
  }

  [[nodiscard]] bool eval(bool val) const noexcept
  {
    return m_id > 0 ? val : !val;
  }

  [[nodiscard]] bool eval(const AnswerTy &assigns) const
  {
    return eval(assigns.at(getId()));
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
  Clause(std::convertible_to<Variable> auto... vars) : m_literals{vars...}
  {
    static_assert(sizeof...(vars) == kSize,
                  "Each clause must contain exactly 3 literals");
  }

  void print(std::ostream &ost) const
  {
    ost << '(';
    utils::joinStr(ost, m_literals, " | ");

    ost << ')';
  }

  [[nodiscard]] auto eval(const AnswerTy &assigns) const
  {
    return std::ranges::any_of(
      m_literals, [&](const auto &var) { return var.eval(assigns); });
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

public:
  CNF() = default;
  CNF(std::initializer_list<Clause> ilist)
    : m_clauses(ilist), m_vars{findVars()}
  {}

  void print(std::ostream &ost) const
  {
    utils::joinStr(ost, m_clauses, " &\n");
  }

  [[nodiscard]] std::optional<AnswerTy> solve() const
  {
    AnswerTy assignments;
    if (!solveImpl(m_vars.begin(), assignments))
      return std::nullopt;

    return assignments;
  }

  [[nodiscard]] bool eval(const AnswerTy &assigns) const
  {
    return std::ranges::all_of(
      m_clauses, [&](const auto &clause) { return clause.eval(assigns); });
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

  [[nodiscard]] bool solveImpl(std::unordered_set<int>::const_iterator curId,
                               AnswerTy &assignments) const
  {
    if (curId == m_vars.end())
      return eval(assignments);

    auto &curVal = assignments[*curId];
    const auto nextId = std::next(curId);

    curVal = true;
    if (solveImpl(nextId, assignments))
      return true;

    curVal = false;
    return solveImpl(nextId, assignments);
  }
};

export auto &operator<<(std::ostream &ost, const CNF &cnf)
{
  cnf.print(ost);
  return ost;
}
} // namespace sat
