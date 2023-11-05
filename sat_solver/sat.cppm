module;

#include <algorithm>
#include <iterator>

#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

export module sat;

namespace sat
{
struct InvalidVariableId : public std::logic_error
{
  using std::logic_error::logic_error;
};

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
  using ConjTy = std::vector<Variable>;
  static constexpr std::size_t kSize = 3;
  ConjTy m_conj{};

public:
  Conjunct(std::initializer_list<Variable> ilist)
  {
    if (ilist.size() != kSize)
      throw std::logic_error{"Unsupported size of conjuct"};

    m_conj.reserve(ilist.size());
    std::move(ilist.begin(), ilist.end(), std::back_inserter(m_conj));
  }

  [[nodiscard]] auto eval() const noexcept
  {
    std::vector<bool> vals(m_conj.size());

    std::transform(m_conj.begin(), m_conj.end(), vals.begin(),
                   [](auto val) { return val.getVal(); });
    return std::accumulate(vals.begin(), vals.end(), false,
                           std::logical_or<>{});
  }

  void print(std::ostream &ost) const
  {
    ost << '(';
    std::copy(m_conj.begin(), m_conj.end(),
              std::ostream_iterator<Variable>(ost, " | "));

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
  explicit CNF(std::initializer_list<Conjunct> ilist)
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
    std::copy(m_conjuncts.begin(), m_conjuncts.end(),
              std::ostream_iterator<Conjunct>(ost, " &\n"));
  }
};

export auto &operator<<(std::ostream &ost, const CNF &cnf)
{
  cnf.print(ost);
  return ost;
}

} // namespace sat
