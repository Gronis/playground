#include <iostream>
#include <vector>
#include <chrono>

auto myheapsort = [](auto begin, auto end) {
  // Build the heap
  auto stableize = [&end, &begin] (int parentindex){//log n time
    int rightindex = 0, leftindex = 0;
    int* v = &*begin;
    while(true){ // we have to recursively stabilize child
      rightindex = (parentindex + 1) * 2;
      leftindex = rightindex - 1;
      if(begin + leftindex >= end) break;
      //if there is only one child take that, otherwise take biggest
      int childindex = (begin + rightindex == end || v[leftindex] > v[rightindex])? leftindex : rightindex;
      int& parent = v[parentindex];
      int& child = v[childindex];
      if(child > parent) {
        std::swap(child, parent);
      }
      parentindex = childindex;
    }
  };
  int n = end - begin;
  for (int i = (n - 1) / 2; i >= 0; --i){ 
    stableize(i);
  }
  // Sort the heap
  while(end - begin > 0){
    std::swap(*begin, *(end-- - 1));
    stableize(0);
  }  
};

class Timer {
 public:
  Timer() { restart(); }
  ~Timer() { std::cout << "Time elapsed: " << elapsed() << std::endl << std::endl; }

  void restart() { _start = std::chrono::system_clock::now(); }
  double elapsed() { return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count(); }
 private:
  std::chrono::time_point<std::chrono::system_clock> _start;
};

int main(int argc, char ** args){
  std::vector<int> v1,v2;
  for (int i = 0; i < 4000000; ++i){
    int rand = random() / 10000000;
    v1.push_back( rand);
    v2.push_back( rand);
  }
  {
    Timer t;
    myheapsort(v1.begin(), v1.end()); 
  }
  {
    Timer t;
    sort_heap(v2.begin(), v2.end()); 
  }

  //for (auto && i : v1) std::cout << i << " ";
  //std::cout << std::endl;
  return 0;
}