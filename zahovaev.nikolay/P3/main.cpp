#include <iostream>
#include <fstream>

size_t cnt_col_nsm(int const * mass, const size_t n, const size_t m)
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

int izmenenie(int * mass, const size_t n, const size_t m, std::ifstream& is)
{
  for (size_t i = 0; i < m*n; i++) {
    is >> mass[i];
  } 
  return 0;
}

void zapis(const int * mass, const size_t n, const size_t m, std::ofstream& as)
{
  as << mass[0];
  for (size_t i = 1; i < m; i++) {
    as << " " << mass[i];
  }
  for (size_t i = 1; i < n; i++) {
    as << "\n" << mass[m*i];
    for (size_t j = 1; j < m; j++) {
      as << " " << mass[m*i + j];
    }
  }
}

void zapis (const size_t counter, std::ofstream& as)
{
  as << counter;
}

int main (int lenargs, char * args[])
{ 
  if (lenargs < 3) {
    std::cerr << "Not enough arguments";
    return 1;  
  } else if (lenargs > 3) {
    std::cerr << "Too many arguments";
    return 1
  }
  short num = 0;
  
  try {
    num = (int)args[1];
    if (!(0 < num && num < 3)) {
      std::cerr << "First parametr is out of range";
      return 1;
    }
  } catch (...) {
    std::cerr << "First parameter is not a number";
    return 1;
  }
  std::ifstream is(args[2]);
 
  if (!is.is_open()) {
    std::cerr << "Гавно ваш файл, переделайте";
    return 1; 
    //В ТЗ нет кода возврата для этого, но по факту эта ошибка относится к вводу переменных окружения
  }
  num--;
  size_t n = 0;
  size_t m = 0;
  is >> n >> m;
  int oshibka = 0;
  if (num) {
    int * mass = new int[n*m];
    oshibka = izmenenie(mass, n, m, is);
    if (!is) {
      std::cerr << "Ваш массив не правелен. Переделайте";
      return 2;
    }

    size_t c = cnt_col_nsm(mass, n, m);
 
    std::ofstream as(args[3]);
    if (!as.is_open()) {
      std::cerr << "Хз, файл не открылся";
      return 2;
    }
    zapis(c, as);
    if (!as) {
      std::cerr << "Вообще такого быть не должно, но, видимо программа что-то не то начала записывать. Вероятно в коде есть UB. Так что если вы это видите, то создатель мёртв";
      return 2;
    }
  } else {
    int mass[10000] = {};
    oshibka = izmenenie(mass, n, m, is);
    if (!is) {
      std::cerr << "Ваш массив не правелен. Переделайте";
      return 2;
    }
    

    size_t c = cnt_col_nsm(mass, n, m);
    std::ofstream as(args[3]);
    if (!as.is_open()) {
      std::cerr << "Хз, файл не открылся";
      return 2;
    }
    zapis(c, as);
    if (!as) {
      std::cerr << "Вообще такого быть не должно, но, видимо программа что-то не то начала записывать. Вероятно в коде есть UB. Так что если вы это видите, то создатель мёртв";
      return 2;
    }
  }
}
