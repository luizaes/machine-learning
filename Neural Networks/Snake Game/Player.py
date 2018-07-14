import pygame

class Player:
	positionX = []
	positionY = []
	speed = 15
	direction = 0
	length = 0
	updateC = 0

	def __init__(self, (x, y)):
		self.length = 1
		self.positionX.append(x)
		self.positionY.append(y)

	def update(self):
		self.updateC = self.updateC + 1
		if self.updateC > 3:

			for x in range(self.length-1, 0, -1):
				self.positionX[x] = self.positionX[x-1]
				self.positionY[x] = self.positionY[x-1]

			if self.direction == 0:
				if(self.positionX[0] + self.speed <= 1366):
					self.positionX[0] = self.positionX[0] + self.speed
			if self.direction == 1:
				if self.positionX[0] - self.speed >= 0 :
					self.positionX[0] = self.positionX[0] - self.speed
			if self.direction == 2:
				if self.positionY[0] + self.speed <= 768:
					self.positionY[0] = self.positionY[0] + self.speed
			if self.direction == 3:
				if self.positionY[0] - self.speed >= 50:
					self.positionY[0] = self.positionY[0] - self.speed
			self.updateC = 0

	def moveRight(self):
		self.direction = 0

	def moveLeft(self):
		self.direction = 1

	def moveUp(self):
		self.direction = 2

	def moveDown(self):
		self.direction = 3

	def drawSnake(self, screen):
		for x in xrange(0, self.length):
			pygame.draw.rect(screen, (126, 100, 41), (self.positionY[x]+10, self.positionX[x]-10, 10, 10))
