#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstddef>

const size_t direction_up = 1;
const size_t direction_right = 2;
const size_t direction_down = 3;
const size_t direction_left = 4;

bool switch_direction(size_t& direction, size_t& row, size_t& column, size_t& left_border, size_t& bottom_border,
    size_t& right_border, size_t& top_border)
{
  switch (direction) {
  case direction_up:
    if (row > top_border) {
      row--;
      return true;
    } else {
      direction = direction_right;
      top_border++;
      [[fallthrough]];
    }
  case direction_right:
    if (column < right_border) {
      column++;
      return true;
    } else {
      direction = direction_down;
      right_border--;
      [[fallthrough]];
    }
  case direction_down:
    if (row < bottom_border) {
      row++;
      return true;
    } else {
      direction = direction_left;
      bottom_border--;
      [[fallthrough]];
    }
  case direction_left:
    if (column > left_border) {
      column--;
      return true;
    } else {
      direction = direction_up;
      left_border++;
    }
  }
  return false;
}

void lft_bot_clk(int* mass, const size_t n, const size_t m)
{
  size_t row = n - 1;
  size_t column = 0;
  size_t left_border = 1;
  size_t bottom_border = n - 1;
  size_t right_border = m - 1;
  size_t top_border = 0;

  size_t direction = direction_up;
  size_t i = 0;
  const size_t nm = n * m;
  while (i != nm) {
    mass[row * m + column] -= ++i;
    if (!switch_direction(direction, row, column, left_border, bottom_border, right_border, top_border)) {
      mass[row * m + column] += i--;
    }
  }
}

bool is_column_nsm(int const* mass, const size_t n, const size_t m, const size_t i)
{
  int top = mass[0 * m + i];
  int bottom = 0;
  for (size_t j = 1; j < n; j++) {
    bottom = mass[j * m + i];
    if (bottom == top) {
      return false;
    }
    top = bottom;
  }
  return true;
}

size_t cnt_col_nsm(int const* mass, const size_t n, const size_t m)
{
  size_t counter = 0;
  for (size_t i = 0; i < m; i++) {
    counter += is_column_nsm(mass, n, m, i);
  }
  return counter;
}

void write_mass(int* mass, const size_t n, const size_t m, std::ifstream& is)
{
  for (size_t i = 0; i < m * n; i++) {
    is >> mass[i];
  }
}

void send_answer(const size_t c, int const* mass, const size_t n, const size_t m, std::ofstream& as)
{
  as << c << "\n";
  as << n << " " << m;
  for (size_t i = 0; i < n * m; i++) {
    as << " " << mass[i];
  }
}

const size_t maxSize = 10000;
int mass[maxSize] = {};

int* mass2 = nullptr;
int main(int lenargs, char* args[])
{
  if (lenargs < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (lenargs > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  short num = 0;
  try {
    num = std::stoi(args[1]);
    if (!(0 < num && num < 3)) {
      std::cerr << "First parametr is out of range\n";
      return 1;
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } catch (const std::out_of_range& e) {
    std::cerr << "First parametr is out of range\n";
    return 1;
  }

  std::ifstream is(args[2]);
  if (!is.is_open()) {
    std::cerr << "Your file is a TRASH\n";
    return 1;
  }

  num--;
  size_t n = 0;
  size_t m = 0;
  is >> n >> m;
  int* both_mass = nullptr;
  if (num) {
    mass2 = new int[n * m];
    both_mass = mass2;
  } else {
    both_mass = mass;
  }

  write_mass(both_mass, n, m, is);
  if (!is) {
    std::cerr << "Your massiv is a TRASH\n";
    delete[] mass2;
    return 2;
  }

  lft_bot_clk(both_mass, n, m);
  const size_t c = cnt_col_nsm(both_mass, n, m);
  std::ofstream as(args[3]);
  if (!as.is_open()) {
    std::cerr << "S.. sorry! I can't open your file(\n";
    delete[] mass2;
    return 2;
  }
  send_answer(c, both_mass, n, m, as);
  if (!as) {
    std::cerr << "My code have UB probably. It means that i already dead\n";
    delete[] mass2;
    return 2;
  } else {
    as << "\n";
  }
  delete[] mass2;
}
