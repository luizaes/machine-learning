from Player import Player
from Food import Food
from NeuralNetwork import NeuralNetwork
from random import randint
import pygame
import numpy
import time
from pygame.locals import *

class Game(object):

	countGeneration = 0
	timeCounter = 0
	myfont = 0
	loseBool = False
	foodBool = False
	obstacle = False

	"""docstring for Game"""
	def __init__(self):
		self.player = Player([400, 400])
		self.windowHeight = 768
		self.windowWidth = 1366
		self.screen = 0
		self.running = True
		self.nn = NeuralNetwork()
		self.food = Food([200,200])
		self.countGeneration = 0
		self.score = 0

	def on_init(self):
		pygame.init()
		self.screen = pygame.display.set_mode([self.windowWidth, self.windowHeight], FULLSCREEN)
		pygame.display.set_caption('Neural Network playing the Snake Game!')
		self.myfont = pygame.font.SysFont("monospace", 16)

		self.on_execute()

	# transform coords to pygame coords
	def to_pygame(self, coords):
		print("returning " + str(coords[0]) + " " + str(768-coords[1]))
		return (768 - coords[1], coords[0])

	# detect collision with food
	def detectCollisionFood(self, x1, y1, x2, y2, bsize):
		if x1 >= x2 and x1 <= x2 + bsize:
			if y1 >= y2 and y1 <= y2 + bsize:
				return True
		return False

	# detect collision with the snake's head and a part of it's body 
	def detectCollisionSnake(self, x1, y1, x2, y2):
		if x1 == x2 and y1 == y2:
			return True
		return False

	# generate output to give to the NN so that it can train
	def getAnswer(self, dir, x, y, foodPosition):
		result = 0

		if dir == 0:
			if x > foodPosition[0] and y > foodPosition[1]:
				res = 3
			elif x > foodPosition[0] and y < foodPosition[1]:
				res = 2
			elif x < foodPosition[0] and y < foodPosition[1]:
				res = 0
			elif x < foodPosition[0] and y > foodPosition[1]:
				res = 0
			elif x > foodPosition[0] and y == foodPosition[1]:
				res = 2
			elif x < foodPosition[0] and y == foodPosition[1]:
				res = 0
			elif x == foodPosition[0] and y > foodPosition[1]:
				res = 3
			elif x == foodPosition[0] and y < foodPosition[1]:
				res = 2
		elif dir == 1:
			if x > foodPosition[0] and y > foodPosition[1]:
				res = 3
			elif x > foodPosition[0] and y < foodPosition[1]:
				res = 2
			elif x < foodPosition[0] and y < foodPosition[1]:
				res = 0
			elif x < foodPosition[0] and y > foodPosition[1]:
				res = 3
			elif x > foodPosition[0] and y == foodPosition[1]:
				res = 1
			elif x < foodPosition[0] and y == foodPosition[1]:
				res = 3
			elif x == foodPosition[0] and y > foodPosition[1]:
				res = 3
			elif x == foodPosition[0] and y < foodPosition[1]:
				res = 0
		elif dir == 2:
			if x > foodPosition[0] and y > foodPosition[1]:
				res = 1
			elif x > foodPosition[0] and y < foodPosition[1]:
				res = 1
			elif x < foodPosition[0] and y < foodPosition[1]:
				res = 0
			elif x < foodPosition[0] and y > foodPosition[1]:
				res = 0
			elif x > foodPosition[0] and y == foodPosition[1]:
				res = 1
			elif x < foodPosition[0] and y == foodPosition[1]:
				res = 0
			elif x == foodPosition[0] and y > foodPosition[1]:
				res = 0
			elif x == foodPosition[0] and y < foodPosition[1]:
				res = 2
		else:
			if x > foodPosition[0] and y > foodPosition[1]:
				res = 1
			elif x > foodPosition[0] and y < foodPosition[1]:
				res = 1
			elif x < foodPosition[0] and y < foodPosition[1]:
				res = 0
			elif x < foodPosition[0] and y > foodPosition[1]:
				res = 0
			elif x > foodPosition[0] and y == foodPosition[1]:
				res = 1
			elif x < foodPosition[0] and y == foodPosition[1]:
				res = 0
			elif x == foodPosition[0] and y > foodPosition[1]:
				res = 3
			elif x == foodPosition[0] and y < foodPosition[1]:
				res = 0
		return res

	# render game
	def on_render(self):
		self.screen.fill((255, 255, 255))
		generation = self.myfont.render("Generation = " + str(self.countGeneration), True, (0,0,0))
		self.screen.blit(generation, (10, 10))
		score = self.myfont.render("Score = " + str(self.score), True, (0,0,0))
		self.screen.blit(score, (10, 50))
		if self.loseBool:
			lose = self.myfont.render("Snake collided with itself!", True, (0,0,0))
			self.screen.blit(lose, (500, 10))
		self.player.drawSnake(self.screen)
		self.food.drawFood(self.screen)
		self.player.update()
		self.food.update()
		pygame.display.flip()
		if self.loseBool:
			time.sleep(2.0)

	# main game loop
	def on_execute(self):
		while(self.running):
			global timeCounter
			timeCounter = 0
			timeCounter = time.time()
			while True:
				foodPosition = []
				output = []
				pygame.event.pump()
				key = pygame.key.get_pressed() 
				if key[K_ESCAPE]:
					self.running = False
					break

				if(time.time() - timeCounter >= 10.0):
					break

				# check for collision with food
				for x in range(0,self.player.length):
					if self.detectCollisionFood(self.food.positionX,self.food.positionY,self.player.positionX[x], self.player.positionY[x], 30):
						self.food.positionX = randint(2,9) * 30
						self.food.positionY = randint(2,9) * 30
						self.player.length = self.player.length + 1
						self.player.positionX.append(self.player.positionX[x])
						self.player.positionY.append(self.player.positionY[x])
						timeCounter = time.time()
						self.score = self.score + 1
						self.foodBool = True

				if not self.foodBool:
					# check for collision with the snake itself
					for x in range(2, self.player.length):
						if self.detectCollisionSnake(self.player.positionX[0],self.player.positionY[0],self.player.positionX[x], self.player.positionY[x]):
							print("You lose!")
							self.score = 0
							self.loseBool = True
							self.player.length = 1
							self.player = Player([400, 400])
							self.food = Food([200, 200])
							#exit(0)
							break
				

				if self.player.direction == 0:
					playerPosition = [self.player.positionX[0]+1, self.player.positionY[0]]
				elif self.player.direction == 1:
					playerPosition = [self.player.positionX[0]-1, self.player.positionY[0]]
				elif self.player.direction == 2:
					playerPosition = [self.player.positionX[0], self.player.positionY[0]+1]
				else:
					playerPosition = [self.player.positionX[0], self.player.positionY[0]-1]

				# check for collision with the snake itself
				for x in range(1, self.player.length):
					if self.detectCollisionSnake(playerPosition[0],playerPosition[1],self.player.positionX[x], self.player.positionY[x]):
						obstacle = True
						break

				playerPosition = [self.player.positionX[0], self.player.positionY[0]]
				foodPosition = self.food.getPosition()

				output = self.getAnswer(self.player.direction, self.player.positionX[0], self.player.positionY[0], foodPosition)
				#print(self.player.positionX[0] + " " + self.player.positionY[0])
				#print(foo)
				
				if output == 0:
					output = numpy.array([[1, 0, 0, 0]], numpy.float)
				elif output == 1:
					output = numpy.array([[0, 1, 0, 0]], numpy.float)
				elif output == 2:
					output = numpy.array([[0, 0, 1, 0]], numpy.float)
				else:
					output = numpy.array([[0, 0, 0, 1]], numpy.float)
				
				if self.obstacle:
					if self.player.direction == 2:
						output = numpy.array([0, 0, 0, 1], numpy.float)
					else:
						output = numpy.array([0, 0, 1, 0], numpy.float)
					self.nn.set(numpy.array([[1] + foodPosition+playerPosition], numpy.float), output)	
				else:	
					self.nn.set(numpy.array([[0] + foodPosition+playerPosition], numpy.float), output)	
					
				self.nn.feedForward()
				self.nn.backPropagation()

				# get NN's output and move the snake
				direction = self.nn.getOutput()
				#print(direction)
				dir = numpy.max(direction)
				#print(dir)
				y = -1
			
				#x = numpy.where(numpy.any(direction == dir))
				y = list(direction[0]).index(dir)

				if y == 0:
					self.player.moveRight()
				if y == 1:
					self.player.moveLeft()
				if y == 2:
					self.player.moveUp()
				if y == 3:
					self.player.moveDown()

				self.on_render()
				time.sleep(0.05)
				self.foodBool = False
				if self.loseBool:
					self.loseBool = False
					break

			self.countGeneration = self.countGeneration + 1
			self.player = Player([400, 400])
			self.food = Food([200, 200])
			self.score = 0
pygame.quit()