#include <iostream>

int main()
{
  int element = 0;
  int tmp = 0;

  size_t count_eql = 1;
  size_t result_eql = 0;
  size_t count_mon = 1;
  size_t result_mon = 0;
  size_t count_element = 0;
  std::cin >> element;
  if (element != 0)
  {
    count_element++;
    result_eql = 1;
    result_mon = 1;
  }
  tmp = element;
  while (element != 0 && std::cin >> element)
  {
    if (tmp == element)
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

    if (element >= tmp)
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
    tmp = element;
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "Bad input" << "\n";
    return 1;
  }
  int exit_code = 0;
  if (count_element == 0)
  {
    std::cerr << "Bad input\n";
    exit_code = 2;
  }

  std::cout << "Result EQL-SEQ: " << result_eql << "\n";
  std::cout << "Result MON-INC: " << result_mon << "\n";
  return exit_code;
}
