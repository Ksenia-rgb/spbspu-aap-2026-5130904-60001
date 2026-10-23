#include <iostream>
#include <fstream>
#include <cstdlib>

size_t CNT_COL_NSM(const int * mtx, int rows, int cols)
{
  size_t count = 0;
  for (size_t i = 0; i < cols; ++i)
  {
    size_t flag = 0;
    for (size_t j = 1; j < rows; ++j)
    {
      int preel = mtx[(j-1) * cols + i];
      if (mtx[j * cols + i] == preel)
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
      {
        ++count;
      }
  }
  return count;
}

size_t CNT_COL_NSM(const int * const * mtx, int rows, int cols)
{
  size_t count = 0;
  for (size_t i = 0; i < cols; ++i)
  {
    size_t flag = 0;
    for (size_t j = 1; j < rows; ++j)
    {
      int preel = mtx[j-1][i];
      if (mtx[j][i] == preel)
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      ++count;
    }
  }
  return count;
}

bool UPP_TRI_MTX(const int * mtx, int rows, int cols)
{
  if (rows == 0 || cols == 0)
  {
    return false;
  }
  for (size_t i = 0; i < rows; ++i) 
  {
    for (size_t j = 0; j < cols; ++j)
    {
      if (i > j && mtx[i * cols + j] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

bool UPP_TRI_MTX(const int * const * mtx, int rows, int cols)
{
  if (rows == 0 || cols == 0)
  {
    return false;
  }
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      if (i > j && mtx[i][j] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

void freeMtx(int** mtx, size_t rows)
{
  for (size_t i = 0; i < rows; ++i)
  {
    std::free(mtx[i]);
  }
  std::free(mtx);
}

int main(int argc, char* argv[])
{
  if (argc<4)
  {
    std::cerr << "Not enough arguments";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments";
    return 1;
  } 

  switch (*argv[1])
  {
  case '1':
  {
    std::ifstream in(argv[2]);
    int rows, cols; 
    if (!(in >> rows >> cols) || rows < 0 || cols < 0)
    { 
      std::cerr << "Error reading file\n";
      return 2;
    }

    const int kmax = 10000;
    if (rows * cols > kmax)
    {
      std::cerr << "Matrix size exceeds maximum allowed size\n";
      return 2;
    }

    int mtx[kmax];
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {   
        if (!(in >> mtx[i * cols + j]))
        {
            std::cerr << "Error reading file\n";
            return 2;
        }
      }
    }

    if (UPP_TRI_MTX(mtx, rows, cols))
    {
      std::cout << "true\n";
    }
    else
    {
      std::cout << "false\n";
    }

    std::cout << CNT_COL_NSM(mtx, rows, cols) << '\n';

    std::ofstream out(argv[3]);
    out << rows << " " << cols;
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {   
        out << " " << mtx[i * cols + j];
      }
    }
    std::cout << '\n';
    return 0;
  }
  case '2':
  {
    std::ifstream in(argv[2]);
    int rows, cols;
    if (!(in >> rows >> cols) || rows < 0 || cols < 0)
    {
      std::cerr << "Error reading file\n";
      return 2;
    }

    int **mtx = static_cast< int** >(std::malloc(rows * sizeof(int*)));
    if (mtx == nullptr && rows > 0)
    {
      std::cerr << "Not enough memory\n";
      return 2;
    }
    for (size_t i = 0; i < rows; ++i)
    {
      mtx[i] = static_cast< int* >(std::malloc(cols * sizeof(int)));
      if (mtx[i] == nullptr && cols > 0)
      {
        freeMtx(mtx, i);
        std::cerr << "Not enough memory\n";
        return 2;
      }
    }

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (!(in >> mtx[i][j]))
        {
          std::cerr << "Error reading file\n";
          freeMtx(mtx, rows);
          return 2;
        }
      }
    }

    if (UPP_TRI_MTX(mtx, rows, cols))
    {
      std::cout << "true\n";
    }
    else
    {
      std::cout << "false\n";
    }

    std::cout << CNT_COL_NSM(mtx, rows, cols) << '\n';

    std::ofstream out(argv[3]);
    out << rows << " " << cols;

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        out << " " << mtx[i][j];
      }
    }
    std::cout << '\n';
    freeMtx(mtx, rows);
    return 0;
  }

  default:
    std::cout << "First parameter isnt a number or out of range\n";
    return 1;
  }
}