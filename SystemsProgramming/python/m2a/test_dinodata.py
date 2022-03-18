import unittest
import dinodata

class dinodataTest(unittest.TestCase):
    def test_readdinos(self):
        dinos = dinodata.dinodata()
        dinoerrs = dinos.readdinos('dinosaur.dat')
        self.assertEqual(dinoerrs, 194)

    def test_readzips(self):
        dinos = dinodata.dinodata()
        ziperrs = dinos.readzips('zipcodes.dat')
        self.assertEqual(ziperrs, 0)

    def get_long_lat(self):
        dinos = dinodata.dinodata()
        dinos.readzips('zipcodes.dat')
        dinos.readdinos('dinosaur.dat')
        test_long, test_lat, test_location = dinos.get_long_lat(23456)
        self.assertEqual(test_long, -76.06139)
        self.assertEqual(test_lat, 36.762459)
        self.assertEqual(test_location, 'Virginia Beach, VA')
   
    def test_dino_finds(self):
        dinos = dinodata.dinodata()
        dinos.readdinos('dinosaur.dat')
        dinos.readzips('zipcodes.dat')
        test_found_dinos = dinos.dino_finds(-76.06139, 36.762459, 5)
        self.assertEqual(len(test_found_dinos), 791)
        self.assertEqual(test_found_dinos[0][0], -72.633331)
        self.assertEqual(test_found_dinos[0][1], 41.566666)
        self.assertEqual(test_found_dinos[0][2], 201.3)
           
unittest.main()
