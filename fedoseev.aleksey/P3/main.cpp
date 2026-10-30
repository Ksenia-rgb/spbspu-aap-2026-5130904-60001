#include <iostream>
#include <fstream>

void processMatrix(int * matrix, size_t rows, size_t cols)
{
  int k = 1;
  size_t top = 0;
  size_t bottom = rows - 1;
  size_t left = 0;
  size_t right = cols - 1;
  while (top <= bottom && left <= right)
  {
    for (size_t i = bottom; i > top; --i) 
    {
      matrix[i * cols + left] -= k;
      ++k;
    }
    ++left;
    for (size_t i = left; i <= right; ++i) 
    {
      matrix[top * cols + i] -= k;
      ++k;
    }
    ++top;
    if (top <= bottom) 
    {
      for (size_t i = top; i <= bottom; ++i)
      {
        matrix[i * cols + right] -= k;
        ++k;
      }
      --right;
    }
    if (left <= right)
    {
      for (size_t i = right; i > left; --i)
      {
        matrix[cols * bottom + i] -= k;
        ++k;
      }
      --bottom;
    }
  }
}
bool checkLowerTriangular(const int * matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = i + 1; j < cols; ++j) 
    {
      if (matrix[i * cols + j] != 0) 
      {
        return false;
      }
    }
  }
  return true;
}


int main(int argc, char* argv[])
{
  const size_t maxSize = 10000;
  if (argc < 4) 
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  int num = 0;
  try 
  {
    num = std::stoi(argv[1]);
    if (num > 2 || num < 1) 
    {
      std::cerr << "First parameter is out of range\n";
      return 1;
    } 
  } catch (...) {
    std::cerr << "First parametr is not a number\n";
    return 1;
  }

  std::ifstream fin(argv[2]);
  if (!fin.is_open()) 
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  
  if (!(fin >> rows >> cols)) {
    std::cerr << "Cannot read file\n";
    return 2;
  }
  if (rows == 0 || cols == 0) 
  {
    std::ofstream fout(argv[3]);
    if (!fout.is_open()) {
      std::cerr << "Cannot open output file\n";
      return 2;
    }
    fout << "0 0\n";
    return 0;
  }

  int * matrix = nullptr;
  bool dynamic = false;
  int staticMatrix[maxSize] = {};
  if (num == 1) 
  {
    if (rows * cols > maxSize) 
    {
      std::cerr << "Matrix is too large\n";
    }
    matrix = staticMatrix;
  } else {
    matrix = new int [rows * cols];
    dynamic = true;
  }

  for (int i = 0; i < rows; ++i) 
  {
    for (int j = 0; j < cols; ++j) 
    {
      int value = 0;
      if (!(fin >> value)) 
      {
        std::cerr << "Invalid input\n";
        if (dynamic) 
        {
          delete [] matrix;
        }
        return 2;
      }
      matrix[i * cols + j] = value;
    }
  }

  fin.close();
  bool isLower = checkLowerTriangular(matrix, rows, cols);
  processMatrix(matrix, rows, cols);

  std::ofstream fout(argv[3]);
  if (!fout.is_open()) {
    std::cerr << "Cannot open output file\n";
    if (dynamic)
    {
      delete [] matrix;
    }
    return 2;
  }

  fout << rows << " " << cols << " ";
  if (isLower) 
  {
    std::cout << "true\n";
  } else {
    std::cout << "false\n";
  }
  for (int i = 0; i < rows; ++i) 
  {
    for (int j = 0; j < cols; ++j) 
    {
      fout << matrix[i * cols + j] << " ";
    }
  }
  fout.close();
  if (dynamic) 
  {
    delete [] matrix;
  }
}

