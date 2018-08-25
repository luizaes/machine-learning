#include <random>
#include <iostream>
#include <chrono>

using namespace std;

class Ambiente {
private:
public:
  int placa[20][20];
  void disporItens(int quantidade);
  int retornaTamanho();
  void zeraMatriz();
};
