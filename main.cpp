#include <iostream>
using namespace std;

int lengthOfLongestSubstring(string s) {
  int sol = 0;
  int start_index = 0;
  int end_index = 0;
  bool used_characters[128];
  for(int i = 0; i < 128; ++i){
      used_characters[i] = 0;
  }
  while(end_index < s.length()){
    char current_char = s[end_index];
    //is current character used?
    if(used_characters[current_char]){
      //check length if current solution is a better solution
      int current_sol = end_index - start_index;
      if(current_sol > sol) sol = current_sol;
      // search for repeated character, and remove every in the way
      while(s[start_index] != current_char){
        used_characters[s[start_index]] = 0;
        ++start_index;
      } 
      // move away from that character, it is still in use, so dont reset it
      ++start_index;

    } else used_characters[current_char] = 1;
    ++end_index;
  }
  return max(sol, end_index - start_index);
} 

int main(int argc, char ** args){
  cout << lengthOfLongestSubstring("abcabcabc") << endl;
  return 0;
}