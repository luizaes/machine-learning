/*
	To compile: g++ main.cpp -o tsp -std=c++11
*/

#include <iostream>
#include <random>
#include <vector>
#include <list>

using namespace std;

#define NUM_VERTICES 8 
#define ITERATIONS 10
#define NUM_ANTS 5
#define ALPHA 0.5
#define BETA 1.2

double matrix[NUM_VERTICES][NUM_VERTICES];
double visibility[NUM_VERTICES][NUM_VERTICES];
double pheromoneTrail[NUM_VERTICES][NUM_VERTICES];
double probability[NUM_VERTICES];
bool visited[NUM_VERTICES];

class ACO {
public:
	void init() {
		int i, j;

		// Initialize any other data structures
		for(i = 0; i < NUM_VERTICES; i++) {
			visited[i] = false;
			probability[i] = 0.0;
			for(j = 0; j < NUM_VERTICES; j++) {
				pheromoneTrail[i][j] = 0.0;
			}
		}

		route();

	}

	int step(int city) {

		

	}

	void route() {

		int currentCity = step(0);

		for(i = 1; i < NUM_VERTICES; i++) {
			currentCity = step(currentCity);
		}
	}

	void updatePheromones() {

	}
	
};

int randomNumber();

int main() {

	int i, j, counter = 0;
	ACO ant_colony;

	// Make a fully connected graph with random weights for the edges
	for(i = 0; i < NUM_VERTICES; i++) {
		for(j = 0; j < NUM_VERTICES; j++){
			if(i != j) {
				matrix[i][j] = (double) randomNumber();
			} else {
				matrix[i][j] = 0.0;
			}
		}
	}

	// Initialize visibility matrix
	for(i = 0; i < NUM_VERTICES; i++) {
		for(j = 0; j < NUM_VERTICES; j++){
			if(matrix[i][j] != 0) {
				visibility[i][j] = 1.0 / matrix[i][j];
			} else {
				visibility[i][j] = 0.0;
			}
		}
	}

	while(counter < ITERATIONS) {

		cout << "Iteration: " << counter << endl;

		for(i = 0; i < NUM_ANTS; i++) {
			cout << "Ant: " << i << endl;
			ant_colony.init();
			//ant_colony.updatePheromones();
		}

		counter++;
	}
	

	return 0;
}

int randomNumber() {
	random_device rd;
	int distance = rd() % 10000;
	if(distance < 0) {
		distance *= -1;
	}
	return distance;
}
