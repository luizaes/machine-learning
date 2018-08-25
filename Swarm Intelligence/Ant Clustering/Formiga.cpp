#include "Formiga.hpp"

void Formiga::posicaoInicial(Ambiente &ambiente) {

	default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distribution(0,ambiente.retornaTamanho()-1);
	uniform_int_distribution<int> secondDistribution(0,3);

	posicaoX = distribution(generator);
	posicaoY = distribution(generator);

	//cout << posicaoX << " " << posicaoY << endl;
	//ultimaDirecao = secondDistribution(generator);

}

Formiga::Formiga(Ambiente &ambiente) {
	raioVisao = 1;
	estado = 0;
	posicaoInicial(ambiente);
}

void Formiga::mover(Ambiente &ambiente) {

  default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> distribution(0,7);
  bool encontreiDirecao = false;
  int direcao;

  //cout << "ultimaDirecao" << ultimaDirecao << endl;

  while(!encontreiDirecao) {
  	  direcao = distribution(generator);
	  if(direcao == 0) { // Cima
	  	if(posicaoY + 1 < ambiente.retornaTamanho()) {
	  		posicaoY++;
	  		encontreiDirecao = true;
	  		//ultimaDirecao = 0;
	  	}
	  } else if(direcao == 1) { // Direita
	    if(posicaoX + 1 < ambiente.retornaTamanho()) {
	    	posicaoX++;
	    	encontreiDirecao = true;
	    	//ultimaDirecao = 1;
	    }
	  } else if(direcao == 2 ) { // Esquerda
	    if(posicaoX - 1 > 0) {
	    	posicaoX--;
	    	encontreiDirecao = true;
	    	//ultimaDirecao = 2;
	    }
	  } else if(direcao == 3 ){ // Baixo 3
	    if(posicaoY - 1 > 0) {
	    	posicaoY--;
	    	encontreiDirecao = true;
	    	//ultimaDirecao = 3;
	    }
	  } else if(direcao == 4) {
	  	if(posicaoY - 1 > 0 && posicaoX - 1 > 0) {
	    	posicaoY--;
	    	posicaoX--;
	    	encontreiDirecao = true;
	    	//ultimaDirecao = 3;
	    }
	  } else if(direcao == 5) {
	  	if(posicaoY - 1 > 0 && posicaoX + 1 < ambiente.retornaTamanho()) {
	    	posicaoY--;
	    	posicaoX++;
	    	encontreiDirecao = true;
	    	//ultimaDirecao = 3;
	    }
	  } else if(direcao == 6) {
	  	if(posicaoY + 1 < ambiente.retornaTamanho() && posicaoX + 1 < ambiente.retornaTamanho()) {
	    	posicaoY++;
	    	posicaoX++;
	    	encontreiDirecao = true;
	    	//ultimaDirecao = 3;
	    }
	  } else if(direcao == 7) {
	  	if(posicaoY + 1 < ambiente.retornaTamanho() && posicaoX - 1 > 0) {
	    	posicaoY++;
	    	posicaoX--;
	    	encontreiDirecao = true;
	    	//ultimaDirecao = 3;
	    }
	  }
  }
  //cout << "Direcao Atual" << ultimaDirecao << endl;

}

bool Formiga::getEstado() {
	return estado;
}

void Formiga::setEstado(bool est) {
	estado = est;
}

int Formiga::getX() {
	return posicaoX;
}

int Formiga::getY() {
	return posicaoY;
}

int Formiga::getRaioVisao() {
	return raioVisao;
}

int Formiga::getQuantidadeCelulas(Ambiente &ambiente) {
	int i, j, contador = 0;

	for(i = posicaoY-raioVisao; i <= posicaoY+raioVisao; i++) {
		for(j = posicaoX-raioVisao; j <= posicaoX+raioVisao; j++) {
			if(i == posicaoY && j == posicaoX) {
				continue;
			} else {
				if(i >= 0 && i < ambiente.retornaTamanho() && j >= 0 && j < ambiente.retornaTamanho()) {
					contador++;
				}
			}
		}
	}

	return contador;
}

int Formiga::getQuantidadeItens(Ambiente &ambiente) {
	int i, j, contador = 0;

	for(i = posicaoY-raioVisao; i <= posicaoY+raioVisao; i++) {
		for(j = posicaoX-raioVisao; j <= posicaoX+raioVisao; j++) {
			if(i == posicaoY && j == posicaoX) {
				continue;
			} else {
				if(i >= 0 && i < ambiente.retornaTamanho() && j >= 0 && j < ambiente.retornaTamanho()) {
					if(ambiente.placa[i][j] == 1) {
						contador++;
					}
				}
			}
		}
	}
	return contador;
}

void Formiga::pegar(Ambiente &ambiente) {
	estado = 1;
	ambiente.placa[posicaoY][posicaoX] = 0;
}

void Formiga::largar(Ambiente &ambiente) {
	estado = 0;
	ambiente.placa[posicaoY][posicaoX] = 1;
}