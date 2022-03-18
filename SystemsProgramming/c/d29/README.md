# C/Python Daily 29 - Language Bindings

THIS ASSIGNMENT IS OPTIONAL.

I PROVIDE IT ONLY SO YOU CAN PRACTICE FOR THE EXAM.

Today your task is to create a Python wrapper library for your C implementation of libdinos.  Actually your wrapper library only needs one binding: to readdinos().

Start by copying in your D24 code.  Compile it so you have a working libdinos.so.  Recall libdinos.h:

    typedef struct
    {
        double lat;
        double lng;
        
        double maxma;
        double minma;
        
        int namelen;
        char *name;
    } dino;

    int split(char *buf, char **splits, char delim, int max, int len);
    int readline(FILE *fp, char *buf, int len);
    int readdinos(char *fn, dino **dinos);
    double nearest_dino(dino *d0, dino *d1, dino **dinos, int numdinos, double (*nearest_calc)(dino *, dino *));

There is a struct to hold the dino information, followed by four C functions.  You only need to worry about the dino struct and readdinos() in this assignment.

Take a look at the d29.py I provided:

    from cdinodata import *

    cdd = cdinodata()

    num_dinos = cdd.readdinos("dinosaur.dat")

    dinos = cdd.get_dinos()

    for i in range(0, 30):
        d = dinos[i]
        print(d['lat'], d['lng'], d['maxma'], d['minma'], d['namelen'], d['name'])

The output of this program should be the information for the first thirty dinosaur finds.  For convienence, here are the first ten:

    51.083332 -1.166667 55.8 37.2 11 Aves indet.
    51.083332 -1.166667 55.8 37.2 11 Aves indet.
    42.9333 123.966698 150.8 132.9 42 n. gen. Chaoyangosaurus n. sp. liaosiensis
    41.799999 120.73333 130.0 122.46 40 n. gen. Protarchaeopteryx n. sp. robusta
    41.799999 120.73333 130.0 122.46 31 n. gen. Caudipteryx n. sp. zoui
    43.299999 99.599998 83.6 72.1 16 Theropoda indet.
    30.538889 34.726665 145.0 113.0 17 Dinosauria indet.
    50.740726 -111.528732 83.5 70.6 29 Gorgosaurus n. sp. sternbergi
    50.753296 -111.461914 83.5 70.6 20 Hadrosauridae indet.
    50.737015 -111.549347 83.5 70.6 20 Gorgosaurus libratus

Your job is to write the cdinodata wrapper library so that d29.py works.  Get started by create a file cdinodata.py and putting the following class in it:

    class cdinodata:
        
        def __init__(self, maxdinos=30000):
            pass
        
        def readdinos(self, fn):
            pass

        def get_dinos(self):
            pass

Now fill in those functions so they actually do something useful!

Remember that the first thing you need to do is set up the struct.  You need to create a Python ctypes template class for the C struct.  Then in init() you create the Python ctypes analog to the dino **dinos parameter to readdinos().

The Python readdinos() should then call the C readdinos() function.  The C readdinos() function will run and then ctypes will fill in your Python dinos template with the information from the C readdinos() function.  You can then access it in Python.

Your Python readdinos() function will also need to convert the ctypes dinos structure into a list/dictionary structure that is familiar to Python programmers.  The structure here is just a list of dictionaries.  When you call get_dinos() in cdinodata, you should get back a list.  Each element in the list is a dictionary with the dinosaur find information.

The dinosaur dictionary here is the Python analog to the C dino struct.  Instead of a struct with lat, lng, maxma, minma, namelen, and name, you should have a dictionary with 'lat', 'lng', etc., keys.

# Grading

As usual, I provide a test script:

    $ bash d29test.sh 
    Testing  ...
    first record, 1 point          ... Success
    all records, 4 points          ... Success
    Time: 6 seconds (max allowed=60)
    Score: 5 / 5

Don't just run it blindly.  Be sure you understand what it is doing so you can write your code to match it.
