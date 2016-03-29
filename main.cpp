#include <iostream>
#include <vector>


int main(int argc, char ** args){
  if(argc < 2){
    std::cout << "Must provide an number" << std::endl;
  }
  int n = std::stoi(args[1]);

  std::vector<int> ar;
  ar.resize(n);

  //iterative since mem complexity O(n)
  for (int i = 1; i <= n; ++i){
    ar[i] = (i & 1) == 1;
    if(i >> 1 > 0) ar[i] += ar[i >> 1];
  }

  for (int i = 0; i <= n; ++i){
    std::cout << ar[i] << " ";
  }
}