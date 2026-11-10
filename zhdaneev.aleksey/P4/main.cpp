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
}

int main()
{
    return 0;
}
