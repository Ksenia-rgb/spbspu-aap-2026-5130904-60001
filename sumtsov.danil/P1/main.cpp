#include <iostream>

namespace sumtsov
{

  size_t maxOf(size_t a, size_t b)
  {
    return (a > b) ? a : b;
  }

  size_t nextRun(size_t current_run, int value, int prev_value, int mode)
  {
    const int continues = (mode == 0) ? (value == prev_value) : (value >= prev_value);
    return continues ? (current_run + 1) : 1;
  }

  int computeSequenceStats(std::istream & in, size_t & max_eql_run, size_t & max_inc_run)
  {
    int value = 0;
    int prev_value = 0;
    size_t current_eql_run = 0;
    size_t current_inc_run = 0;
    size_t count = 0;

    max_eql_run = 0;
    max_inc_run = 0;

    while ((in >> value) && (value != 0))
    {
      if (count == 0)
      {
        current_eql_run = 1;
        current_inc_run = 1;
      }
      else
      {
        current_eql_run = nextRun(current_eql_run, value, prev_value, 0);
        current_inc_run = nextRun(current_inc_run, value, prev_value, 1);
      }

      max_eql_run = maxOf(max_eql_run, current_eql_run);
      max_inc_run = maxOf(max_inc_run, current_inc_run);

      prev_value = value;
      ++count;
    }

    return in ? 0 : 1;
  }

}

int main()
{
  size_t max_eql_run = 0;
  size_t max_inc_run = 0;

  const int status = sumtsov::computeSequenceStats(std::cin, max_eql_run, max_inc_run);

  if (status != 0)
  {
    std::cerr << "Error: input is not a valid sequence of integers terminated by zero\n";
    return 1;
  }

  std::cout << max_eql_run << '\n';
  std::cout << max_inc_run << '\n';

  return 0;
}
