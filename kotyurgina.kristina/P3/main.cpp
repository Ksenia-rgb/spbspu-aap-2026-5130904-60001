#include <iostream>
#include <fstream>
#include <new>
#include <cstddef>

namespace kotyurgina
{
  void increaseWaves(int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        size_t layer = i;
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
        matrix[i * cols + j] += static_cast< int >(layer + 1);
      }
    }
  }

  long long minSumMdg(const int* matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }
    long long minimum_sum = 0;
    const size_t diagonal_count = rows + cols - 1;

    for (size_t diagonal = 0; diagonal < diagonal_count; diagonal++)
    {
      long long diagonal_sum = 0;
      size_t first_row = 0;

      if (diagonal >= cols)
      {
        first_row = diagonal - cols + 1;
      }

      size_t last_row = diagonal;
      if (last_row >= rows)
      {
        last_row = rows - 1;
      }

      for (size_t i = first_row; i <= last_row; i++)
      {
        const size_t j = diagonal - i;
        diagonal_sum += matrix[i * cols + j];
      }
      if (diagonal == 0 || diagonal_sum < minimum_sum)
      {
        minimum_sum = diagonal_sum;
      }
    }
    return minimum_sum;
  }

  int processMatrix(std::istream& input, std::ostream& output, int* matrix, size_t rows, size_t cols)
  {
    const size_t count = rows * cols;

    for (size_t i = 0; i < count; i++)
    {
      if (!(input >> matrix[i]))
      {
        std::cerr << "invalid matrix elements\n";
        return 2;
      }
    }

    const long long minimum_sum = minSumMdg(matrix, rows, cols);
    output << minimum_sum << '\n';

    increaseWaves(matrix, rows, cols);

    output << rows << ' ' << cols;
    for (size_t i = 0; i < count; i++)
    {
      output << ' ' << matrix[i];
    }
    output << '\n';

    return 0;
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

  int input_rows = 0;
  int input_cols = 0;
  if (!(input >> input_rows >> input_cols) || input_rows < 0 || input_cols < 0)
  {
    std::cerr << "invalid matrix dimensions\n";
    return 2;
  }

  const size_t rows = static_cast< size_t >(input_rows);
  const size_t cols = static_cast< size_t >(input_cols);

  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "cannot open output file\n";
    return 2;
  }

  if (num == '1')
  {
    const size_t max_elements = 10000;
    if (rows != 0 && cols > max_elements / rows)
    {
      std:: cerr << "matrix is too large\n";
      return 2;
    }

    int matrix[max_elements] = {};
    return kotyurgina::processMatrix(input, output, matrix, rows, cols);
  }
  try
  {
    const size_t count = rows * cols;
    int* const matrix = new int[count];

    const int result = kotyurgina::processMatrix(input, output, matrix, rows, cols);

    delete[] matrix;
    return result;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "cannot allocate memory\n";
    return 2;
  }
}
