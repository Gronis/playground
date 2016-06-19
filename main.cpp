#include <iostream>
#include <vector>
#include <cmath>



double findMedianSortedArrays(std::vector<int>& v1,
  /* v1 is biggest */         std::vector<int>& v2) {
  if(v1.size() < v2.size()) std::swap(v1,v2);

  //setup itervals
  struct interval {
    std::vector<int>& v;
    std::size_t begin;
    std::size_t end;
    std::size_t i;
  }
  iv1{v1, 0,v1.size() - 1, v1.size() / 2 - 1},
  iv2{v2, 0,v2.size() - 1, v2.size() / 2 - 1};

  // setup helper functions
  auto expand_set = [&]() -> interval &{
    if(v1[iv1.i + 1] < v2[iv2.i + 1]) return iv1;
    else return iv2;
  };
  auto reduce_set = [&]() -> interval &{
    if(v1[iv1.i] > v2[iv2.i]) return iv1;
    else return iv2;
  };
  auto expand = [&](){
    auto& iv = expand_set();
    auto steps = (iv.end - iv.i) / 2;
    if(steps < 1) steps = 1;
    iv.begin = iv.i + 1;
    iv.i = iv.begin + steps;
  };
  auto reduce = [&](){
    auto& iv = reduce_set();
    auto steps = (iv.i - iv.begin) / 2;
    if(steps < 1) steps = 1;
    iv.end = iv.i;
    iv.i = iv.end - steps;
  };
  int const total_size = v1.size() + v2.size();
  auto small_set_size = [&](){ return (int)(iv1.i + iv2.i + 2); };
  auto large_set_size = [&](){ return total_size - small_set_size(); };
  auto largest_min    = [&](){ return std::max(v1[iv1.i], v2[iv2.i]); };
  auto smallest_max   = [&](){ return std::min(v1[iv1.i + 1], v2[iv2.i + 1]);};
  auto unbalanced = [&](){ return abs(total_size - small_set_size() * 2) > 1;};

  // main algorithm
  while (unbalanced() || largest_min() > smallest_max()){
    if(small_set_size() > large_set_size())  {
      reduce();
    } else {
      expand();
    }
    std::cout << "[" << iv1.begin << " i1: " << iv1.i << " ]" << iv1.end << std::endl;
    std::cout << "[" << iv2.begin << " i2: " << iv2.i << " ]" << iv2.end << std::endl;
    std::cout << "smallest max: " << smallest_max() << std::endl;
    std::cout << "largest  min: " << largest_min()  << std::endl;
  }
  return 0;
}

int main(int argc, char ** args){
  std::vector<int> v1 = {0,5,6,7,8,9,10,11,12};
  std::vector<int> v2 = {0,1,2,3,4,5,6,7,8};
  std::cout << findMedianSortedArrays(v1,v2) << std::endl;
  return 0;
}