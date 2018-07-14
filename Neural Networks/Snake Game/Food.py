import pygame
import numpy
from random import randint

class Food(object):

	step = 50
	counter = 0

	"""docstring for Food"""
	def __init__(self, (x,y)):
		self.positionX = x + self.step
		self.positionY = y + self.step

	def drawFood(self, screen):
		pygame.draw.rect(screen, (124, 252, 0), (self.positionY+10, self.positionX-10, 10, 10))

	def getPosition(self):
		return [self.positionX, self.positionY]

	def update(self):
		self.counter = self.counter + 1
		if self.counter > 200:
			self.positionX = randint(2,9) * 50
			self.positionY = randint(2,9) * 50
			self.counter = 0