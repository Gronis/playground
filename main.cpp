#include <iostream>
#include <string>
#include <sstream>
#include <exception>

int myAtoi(std::string str) {
  int startindex      = -1;
  int endindex        = -1;
  int number          =  0;
  int digitmultiplier =  1;
  int sign            =  1;

  auto is_whitespace = [] (char c){ return c == ' ' || c == '\t'; };
  auto is_number = [] (char c) { return c >= '0' && c <= '9'; };

  // Find start index at the first non whitespace character
  for(int i = 0; i < str.length() != 0 && startindex < 0; ++i){
    if(!is_whitespace(str[i])) startindex = i;
  }

  // In case we start with a minus sign, skip that and make negative
  if(str[startindex] == '-') {
    ++startindex;
    sign = -1;
  } else if(str[startindex] == '+'){
    ++startindex;
  }

  // Find end index at the first non whitespace character
  endindex = startindex;
  while(endindex < str.length() && is_number(str[endindex])) ++endindex;
  
  // Calculate number, starting from the right most digit.
  for (int i = endindex - 1; i >= startindex; --i){
    int digit = (str[i] - '0');
    int tmp = digit * digitmultiplier;
    // check for overflow

    //std::cout << number << std::endl;
    //std::cout << i << std::endl;
    //std::cout << digitmultiplier << std::endl;
    //std::cout << tmp << std::endl;
    if(number > INT_MAX - tmp || tmp / digitmultiplier != digit || (digitmultiplier % 10 != 0 && number != 0)) {
      return sign == 1? INT_MAX : INT_MIN; 
    }
    digitmultiplier *= 10;
    number += tmp;
  }

  return sign * number;
}

int main(int argc, char ** args){
  auto test = [](const char * p, int sol){ 
    int my_sol = myAtoi(p);
    if(my_sol != sol){
      std::cout << p << ", " << my_sol << " != " << sol << std::endl;  
    }
  };

  test("-2147483647",    -2147483647);
  test("    10522545459", 2147483647);
  test("1",               1);
  test("-1",             -1);
  test("+1",              1);
  test("",                0);
  test("-2147483648",    -2147483648);
  test("2147483647",      2147483647);
  test("2147483648",      2147483647);
  test("010",             10);
  return 0;
}