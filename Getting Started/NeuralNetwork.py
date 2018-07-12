'''
	Python implementation of a simple 2 layer Neural Network 
	that given an input [x, y, z] where x, y and z are either 0 or 1
	outputs the result of the corresponding logic operation especified on Y.

	    X	         Y
	|0, 0, 0|      | 0 |
	|0, 1, 0|      | 0 |
	|1, 0, 0|   =  | 0 |    (AND)
	|1, 1, 1|      | 1 |

	PS. Still have to fix the problem where if the numbers randomed for weight1 or weight2
	are too big, exp() overflows.

'''

import numpy

class NeuralNetwork(object):
	"""class for the NN"""
	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.weight1 = numpy.random.rand(self.x.shape[1],4) % 100
		self.weight2 = numpy.random.rand(4,1) % 100
		self.output = numpy.zeros(self.y.shape)
		self.layer1 = numpy.zeros((4, 4))

	# using sigmoid as the activation function
	def sigmoid(self, num, arg):
		if arg == True:
			return numpy.dot(num, (1 - num.T))
		return 1 / (1 + numpy.exp(-num))

	# feed forward
	def feedForward(self):
		self.layer1 = self.sigmoid(numpy.dot(self.x, self.weight1), False)
		self.output = self.sigmoid(numpy.dot(self.layer1, self.weight2), False)

	# do back propagation to update the weights 
	def backPropagation(self):
		updatedWeight2 = numpy.dot(self.layer1.T, (2*(self.y - self.output) * self.sigmoid(self.output.T, True)))
		updatedWeight1 = numpy.dot(self.x.T, (numpy.dot(2*(self.y - self.output) * self.sigmoid(self.output.T, True), self.weight2.T) * self.sigmoid(self.layer1, True)))
		self.weight1 += updatedWeight1
		self.weight2 += updatedWeight2

	def getOutput(self):
		return self.output

	def setX(self, x):
		self.x = x
