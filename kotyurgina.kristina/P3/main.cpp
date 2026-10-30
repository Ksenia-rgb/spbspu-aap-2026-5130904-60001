#include <iostream>
#include <fstream>
#include <new>

namespace kotyurgina
{
  void increaseWaves(int* matrix, int rows, int cols)
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        int layer = i;
        if (j < layer)
        {
          layer = j;
        }
        if (rows - i - 1 < layer)
        {
          layer = rows - i - 1;
        }
        if (cols - j - 1 < layer)
        {
          layer = cols - j - 1;
        }
        matrix[i * cols + j] += layer + 1;
      }
    }
  }
  long long minSumMdg(const int* matrix, int rows, int cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }
    long long minimum_sum = 0;
    const long long diagonal_count = static_cast< long long >(rows) + cols - 1;
    for (long long diagonal = 0; diagonal < diagonal_count; diagonal++)
    {
      long long diagonal_sum = 0;
      long long first_row = diagonal - cols + 1;
      if (first_row < 0)
      {
        first_row = 0;
      }
      long long last_row = diagonal;
      if (last_row >= rows)
      {
        last_row = rows - 1;
      }
      for (long long i = first_row; i <= last_row; i++)
      {
        const long long j = diagonal - i;
        diagonal_sum += matrix[i * cols + j];
      }
      if (diagonal == 0 || diagonal_sum < minimum_sum)
      {
        minimum_sum = diagonal_sum;
      }
    }
    return minimum_sum;
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "invalid number of argumments\n";
    return 1;
  }

  if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
  {
    std::cerr << "invalid first argument\n";
    return 1;
  }

  const char num = argv[1][0];

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

  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "cannot open output file\n";
    return 2;
  }

  if (num == '1')
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
    }
    const long long minimum_sum = kotyurgina::minSumMdg(matrix, rows, cols);

    output << minimum_sum << '\n';

    kotyurgina::increaseWaves(matrix, rows, cols);

    output << rows << " " << cols << '\n';

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        output << matrix[i * cols + j] << " ";
      }
      output << "\n";
    }
  }
  else
  {
    long long count = rows;
    count *= cols;
    try
    {
      int* const matrix = new int[count];
      for (long long i = 0; i < count; i++)
      {
        if (!(input >> matrix[i]))
        {
          std::cerr << "invalid matrix elements";
          delete[] matrix;
          return 2;
        }
      }
      const long long minimum_sum = kotyurgina::minSumMdg(matrix, rows, cols);

      output << minimum_sum << '\n';

      kotyurgina::increaseWaves(matrix, rows, cols);

      output << rows << " " << cols << '\n';

      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          output << matrix[i * cols + j] << " ";
        }
        output << "\n";
      }

      delete[] matrix;
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "cannot allocate memory\n";
      return 2;
    }
  }

  char extra = '\0';
  if (input >> extra)
  {
    std::cerr << "extra data in input file\n";
    return 2;
  }
  return 0;
}
