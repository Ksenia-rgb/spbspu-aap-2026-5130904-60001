#include "string-ops.hpp"

#include <cctype>

namespace sharov {
  namespace {
    constexpr int kLatinLetterCount = 26;
    constexpr int kCharacterTableSize = 256;
    constexpr int kNumberBufferSize = 16;
    constexpr int kDecimalBase = 10;
    constexpr int kTopCount = 3;

    int getLength(const char *const str)
    {
      int length = 0;
      while (str[length] != '\0') {
        ++length;
      }
      return length;
    }

    int isSpaceCharacter(int character)
    {
      return std::isspace(character) != 0 ? 1 : 0;
    }

    int isDigitCharacter(int character)
    {
      return std::isdigit(character) != 0 ? 1 : 0;
    }

    int isLatinLetter(int character)
    {
      const int isUpper = character >= 'A' && character <= 'Z' ? 1 : 0;
      const int isLower = character >= 'a' && character <= 'z' ? 1 : 0;
      return isUpper != 0 || isLower != 0 ? 1 : 0;
    }

    int toLowerLatin(int character)
    {
      if (character >= 'A' && character <= 'Z') {
        return character - 'A' + 'a';
      }
      return character;
    }

    int isLatinVowel(int character)
    {
      const int lower = toLowerLatin(character);
      return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u' ? 1 : 0;
    }

    int containsCharacter(const char *const str, int character)
    {
      for (int i = 0; str[i] != '\0'; ++i) {
        if (static_cast< unsigned char >(str[i]) == character) {
          return 1;
        }
      }
      return 0;
    }

    int isFirstOccurrence(const char *const str, int character, int position)
    {
      for (int i = 0; i < position; ++i) {
        if (static_cast< unsigned char >(str[i]) == character) {
          return 0;
        }
      }
      return 1;
    }

    int countOccurrences(const char *const str, int character)
    {
      int count = 0;
      for (int i = 0; str[i] != '\0'; ++i) {
        if (static_cast< unsigned char >(str[i]) == character) {
          ++count;
        }
      }
      return count;
    }

    int latinLetterMask(const char *const str)
    {
      int mask = 0;
      for (int i = 0; str[i] != '\0'; ++i) {
        const int character = static_cast< unsigned char >(str[i]);
        if (isLatinLetter(character) != 0) {
          mask = mask | (1 << (toLowerLatin(character) - 'a'));
        }
      }
      return mask;
    }

    int countBits(int mask)
    {
      int count = 0;
      for (int i = 0; i < kLatinLetterCount; ++i) {
        if ((mask & (1 << i)) != 0) {
          ++count;
        }
      }
      return count;
    }

    int writeNumber(int value, char *const dst, int dstCapacity)
    {
      char digits[kNumberBufferSize];
      int count = 0;
      if (value == 0) {
        digits[count] = '0';
        ++count;
      }
      while (value > 0) {
        digits[count] = static_cast< char >('0' + value % kDecimalBase);
        ++count;
        value = value / kDecimalBase;
      }
      if (count >= dstCapacity) {
        return -1;
      }
      for (int i = 0; i < count; ++i) {
        dst[i] = digits[count - 1 - i];
      }
      dst[count] = '\0';
      return count;
    }
  }

