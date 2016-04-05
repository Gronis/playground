#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
  std::vector<std::vector<int>> v;
  std::sort(nums.begin(), nums.end());

  int n = nums.size();
  int last_v1 = INT_MIN;

  for (int i = 0; i < n - 2; ++i){
    int v1 = nums[i];
    if(v1 == last_v1) continue;
    last_v1 = v1;
    int startindex = i + 1;
    int endindex = n - 1;
    while(startindex < endindex){
      int v2 = nums[startindex];
      int v3 = nums[endindex];
      int sum = v1 + v2 + v3;
      if(sum == 0){
        v.push_back( {v1,v2, v3});
        std::cout << "{" << v1 << "," << v2 << "," << v3 << "}" << std::endl;
        while(nums[endindex] == v3 && endindex > startindex) --endindex;
      } else if(sum > 0){
        while(nums[endindex] == v3 && endindex > startindex) --endindex;
      } else{
        while(nums[startindex] == v2 && endindex > startindex) ++startindex;
      }
    }
  }
  return v;
}

int main(int argc, char ** args){
  std::vector<int> v = {-1, 0, 1, 2, -1, -4};
  //std::vector<int> v = {8,-15,-2,-13,8,5,6,-3,-9,3,6,-6,8,14,-9,-8,-9,-6,-14,5,-7,3,-10,-14,-12,-11,12,-15,-1,12,8,-8,12,13,-13,-3,-5,0,10,2,-11,-7,3,4,-8,9,3,-10,11,5,10,11,-7,7,12,-12,3,1,11,9,-9,-4,9,-12,-6,11,-7,4,-4,-12,13,-8,-12,2,3,-13,-12,-8,14,14,12,9,10,12,-6,-1,8,4,8,4,-1,14,-15,-7,9,-14,11,9,5,14};
  threeSum(v);
  return 0;
}