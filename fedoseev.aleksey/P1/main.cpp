#include <iostream>

int main()
{
  int a = 1;
  int tmp = 0;

  int count_eql = 1;
  int result_eql = -1;
  int count_mon = 1;
  int result_mon = -1;

  bool first = true;

  while (std::cin >> a)
  {
    if (a == 0)
    {
      break;
    }

    if (first)
    {
      count_eql = 1;
      result_eql = 1;
    }
    else
    {
      if (tmp == a)
      {
        count_eql++;
        if (count_eql > result_eql)
        {
          result_eql = count_eql;
        }
      }
      else
      {
        count_eql = 1;
      }
    }

    if (first)
    {
      count_mon = 1;
      result_mon = 1;
    }
    else
    {
      if (a >= tmp)
      {
        ++count_mon;
        if (count_mon > result_mon)
        {
          result_mon = count_mon;
        }
      }
      else
      {
        count_mon = 1;
      }
    }
    tmp = a;
    first = false;
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "Bad input " << "\n";
    return 1;
  }

  bool error = false;
  if (result_eql != -1)
  {
    std::cout << "Result EQL-SEQ: " << result_eql << "\n";
  }
  else
  {
    std::cerr << "Bad input" << "\n";
    error = true;
  }

  if (result_mon != -1)
  {
    std::cout << "Result MON-INC: " << result_mon << "\n";
  }
  else
  {
    std::cerr << "Bad input" << "\n";
    error = true;
  }

  if (error)
  {
    return 2;
  }
}
