#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>

using namespace std;

vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
  int i = 0;
  int j = 0;
  int n = nums1.size();
  int m = nums2.size();
  vector<int> solution;

  while(k > 0){
    int l1 = -1;
    int l2 = -1;
    int reverse = 1;
    for(int l = i; l < n && n - l + m - j >= k; ++l){
      if(l1 == -1 || nums1[l] > nums1[l1]) l1 = l;
    }
    for(int l = j; l < m && m - l + n - i >= k; ++l){
      if(l2 == -1 || nums2[l] > nums2[l2]) l2 = l;
    }
    int i1 = l1, i2 = l2;
    if(l1 != -1 && l2 != -1 && nums1[l1] == nums2[l2]) {
      //look ahead
      for(; i1 < n && i2 < m && nums1[i1] == nums2[i2]; i1++) i2++;
      if(i1 == n || i2 == m){
        int j1 = l1, j2 = l2;
        //look behind
        for(; j1 >= i && j2 >= j && nums1[j1] == nums2[j2]; j1--) j2--;
        bool never_1 = j1 < i && i1 == n;
        bool never_2 = j2 < j && i2 == m;
        if(never_1) i1 = -1;
        if(never_2) i2 = -1;
        if(!never_1 && !never_2) { reverse = -1; i1 = j1; i2 = j2; }
      }
    }
    if(i2 == -1 || (i1 != -1 && nums1[i1] * reverse > nums2[i2] * reverse)) {
      solution.push_back(nums1[l1]);
      i = l1 + 1;
    }
    else if (i1 == -1 || (i2 != -1 && nums1[i1] * reverse < nums2[i2] * reverse)) {
      solution.push_back(nums2[l2]);
      j = l2 + 1;
    }
    k--;
  }
  return solution;
}



template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec){
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

int main(int argc, char ** args){
   std::vector<int> num1 = {4,6,9,1,0,6,3,1,5,2,8,3,8,8,4,7,2,0,7,1,9,9,0,1,5,9,3,9,3,9,7,3,0,8,1,0,9,1,6,8,8,4,4,5,7,5,2,8,2,7,7,7,4,8,5,0,9,6,9,2}; std::vector<int> num2 = {9,9,4,5,1,2,0,9,3,4,6,3,0,9,2,8,8,2,4,8,6,5,4,4,2,9,5,0,7,3,7,5,9,6,6,8,8,0,2,4,2,2,1,6,6,5,3,6,2,9,6,4,5,9,7,8,0,7,2,3}; int k = 60;
   cout << std::vector<int>{9,9,9,9,9,9,9,9,9,9,9,9,9,8,8,6,8,8,4,4,5,7,5,2,8,2,7,7,7,4,8,5,0,9,6,9,2,0,2,4,2,2,1,6,6,5,3,6,2,9,6,4,5,9,7,8,0,7,2,3} << endl;

//   std::vector<int> num1 = {5,0,2,1,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3}; std::vector<int> num2 = {7,6,7,1,0,1,0,5,6,0,5,0}; int k = 31;
//   cout << std::vector<int>{7,6,7,5,1,0,2,1,0,1,0,5,6,0,5,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3,0} << endl;

//   std::vector<int> num1 = {2,5,6,4,4,0}; std::vector<int> num2 = {7,3,8,0,6,5,7,6,2}; int k = 15;
//   cout << std::vector<int>{7,3,8,2,5,6,4,4,0,6,5,7,6,2,0} << endl;

//   std::vector<int> num1 = {2}; std::vector<int> num2 = {2,9,7,7,9,2,5,5,1,9,6,8,4,5,1,3,3,1,4,8,7,1,8,2,2,9,6,9,9,7,4,0,6,5,9,0,4,7,6,8,0,1,6}; int k = 44;
//   cout << std::vector<int>{2,9,7,7,9,2,5,5,2,1,9,6,8,4,5,1,3,3,1,4,8,7,1,8,2,2,9,6,9,9,7,4,0,6,5,9,0,4,7,6,8,0,1,6} << endl;

//   std::vector<int> num1 = {}; std::vector<int> num2 = {1}; int k = 1;

//   std::vector<int> num1 = {3, 4, 6, 5}; std::vector<int> num2 = {9, 1, 2, 5, 8, 3}; int k = 5;

//   std::vector<int> num1 = {6,7}; std::vector<int> num2 = {6,0,4}; int k = 5;

//   std::vector<int> num1 = {3, 9}; std::vector<int> num2 = {8, 9}; int k = 3;
   cout << maxNumber(num1,num2,k) << endl;
   
   return 0;
}