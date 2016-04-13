#include <stdio.h>

int lengthOfLongestSubstring(char* s) {
  int sol = 0;
  char used_characters[128];
  char* start_p = s;
  char* end_p = s;
  for(char* i = used_characters; i < used_characters + 128; ++i){
      *i = 0;
  }
  while(*end_p != '\0'){
    char current_char = *end_p;
    if(used_characters[current_char]){
      int current_sol = end_p - start_p;
      //check length if current solution is a better solution
      if(current_sol > sol) sol = current_sol;
      // search for repeated character, and remove every in the way
      while(*start_p != current_char){
        used_characters[*start_p] = 0;
        ++start_p;
      } 
      // move away from that character, it is still in use, so dont reset it
      ++start_p;
    } else  used_characters[current_char] = 1;
    ++end_p;
  }
  if(end_p - start_p > sol) sol = end_p - start_p;
  return sol;
} 

int main(){
  printf("%d\n", lengthOfLongestSubstring("abcabcabc"));
}
