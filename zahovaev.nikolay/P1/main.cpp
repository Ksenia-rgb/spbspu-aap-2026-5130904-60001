#include <iostream>
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace zahovaev
{
  const size_t max_size_t = std::numeric_limits< size_t >::max();

  class InterfaceForSeq
  {
  public:
    virtual void operator()(int next) = 0;
    virtual size_t operator()() const = 0;
    virtual bool isCorrectSeq() const noexcept = 0;
    virtual ~InterfaceForSeq() = default;
  };

  class DivRem final: public InterfaceForSeq
  {
  public:
    void operator()(int next) override;
    size_t operator()() const override;
    bool isCorrectSeq() const noexcept override;
  private:
    size_t count_del_ = 0;
    int before_ = 0;
    int before_before_ = 0;
    void div(int next);
  };

  class CntMax final: public InterfaceForSeq
  {
  public:
    void operator()(int next) override;
    size_t operator()() const override;
    bool isCorrectSeq() const noexcept override;
  private:
    size_t count_max_ = 0;
    int max_e_ = std::numeric_limits< int >::min();
    void cnt(int next);
  };

  InterfaceForSeq* getParam(int id)
  {
    switch (id)
    {
    case 3:
      return new CntMax();
    case 11:
      return new DivRem();
    default:
      throw std::logic_error("Can't create object with your id");
    }
  }

  void clearParams(InterfaceForSeq** params, size_t size = 2) noexcept
  {
    for (size_t i = 0; i < size; i++)
    {
      delete params[i];
    }
    delete[] params;
  }

  InterfaceForSeq** makeParams(const int params_ids[], size_t count_params)
  {
    InterfaceForSeq** params = new zahovaev::InterfaceForSeq* [count_params]
    {
    };
    try
    {
      size_t i = 0;
      for (; i < count_params; i++)
      {
        params[i] = getParam(params_ids[i]);
      }
    }
    catch (...)
    {
      clearParams(params, count_params);
      throw;
    }
    return params;
  }
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

bool zahovaev::CntMax::isCorrectSeq() const noexcept
{
  return count_max_ > 0;
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
  const size_t count_params = 2;
  int params_ids[count_params] = {3, 11};
  zahovaev::InterfaceForSeq** params = nullptr;
  try
  {
    params = zahovaev::makeParams(params_ids, count_params);
  }
  catch (...)
  {
    std::cerr << "Sorry, i cant make mass(((";
    return 3;
  }

  int first = 0;
  try
  {
    while (std::cin >> first && first != 0)
    {
      for (size_t i = 0; i < count_params; i++)
      {
        (*params[i])(first);
      }
    }
  }
  catch (const std::logic_error& e)
  {
    zahovaev::clearParams(params);
    std::cerr << "Your sequence too big\n";
    return 1;
  }

  if (!std::cin)
  {
    zahovaev::clearParams(params);
    std::cerr << "Your sequence is incorrect\n";
    return 1;
  }

  bool all_params_are_calculated = true;
  for (size_t i = 0; i < count_params; i++)
  {
    if (params[i]->isCorrectSeq())
    {
      std::cout << (*params[i])() << "\n";
      continue;
    }
    all_params_are_calculated = false;
  }
  if (!all_params_are_calculated)
  {
    zahovaev::clearParams(params);
    std::cerr << "Your sequence is not calculated\n";
    return 2;
  }
  zahovaev::clearParams(params);
}

