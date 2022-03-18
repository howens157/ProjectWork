import ctypes
import pathlib

class c_dino(ctypes.Structure):
    _fields_ = [('lat', ctypes.c_double),
                ('lng', ctypes.c_double),
                ('maxma', ctypes.c_double),
                ('minma', ctypes.c_double),
                ('namelen', ctypes.c_int),
                ('name', ctypes.c_char_p)];

class cdinodata:

    def __init__(self, maxdinos=30000):
        self.libname = pathlib.Path().absolute() / "libdinos.so"
        self.c_lib = ctypes.CDLL(self.libname)
        self.maxdinos = maxdinos
        self.dinos = list()

    def readdinos(self, fn):
        fn = ctypes.c_char_p(fn.encode('utf-8'))
        
        elems = (ctypes.POINTER(c_dino) * self.maxdinos)()
        wrkdinos = ctypes.cast(elems, ctypes.POINTER(ctypes.POINTER(c_dino)))
        
        numread = self.c_lib.readdinos(fn, wrkdinos)

        for i in range(0, numread):
            w = wrkdinos[i].contents
            d = dict()
            d['lat'] = w.lat 
            d['lng'] = w.lng
            d['maxma'] = w.maxma
            d['minma'] = w.minma
            d['namelen'] = w.namelen
            d['name'] = w.name.decode('utf-8')
            self.dinos.append(d)

        return numread
    
    def get_dinos(self):
        return self.dinos

