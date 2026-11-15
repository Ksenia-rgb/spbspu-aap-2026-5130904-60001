#include <cstddef>
#include <cctype>
#include <cstring>
#include <iostream>

namespace efremenko
{
  const std::size_t k_max_length = 1024;

  // Вариант 7: DIF-LAT
  int count_distinct_latin_letters(const char *str)
  {
    if (str == nullptr)
    {
      return 0;
    }

    int letter_counts[256] = {0};
    int distinct_count = 0;

    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
      const unsigned char c = static_cast<unsigned char>(str[i]);
      
      if (std::isalpha(c))
      {
        const bool is_latin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        
        if (is_latin && letter_counts[c] == 0)
        {
          letter_counts[c] = 1;
          ++distinct_count;
        }
      }
    }

    return distinct_count;
  }

  // Вариант 12: UNI-TWO
  int merge_strings_interleaved(
    const char *str1,
    const char *str2,
    char *result,
    const std::size_t max_length)
  {
    if (str1 == nullptr || str2 == nullptr || result == nullptr || max_length == 0)
    {
      return 1;
    }

    const std::size_t len1 = std::strlen(str1);
    const std::size_t len2 = std::strlen(str2);
    const std::size_t max_len = (len1 > len2) ? len1 : len2;
    std::size_t out_index = 0;

    for (std::size_t i = 0; i < max_len; ++i)
    {
      if (i < len1)
      {
        if (out_index >= max_length - 1)
        {
          return 1;
        }
        result[out_index] = str1[i];
        ++out_index;
      }

      if (i < len2)
      {
        if (out_index >= max_length - 1)
        {
          return 1;
        }
        result[out_index] = str2[i];
        ++out_index;
      }
    }

    result[out_index] = '\0';
    return 0;
  }
}

int main()
{
  using namespace efremenko;

  char input_buffer[k_max_length] = {0};
  char output_buffer[k_max_length] = {0};
  
  std::size_t input_length = 0;
  char current_char = '\0';

  while (std::cin.get(current_char) && current_char != '\n')
  {
    if (input_length >= k_max_length - 1)
    {
      std::cerr << "Error: input string cannot be placed in memory.\n";
      return 1;
    }
    input_buffer[input_length] = current_char;
    ++input_length;
  }
  input_buffer[input_length] = '\0';

  const int dif_lat_result = count_distinct_latin_letters(input_buffer);
  std::cout << dif_lat_result << "\n";

  const char second_string[] = "def_"; 
  
  const int uni_two_result = merge_strings_interleaved(
    input_buffer,
    second_string,
    output_buffer,
    k_max_length);

  if (uni_two_result != 0)
  {
    std::cerr << "Error: result string cannot be placed in memory.\n";
    return 1;
  }

  std::cout << output_buffer << "\n";

  return 0;
}
