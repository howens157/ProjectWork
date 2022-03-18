import unittest
from muchmath import MuchMath

class MuchMathTest(unittest.TestCase):
    def test_triangleArea(self):
        math = MuchMath()
        p = math.triangleArea(5, 10)
        self.assertEquals(p, 25)

    def test_celsiusToFahrenheit(self):
        math = MuchMath()
        p = math.celsiusToFahrenheit(40)
        self.assertEquals(p, 104)

    def test_matrixAdd(self):
        math = MuchMath()
        test_x = [[1, 2, 3], [2, 3, 4], [3, 4, 5]]
        test_y = [[2, 4, 6], [4, 6, 8], [6, 8, 10]]
        check_matrix = [[3, 6, 9], [6, 9, 12], [9, 12, 15]]
        p_list = math.matrixAdd(test_x, test_y)
        for i in range(len(p_list)):
            for j in range(len(p_list[0])):
                self.assertEquals(p_list[i][j], check_matrix[i][j])

    def test_compute_lcm(self):
        math = MuchMath()
        p = math.compute_lcm(10, 6)
        self.assertEquals(p, 30)
        p = math.compute_lcm(6, 10)
        self.assertEquals(p, 30)

    def test_leapyear_4(self):
        math = MuchMath()
        p = math.leapyear(2016)
        self.assertTrue(p)
        p = math.leapyear(2100)
        self.assertFalse(p)       
        p = math.leapyear(2000)
        self.assertTrue(p)       
        p = math.leapyear(2021)
        self.assertFalse(p)

unittest.main()
