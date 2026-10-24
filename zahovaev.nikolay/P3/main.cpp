#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstddef>

void lftBotClk(int* mass, const size_t n, const size_t m)
{
  size_t row = n - 1;
  size_t column = 0;
  size_t left_border = 1;
  size_t bottom_border = n - 1;
  size_t right_border = m - 1;
  size_t top_border = 0;

  const size_t direction_up = 1;
  const size_t direction_right = 2;
  const size_t direction_down = 3;
  const size_t direction_left = 4;
  size_t direction = direction_up;
  size_t i = 0;
  const size_t nm = n * m;
  while (i != nm) {
    mass[row * m + column] -= ++i;
    switch (direction){
      case direction_right:
        if (column < right_border) {
          column++;
          continue;
        } else {
          direction = direction_down;
          right_border--;
          [[fallthrough]];
        }
      case direction_up:
        if (row > top_border) {
          row--;
          continue;
        } else {
          direction = direction_left;
          top_border++;
          [[fallthrough]];
        }
      case direction_left:
        if (column > left_border) {
          column--;
          continue;
        } else {
          direction = direction_down;
          left_border++;
          [[fallthrough]];
        }
      case direction_down:
        if (row < bottom_border) {
          row++;
          continue;
        } else {
          direction = direction_left;
          bottom_border--;
        }
    }
    mass[row * m + column] += i--;
  }
}

size_t cntColNsm(int const* mass, const size_t n, const size_t m)
{
  size_t counter = 0;
  int top = 0;
  int bottom = 0;
  bool norm = true;
  for (size_t i = 0; i < m; i++) {
    norm = true;
    top = mass[0 + i];
    for (size_t j = 1; j < n; j++) {
      bottom = mass[j * m + i];
      if (bottom == top) {
        norm = false;
        break;
      }
      top = bottom;
    }
    if (norm) {
      counter++;
    }
  }
  return counter;
}

void izmenenie(int* mass, const size_t n, const size_t m, std::ifstream& is)
{
  for (size_t i = 0; i < m * n; i++) {
    is >> mass[i];
  }
}

void zapis(int const* mass, const size_t n, const size_t m, std::ofstream& as)
{
  as << n;
  as << " " << m;
  for (size_t i = 0; i < n * m; i++) {
    as << " " << mass[i];
  }
}

void zapis(const size_t counter, std::ofstream& as)
{
  as << counter;
}

void zapis(const size_t counter, int const* mass, const size_t n, const size_t m, std::ofstream& as)
{
  zapis(counter, as);
  as << "\n";
  zapis(mass, n, m, as);
}

constexpr size_t maxSize = 10000;
int main(int lenargs, char* args[])
{
  if (lenargs < 4) {
    std::cerr << "Not enough arguments";
    return 1;
  } else if (lenargs > 4) {
    std::cerr << "Too many arguments";
    return 1;
  }
  short num = 0;

  try {
    num = std::stoi(args[1]);
    if (!(0 < num && num < 3)) {
      std::cerr << "First parametr is out of range";
      return 1;
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "First parameter is not a number";
    return 1;
  } catch (const std::out_of_range& e) {
    std::cerr << "First parametr is out of range";
    return 1;
  }
  std::ifstream is(args[2]);

  if (!is.is_open()) {
    std::cerr << "Your file is TRASH";
    return 1;
  }
  num--;
  size_t n = 0;
  size_t m = 0;
  is >> n >> m;
  if (num) {
    int* const mass = new int[n * m];
    izmenenie(mass, n, m, is);
    if (!is) {
      std::cerr << "Your massiv is a TRASH";
      delete[] mass;
      return 2;
    }

    lftBotClk(mass, n, m);
    const size_t c = cntColNsm(mass, n, m);
    std::ofstream as(args[3]);
    if (!as.is_open()) {
      std::cerr << "S.. sorry! I can't open your file(";
      delete[] mass;
      return 2;
    }
    zapis(c, mass, n, m, as);
    if (!as) {
      std::cerr << "My code have UB probably. It means that i already dead";
      delete[] mass;
      return 2;
    }
    delete[] mass;
  } else {
    int mass[maxSize] = {};
    izmenenie(mass, n, m, is);
    if (!is) {
      std::cerr << "Your massiv is a TRASH";
      return 2;
    }

    lftBotClk(mass, n, m);
    const size_t c = cntColNsm(mass, n, m);
    std::ofstream as(args[3]);
    if (!as.is_open()) {
      std::cerr << "S.. sorry! I can't open your file(";
      return 2;
    }
    zapis(c, mass, n, m, as);
    if (!as) {
      std::cerr << "Idk what happened if you see this message";
      return 2;
    }
  }
}
