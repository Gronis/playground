#include <iostream>
#include <vector>
#include <cmath>

std::size_t bin_search(std::vector<int>& v, int val){
  auto lower = 0UL, upper = v.size() - 1;
  while(lower < upper){
    auto half = (upper - lower) / 2;
    if(half < 2) half = 1;
    if(v[lower + half] > val) upper -= half;
    else                      lower += half;
  }
  if(lower == 0            && v[lower] > val) return -1;
  //if(lower == v.size() - 1 && v[lower] < val) return v.size();
  return lower;
}

double findMedian_inner(std::vector<int>& v1, std::vector<int>& v2) {
  int i1 = 0;
  int i2 = 0;
  int size_both = v1.size() + v2.size();
  int half_size_both = size_both / 2;
  int steps = v1.size();
  int lower_bound_size = 0;
  do{
    lower_bound_size = i1 + 1 + i2 + 1;
    steps = steps > 1? steps / 2 : 1;
    if(lower_bound_size > half_size_both) i1 -= steps;
    else                                  i1 += steps;
    i2 = bin_search(v2, v1[i1]);
    std::cout << "i1: " << i1 << ", i2: " << i2 << std::endl;
  } while(abs(lower_bound_size - half_size_both) > 1);

  // extract median
  int highest_low = i2 == -1 || v1[i1] > v2[i2]? v1[i1] : v2[i2];
  i2++; i1++;
  int lowest_high = i2 > v2.size() || v1[i1] < v2[i2]? v1[i1] : v2[i2];
  if(lower_bound_size * 2 > size_both){
    return highest_low;
  }
  else if(lower_bound_size  * 2 < size_both){
    return lowest_high;
  }
  else{
    return (lowest_high + highest_low) / 2;
  }
}

double findMedianSortedArrays(std::vector<int>& v1,
                              std::vector<int>& v2) {
  return v1.size() >= v2.size()? findMedian_inner(v1, v2) :
                                 findMedian_inner(v2, v1);
}

int main(int argc, char ** args){
  std::vector<int> v1 = {0,5,6,7,8,9};
  std::vector<int> v2 = {0,1,2,3,4};
  std::cout << findMedianSortedArrays(v1,v2) << std::endl;
  return 0;
}