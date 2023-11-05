module;

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
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
    std::move(ilist.begin(), ilist.end(), m_literals.begin());
  }

  [[nodiscard]] auto eval() const noexcept
  {
    std::array<bool, kSize> vals{};

    std::transform(m_literals.begin(), m_literals.end(), vals.begin(),
                   [](auto val) { return val.getVal(); });
    return std::accumulate(vals.begin(), vals.end(), false,
                           std::logical_or<>{});
  }

  void print(std::ostream &ost) const
  {
    ost << '(';
    ost << joinStr(m_literals.begin(), m_literals.end(), " | ");

    ost << ')';
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
  using AnswerTy = std::unordered_map<std::size_t, bool>;

public:
  CNF() = default;
  CNF(std::initializer_list<Clause> ilist)
  {
    m_clauses.reserve(ilist.size());
    std::move(ilist.begin(), ilist.end(), std::back_inserter(m_clauses));
  }

  [[nodiscard]] auto eval() const noexcept
  {
    std::vector<bool> vals(m_clauses.size());

    std::transform(m_clauses.begin(), m_clauses.end(), vals.begin(),
                   [](auto val) { return val.eval(); });

    return std::accumulate(vals.begin(), vals.end(), true,
                           std::logical_and<>{});
  }

  void print(std::ostream &ost) const
  {
    ost << joinStr(m_clauses.begin(), m_clauses.end(), " &\n");
  }

  [[nodiscard]] std::optional<AnswerTy> solve() const
  {
    std::unordered_map<unsigned, bool> assignments;
  }

private:
  [[nodiscard]] bool solveImpl(
    std::unordered_map<unsigned, bool> &assignments) const
  {}
};

export auto &operator<<(std::ostream &ost, const CNF &cnf)
{
  cnf.print(ost);
  return ost;
}
} // namespace sat
