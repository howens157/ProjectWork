# Systems Programming Daily 15 - Test Coverage

Write a script that will achieve 100% statement coverage for the provided module muchmath.  Use the coverage tool to generate a test coverage report in both console and html format.

Use the unittest module as demonstrated in class.  Write one function in your unittest for each function in muchmath.

Call your script d15.py and run it with the coverage tool:

    $ coverage run d15.py
    .....
    ----------------------------------------------------------------------
    Ran 5 tests in 0.039s

    OK

Then generate a console report:

    $ coverage report
    Name          Stmts   Miss  Cover
    ---------------------------------
    d15.py           35      0   100%
    muchmath.py      31      0   100%
    ---------------------------------
    TOTAL            66      0   100%

And then an html report:

    $ coverage html
    $ ls htmlcov/
    astwrk_py.html                      jquery.min.js
    coverage_html.js                    jquery.tablesorter.min.js
    d15_py.html                         keybd_closed.png
    index.html                          keybd_open.png
    jquery.ba-throttle-debounce.min.js  muchmath_py.html
    jquery.hotkeys.js                   status.json
    jquery.isonscreen.js                style.css

Note that you will have to download the htmlcov folder or use the text-based browser 'lynx' to view the html files.

You must obtain 100% statement coverage of muchmath.py.  That means you'll have to think of example inputs that cause the execution path of muchmath to reach every line at least once.

# Grading

There is no test script due to the need to generate reports which have to be evaluated by hand (there could be many tiny differences that lead scripts to report false errors).  Instead, I will go to your dropbox d15 directory and run:

    $ coverage run d15.py
    $ coverage report
    $ coverage html
    
And look for reports indicating 100% test coverage.  Then I will also open your d15.py and look to see if you have a test function for every function in muchmath.py.

This assignment is worth 4 points.

