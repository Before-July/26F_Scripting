
import random

def multiplyNumbers(num1, num2):
	return num1*num2

def addUpNumbers(num1, num2):
    return num1 + num2


number1 =int( input("pick a number"))
number2 = random.randint(1,101)

value = multiplyNumbers(number1,number2)
value1 = addUpNumbers(number1,number2)


import random
import myFunc

start = random.randint(1,50)
end = random.randint(1,100)

while(end <= start):
    end = random.randint(1,100)


myFunc.printRange(start,end)