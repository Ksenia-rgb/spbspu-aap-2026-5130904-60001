#include <iostream>
#include <fstream>
#include <new>
#include <string>

namespace davydkina
{

  int checkColumn(const int *matrix, const size_t rows, const size_t cols, const size_t col)
  {
    for (int row = 1; row < rows; row++)
    {
      if (matrix[(row) * cols + col] == matrix[(row - 1) * cols + col])
      {
          return 0;
      }
    }

    return 1;
  }

  int countColumns(const int *matrix, const size_t rows, const size_t cols)
  {
    size_t result = 0;

    for (size_t col = 0; col < cols; col++)
    {
        result += checkColumn(matrix, rows, cols, col);
    }

    return result;
  }

  int checkDiagonal(const int *matrix, const size_t rows, const size_t cols,
                  const size_t start_row, const size_t start_col)
  {
    size_t row = start_row;
    size_t col = start_col;
    size_t length = 0;

    while (row < rows && col < cols)
    {
        if (matrix[(row) * cols + col] == 0)
        {
            return 0;
        }

        length++;
        row++;
        col++;
    }

    if (length < 2)
    {
        return 0;
    }

    return 1;
  }

  int countDiagonals(const int *matrix, const size_t rows, const size_t cols)
  {
    size_t result = 0;

    for (size_t col = 0; col < cols; col++)
    {
        result += checkDiagonal(matrix, rows, cols, 0, col);
    }

    for (size_t row = 1; row < rows; row++)
    {
        result += checkDiagonal(matrix, rows, cols, row, 0);
    }

    return result;
  }
}

int main(int argc, char *argv[])
{
  const size_t max_size = 10000;

  if (argc != 4)
  {
    std::cerr << "error: expected 3 arguments\n";
    return 1;
  }

  int num = 0;
  size_t pos = 0;
  std::string argument = argv[1];

  try
  {
    num = std::stoi(argument, &pos);
  }
  catch (const std::exception&)
  {
    std::cerr << "error: first argument must be 1 or 2\n";
    return 1;
  }

  if (pos != angument.length() || (num != 1 && num != 2))
  {
    std::cerr << "error: first argument must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);

  if (!input)
  {
    std::cerr << "error: cannot open input file\n";
    return 2;
  }

  int input_rows = 0;
  int input_cols = 0;

  if (!(input >> input_rows >> input_cols) ||
      input_rows < 0 || input_cols < 0 ||
      ((input_rows == 0) != (input_cols == 0)))
  {
    std::cerr << "error: invalid matrix\n";
    return 2;
  }

  const size_t rows = static_cast<std::size_t>(input_rows);
  const size_t cols = static_cast<std::size_t>(input_cols);

  if (cols != 0 && rows > std::numeric_limits<std::size_t>::max() / cols)
  {
    std::cerr << "error: invalid matrix\n";
    return 2;
  }

  const size_t size = rows * cols;

  int fixed[max_size];
  int *matrix = fixed;
  int *dynamic_matrix = nullptr;

  if (num == 2 && size > 0)
  {
    try
    {
      dynamic_matrix = new int[size];
      matrix = dynamic_matrix;
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "error: not enough memory\n";
      return 2;
    }
  }

  for (size_t i = 0; i < size; i++)
  {
    if (!(input >> matrix[i]))
    {
      std::cerr << "error: invalid matrix\n";

      if (num == 2 && size > 0)
      {
        delete[] matrix;
      }

        return 2;
    }
  }

  char extra = '\0';

  const size_t columns_result = davydkina::countColumns(matrix, rows, cols);
  const size_t diagonals_result = davydkina::countDiagonals(matrix, rows, cols);

  std::ofstream output(argv[3]);

  if (!output)
  {
    std::cerr << "error: cannot open output file\n";

    if (num == 2 && size > 0)
    {
      delete[] matrix;
    }

    return 2;
  }

  output << columns_result << '\n';
  output << diagonals_result << '\n';

  if (!output)
  {
    std::cerr << "error: cannot write output file\n";

    if (num == 2 && size > 0)
    {
      delete[] matrix;
    }

    return 2;
  }
 
  if (num == 2 && size > 0)
  {
    delete[] dynamic_matrix;
  }

  return 0;
}
