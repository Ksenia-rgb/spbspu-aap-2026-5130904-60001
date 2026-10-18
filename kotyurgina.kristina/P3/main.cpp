#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "invalid number of argumments\n";
    return 1;
  }
  const std::string num = argv[1];
  if (num != "1" && num != "2")
  {
    std::cerr << "invalid task number\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "cannot open input file\n";
    return 2;
  }
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols))
  {
    std::cerr << "invalid matrix dimensions\n";
    return 2;
  }
  if (rows < 0 || cols < 0)
  {
    std::cerr << "invalid matrix dimensions\n";
    return 2;
  }
  if (num == "1")
  {
    const int max_elements = 10000;
    if (rows != 0 && cols > max_elements / rows)
    {
      std::cerr << "matrix is too large\n";
      return 2;
    }
    int matrix[max_elements] = {};
    for (int i = 0; i < rows * cols; i++)
    {
      if (!(input >> matrix[i]))
      {
        std::cerr << "invalid matrix elements";
        return 2;
      }
      std::cout << matrix[i] << " ";
    }
    std::cout << "\n";
  }
  else
  {
    long long count = rows;
    count *= cols;
    int* matrix = new int[count];
    for (long long i = 0; i < count; i++)
    {
      if (!(input >> matrix[i]))
      {
        std::cerr << "invalid matrix elements";
        delete[] matrix;
        return 2;
      }
    }
    delete[] matrix;
  }
  return 0;
}
