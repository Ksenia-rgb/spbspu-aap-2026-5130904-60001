#include <iostream>
#include <cstring>
#include <cctype>
#include <cstddef>
#include <new>

char * removeCommon(const char *input, const char *second, char *output)
{
  size_t j = 0;

  for (size_t i = 0; input[i] != '\0'; i++)
  {
    if (std::strchr(second, input[i]) == nullptr)
    {
      output[j] = input[i];
      j++;
    }
  }

  output[j] = '\0';

  return output;
}

char * removeLatin(const char *input, char *output)
{
  size_t j = 0;

  for (size_t i = 0; input[i] != '\0'; i++)
  {
    if (std::isalpha(static_cast< unsigned char >(input[i])) == 0)
    {
      output[j] = input[i];
      j++;
    }
  }

  output[j] = '\0';

  return output;
}

int main()
{
  const size_t initial_capacity = 16;
  size_t capacity = initial_capacity;
  size_t length = 0;

  char *input = new (std::nothrow) char[capacity];

  if (input == nullptr)
  {
    std::cerr << "error: not enough memory\n";
    return 1;
  }

  char ch = 0;

  while (std::cin.get(ch) && ch != '\n')
  {
    if (length + 1 >= capacity)
    {
      if (capacity > static_cast< std::size_t >(-1) / 2)
      {
        delete[] input;
        std::cerr << "error: not enough memory\n";
        return 1;
      }

      const size_t new_capacity = capacity * 2;

      const char *temp = new (std::nothrow) char[new_capacity];

      if (temp == nullptr)
      {
        delete[] input;
        std::cerr << "error: not enough memory\n";
        return 1;
      }

      std::memcpy(temp, input, length);

      delete[] input;

      input = temp;
      capacity = new_capacity;
    }

    input[length] = ch;
    length++;
  }

  if (std::cin.bad() || (std::cin.fail() && !std::cin.eof()))
  {
    delete[] input;
    std::cerr << "error: input failure\n";
    return 1;
  }

  if (std::cin.eof() && length == 0)
  {
    delete[] input;
    std::cerr << "error: input failure\n";
    return 1;
  }

  input[length] = '\0';

  const char *output = new (std::nothrow) char[length + 1];

  if (output == nullptr)
  {
    delete[] input;
    std::cerr << "error: not enough memory\n";
    return 1;
  }

  const char second[] = "abc";

  std::cout << removeCommon(input, second, output) << '\n';
  std::cout << removeLatin(input, output) << '\n';

  if (!std::cout)
  {
    delete[] input;
    delete[] output;
    std::cerr << "error: output failure\n";
    return 1;
  }

  delete[] input;
  delete[] output;

  return 0;
}

