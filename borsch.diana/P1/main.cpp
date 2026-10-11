#include <iostream>

namespace borsch {
  int analyzeSequence();
}

int main()
{
  return borsch::analyzeSequence();
}

int borsch::analyzeSequence()
{
  const int singleElementLength = 1;
  const int invalidInputCode = 1;

  int maxEqualLength = 0;
  int equalLength = 0;
  int maxIncreasingLength = 0;
  int increasingLength = 0;
  int previous = 0;
  int current = 0;
  bool isTerminated = false;

  while (std::cin >> current) {
    if (current == 0) {
      isTerminated = true;
      break;
    }

    if (equalLength > 0 && current == previous) {
      ++equalLength;
    } else {
      equalLength = singleElementLength;
    }

    if (increasingLength > 0 && current >= previous) {
      ++increasingLength;
    } else {
      increasingLength = singleElementLength;
    }

    if (equalLength > maxEqualLength) {
      maxEqualLength = equalLength;
    }
    if (increasingLength > maxIncreasingLength) {
      maxIncreasingLength = increasingLength;
    }

    previous = current;
  }

  if (!isTerminated) {
    std::cerr << "Ошибка: входные данные не являются допустимой последовательностью\n";
    return invalidInputCode;
  }

  std::cout << maxEqualLength << "\n";
  std::cout << maxIncreasingLength << "\n";
  return 0;
}
