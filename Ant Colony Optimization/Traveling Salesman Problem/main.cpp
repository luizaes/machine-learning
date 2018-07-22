/*
	To compile: g++ main.cpp -o tsp -std=c++11
*/

#include <iostream>
#include <random>
#include <cmath>

using namespace std;

// Definitions
#define NUM_VERTICES 20
#define ITERATIONS 50
#define NUM_ANTS 6
#define ALPHA 0.5
#define BETA 0.8
#define PHEROMONE_EVAPORATION 0.1
#define Q 50

// Global data structures
double matrix[NUM_VERTICES][NUM_VERTICES];
double visibility[NUM_VERTICES][NUM_VERTICES];
double pheromoneTrail[NUM_VERTICES][NUM_VERTICES];
double probability[NUM_VERTICES];
bool visited[NUM_VERTICES];
int edges[NUM_VERTICES][NUM_VERTICES][NUM_ANTS];
double costRoute[NUM_ANTS];

// Function to randomize a number
int randomNumber();

// Ant colony class
class ACO {
public:
	double init(int num) {
		int i, j;
		double cost;
		// Initialize any other data structures
		for(i = 0; i < NUM_VERTICES; i++) {
			visited[i] = false;
			probability[i] = 0.0;
		}
		cost = route(num);
		return cost;
	}

	int step(int city, int num) {
		int i;
		int maior = 0;
		visited[city] = true;

		for(i = 0; i < NUM_VERTICES; i++) {
			if(visited[i] == false) {
				maior = i;
				break;
			}
		}

		for(i = 0; i < NUM_VERTICES; i++){
			if(visited[i] == false) {
				probability[i] = calcProbability(city, i);
				if(probability[i] > probability[maior]) {
					maior = i;
				}
			}
		}
		edges[city][i][num]++;
		return maior;
	}

	double route(int num) {
		int aux, i;
		//random_device rd;
		//int vertex = rd() % NUM_VERTICES;
		int vertex = 0;
		double cost = 0.0;
		int currentCity = step(vertex, num);
		for(i = 1; i < NUM_VERTICES; i++) {
			aux = currentCity;
			currentCity = step(currentCity, num);
			cout << currentCity << " ";
			cost += matrix[aux][currentCity];
		} 
		return cost;
	}

	void updatePheromones() {
		int i, j;

		for(i = 0; i < NUM_VERTICES; i++) {
			for(j = 0; j < NUM_VERTICES; j++) {
				pheromoneTrail[i][j] = (1 - PHEROMONE_EVAPORATION)*pheromoneTrail[i][j]+calcPassages(i, j);
			}
		}
	}

	double calcPassages(int i, int j) {
		double sum = 0.0;
		for(int z = 0; z < NUM_ANTS; z++) {
			if(edges[i][j][z] == 1) {
				sum += Q / costRoute[z];
			}
		}
		return sum;
	}

	double calcProbability(int city, int i) {
		double prob;
		prob = pow(pheromoneTrail[city][i], ALPHA) * pow(visibility[city][i], BETA);
		prob = prob / calcOtherProbability(city);
		return prob;
	}
	
	double calcOtherProbability(int city) {
		int i;
		double prob = 0.0;
		for(i = 0; i < NUM_VERTICES; i++) {
			if(visited[i] == false) {
				prob += pow(pheromoneTrail[city][i], ALPHA) * pow(visibility[city][i], BETA);
			}
		}
		return prob;
	}

};

int main() {

	int i, j, counter = 0, z;
	ACO ant_colony;
	double cost;

	// Make a fully connected graph with random weights for the edges
	for(i = 0; i < NUM_VERTICES; i++) {
		for(j = 0; j < NUM_VERTICES; j++){
			if(i != j) {
				matrix[i][j] = (double) randomNumber();
			} else {
				matrix[i][j] = 0.0;
			}
			cout << matrix[i][j] << " ";

		}
		cout << endl;
	}

	// Initialize visibility matrix
	for(i = 0; i < NUM_VERTICES; i++) {
		for(j = 0; j < NUM_VERTICES; j++){
			pheromoneTrail[i][j] = 1.0;
			if(matrix[i][j] != 0) {
				visibility[i][j] = 1.0 / matrix[i][j];
			} else {
				visibility[i][j] = 0.0;
			}
		}
	}

	while(counter < ITERATIONS) {

		cout << "Iteration: " << counter << endl;

		for(i = 0; i < NUM_VERTICES; i++) {
			for(j = 0; j < NUM_VERTICES; j++){
				for(z = 0; z < NUM_ANTS; z++) {
					edges[i][j][z] = 0;
				}
			}
		}

		for(i = 0; i < NUM_ANTS; i++) {
			cout << "Ant: " << i << endl;
			cost = ant_colony.init(i);
			costRoute[i] = cost;
			cout << endl << "Cost: " << cost << endl;
		}

		ant_colony.updatePheromones();

		counter++;
	}
	
	return 0;
}

/* randomNumber - randomize a integer between 0 and 9999 */
int randomNumber() {
	random_device rd;
	int distance = rd() % 10000;
	return distance;
}
