#include <iostream>
#include <string>
#include <sstream>

void reverse(std::string::iterator begin, std::string::iterator end){
  end--;
  while(begin < end){
    char tmp = *begin;
    *begin = *end;
    *end = tmp;
    begin++; end--;
  }
}

void reverse_words(std::string& s){
  auto start = s.begin();
  for(auto it = s.begin(); it < s.end(); ++it){
    if(*it == ' '){
      reverse(start, it);
      start = it + 1;
    }
  }
  if(start < s.end()) reverse(start, s.end());
  reverse(s.begin(), s.end());
}

int main(int argc, char ** args){
  std::string token, s = "hej jag gillar kakor";
 
  std::cout << s << std::endl;
  reverse_words(s);
  std::cout << s << std::endl;
}