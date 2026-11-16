import enum
import random


class Compared(enum.Enum):
	HIGHTER = 1
	LOWER = 2
	EQUAL = 3

class Game:

	guessNum = random.randint(0,100)

	def run(self):
		while True:
			inputNum = int(input("pick a number between 0 to 100: "))

			if inputNum == self.guessNum:
				print(Compared.EQUAL)
				break
			elif inputNum > self.guessNum:
				print(Compared.HIGHTER)
			elif inputNum < self.guessNum:
				print(Compared.LOWER)

    