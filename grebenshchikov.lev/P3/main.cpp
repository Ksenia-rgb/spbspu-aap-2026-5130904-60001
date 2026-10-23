#include <iostream>
#include <fstream>
#include <cstdlib>

bool UPP_TRI_MTX(const int * mtx, int rows, int cols)
{
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

// освобождаем первые rows рядов и сам массив указателей
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
    // если первый арг равен 1 то статический массив
  case '1':
  {
    std::ifstream in(argv[2]); // читаем из файла
    int rows, cols; 
    if (!(in >> rows >> cols) || rows <= 0 || cols <= 0) // проверка на корректность ввода
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

    int mtx[kmax]; // создаем массив статического размера
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {   
        if (!(in >> mtx[i * cols + j])) // проверяем ошибку ввода
        {
            std::cerr << "Error reading file\n";
            return 2;
        }
      }
    }

    if (UPP_TRI_MTX(mtx, rows, cols))
    {
      std::cout << "true";
    }
    else
    {
      std::cout << "false";
    }

    std::ofstream out(argv[3]); // вывод в файл
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
  // если первый арг равен 2 то динамический массив
  case '2':
  {
    std::ifstream in(argv[2]); // читаем из файла
    int rows, cols;
    if (!(in >> rows >> cols))
    {
      std::cerr << "Error reading file\n";
      return 2;
    }

    int **mtx = static_cast< int** >(std::malloc(rows * sizeof(int*)));
    if (mtx == nullptr)
    {
      std::cerr << "Not enough memory\n";
      return 2;
    }
    for (size_t i = 0; i < rows; ++i)
    {
      mtx[i] = static_cast< int* >(std::malloc(cols * sizeof(int))); // так же выделяем память под каждый ряд
      if (mtx[i] == nullptr)
      {
        freeMtx(mtx, i); // освобождаем уже выделенные ряды
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
          std::cerr << "Error reading file\n"; // провверка ввода
          freeMtx(mtx, rows);
          return 2;
        }
      }
    }

    if (UPP_TRI_MTX(mtx, rows, cols))
    {
      std::cout << "true";
    }
    else
    {
      std::cout << "false";
    }

    std::ofstream out(argv[3]); // вывод в файл
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
    std::cout << "First parameter isnt a number or out of range\n"; // если первый арг не 1 и не 2
    return 1;
  }
}