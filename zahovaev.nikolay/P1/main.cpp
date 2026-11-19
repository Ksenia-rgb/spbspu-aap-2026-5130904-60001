#include <iostream>
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace zahovaev
{
  const size_t max_size_t = std::numeric_limits< size_t >::max();
  class divRem
  {
  public:
    void operator()(const int next);
    size_t operator()() const;
    bool isCorrectSeq() const noexcept;
  private:
    size_t count_del = 0;
    int before = 0;
    int before_before = 0;
    void div(const int next)
    {
      if (before != 0 && next % before == 0)
      {
        if (count_del == max_size_t)
        {
          throw std::logic_error("Overflow");
        }
        count_del++;
      }
      before_before = before;
      before = next;
    }
  };

  class cntMax
  {
  public:
    void operator()(const int next);
    size_t operator()() const;
  private:
    size_t count_max = 0;
    int max_e = std::numeric_limits< int >::min();
    void cnt(const int next)
    {
      if (next > max_e)
      {
        max_e = next;
        count_max = 1;
      }
      else if (next == max_e)
      {
        if (count_max == max_size_t)
        {
          throw std::logic_error("Overflow");
        }
        count_max++;
      }
    }
  };
};

void zahovaev::divRem::operator()(const int next)
{
  div(next);
}

size_t zahovaev::divRem::operator()() const
{
  return count_del;
}

bool zahovaev::divRem::isCorrectSeq() const noexcept
{
  return before_before != 0;
}

void zahovaev::cntMax::operator()(const int next)
{
  cnt(next);
}

size_t zahovaev::cntMax::operator()() const
{
  return count_max;
}

int main()
{
  int first = 0;
  zahovaev::divRem div_rem;
  zahovaev::cntMax cnt_max;
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
