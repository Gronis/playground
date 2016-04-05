#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

auto myheapsort = [](auto begin, auto end) {
  int n = end - begin;
  //Build heap
  struct {
    int* begin, * end;
    void stableize(int i){  //log n time
      int rightindex = (i + 1) * 2;
      int leftindex = rightindex - 1;
      if(begin + leftindex < end){
        int* v = begin;
        //if there is only one child take that, otherwise take biggest
        int childindex = (v[leftindex] > v[rightindex] || begin + rightindex == end)? leftindex : rightindex;
        int& parent = v[i];
        int& child = v[childindex];
        if(child > parent){
          std::swap(child, parent);
          // we have to recursively stabilize child in case we swapped
          stableize(childindex);
        }
      }
    }
  } recursive{&*begin,&*end};
  for (int i = (n - 1) / 2; i >= 0; --i){ 
    recursive.stableize(i);
  }

  //sort the heap
  while(recursive.end - recursive.begin > 0){
    std::swap(*recursive.begin,*(recursive.end - 1));
    --recursive.end;
    recursive.stableize(0);
  }  
};

int main(int argc, char ** args){
  std::vector<int> v = {1,10,2,9,6,4,2,34,5,6,75,3,5,6,7,7};
  myheapsort(v.begin(), v.end());
  for (auto && i : v) std::cout << i << " ";
  std::cout << std::endl;
  return 0;
}