#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
  for(int i = 0; i < nums.size(); ++i){
    for(int j = i + 1; j < nums.size(); ++j){
      if(nums[i] + nums[j] == target ) return vector<int>{i,j};
    }
  }
  return vector<int>{-1,-1};
}

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec){
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

int main(int argc, char ** args){
  std::vector<int> v = {-1, 0, 1, 2, -1, -4};
  std::cout << twoSum(v, -3) << std::endl;
  return 0;
}