#include <random>
#include <iostream>
#include <chrono>
#include "Ambiente.hpp"

using namespace std;

class Formiga {
private:
  bool estado;
  int posicaoX;
  int posicaoY;
  int raioVisao;
  //int ultimaDirecao;
public:
  Formiga(Ambiente &ambiente);
  void posicaoInicial(Ambiente &ambiente);
  void mover(Ambiente &ambiente);
  bool getEstado();
  void setEstado(bool est);
  int getX();
  int getY();
  int getRaioVisao();
  int getQuantidadeCelulas(Ambiente &ambiente);
  int getQuantidadeItens(Ambiente &ambiente);
  void pegar(Ambiente &ambiente);
  void largar(Ambiente &ambiente);
};
