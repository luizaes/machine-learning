#include "Ambiente.hpp"

void Ambiente::zeraMatriz() {
  int i, j;

  for (i = 0; i < retornaTamanho(); i++) {
    for (j = 0; j < retornaTamanho(); j++) {
      placa[i][j] = 0;
    }
  }
}

void Ambiente::disporItens(int quantidade) {

  default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> distribution(0,retornaTamanho()-1);
  int x, y, i, j;

  for(i = 0; i < quantidade; i++) {
      x = distribution(generator);
      y = distribution(generator);
      placa[x][y] = 1;
  }

  /*for (i = 0; i < retornaTamanho(); i++) {
    for (j = 0; j < retornaTamanho(); j++) {
      cout << placa[i][j] << " ";
    }
    cout << endl;
  }*/
}

int Ambiente::retornaTamanho() {

  return 20;

}

