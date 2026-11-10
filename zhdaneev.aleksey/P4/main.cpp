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
}

int main()
{
    return 0;
}
