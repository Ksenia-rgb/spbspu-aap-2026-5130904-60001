#include <iostream>
#include <fstream>

void lft_bot_clk(int* mass, const size_t n, const size_t m)
{
  size_t row = n - 1;
  size_t column = 0;
  size_t left_border = 1;
  size_t bottom_border = n - 1;
  size_t right_border = m - 1;
  size_t top_border = 0;
  size_t direction = 1;
  size_t i = 0;
  size_t nm = n * m;
  while (true) {
    if (i == nm) {
      return;
    }
    mass[row * m + column] -= ++i;
    if (direction == 1) {
      if (row > top_border) {
        row--;
        continue;
      } else {
        direction--;
        top_border++;
      }
    }
    if (direction == 0) {
      if (column < right_border) {
        column++;
        continue;
      } else {
        direction = 3;
        right_border--;
      }
    }
    if (direction == 3) {
      if (row < bottom_border) {
        row++;
        continue;
      } else {
        direction--;
        bottom_border--;
      }
    }
    if (direction == 2) {
      if (column > left_border) {
        column--;
        continue;
      } else {
        direction--;
        left_border++;
      }
    }
    mass[row * m + column] += i--;
  }
}

size_t cnt_col_nsm(int const* mass, const size_t n, const size_t m)
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

void zapis(const int* mass, const size_t n, const size_t m, std::ofstream& as)
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
    int* mass = new int[n * m];
    izmenenie(mass, n, m, is);
    if (!is) {
      std::cerr << "Your massiv is a TRASH";
      return 2;
    }

    lft_bot_clk(mass, n, m);
    size_t c = cnt_col_nsm(mass, n, m);
    std::ofstream as(args[3]);
    if (!as.is_open()) {
      std::cerr << "S.. sorry! I can't open your file(";
      return 2;
    }
    zapis(c, mass, n, m, as);
    if (!as) {
      std::cerr << "My code have UB probably. It means that i already dead";
      return 2;
    }
  } else {
    int mass[10000] = {};
    izmenenie(mass, n, m, is);
    if (!is) {
      std::cerr << "Your massiv is a TRASH";
      return 2;
    }

    lft_bot_clk(mass, n, m);
    size_t c = cnt_col_nsm(mass, n, m);
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
