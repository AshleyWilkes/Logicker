#include "chaiscript/chaiscript.hpp"
#include "worker.h"

#include <iostream>
#include <string>
#include <utility>

int main() {
  chaiscript::ChaiScript chai;
  //1) Precist Reader.chai
  chai.eval_file("reader.chai");
  //2) Precist Puzzle.chai; ten obsahuje read() a conditions()
  chai.eval_file("puzzle.chai");
  //3) Precist Input.chai; ten obsahuje pro zacatek jeden DataInput
  chai.eval_file("input.chai");
  //4) zavolat read(); pomoci jedineho existjiciho Readera cte jediny existujici DataInput; kdyz skonci, obsahuje Reader inicializovany Grid
  auto read = chai.eval<std::function<void()>>("read");
  read();
  //5) Inicializovat Workera; tj. treba bez ohledu na obsah conditions() vytvorit v Readeru prekladaci tabulky a dovedet se parametry pouziteho IntVarArray, pro zacatek pocet IntVars a jednu spolecnou max hodnotu domeny kazde IntVar
  chai.add(chaiscript::bootstrap::standard_library::pair_type<std::pair<int, int>> ("PairInt"));
  auto getInitWorkerData = chai.eval<std::function<std::pair<int, int>()>>("getInitWorkerData");
  Worker worker(getInitWorkerData());
  //6) Inicializovat constrainty jako ze scriptu volatelne c++ metody dle potreb konkretniho Workera
  Worker::initConditions(chai);
  //7) zavolat conditions(); ta vyhodnocuje podle stavu Gridu jednotlive transformace a pak zavola constrainty s vyhodnocenymi argumenty
  auto conditions = chai.eval<std::function<void()>>("conditions");
  //8) pustit workera
  worker.solve();
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
