#include <climits>
#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

#include "characteristics.hpp"

namespace {
  constexpr unsigned int RANDOM_SEED = 20261123U;
  constexpr int RANDOM_CASE_COUNT = 300;

  int checksCount = 0;
  int failuresCount = 0;

  sharov::SequenceCharacteristics build(const std::vector< int > &values)
  {
    sharov::SequenceCharacteristics characteristics;
    for (std::size_t i = 0; i < values.size(); ++i) {
      characteristics.add(values[i]);
    }
    return characteristics;
  }

  void printSequence(const std::vector< int > &values)
  {
    std::cout << " sequence:";
    for (std::size_t i = 0; i < values.size(); ++i) {
      std::cout << ' ' << values[i];
    }
    std::cout << "\n";
  }

  void checkMonDec(const std::vector< int > &values, int expected, const char *const label)
  {
    ++checksCount;
    const int actual = build(values).getMonDec();
    if (actual != expected) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": MON-DEC expected " << expected << ", actual " << actual;
      printSequence(values);
    }
  }

  void checkLocMax(const std::vector< int > &values, int expected, const char *const label)
  {
    ++checksCount;
    const int actual = build(values).getLocMax();
    if (actual != expected) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": LOC-MAX expected " << expected << ", actual " << actual;
      printSequence(values);
    }
  }

  void checkDefined(const std::vector< int > &values, bool expected, const char *const label)
  {
    ++checksCount;
    const bool actual = build(values).isLocMaxDefined();
    if (actual != expected) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": LOC-MAX defined expected " << expected << ", actual " << actual;
      printSequence(values);
    }
  }

  void checkSize(const std::vector< int > &values, int expected, const char *const label)
  {
    ++checksCount;
    const int actual = build(values).getSize();
    if (actual != expected) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": size expected " << expected << ", actual " << actual;
      printSequence(values);
    }
  }

  void checkTrue(bool actual, const char *const label)
  {
    ++checksCount;
    if (!actual) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": expected true, actual false\n";
    }
  }

  void checkFalse(bool actual, const char *const label)
  {
    ++checksCount;
    if (actual) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": expected false, actual true\n";
    }
  }

  int bruteMonDec(const std::vector< int > &values)
  {
    int best = 0;
    const std::size_t size = values.size();
    for (std::size_t begin = 0; begin < size; ++begin) {
      for (std::size_t end = begin + 1; end <= size; ++end) {
        bool nonIncreasing = true;
        for (std::size_t i = begin + 1; i < end; ++i) {
          if (values[i] > values[i - 1]) {
            nonIncreasing = false;
            break;
          }
        }
        const int length = static_cast< int >(end - begin);
        if (nonIncreasing && length > best) {
          best = length;
        }
      }
    }
    return best;
  }

  int bruteLocMax(const std::vector< int > &values)
  {
    int count = 0;
    for (std::size_t i = 1; i + 1 < values.size(); ++i) {
      if (values[i - 1] < values[i] && values[i] > values[i + 1]) {
        ++count;
      }
    }
    return count;
  }

  void testMonDec()
  {
    checkMonDec({3, 2, 8, 4, 4, 2, 1}, 5, "MON-DEC pdf example");
    checkMonDec({1}, 1, "MON-DEC single element");
    checkMonDec(std::vector< int >(), 0, "MON-DEC empty sequence");
    checkMonDec({1, 2, 3}, 1, "MON-DEC strictly increasing");
    checkMonDec({1, 1, 1, 1}, 4, "MON-DEC equal elements");
    checkMonDec({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10, "MON-DEC fully decreasing");
    checkMonDec({-1, -2, -3}, 3, "MON-DEC negative decreasing");
    checkMonDec({-3, -2, -1}, 1, "MON-DEC negative increasing");
    checkMonDec({2, 2, 4, 1, 3, 3, 5}, 2, "MON-DEC pdf mon inc sequence");
    checkMonDec({1, 3, 2}, 2, "MON-DEC short sequence");
    checkMonDec({1, 3, 3, 2, 4, 1}, 3, "MON-DEC pdf loc max sequence");
    checkMonDec({INT_MAX, INT_MIN}, 2, "MON-DEC extreme values");
    checkMonDec({INT_MIN, INT_MAX}, 1, "MON-DEC extreme values increasing");
  }

  void testLocMax()
  {
    checkLocMax({1, 3, 2}, 1, "LOC-MAX pdf example");
    checkLocMax({1, 3, 3, 2, 4, 1}, 1, "LOC-MAX pdf plateau example");
    checkLocMax({1}, 0, "LOC-MAX single element");
    checkLocMax({1, 2}, 0, "LOC-MAX two elements increasing");
    checkLocMax({2, 1}, 0, "LOC-MAX two elements decreasing");
    checkLocMax({3, 2, 8, 4, 4, 2, 1}, 1, "LOC-MAX peak inside mon dec sequence");
    checkLocMax({1, 3, 1, 3, 1}, 2, "LOC-MAX two peaks");
    checkLocMax({-3, -1, -2}, 1, "LOC-MAX negative peak");
    checkLocMax({1, INT_MAX, 2}, 1, "LOC-MAX extreme peak");
    checkLocMax({INT_MAX, 1, INT_MAX}, 0, "LOC-MAX equal values are not peaks");
    checkLocMax({1, 2, 1}, 1, "LOC-MAX single peak");
  }

  void testDefinition()
  {
    checkDefined(std::vector< int >(), false, "LOC-MAX undefined for empty sequence");
    checkDefined({1}, true, "LOC-MAX defined for single element");
    checkDefined({1, 2}, true, "LOC-MAX defined for two elements");
    checkSize(std::vector< int >(), 0, "size of empty sequence");
    checkSize({1, 2, 3, 4}, 4, "size of four elements");
  }

  void testPureFunctions()
  {
    checkTrue(sharov::isNonIncreasingStep(2, 1), "step 2 -> 1 is non-increasing");
    checkTrue(sharov::isNonIncreasingStep(2, 2), "step 2 -> 2 is non-increasing");
    checkFalse(sharov::isNonIncreasingStep(2, 3), "step 2 -> 3 is increasing");
    checkFalse(sharov::isNonIncreasingStep(INT_MIN, INT_MAX), "step INT_MIN -> INT_MAX is increasing");
    checkTrue(sharov::isLocalMaximum(1, 3, 2), "1 3 2 has a local maximum");
    checkFalse(sharov::isLocalMaximum(3, 3, 2), "equal left neighbour is not a local maximum");
    checkFalse(sharov::isLocalMaximum(1, 3, 3), "equal right neighbour is not a local maximum");
    checkFalse(sharov::isLocalMaximum(5, 3, 1), "decreasing triple has no local maximum");
    checkTrue(sharov::isLocalMaximum(INT_MIN, INT_MAX, INT_MIN), "extreme values form a local maximum");
  }

  void testRandomAgainstBruteForce()
  {
    std::mt19937 generator(RANDOM_SEED);
    std::uniform_int_distribution< int > lengthDistribution(0, 24);
    std::uniform_int_distribution< int > valueDistribution(-6, 6);
    for (int caseIndex = 0; caseIndex < RANDOM_CASE_COUNT; ++caseIndex) {
      const int length = lengthDistribution(generator);
      std::vector< int > values;
      for (int i = 0; i < length; ++i) {
        values.push_back(valueDistribution(generator));
      }
      const sharov::SequenceCharacteristics characteristics = build(values);
      const int expectedMonDec = bruteMonDec(values);
      const bool expectedDefined = !values.empty();
      const int expectedLocMax = bruteLocMax(values);
      ++checksCount;
      if (characteristics.getMonDec() != expectedMonDec) {
        ++failuresCount;
        std::cout << "FAIL random case " << caseIndex << ": MON-DEC expected " << expectedMonDec << ", actual "
                  << characteristics.getMonDec();
        printSequence(values);
      }
      ++checksCount;
      if (characteristics.isLocMaxDefined() != expectedDefined) {
        ++failuresCount;
        std::cout << "FAIL random case " << caseIndex << ": LOC-MAX defined differs from non-empty sequence";
        printSequence(values);
      }
      ++checksCount;
      if (expectedDefined && characteristics.getLocMax() != expectedLocMax) {
        ++failuresCount;
        std::cout << "FAIL random case " << caseIndex << ": LOC-MAX expected " << expectedLocMax << ", actual "
                  << characteristics.getLocMax();
        printSequence(values);
      }
    }
  }
}

int main()
{
  testMonDec();
  testLocMax();
  testDefinition();
  testPureFunctions();
  testRandomAgainstBruteForce();
  if (failuresCount == 0) {
    std::cout << "ALL TESTS PASSED: " << checksCount << " checks\n";
    return 0;
  }
  std::cout << "TESTS FAILED: " << failuresCount << " of " << checksCount << " checks failed\n";
  return 1;
}
