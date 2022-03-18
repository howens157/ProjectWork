import time

cached = dict()

#cached[5] = 'a'
#cached['qqq'] = 'b'
#print(cached['qqq'])

def cache(fcn):
	def inner(a):
		if a not in cached.keys():
			cached[a] = fcn(a)
		return cached[a]
	return inner

@cache
def expensive(a):
	time.sleep(2)
	return a+1

expensive(5)
expensive(5)

expensive(6)

