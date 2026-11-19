#include <iostream>
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace zahovaev
{
  const size_t max_size_t = std::numeric_limits< size_t >::max();
  class DivRem
  {
  public:
    void operator()(int next);
    size_t operator()() const;
    bool isCorrectSeq() const noexcept;
  private:
    size_t count_del_ = 0;
    int before_ = 0;
    int before_before_ = 0;
    void div(int next);
  };

  class CntMax
  {
  public:
    void operator()(int next);
    size_t operator()() const;
  private:
    size_t count_max_ = 0;
    int max_e_ = std::numeric_limits< int >::min();
    void cnt(int next);
  };
};

void zahovaev::DivRem::operator()(const int next)
{
  div(next);
}

size_t zahovaev::DivRem::operator()() const
{
  return count_del_;
}

bool zahovaev::DivRem::isCorrectSeq() const noexcept
{
  return before_before_ != 0;
}

void zahovaev::DivRem::div(const int next)
{
  if (before_ != 0 && next % before_ == 0)
  {
    if (count_del_ == max_size_t)
    {
      throw std::logic_error("Overflow");
    }
    count_del_++;
  }
  before_before_ = before_;
  before_ = next;
}

void zahovaev::CntMax::operator()(const int next)
{
  cnt(next);
}

size_t zahovaev::CntMax::operator()() const
{
  return count_max_;
}

void zahovaev::CntMax::cnt(const int next)
{
  if (next > max_e_)
  {
    max_e_ = next;
    count_max_ = 1;
  }
  else if (next == max_e_)
  {
    if (count_max_ == max_size_t)
    {
      throw std::logic_error("Overflow");
    }
    count_max_++;
  }
}

int main()
{
  int first = 0;
  zahovaev::DivRem div_rem;
  zahovaev::CntMax cnt_max;
  try
  {
    while (std::cin >> first && first != 0)
    {
      div_rem(first);
      cnt_max(first);
    }
  }
  catch (const std::logic_error & e)
  {
    std::cerr << "Your sequence too big\n";
    return 1;
  }

  if (!std::cin)
  {
    std::cerr << "Your sequence is incorrect\n";
    return 1;
  }

  std::cout << cnt_max() << "\n";
  if (!div_rem.isCorrectSeq())
  {
    std::cerr << "Your sequence is not calculated\n";
    return 2;
  }
  else
  {
    std::cout << div_rem() << "\n";
  }
}
