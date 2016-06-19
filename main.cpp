#include <iostream>
#include <vector>
#include <cmath>

double findMedianSortedArrays(std::vector<int>& v1,
  /* v1 is biggest */         std::vector<int>& v2) {
  if(v1.size() < v2.size()) std::swap(v1,v2);

  //setup itervals
  struct interval {
    std::vector<int>& v;
    int begin, end, i;
  }
  iv1{v1, -1,(int)v1.size() - 1, (int)(v1.size() - 1) / 2},
  iv2{v2, -1,(int)v2.size() - 1, (int)(v2.size() - 1) / 2};

  // total size of both arrays
  int const total_size = v1.size() + v2.size();

  // v2 ran out of values and all of them are either in the small or large set
  // Finding median of v1, considering v2 as all small or large depending on
  // small_set_size
  auto median = [&](auto& v1, auto& v2, int small_set_size){
    // small_set_size should be either 0 of sizeof(v2), correct the index
    int v2_index = small_set_size == 0? small_set_size : small_set_size - 1;
    int median_i = total_size / 2 - small_set_size;
    // In case the small set and large set are the same in size, combine them
    if((median_i + small_set_size) * 2 == total_size){
      // Make sure they overflow on v2 when out of bounds
      int v1val = median_i < v1.size()? v1[median_i    ] : v2[v2_index];
      int v2val = median_i - 1    >= 0? v1[median_i - 1] : v2[v2_index];
      return (v1val + static_cast<double>(v2val)) / 2;
    }
    // If the set are not equal, we know that the result is located on v1
    else {
      return static_cast<double>(v1[median_i]);
    }
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
    return (largest_min() + static_cast<double>(smallest_max())) / 2;
  }
}

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec){
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

int main(int argc, char ** args){

  // Evaluation that algorithm is working
  struct test{
    std::vector<int> v1, v2;
    double median;
  };

  auto tests =
  { test{ {             1, 2, 3 }
        , {-3,-2,-1,-1,-1,-1,-1 }
        , -1.0 //<- median
        }
  , test{ {       2 }
        , { 1, 3, 4 }
        , 2.5 //<- median
        }
  , test{ {  1, 2, 3, 4, 5, 6, 7 }
        , { -3,-2,-1, 1, 2, 3, 4 }
        , 2.5 //<- median
        }
  , test{ {   }
        , { 1 }
        , 1.0 //<- median
        }
  , test{ {       -1 }
        , {  2, 3, 5 }
        , 2.5 //<- median
        }
  , test{ {      }
        , { 2, 3 }
        , 2.5 //<- median
        }
  , test{ { 3, 4 }
        , { 1, 2 }
        , 2.5 //<- median
        }
  , test{ { -1, 0, 1 }
        , {  2, 3, 5 }
        , 1.5 //<- median
        }
  };
  for(auto&& t : tests){
    std::vector<int> v1 = t.v1;
    std::vector<int> v2 = t.v2;
    double median = findMedianSortedArrays(v1, v2);

    // Print trace if not correct
    if(median != t.median){
      std::cout << "v1: " << v1 << std::endl;
      std::cout << "v2: " << v2 << std::endl;
      std::cout << "Expected: " << t.median << std::endl;
      std::cout << "Found:    " <<   median << std::endl;
    }
  }
  return 0;
}