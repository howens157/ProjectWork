
class MuchMath:
    
    def triangleArea(self, b, h):
        return((b * h) / 2)
    
    def celsiusToFahrenheit(self, c):
        f = (c * 1.8) + 32
        return(round(f, 2))
    
    def matrixAdd(self, X, Y):
        result = list()
        for i in range(len(X)):
            result.append(list())
            for j in range(len(X[0])):
                result[i].append(X[i][j] + Y[i][j])
        return(result)
    
    def compute_lcm(self, x, y):
        if x > y:
            greater = x
        else:
            greater = y

        while(True):
            if((greater % x == 0) and (greater % y == 0)):
                lcm = greater
                break
            greater += 1

        return lcm

    def leapyear(self, year):
        if (year % 4) == 0:
            if (year % 100) == 0:
                if (year % 400) == 0:
                    return True
                else:
                    return False
            else:
                return True
        else:
            return False
