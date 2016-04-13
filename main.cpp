#include <iostream>
#include <vector>
using namespace std;

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec){
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

vector<int> twoSum(vector<int>& nums, int target) {
  vector<int> nums_sorted = nums;
  sort(nums_sorted.begin(), nums_sorted.end());
  int start_index = 0;
  int end_index = nums_sorted.size() - 1;
  while(start_index < end_index){
    int sum = nums_sorted[start_index] + nums_sorted[end_index];
    if(sum > target) end_index--;
    else if(sum < target) start_index++;
    else {
      //find indicies
      int i = 0;
      int last_target = -1;
      for (;i < nums_sorted.size(); ++i) {
        if(nums[i] == nums_sorted[start_index]) {
          last_target = end_index;
          break;
        }
        if(nums[i] == nums_sorted[end_index]){
          last_target = start_index;
          break;
        }
      }
      int j = i + 1;
      for (;j < nums_sorted.size(); ++j){
        if(nums[j] == nums_sorted[last_target]) break;
      } 
      return vector<int>{i,j};
    }
  }
  return vector<int>{-1,-1};
}

int main(int argc, char ** args){
  std::vector<int> v = {-1,-2,-3,-4,-5};
  std::cout << twoSum(v, -8) << std::endl;
  return 0;
}