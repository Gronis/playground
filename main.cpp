#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char ** args){
  std::string token, s = "hej,jag,gillar,kakor";
  std::stringstream ss(s);

  std::string ar[4];
  for(int i = 0; i < 4 && getline(ss,token,','); ++i) ar[i] = token;
  reverse(&ar[0], &ar[4]);
  for(int i = 0; i < 4; ++i) std::cout << ar[i] << " ";
  std::cout << std::endl;  
}