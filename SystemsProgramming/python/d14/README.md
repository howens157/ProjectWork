# Python Daily 14 - Stop Procrastinating on the Milestone

Due: October 4, 2021 at classtime

In this assignment, I am making you start on m2b, so you won't all come whining later that there is too much work to do because you waited until 10pm Sunday October 24 to start the milestone assignments.

"Recall" (like you even read it) that m2b involves writing an updated version of the uniq utility.  You can go read the README for m2b for more information about that assignment, but in this daily please write a small script that does the following:

Given a document like dinosaur.txt:

    $ cat dinosaur.txt 
    tyrannosaur
    stegosaur
    Allosaur
    allosaur
    allosaur
    tyrannosaur
    
Your program should print only the first instance of each line, like so:

    $ python3 unique.py dinosaur.txt 
    tyrannosaur
    stegosaur
    Allosaur
    allosaur
    
Notice that in this daily, the unique.py script is case sensitive and prints only the first occurrence of a line.  So tyrannosaur appears first but not last, and Allosaur is not a duplicate of allosaur.

ALSO NOTICE that the lines do not need to be next to each other, i.e. they do not need to be sorted first.  The actual uniq utility would give this:

    $ uniq dinosaur.txt 
    tyrannosaur
    stegosaur
    Allosaur
    allosaur
    tyrannosaur

Your program should not require sorting first.

# How do I do this?

There is a neat little data structure in Python called a dictionary.  It works like so:

    myd = dict()
    myd['a'] = 55
    print(myd['a']) # will print 55
    
You've encounted dictionaries before, but you may not have used one yet.  There is a key and a value.  The keys in dictionaries are unique.  The values are not unique.  There is one value per key.  The key and value can be most any object in Python, but usually they are either strings or ints.  Dictionaries are great for recording things like zip codes and city names (zip codes are unique but a city may have multiple zip codes in it).  For example:

    zips[46615] = "South Bend"
    zips[46616] = "South Bend"
    zips[46617] = "South Bend"
    zips[23456] = "Virginia Beach"

You can also use dictionaries to hold lists, such as:

    zips[46615] = [ "South Bend", "IN" ]
    zips[46616] = [ "South Bend", "IN" ]
    zips[46617] = [ "South Bend", "IN" ]
    zips[23456] = [ "Virginia Beach", "VA" ]

Then you'd access the city and state, say, like this:

    zips[46615][0] # would be the city
    zips[46615][1] # would be the state
    
You can even put dictionaries in dictionaries!

    cs = dict()
    cs['city'] = 'South Bend'
    cs['state'] = 'IN'

    zips = dict()
    zips[46615] = cs
    
    zips[46615]['city'] # would be the city
    zips[46615]['state'] # would be the state
    
Anyway, dictionaries are great for keeping track of the number of unique things.  You just add the item to the dictionary as a key and increment the value for that key.  So say you wanted to know how many zipcodes a city had, you could do something like this:

    # for each zipcode, city combination:
        cities[cityname] = cities[cityname] + 1
        # just be sure to catch the exception if cityname is not a key yet
        # in that exception you'd just:
        cities[cityname] = 1

# What am I really learning here?

You are learning to use a Python dictionary.  The typical textbook Python intro sequence has a whole lecture on nothing but dictionaries.  I think that is way overkill because I am certain you can learn it on your own.  At the same time, I can't in good conscious let you leave the class without practicing something so important.  So: this assignment!

# Testing

A test script is available like normal! :-)

    $ bash d14test.sh uniq.py 
    Testing uniq.py ...
    Sample 1, 2 points             ... Success
    Sample 2, 3 points             ... Success
    Time: 0 seconds (max allowed=5)
    Score: 5 / 5

# Turnin

Thank you everyone for putting your code in a folder called d14 in your dropbox under a subdirectory called python, and not under a subdirectory such as username/randomthing/d14.  Also thank you for calling your script uniq.py and not uniq-lastname.py or something else.
