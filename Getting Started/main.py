'''
	Python implementation of a simple 2 layer Neural Network 
	that given a input [x, y, z] where x, y and z are either 0 or 1
	outputs the result of the corresponding logic operation especified on Y.

	    X	         Y
	|0, 0, 0|      | 0 |
	|0, 1, 0| 	   | 0 |
	|1, 0, 0|   =  | 0 |    (AND)
	|1, 1, 1|      | 1 |

	PS. Still have to fix the problem where if the numbers randomed for weight1 or weight2
	are too big, exp() overflows.

'''

from NeuralNetwork import NeuralNetwork
import numpy

neural = NeuralNetwork(numpy.array([[0, 0, 0], [0, 1, 0], [1, 0, 0], [1, 1, 1]], numpy.float), numpy.array([[0, 0, 0, 1]], numpy.float).T)

# train the Neural Network 10000 times
for i in xrange(10000):
	neural.feedForward()
	neural.backPropagation()

print(neural.getOutput())