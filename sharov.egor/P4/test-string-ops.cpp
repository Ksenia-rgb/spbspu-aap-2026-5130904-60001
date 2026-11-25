#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include "string-io.hpp"
#include "string-ops.hpp"
#include "variants.hpp"

namespace {
  constexpr int kBufferSize = 512;
  constexpr int kLongLineLength = 1000;
  constexpr int kExpectedVariantCount = 20;
  int failures = 0;
  int checks = 0;

  using StringOperation = int (*)(const char *source, char *destination, int destinationCapacity);

  struct StringCase {
    const char *name;
    StringOperation operation;
    const char *source;
    const char *expected;
  };

  void checkString(
      const char *const name, StringOperation operation, const char *const source, const char *const expected)
  {
    char buffer[kBufferSize] = {};
    const int length = operation(source, buffer, kBufferSize);
    ++checks;
    if (length < 0) {
      std::cout << "FAIL " << name << " on \"" << source << "\": returned " << length << "\n";
      ++failures;
      return;
    }
    if (std::strcmp(buffer, expected) != 0) {
      std::cout << "FAIL " << name << " on \"" << source << "\": expected \"" << expected << "\", got \"" << buffer
                << "\"\n";
      ++failures;
      return;
    }
    const int expectedLength = static_cast< int >(std::strlen(expected));
    if (length != expectedLength) {
      std::cout << "FAIL " << name << " on \"" << source << "\": length " << length << ", expected " << expectedLength
                << "\n";
      ++failures;
    }
  }

  void checkTooSmall(
      const char *const name, StringOperation operation, const char *const source, const char *const expected)
  {
    const int required = static_cast< int >(std::strlen(expected));
    char buffer[kBufferSize];
    for (int i = 0; i < kBufferSize; ++i) {
      buffer[i] = '#';
    }
    const int length = operation(source, buffer, required);
    ++checks;
    if (length != -1) {
      std::cout << "FAIL " << name << " on \"" << source << "\" with a short buffer: returned " << length
                << ", expected -1\n";
      ++failures;
      return;
    }
    if (buffer[required] != '#') {
      std::cout << "FAIL " << name << " on \"" << source << "\": wrote past the buffer capacity\n";
      ++failures;
    }
  }

  void checkExactCapacity(
      const char *const name, StringOperation operation, const char *const source, const char *const expected)
  {
    const int required = static_cast< int >(std::strlen(expected));
    char buffer[kBufferSize];
    for (int i = 0; i < kBufferSize; ++i) {
      buffer[i] = '#';
    }
    const int length = operation(source, buffer, required + 1);
    buffer[kBufferSize - 1] = '\0';
    ++checks;
    if (length != required || std::strcmp(buffer, expected) != 0) {
      std::cout << "FAIL " << name << " on \"" << source << "\": exact capacity failed, returned " << length
                << ", got \"" << buffer << "\"\n";
      ++failures;
      return;
    }
    if (buffer[required + 1] != '#') {
      std::cout << "FAIL " << name << " on \"" << source << "\": wrote past the buffer capacity\n";
      ++failures;
    }
  }

  const StringCase kPdfCases[] = {
      {"SPC-RMV", sharov::spcRmv, " abc   def   ", "abc def"},
      {"DEC-RMV", sharov::decRmv, "ab c 1d", "ab c d"},
      {"LAT-RMV", sharov::latRmv, "2ab c 1d", "2  1"},
      {"CMN-SYM", sharov::cmnSym, "bc f", "bc f"},
      {"UNC-SYM", sharov::uncSym, "bc fu", "aeu"},
      {"REP-SYM", sharov::repSym, "abfc af eef", "af e"},
      {"DIF-LAT", sharov::difLat, "1abfc11 a2f eef", "5"},
      {"HAS-REP", sharov::hasRep, " abc ", "1"},
      {"SEQ-SYM", sharov::seqSym, "aab b ", "1"},
      {"RPL-SYM", sharov::rplSym, "abc abc", "abb abb"},
      {"UPP-LOW", sharov::uppLow, "AbC aBc", "abc abc"},
      {"UNI-TWO", sharov::uniTwo, "abc abc", "adbecf  abc"},
      {"HAS-SAM", sharov::hasSam, "ABS ABC", "0"},
      {"HAS-SAM", sharov::hasSam, "aBS ABC", "1"},
      {"SHR-SYM", sharov::shrSym, "defzabc", "ghijklmnopqrstuvwxy"},
      {"EXC-SND", sharov::excSnd, "AbC aBc", "AC B"},
      {"DGT-SND", sharov::dgtSnd, "abc def", "abc def12"},
      {"REP-DGT", sharov::repDgt, "abc3 def2 3abc", "1"},
      {"RMV-VOW", sharov::rmvVow, "abc def abc", "bc df bc"},
      {"FRQ-TOP", sharov::frqTop, "abc def ab de a e", "abe"},
      {"LAT-TWO", sharov::latTwo, "abc def", "abcdefghk"},
  };

