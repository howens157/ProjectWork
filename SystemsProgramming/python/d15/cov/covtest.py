import unittest
from covdemolib import CovDemoLib

class CovDemoTest(unittest.TestCase):

    def test_primeq_a(self):
        cdl = CovDemoLib()
        p = cdl.primeq(8)
        self.assertFalse(p)

    def test_primeq_b(self):
        cdl = CovDemoLib()
        p = cdl.primeq(67)
        self.assertTrue(p)

#    def test_primeq_c(self):
#        cdl = CovDemoLib()
#        p = cdl.primeq(1)
#        self.assertFalse(p)

unittest.main()

