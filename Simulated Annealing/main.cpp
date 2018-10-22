#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;

#define NUM_ITERACOES 250000
#define TEMP_INICIAL 5
#define TEMP_FINAL 0.0

struct Clausula {
  int x;
  int y;
  int z;
};

int avaliarSolucao(vector<Clausula> &formula, int solucao[]);

double temp = TEMP_INICIAL;

int main() {

  int num_variaveis, num_clausulas, aux3, cont = 0, num_clausulas_verdade = 0, proximo, auxiliar,num_clausulas_verdade_prox = 0, deltaE;
  string linha, aux, aux2;
  vector<Clausula> formula;
  Clausula c1;
  double a;
  mt19937 generator (chrono::high_resolution_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> distribution(0,1);
  uniform_real_distribution<double> thirdDistribution(0.0,1.0);

  /* Pegando informações do .txt */
  ifstream arquivo;
  arquivo.open("uf250_01.txt");

  for(int i = 0; i < 7; i++) {
    getline(arquivo, linha);
  }
  arquivo >> aux >> aux2 >> num_variaveis >> num_clausulas;
  //cout << num_variaveis << " " <<  num_clausulas << endl;
  int solucao[num_variaveis+1];
  uniform_int_distribution<int> secondDistribution(1,num_variaveis);

  for(int i = 0; i <= num_variaveis; i++) {
    solucao[i] = distribution(generator);
    //cout << solucao[i] << endl;
  }

  for(int i = 0; i < num_clausulas; i++) {
    arquivo >> c1.x >> c1.y >> c1.z >> aux3;
    formula.push_back(c1);
    //cout << c1.x << " " << c1.y << " " << c1.z << endl;
  }

  while(temp > TEMP_FINAL) {

    cont++;

    num_clausulas_verdade = avaliarSolucao(formula, solucao);

    proximo = secondDistribution(generator);
    auxiliar = solucao[proximo];
    solucao[proximo] = solucao[proximo] == 1 ? 0 : 1;

    num_clausulas_verdade_prox = avaliarSolucao(formula, solucao);
    deltaE = num_clausulas_verdade - num_clausulas_verdade_prox; 

    if(deltaE <= 0) {
      // faz nada
    } else {
      if(thirdDistribution(generator) < exp(-deltaE/temp)) {
        // faz nada
      } else {
        solucao[proximo] = auxiliar;
      }
    }

    cout << temp << endl;

    a = log(TEMP_INICIAL-TEMP_FINAL)/log(NUM_ITERACOES);
    temp = TEMP_INICIAL - pow(cont, a);
    //temp_inicial = TEMP_INICIAL - cont * (TEMP_INICIAL - TEMP_FINAL)/NUM_ITERACOES;
  }

  num_clausulas_verdade = avaliarSolucao(formula, solucao);

  cout << num_clausulas_verdade << " de " << num_clausulas << endl;

  return 0;
}

int avaliarSolucao(vector<Clausula> &formula, int solucao[]) {
  int x, y, z, num_clausulas_verdade = 0;

  /* Avaliação da solução */
  for(int i = 0; i < formula.size(); i++) {
    if(formula[i].x < 0) {
      x = solucao[formula[i].x * -1];
      x = x == 1 ? 0 : 1;
    } else {
      x = solucao[formula[i].x];
    }
    if(formula[i].y < 0) {
      y = solucao[formula[i].y * -1];
      y = y == 1 ? 0 : 1;
    } else {
      y = solucao[formula[i].y];
    }
    if(formula[i].z < 0) {
      z = solucao[formula[i].z * -1];
      z = z == 1 ? 0 : 1;
    } else {
      z = solucao[formula[i].z];
    }

    if(x || y || z) {
      num_clausulas_verdade++;
    }
  }
  return num_clausulas_verdade;
}