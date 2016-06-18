#include <iostream>
#include <vector>


int main(int argc, char ** args){
  if(argc < 2){
    std::cout << "Must provide an number" << std::endl;
    return 0;
  }
  int num = std::stoi(args[1]);

  std::vector<int> ar;
  ar.resize(num + 1);
  //iterative since mem complexity O(n)
  for (int i = 1; i <= num; ++i){
      ar[i] = (i & 1) == 1;
      int iover2 = i >> 1;
      if(iover2 > 0) ar[i] += ar[iover2];
  }

  for (int i = 0; i <= num; ++i){
    std::cout << ar[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}