#include "chaiscript/chaiscript.hpp"

#include <iostream>
#include <string>

int main() {
  chaiscript::ChaiScript chai;
  chai.eval_file("script.chai");
}

/*double function(int i, double j) {
  return i * j;
}

std::string print(const std::string& str) {
  return str + ", Ashley\n";
}

int main() {
  chaiscript::ChaiScript chai;
  chai.add(chaiscript::fun(&function), "function");
  chai.add(chaiscript::fun(&print), "print");
  //chai.add(chaiscript::fun(&std::string::operator==), "equals");

  std::cout << chai.eval<double>("function(4, 2.5);") << '\n';
  chai.eval(R"(
    puts(function(1,3));
    puts('\n');
    puts(function(6,14)); 
    //puts('\n');
    //puts(function(1,3) + '\n' + '\n');
  )");
  chai.eval(R"(
    puts(print("hello"));
  )");
  chai.eval_file("script.chai");
}*/
