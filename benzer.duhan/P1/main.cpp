#include <iostream>

namespace benzer {

  void updateEqualRun(
      int value,
      int& previous,
      int& currentRun,
      int& maxRun,
      bool& hasPrevious)
  {
    if (!hasPrevious || value != previous) {
      currentRun = 1;
    } else {
      ++currentRun;
    }

    if (currentRun > maxRun) {
      maxRun = currentRun;
    }

    previous = value;
    hasPrevious = true;
  }

  void updateMonInc(
      int value,
      int previous,
      int& currentRun,
      int& maxRun,
      bool& hasPrevious)
  {
    if (!hasPrevious || value >= previous) {
      ++currentRun;
    } else {
      currentRun = 1;
    }

    if (currentRun > maxRun) {
      maxRun = currentRun;
    }

    hasPrevious = true;
  }

}

int main()
{
  int value = 0;
  int previousEqual = 0;
  int previousMon = 0;

  int currentEqual = 0;
  int maxEqual = 0;

  int currentMon = 0;
  int maxMon = 0;

  bool hasPreviousEqual = false;
  bool hasPreviousMon = false;
  bool hasTerminator = false;

  while (std::cin >> value) {
    if (value == 0) {
      hasTerminator = true;
      break;
    }

    benzer::updateEqualRun(
        value,
        previousEqual,
        currentEqual,
        maxEqual,
        hasPreviousEqual);

    benzer::updateMonInc(
        value,
        previousMon,
        currentMon,
        maxMon,
        hasPreviousMon);

    previousMon = value;
  }

  if (!hasTerminator) {
    std::cerr << "Input error\n";
    return 1;
  }

  std::cout << maxEqual << '\n';
  std::cout << maxMon << '\n';

  return 0;
}
