#include <algorithm>
#include <iostream>

namespace sumtsov
{

  struct SequenceResult
  {
    bool valid;
    size_t maxEqlRun;
    size_t maxIncRun;
  };

  SequenceResult analyzeSequence(std::istream & in)
  {
    SequenceResult result{ false, 0, 0 };

    bool hasPrev = false;
    int prevValue = 0;
    size_t currentEqlRun = 0;
    size_t currentIncRun = 0;

    int value = 0;
    bool terminated = false;

    while (in >> value)
    {
      if (value == 0)
      {
        terminated = true;
        break;
      }

      if (!hasPrev)
      {
        currentEqlRun = 1;
        currentIncRun = 1;
      }
      else
      {
        currentEqlRun = (value == prevValue) ? (currentEqlRun + 1) : 1;
        currentIncRun = (value >= prevValue) ? (currentIncRun + 1) : 1;
      }

      result.maxEqlRun = std::max(result.maxEqlRun, currentEqlRun);
      result.maxIncRun = std::max(result.maxIncRun, currentIncRun);

      prevValue = value;
      hasPrev = true;
    }

    result.valid = terminated;
    return result;
  }

}

int main()
{
  sumtsov::SequenceResult result = sumtsov::analyzeSequence(std::cin);

  if (!result.valid)
  {
    std::cerr << "Error: input is not a valid sequence of integers terminated by zero\n";
    return 1;
  }

  std::cout << result.maxEqlRun << '\n';
  std::cout << result.maxIncRun << '\n';

  return 0;
}
