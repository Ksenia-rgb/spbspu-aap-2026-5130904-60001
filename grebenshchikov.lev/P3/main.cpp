#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{

    // проверка количества аргументов
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
  
  // начало проверки первого аргумента
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

    const int kmax = 10000; // задаем максимальный размер массива
    if (rows * cols > kmax) // проверка на превышение максимального размера
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

    int **mtx = new int* [rows]; // создаем динамический массив
    for (size_t i = 0; i < rows; ++i)
    {
      mtx[i] = new int [cols]; // так же выделяем память под каждый ряд
    }

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (!(in >> mtx[i][j]))
        {
          std::cerr << "Error reading file\n"; // провверка ввода
          return 2;
        }
      }
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
    return 0;
  }

  default:
    std::cout << "First parameter isnt a number or out of range\n"; // если первый арг не 1 и не 2
    return 1;
  }
}

