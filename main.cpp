#include <iostream>
#include <unordered_map>

struct Foo{
  double price;
  int amount;
};

namespace std{
  template <>
  struct hash<Foo>{
    std::size_t operator()(const Foo & foo){
      return hash<decltype(foo.price)>()(foo.price) << 32 ^
             hash<decltype(foo.amount)>()(foo.amount);
    }
  };
}

std::ostream & operator <<(std::ostream & stream, const Foo & foo){
  return stream << foo.price << " " << foo.amount;
}

template<typename K, typename V>
std::ostream & operator <<(std::ostream & stream, const std::unordered_map<K, V> & hashMap){
  stream << "{ ";
  for(auto && kvPair : hashMap){
    stream << "(" << kvPair.first << ", " << kvPair.second << ") ";
  }
  return stream << "}";
}

int main(int argc, char ** args){
  std::unordered_map<std::string, Foo> shoppingList = {
    {"potatis", Foo{10.5, 3}},
    {"socker", Foo{5.2, 2}}
  };
  shoppingList.insert({"socks", Foo{0.2,10}});
  std::cout << shoppingList << std::endl;
}