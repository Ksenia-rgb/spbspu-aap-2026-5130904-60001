#include <cstdlib>
#include <iostream>

namespace zhdaneev
{
  int has_sam(const char* first, const char* second)
  {
    for (int i = 0; first[i] != '\0'; i++)
    {
        for (int j = 0; second[j] != '\0'; j++)
        {
            if (first[i] == second[j])
            {
                return 1;
            }
        }
    }

    return 0;
  }
  void lat_rmv(char* result, const char* source)
  {
    int j = 0;

    for (int i = 0; source[i] != '\0'; i++)
    {
        char symbol = source[i];

        if (!((symbol >= 'A' && symbol <= 'Z') ||
              (symbol >= 'a' && symbol <= 'z')))
        {
            result[j] = symbol;
            j++;
        }
    }

    result[j] = '\0';
  }
  char* read_line()
  {
    int capacity = 100;
    int length = 0;

    char* line = static_cast<char*>(std::malloc(capacity));

    if (line == nullptr)
    {
        return nullptr;
    }

    char symbol;

    while (std::cin.get(symbol) && symbol != '\n')
    {
        if (length + 1 >= capacity)
        {
            capacity *= 2;

            char* new_line =
                static_cast<char*>(std::realloc(line, capacity));

            if (new_line == nullptr)
            {
                std::free(line);
                return nullptr;
            }

            line = new_line;
        }

        line[length] = symbol;
        length++;
    }

    line[length] = '\0';
    return line;
  }
}

int main()
{
    char* input = zhdaneev::read_line();

    if (input == nullptr)
    {
        std::cerr << "Memory allocation error\n";
        return 1;
    }

    std::cout << zhdaneev::has_sam(input, "abs") << '\n';

    char* output = static_cast<char*>(std::malloc(100));

    if (output == nullptr)
    {
        std::free(input);
        std::cerr << "Memory allocation error\n";
        return 1;
    }

    zhdaneev::lat_rmv(output, input);

    std::cout << output << '\n';

    std::free(input);
    std::free(output);

    return 0;
}