  int spcRmv(const char *const src, char *const dst, int dstCapacity)
  {
    int position = 0;
    int pendingSpace = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      const int character = static_cast< unsigned char >(src[i]);
      if (isSpaceCharacter(character) != 0) {
        if (position > 0) {
          pendingSpace = 1;
        }
      } else {
        if (pendingSpace != 0) {
          if (position >= dstCapacity) {
            return -1;
          }
          dst[position] = ' ';
          ++position;
          pendingSpace = 0;
        }
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int decRmv(const char *const src, char *const dst, int dstCapacity)
  {
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      if (isDigitCharacter(static_cast< unsigned char >(src[i])) == 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int latRmv(const char *const src, char *const dst, int dstCapacity)
  {
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      if (isLatinLetter(static_cast< unsigned char >(src[i])) == 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int cmnSym(const char *const src, char *const dst, int dstCapacity)
  {
    const char second[] = "abc ef";
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      const int character = static_cast< unsigned char >(src[i]);
      if (containsCharacter(second, character) != 0 && isFirstOccurrence(src, character, i) != 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int uncSym(const char *const src, char *const dst, int dstCapacity)
  {
    const char second[] = "abc ef";
    int position = 0;
    for (int i = 0; second[i] != '\0'; ++i) {
      const int character = static_cast< unsigned char >(second[i]);
      if (containsCharacter(src, character) == 0 && isFirstOccurrence(second, character, i) != 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = second[i];
        ++position;
      }
    }
    for (int i = 0; src[i] != '\0'; ++i) {
      const int character = static_cast< unsigned char >(src[i]);
      if (containsCharacter(second, character) == 0 && isFirstOccurrence(src, character, i) != 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int repSym(const char *const src, char *const dst, int dstCapacity)
  {
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      const int character = static_cast< unsigned char >(src[i]);
      if (countOccurrences(src, character) > 1 && isFirstOccurrence(src, character, i) != 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int difLat(const char *const src, char *const dst, int dstCapacity)
  {
    return writeNumber(countBits(latinLetterMask(src)), dst, dstCapacity);
  }

  int hasRep(const char *const src, char *const dst, int dstCapacity)
  {
    int found = 0;
    for (int i = 0; src[i] != '\0' && found == 0; ++i) {
      if (countOccurrences(src, static_cast< unsigned char >(src[i])) > 1) {
        found = 1;
      }
    }
    return writeNumber(found, dst, dstCapacity);
  }

  int seqSym(const char *const src, char *const dst, int dstCapacity)
  {
    int found = 0;
    for (int i = 1; src[i] != '\0' && found == 0; ++i) {
      if (src[i] == src[i - 1]) {
        found = 1;
      }
    }
    return writeNumber(found, dst, dstCapacity);
  }

  int rplSym(const char *const src, char *const dst, int dstCapacity)
  {
    const char from = 'c';
    const char to = 'b';
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      if (position >= dstCapacity) {
        return -1;
      }
      if (src[i] == from) {
        dst[position] = to;
      } else {
        dst[position] = src[i];
      }
      ++position;
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int uppLow(const char *const src, char *const dst, int dstCapacity)
  {
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      if (position >= dstCapacity) {
        return -1;
      }
      const int character = static_cast< unsigned char >(src[i]);
      if (character >= 'A' && character <= 'Z') {
        dst[position] = static_cast< char >(toLowerLatin(character));
      } else {
        dst[position] = src[i];
      }
      ++position;
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int uniTwo(const char *const src, char *const dst, int dstCapacity)
  {
    const char second[] = "def ";
    const int firstLength = getLength(src);
    const int secondLength = getLength(second);
    const int maxLength = firstLength > secondLength ? firstLength : secondLength;
    int position = 0;
    for (int i = 0; i < maxLength; ++i) {
      if (i < firstLength) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
      if (i < secondLength) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = second[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int hasSam(const char *const src, char *const dst, int dstCapacity)
  {
    const char second[] = "abs";
    int found = 0;
    for (int i = 0; src[i] != '\0' && found == 0; ++i) {
      if (containsCharacter(second, static_cast< unsigned char >(src[i])) != 0) {
        found = 1;
      }
    }
    return writeNumber(found, dst, dstCapacity);
  }

  int shrSym(const char *const src, char *const dst, int dstCapacity)
  {
    const int mask = latinLetterMask(src);
    int position = 0;
    for (int i = 0; i < kLatinLetterCount; ++i) {
      if ((mask & (1 << i)) == 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = static_cast< char >('a' + i);
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int excSnd(const char *const src, char *const dst, int dstCapacity)
  {
    const char second[] = "abc";
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      if (containsCharacter(second, static_cast< unsigned char >(src[i])) == 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int dgtSnd(const char *const src, char *const dst, int dstCapacity)
  {
    const char second[] = "g1h2k";
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      if (position >= dstCapacity) {
        return -1;
      }
      dst[position] = src[i];
      ++position;
    }
    for (int i = 0; second[i] != '\0'; ++i) {
      if (isDigitCharacter(static_cast< unsigned char >(second[i])) != 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = second[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int repDgt(const char *const src, char *const dst, int dstCapacity)
  {
    int found = 0;
    for (int i = 0; src[i] != '\0' && found == 0; ++i) {
      const int character = static_cast< unsigned char >(src[i]);
      if (isDigitCharacter(character) != 0 && countOccurrences(src, character) > 1) {
        found = 1;
      }
    }
    return writeNumber(found, dst, dstCapacity);
  }

  int rmvVow(const char *const src, char *const dst, int dstCapacity)
  {
    int position = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
      if (isLatinVowel(static_cast< unsigned char >(src[i])) == 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = src[i];
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }

  int frqTop(const char *const src, char *const dst, int dstCapacity)
  {
    int counts[kCharacterTableSize] = {0};
    int firstPositions[kCharacterTableSize] = {0};
    for (int i = 0; i < kCharacterTableSize; ++i) {
      firstPositions[i] = -1;
    }
    for (int i = 0; src[i] != '\0'; ++i) {
      const int character = static_cast< unsigned char >(src[i]);
      if (isSpaceCharacter(character) != 0) {
        continue;
      }
      if (counts[character] == 0) {
        firstPositions[character] = i;
      }
      ++counts[character];
    }
    int selected[kTopCount] = {0};
    int selectedCount = 0;
    while (selectedCount < kTopCount) {
      int best = -1;
      for (int character = 0; character < kCharacterTableSize; ++character) {
        if (counts[character] == 0) {
          continue;
        }
        if (best < 0 || counts[character] > counts[best]
            || (counts[character] == counts[best] && firstPositions[character] < firstPositions[best])) {
          best = character;
        }
      }
      if (best < 0) {
        break;
      }
      selected[selectedCount] = best;
      ++selectedCount;
      counts[best] = 0;
    }
    for (int i = 0; i < selectedCount; ++i) {
      for (int j = i + 1; j < selectedCount; ++j) {
        if (selected[j] < selected[i]) {
          const int temporary = selected[i];
          selected[i] = selected[j];
          selected[j] = temporary;
        }
      }
    }
    if (selectedCount >= dstCapacity) {
      return -1;
    }
    for (int i = 0; i < selectedCount; ++i) {
      dst[i] = static_cast< char >(selected[i]);
    }
    dst[selectedCount] = '\0';
    return selectedCount;
  }

  int latTwo(const char *const src, char *const dst, int dstCapacity)
  {
    const char second[] = "def ghk";
    const int mask = latinLetterMask(src) | latinLetterMask(second);
    int position = 0;
    for (int i = 0; i < kLatinLetterCount; ++i) {
      if ((mask & (1 << i)) != 0) {
        if (position >= dstCapacity) {
          return -1;
        }
        dst[position] = static_cast< char >('a' + i);
        ++position;
      }
    }
    if (position >= dstCapacity) {
      return -1;
    }
    dst[position] = '\0';
    return position;
  }
}
