#include <iostream>
#include <fstream>

int izmenenie(int * mass, const size_t n, const size_t m, std::ifstream& is)
{
  for (size_t i = 0; i < m*n; i++) {
    is >> mass[i];
  } 
  return 0;
}

void zapis(const int * mass, const size_t n, const size_t m, std::ofstream& as, char * args[])
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
int main (int lenargs, char * args[])
{ 
  if (lenargs != 4) {
    std::cerr << "Кол-во переменных не 3, переделайте";
    return 1;  
  }  
  short num = 0;
  
  try {
    num = args[1][0]-48;
    if (!(0 < num && num < 3)) {
      std::cerr << "Ваша переменная не подходит, должно быть 1 или 2: переделывать";
      return 1;
    }
  } catch (...) {
    std::cerr << "Первая переменная должна быть 1 или 2. Переделайте";
    return 1;
  }
  std::ifstream is(args[2]);
 
  if (!is.is_open()) {
    std::cerr << "Гавно ваш файл, переделайте";
    return 1;
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
    //Некие действия над массивом
    //.
    //.
    std::ofstream as(args[3]);
    if (!as.is_open()) {
      std::cerr << "Хз, файл не открылся";
      return 2;
    }
    zapis(mass, n, m, as, args);
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
    //Некие действия над массивом
    //.
    //.
    std::ofstream as(args[3]);
    if (!as.is_open()) {
      std::cerr << "Хз, файл не открылся";
      return 2;
    }
    zapis(mass, n, m, as, args);
    if (!as) {
      std::cerr << "Вообще такого быть не должно, но, видимо программа что-то не то начала записывать. Вероятно в коде есть UB. Так что если вы это видите, то создатель мёртв";
      return 2;
    }
  }
}
