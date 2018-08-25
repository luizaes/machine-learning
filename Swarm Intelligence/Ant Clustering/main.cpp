#include "Formiga.hpp"
#include <vector>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#define NUMERO_FORMIGAS 10
#define NUMERO_ITERACOES 10000

int main() {
  vector<Formiga> formigas;
  int i, j, k, qtdCelulas, qtdItens;
  default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());
  uniform_real_distribution<double> distribution(0.0, 1.0);


  Ambiente ambiente;
  ambiente.zeraMatriz();
  ambiente.disporItens(100);

  for(i = 0; i < NUMERO_FORMIGAS; i++) {
  	formigas.push_back(Formiga(ambiente));
  }

  for(i = 0; i < NUMERO_ITERACOES; i++) {

  		//system("clear");
  		if(i == 0 || i == NUMERO_ITERACOES-1) {
  			//cout << distribution(generator) << endl;
	  		for(j = 0; j < ambiente.retornaTamanho(); j++) {
	  			for(k = 0; k < ambiente.retornaTamanho(); k++) {
	  				if(ambiente.placa[j][k] == 1) {
	  					cout << "▄ ";
	  				} else {
	  					cout << "_ ";
	  				}
	  			}
	  			cout << endl;
	  		}
	  		cout << endl;
  		}
 		//usleep(30000);
  		for(j = 0; j < NUMERO_FORMIGAS; j++) {
  			//cout << "Formiga " << j << endl;

  			if(formigas[j].getEstado() == 0) {
  				if(ambiente.placa[formigas[j].getY()][formigas[j].getX()] == 1) {
  					qtdCelulas = formigas[j].getQuantidadeCelulas(ambiente);
  					qtdItens = formigas[j].getQuantidadeItens(ambiente);
  					//cout << "Probabilidade de pegar "<< (1 - qtdItens/(double)qtdCelulas) - 0.01 << endl;

  					if(distribution(generator) <= (1 - qtdItens/(double)qtdCelulas) - 0.01) {
  						//cout << "Pegou " << formigas[j].getY() << " " << formigas[j].getX() << endl;
  						formigas[j].pegar(ambiente);
  					}
  					formigas[j].mover(ambiente);
  				} else {
  					formigas[j].mover(ambiente);
  				}
  			} else {
  				if(ambiente.placa[formigas[j].getY()][formigas[j].getX()] == 0) {
  					qtdCelulas = formigas[j].getQuantidadeCelulas(ambiente);
  					qtdItens = formigas[j].getQuantidadeItens(ambiente);
  					//cout << "Probabilidade de largar "<< qtdItens/(double)qtdCelulas + 0.01 << endl;
  					if(distribution(generator) <= (qtdItens/(double)qtdCelulas) + 0.01) {
  						//cout << "Largou " << formigas[j].getY() << " " << formigas[j].getX() << endl;
  						formigas[j].largar(ambiente);
  					}
  						formigas[j].mover(ambiente);
  				} else {
  					formigas[j].mover(ambiente);
  				}
  			}


  		}
  }
  /*int cont = 0;
  for(i = 0; i < NUMERO_FORMIGAS; i++) {
  	if(formigas[i].getEstado() == 1) {
  		cont++;
  	}
  }
  cout << cont << endl;*/

  return 0;
}
