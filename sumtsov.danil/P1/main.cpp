#include <algorithm>
#include <iostream>

namespace sumtsov
{

  struct SequenceResult
  {
    bool valid;
    size_t max_eql_run;
    size_t max_inc_run;
  };

  SequenceResult analyzeSequence(std::istream & in)
  {
    SequenceResult result{false, 0, 0};

    bool has_prev = false;
    int prev_value = 0;
    size_t current_eql_run = 0;
    size_t current_inc_run = 0;

    int value = 0;
    bool terminated = false;

    while (in >> value)
    {
      if (value == 0)
      {
        terminated = true;
        break;
      }

      if (!has_prev)
      {
        current_eql_run = 1;
        current_inc_run = 1;
      }
      else
      {
        current_eql_run = (value == prev_value) ? (current_eql_run + 1) : 1;
        current_inc_run = (value >= prev_value) ? (current_inc_run + 1) : 1;
      }

      result.max_eql_run = std::max(result.max_eql_run, current_eql_run);
      result.max_inc_run = std::max(result.max_inc_run, current_inc_run);

      prev_value = value;
      has_prev = true;
    }

    result.valid = terminated;
    return result;
  }

}

int main()
{
  const sumtsov::SequenceResult result = sumtsov::analyzeSequence(std::cin);

  if (!result.valid)
  {
    std::cerr << "Error: input is not a valid sequence of integers terminated by zero\n";
    return 1;
  }

  std::cout << result.max_eql_run << '\n';
  std::cout << result.max_inc_run << '\n';

  return 0;
}
