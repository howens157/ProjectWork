class Dataframe:
	def __init__(self):
		self.frame = list()

	def set_headers(self, headers):
		self.frame.append(headers)

	def append(self, d):
		self.frame.append(d)

