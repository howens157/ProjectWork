import ray
import time

ray.init()

@ray.remote
def foo(x):
	time.sleep(x)
	print(x*x)
	return(x*x)

f1 = foo.remote(1)
f2 = foo.remote(2)

res = ray.get([f1, f2])

print(res)

