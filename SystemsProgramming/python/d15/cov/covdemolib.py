class CovDemoLib:

	def primeq(self, num):
		if num > 1:
			for i in range(2, num): 
				if (num % i) == 0: 
					return False
			return True
		else: 
			return False

