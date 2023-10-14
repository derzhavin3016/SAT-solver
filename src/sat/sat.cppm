export module sat;

import <tuple>;
import <stdexcept>;
import <string>;
import <cmath>;

namespace sat
{
struct InvalidVariableId : public std::logic_error
{
  using std::logic_error::logic_error;
};

export class Variable final
{
  int m_id{};

public:
  explicit Variable(int idx) : m_id{idx}
  {
    if (idx == 0)
      throw InvalidVariableId{"Trying to set variable w/ zero id"};
  }

  [[nodiscard]] auto getId() const
  {
    return std::abs(m_id);
  }

  [[nodiscard]] auto getVal() const
  {
    return m_id;
  }

  [[nodiscard]] auto toString() const
  {
    std::string res = m_id > 0 ? "" : "~";
    res += "v";
    res += std::to_string(getId());
    return res;
  }
};

} // namespace sat
