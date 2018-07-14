import numpy

class NeuralNetwork(object):
	"""class for the NN"""
	x = 0
	y = 0
	weight1 = 0
	weight2 = 0
	output = 0
	layer1 = 0

	def __init__(self):
		self.x = numpy.array([[0, 0, 0, 0]], numpy.float)
		self.weight1 = numpy.random.rand((self.x.shape[1]), 4) % 100
		self.weight2 = numpy.random.rand(4,4) % 100

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
		updatedWeight2 = numpy.dot(self.layer1.T, (2*(self.y - self.output) * self.sigmoid(self.output, True)))
		updatedWeight1 = numpy.dot(self.x.T, (numpy.dot(2*(self.y - self.output) * self.sigmoid(self.output, True), self.weight2.T) * self.sigmoid(self.layer1, True)))
		self.weight1 += updatedWeight1
		self.weight2 += updatedWeight2

	def getOutput(self):
		return self.output

	def set(self, x, y):
		self.x = x
		self.y = y
		self.output = numpy.zeros(self.y.shape)
		self.layer1 = numpy.zeros((1, 4))
