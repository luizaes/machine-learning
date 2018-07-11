/*
	C++ implementation of a simple 2 layer Neural Network 
	that given a input [x, y] where x, y are either 0 or 1
	outputs the result of the corresponding AND logic operation.

*/

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <unsupported/Eigen/MatrixFunctions>

using namespace std;
using namespace Eigen;

class NeuralNetwork {
private:
	// Matrix with inputs
	MatrixXf x;
	// Matrix with outputs
	MatrixXf y;
	// Matrix with weights of the first layer
	vector<MatrixXf> weights1;
	// Matrix with weights of the second layer
	MatrixXf weights2;
	// Matrix with the NN first layer
	MatrixXf layer1;
	// Matrix with the NN outputs
	MatrixXf outputs;

public:
	NeuralNetwork(MatrixXf input, MatrixXf output, vector<MatrixXf> w1, MatrixXf w2) {
		x = input;
		y = output;
		weights1 = w1;
		weights2 = w2;
		// Giving the output value just to inicialize the matrix, gonna change it later
		layer1 = output;
		outputs = output;
	}

	void setOutput(MatrixXf m) {
		outputs = m;
	}

	void setLayer(MatrixXf m) {
		layer1 = m;
	}

	MatrixXf getX() {
		return x;
	}

	MatrixXf getY() {
		return y;
	}

	MatrixXf getW2() {
		return weights2;
	}

	vector<MatrixXf> getW1() {
		return weights1;
	}

	MatrixXf getOutput() {
		return outputs;
	}

	MatrixXf getLayer() {
		return layer1;
	}

};

float sigmoid(float m, bool deriv);
void feedForward(MatrixXf &layer1, MatrixXf &outputs, MatrixXf input, vector<MatrixXf> weights1, MatrixXf weights2);
void backPropagation(MatrixXf &layer1, MatrixXf &outputs, MatrixXf &input, MatrixXf &weights1, MatrixXf &weights2);

int main() {

	float num;
	srand(time(NULL));
	// Inputs and Outputs
	MatrixXf x(4,2);
	MatrixXf y(4,1);

	MatrixXf mAux = MatrixXf();
	mAux.resize(1,1);

	// Randoming weights
	vector<MatrixXf> weight1;
	MatrixXf w1 = MatrixXf();
	w1.resize(2,3);
	for(int i = 0; i < 4; i++) {
		//w1.setRandom();
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < 3; k++) {
				num = rand() % 10;
				num = sigmoid(num, false);
				w1(j,k) = num;
			}
		}
		weight1.push_back(w1);
	}

	MatrixXf weight2(3,1);
	//weight2.setRandom();
	for(int j = 0; j < 3; j++) {
		num = rand() % 10;
		//cout << num << endl;
		num = sigmoid(num, false);
		//cout << num << endl;
		weight2(j,0) = num;
	}


	// First layer and outputs of the NN
	MatrixXf layer1(4,3);
	MatrixXf output(4,1);

	x << 0, 0,
		 0, 1,
		 1, 0,
		 1, 1;

	y << 0,
		 0, 
		 0,
		 1;

	NeuralNetwork nn = NeuralNetwork(x, y, weight1, weight2);

	feedForward(layer1, output, x, weight1, weight2);
	cout << output << endl;


	return 0;
}

void feedForward(MatrixXf &layer1, MatrixXf &outputs, MatrixXf input, vector<MatrixXf> weights1, MatrixXf weights2) {

	for(int i = 0; i < 4; i++) {
		//cout << input.row(i) * weights1[i] << endl << endl;
		layer1.row(i) = input.row(i) * weights1[i];
	}
	for(int i = 0; i < 4; i++){
		for (int j = 0; j < 3; j++){
			if(layer1(i,j) > 1.0) {
				layer1(i, j) = 1.0;
			}
		}
	}
	//layer1 = sigmoid(input * weights1, 4, 1, false);
	//outputs = sigmoid(layer1 * weights2, 4, 1, false);
	
	outputs = layer1 * weights2;
	for(int i = 0; i < 4; i++){
		if(outputs(i,0) > 1.0) {
			outputs(i, 0) = 1.0;
		}
	}
}

void backPropagation(MatrixXf &layer1, MatrixXf &outputs, MatrixXf &input, MatrixXf &weights1, MatrixXf &weights2) {

}

float sigmoid(float m, bool deriv) {
	//MatrixXf mAux;
	if(deriv) {
		return m*(1-m);
	}

	//cout << "exp: " << exp(-m) << " seq: " << 1 +exp(-m) << " res: " << 1/(1 + exp(-m)) << endl;

	return 1/(1 + exp(-m));
}