  const StringCase kEdgeCases[] = {
      {"SPC-RMV", sharov::spcRmv, "", ""},
      {"SPC-RMV", sharov::spcRmv, "   ", ""},
      {"SPC-RMV", sharov::spcRmv, " a  b ", "a b"},
      {"DEC-RMV", sharov::decRmv, "12345", ""},
      {"LAT-RMV", sharov::latRmv, "ABCxyz", ""},
      {"LAT-RMV", sharov::latRmv, "abcXYZ123", "123"},
      {"CMN-SYM", sharov::cmnSym, "", ""},
      {"UNC-SYM", sharov::uncSym, "", "abc ef"},
      {"REP-SYM", sharov::repSym, "abc", ""},
      {"DIF-LAT", sharov::difLat, "", "0"},
      {"DIF-LAT", sharov::difLat, "aA", "1"},
      {"DIF-LAT", sharov::difLat, "abcdefghijklmnopqrstuvwxyz", "26"},
      {"HAS-REP", sharov::hasRep, "abc", "0"},
      {"HAS-REP", sharov::hasRep, "a a", "1"},
      {"SEQ-SYM", sharov::seqSym, "abc", "0"},
      {"SEQ-SYM", sharov::seqSym, "aa", "1"},
      {"RPL-SYM", sharov::rplSym, "ccc", "bbb"},
      {"UPP-LOW", sharov::uppLow, "A1Z z", "a1z z"},
      {"UNI-TWO", sharov::uniTwo, "", "def "},
      {"HAS-SAM", sharov::hasSam, "xyz", "0"},
      {"SHR-SYM", sharov::shrSym, "", "abcdefghijklmnopqrstuvwxyz"},
      {"SHR-SYM", sharov::shrSym, "abcdefghijklmnopqrstuvwxyz", ""},
      {"SHR-SYM", sharov::shrSym, "ABCxyz", "defghijklmnopqrstuvw"},
      {"EXC-SND", sharov::excSnd, "abc", ""},
      {"DGT-SND", sharov::dgtSnd, "", "12"},
      {"REP-DGT", sharov::repDgt, "abc", "0"},
      {"RMV-VOW", sharov::rmvVow, "aeiouAEIOU", ""},
      {"RMV-VOW", sharov::rmvVow, "xyz", "xyz"},
      {"FRQ-TOP", sharov::frqTop, "", ""},
      {"FRQ-TOP", sharov::frqTop, "aaaa", "a"},
      {"FRQ-TOP", sharov::frqTop, "aa bb c", "abc"},
      {"LAT-TWO", sharov::latTwo, "", "defghk"},
      {"LAT-TWO", sharov::latTwo, "ABC", "abcdefghk"},
      {"LAT-TWO", sharov::latTwo, "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"},
  };

  const char *const kExpectedNames[] = {
      "SPC-RMV",
      "DEC-RMV",
      "LAT-RMV",
      "CMN-SYM",
      "UNC-SYM",
      "REP-SYM",
      "DIF-LAT",
      "HAS-REP",
      "SEQ-SYM",
      "RPL-SYM",
      "UPP-LOW",
      "UNI-TWO",
      "HAS-SAM",
      "SHR-SYM",
      "EXC-SND",
      "DGT-SND",
      "REP-DGT",
      "RMV-VOW",
      "FRQ-TOP",
      "LAT-TWO",
  };

  void checkRegistry()
  {
    ++checks;
    if (sharov::getVariantCount() != kExpectedVariantCount) {
      std::cout << "FAIL variant registry: " << sharov::getVariantCount() << " entries, expected "
                << kExpectedVariantCount << "\n";
      ++failures;
    }
    const sharov::VariantEntry *const variants = sharov::getVariants();
    for (int i = 0; i < kExpectedVariantCount; ++i) {
      ++checks;
      if (sharov::findVariant(kExpectedNames[i]) == nullptr) {
        std::cout << "FAIL variant registry: name " << kExpectedNames[i] << " is missing\n";
        ++failures;
      }
    }
    ++checks;
    int duplicate = 0;
    for (int i = 0; i < sharov::getVariantCount() && duplicate == 0; ++i) {
      for (int j = i + 1; j < sharov::getVariantCount() && duplicate == 0; ++j) {
        if (std::strcmp(variants[i].name, variants[j].name) == 0) {
          duplicate = 1;
          std::cout << "FAIL variant registry: duplicate name " << variants[i].name << "\n";
          ++failures;
        }
      }
    }
    char buffer[kBufferSize] = {};
    for (int i = 0; i < sharov::getVariantCount(); ++i) {
      ++checks;
      if (variants[i].apply("abc", buffer, kBufferSize) < 0) {
        std::cout << "FAIL variant registry: " << variants[i].name << " cannot be applied\n";
        ++failures;
      }
    }
    ++checks;
    if (sharov::applyVariant("XXX-XXX", "abc", buffer, kBufferSize) != -1) {
      std::cout << "FAIL variant registry: unknown name is not rejected\n";
      ++failures;
    }
    ++checks;
    if (sharov::getActiveVariantCount() < 1) {
      std::cout << "FAIL variant registry: no active variants\n";
      ++failures;
    }
    for (int i = 0; i < sharov::getActiveVariantCount(); ++i) {
      ++checks;
      const char *const name = sharov::getActiveVariant(i);
      if (sharov::findVariant(name) == nullptr) {
        std::cout << "FAIL active variant " << name << " is not implemented\n";
        ++failures;
      }
    }
  }

