module;

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

export module sat;

namespace sat
{
struct InvalidVariableId : public std::logic_error
{
  using std::logic_error::logic_error;
};

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
  Variable(int idx) : m_id{idx}
  {
    if (idx == 0)
      throw InvalidVariableId{"Trying to set variable w/ zero id"};
  }

  [[nodiscard]] auto getId() const noexcept
  {
    return std::abs(m_id);
  }

  [[nodiscard]] auto getVal() const noexcept
  {
    return m_id > 0;
  }

  void negate() noexcept
  {
    m_id = -m_id;
  }

  [[nodiscard]] auto operator!() const noexcept
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

class Conjunct final
{
  using DisjunctTy = std::vector<Variable>;
  static constexpr std::size_t kSize = 3;
  DisjunctTy m_disjuncts{};

public:
  Conjunct(std::initializer_list<Variable> ilist)
  {
    if (ilist.size() != kSize)
      throw std::logic_error{"Unsupported size of conjuct"};

    m_disjuncts.reserve(ilist.size());
    std::move(ilist.begin(), ilist.end(), std::back_inserter(m_disjuncts));
  }

  [[nodiscard]] auto eval() const noexcept
  {
    std::vector<bool> vals(m_disjuncts.size());

    std::transform(m_disjuncts.begin(), m_disjuncts.end(), vals.begin(),
                   [](auto val) { return val.getVal(); });
    return std::accumulate(vals.begin(), vals.end(), false,
                           std::logical_or<>{});
  }

  void print(std::ostream &ost) const
  {
    ost << '(';
    ost << joinStr(m_disjuncts.begin(), m_disjuncts.end(), " | ");

    ost << ')';
  }
};

auto &operator<<(std::ostream &ost, const Conjunct &conj)
{
  conj.print(ost);
  return ost;
}

export class CNF final
{
  std::vector<Conjunct> m_conjuncts{};

public:
  CNF() = default;
  CNF(std::initializer_list<Conjunct> ilist)
  {
    m_conjuncts.reserve(ilist.size());
    std::move(ilist.begin(), ilist.end(), std::back_inserter(m_conjuncts));
  }

  [[nodiscard]] auto eval() const noexcept
  {
    std::vector<bool> vals(m_conjuncts.size());

    std::transform(m_conjuncts.begin(), m_conjuncts.end(), vals.begin(),
                   [](auto val) { return val.eval(); });

    return std::accumulate(vals.begin(), vals.end(), true,
                           std::logical_and<>{});
  }

  void print(std::ostream &ost) const
  {
    ost << joinStr(m_conjuncts.begin(), m_conjuncts.end(), " &\n");
  }
};

export auto &operator<<(std::ostream &ost, const CNF &cnf)
{
  cnf.print(ost);
  return ost;
}
} // namespace sat
