#include <iostream>
#include <vector>
#include <cmath>

// pretty printer for arrays
template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec){
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

double findMedianSortedArrays(std::vector<int>& v1,
  /* v1 is biggest */         std::vector<int>& v2) {
  if(v1.size() < v2.size()) std::swap(v1,v2);

  //setup itervals
  struct interval {
    std::vector<int>& v;
    int begin;
    int end;
    int i;
  }
  iv1{v1, -1,(int)v1.size() - 1, (int)(v1.size() - 1) / 2},
  iv2{v2, -1,(int)v2.size() - 1, (int)(v2.size() - 1) / 2};

  // total size of both arrays
  int const total_size = v1.size() + v2.size();

  // v2 ran out of values and all of them are either in the small or large set
  // Finding median of v1, considering v2 as all small or large depending on
  // small_set_size
  auto median = [&](auto& v1, auto& v2, int small_set_size){
    int v2_index = small_set_size == 0? small_set_size : small_set_size - 1;
    int index = total_size / 2 - small_set_size;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    // in case the small set and large set are the same in size, combine them
    if((index + small_set_size) * 2 == total_size){
      std::cout << "index:    " << index << std::endl;
      std::cout << "v2_index: " <<  v2_index << std::endl;
      int v1val = index < v1.size()? v1[index] : v2[v2_index];
      int v2val = index - 1 >= 0? v1[index - 1] : v2[v2_index];
      return (v1val + (double)v2val) / 2;
    } else return (double)v1[index];
  };

  // get set to expand if expand is needed
  auto expand_set = [&]() -> interval &{
    if(iv2.i + 1 > iv2.end || v1[iv1.i + 1] < v2[iv2.i + 1]) return iv1;
    else return iv2;
  };

  // get set to reduce if reduce is needed
  auto reduce_set = [&]() -> interval &{
    if(v1[iv1.i] > v2[iv2.i]) return iv1;
    else return iv2;
  };

  // reduce expand the small set
  auto expand = [&](){
    auto& iv = expand_set();
    auto steps = (iv.end - iv.i) / 2;
    if(steps < 1) steps = 1;
    iv.begin = iv.i;
    iv.i = iv.begin + steps;
  };

  // reduce the size of the small set
  auto reduce = [&](){
    auto& iv = reduce_set();
    auto steps = (iv.i - iv.begin) / 2;
    if(steps < 1) steps = 1;
    iv.end = iv.i;
    iv.i = iv.end - steps;
  };

  // num of numbers in the small set
  auto small_set_size = [&](){
    return (int)(iv1.i + iv2.i + 2);
  };

  // num of number in the large set
  auto large_set_size = [&](){
    return total_size - small_set_size();
  };

  // get the largest if the numbers in the small set
  auto largest_min    = [&](){
    int v1val = iv1.i >= 0? v1[iv1.i] : INT_MIN;
    int v2val = iv2.i >= 0? v2[iv2.i] : INT_MIN;
    return std::max(v1val, v2val);
  };

  // get the smallest of the number in the large set
  auto smallest_max   = [&](){
    int v1val = iv1.i + 1 <= iv1.end? v1[iv1.i + 1] : INT_MAX;
    int v2val = iv2.i + 1 <= iv2.end? v2[iv2.i + 1] : INT_MAX;
    return std::min(v1val, v2val);
  };

  // check if small and large set are unbalenced => reduce of extend is needed
  auto unbalanced = [&](){
    return abs(total_size - small_set_size() * 2) > 1;
  };

  std::cout << "v1: " << v1 << std::endl;
  std::cout << "v2: " << v2 << std::endl;
  std::cout << "[" << iv1.begin << " i1: " << iv1.i << " ]" << iv1.end << std::endl;
  std::cout << "[" << iv2.begin << " i2: " << iv2.i << " ]" << iv2.end << std::endl;
  std::cout << "smallest max: " << smallest_max() << std::endl;
  std::cout << "largest  min: " << largest_min()  << std::endl;

  // before we do anything, call median if one list is empty
  if(v2.size() == 0) return median(v1,v2,0);

  // so long as it is unbalanced, or the small set and large sets are wrong
  // reduce and expand the small set until condition is true
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

    // In case one set is fully enclosed, find the median of the other set
    if(iv1.begin > iv1.end)
      return median(v2, v1, iv1.begin);
    if(iv2.begin > iv2.end)
      return median(v1, v2, iv2.begin);
  }
  // Calculate median based on result from algorithm. Intervals for v1
  // and v2 should point to edge values
  if(small_set_size() > large_set_size()){
    return largest_min();
  } else if (small_set_size() < large_set_size()){
    return smallest_max();
  } else {
    return (largest_min() + (double)smallest_max()) / 2;
  }
}

int main(int argc, char ** args){
  // std::vector<int> v1 = { 1, 2, 3};
  // std::vector<int> v2 = {-3,-2,-1,-1,-1,-1,-1};
  // std::vector<int> v1 = { 2 };
  // std::vector<int> v2 = { 1, 3, 4};
  // std::vector<int> v1 = { 1, 2, 3,4,5,6,7};
  // std::vector<int> v2 = {-3,-2,-1,1,2,3,4};
  // std::vector<int> v1 = {};
  // std::vector<int> v2 = {1};
  // std::vector<int> v1 = {-1};
  // std::vector<int> v2 = {2,3,5};
  // std::vector<int> v1 = {};
  // std::vector<int> v2 = {2,3};
  // std::vector<int> v1 = {3,4};
  // std::vector<int> v2 = {1,2};
  std::vector<int> v1 = {-1,0,1};
  std::vector<int> v2 = {2,3,5};
  std::cout << findMedianSortedArrays(v1,v2) << std::endl;
  return 0;
}