  void checkLine(const char *const name, const char *const text, const char *const expected)
  {
    std::istringstream input(text);
    int length = -1;
    char const *const line = sharov::readString(input, &length);
    ++checks;
    if (line == nullptr) {
      std::cout << "FAIL " << name << ": readString returned null\n";
      ++failures;
      return;
    }
    const int expectedLength = static_cast< int >(std::strlen(expected));
    if (std::strcmp(line, expected) != 0) {
      std::cout << "FAIL " << name << ": expected \"" << expected << "\", got \"" << line << "\"\n";
      ++failures;
    } else if (length != expectedLength) {
      std::cout << "FAIL " << name << ": length " << length << ", expected " << expectedLength << "\n";
      ++failures;
    }
    delete[] line;
  }

  void checkLongLine()
  {
    const std::string text(kLongLineLength, 'a');
    std::istringstream input(text + "\n");
    int length = -1;
    char const *const line = sharov::readString(input, &length);
    ++checks;
    if (line == nullptr) {
      std::cout << "FAIL long line: readString returned null\n";
      ++failures;
      return;
    }
    if (length != kLongLineLength || std::strcmp(line, text.c_str()) != 0) {
      std::cout << "FAIL long line: length " << length << ", expected " << kLongLineLength << "\n";
      ++failures;
    }
    delete[] line;
  }

  void checkTwoLines()
  {
    std::istringstream input("first\nsecond\n");
    int firstLength = -1;
    char const *const first = sharov::readString(input, &firstLength);
    int secondLength = -1;
    char const *const second = sharov::readString(input, &secondLength);
    ++checks;
    if (first == nullptr || second == nullptr) {
      std::cout << "FAIL two lines: readString returned null\n";
      ++failures;
    } else if (std::strcmp(first, "first") != 0 || std::strcmp(second, "second") != 0) {
      std::cout << "FAIL two lines: got \"" << first << "\" and \"" << second << "\"\n";
      ++failures;
    } else if (firstLength != static_cast< int >(std::strlen("first"))
        || secondLength != static_cast< int >(std::strlen("second"))) {
      std::cout << "FAIL two lines: lengths " << firstLength << " and " << secondLength << "\n";
      ++failures;
    }
    delete[] first;
    delete[] second;
  }
}

int main()
{
  const int pdfCaseCount = static_cast< int >(sizeof(kPdfCases) / sizeof(kPdfCases[0]));
  for (int i = 0; i < pdfCaseCount; ++i) {
    checkString(kPdfCases[i].name, kPdfCases[i].operation, kPdfCases[i].source, kPdfCases[i].expected);
    checkTooSmall(kPdfCases[i].name, kPdfCases[i].operation, kPdfCases[i].source, kPdfCases[i].expected);
    checkExactCapacity(kPdfCases[i].name, kPdfCases[i].operation, kPdfCases[i].source, kPdfCases[i].expected);
  }
  const int edgeCaseCount = static_cast< int >(sizeof(kEdgeCases) / sizeof(kEdgeCases[0]));
  for (int i = 0; i < edgeCaseCount; ++i) {
    checkString(kEdgeCases[i].name, kEdgeCases[i].operation, kEdgeCases[i].source, kEdgeCases[i].expected);
    checkTooSmall(kEdgeCases[i].name, kEdgeCases[i].operation, kEdgeCases[i].source, kEdgeCases[i].expected);
    checkExactCapacity(kEdgeCases[i].name, kEdgeCases[i].operation, kEdgeCases[i].source, kEdgeCases[i].expected);
  }
  checkRegistry();
  checkLine("empty line", "\n", "");
  checkLine("spaces are kept", "  a  b  \n", "  a  b  ");
  checkLine("no terminator", "no newline", "no newline");
  checkLine("only spaces", "   \n", "   ");
  checkLongLine();
  checkTwoLines();

  std::cout << (failures == 0 ? "PASS" : "FAIL") << ": " << checks << " checks, " << failures << " failures\n";
  return failures == 0 ? 0 : 1;
}
