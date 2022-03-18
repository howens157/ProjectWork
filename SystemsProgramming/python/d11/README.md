# Systems Programming Daily 11 - Decorators

Today you will practice writing Python function decorators.  Here's a Christmas tree to help think of happy thoughts about tree decoration:

    _\/_
     /\
     /\
    /  \
    /~~\o
   /o   \
  /~~*~~~\
 o/    o \
 /~~~~~~~~\~`
/__*_______\
     ||
   \====/
    \__/
    
# dinocolumns.py (a file I provide)

In D10 you wrote a module called dinodata that reads dinosaur.dat into a dataframe.  You also used the dataframe to calculate the prey-predator ratio.

In this assignment, you will add functionality to write the data back out to a file, except only writing out specific columns.  This is similar to using awk like so:

$ cat dinosaur.dat | awk -v FS='\t' -v OFS='\t' '{ print $6, $16, $17; }'

I have provided a script called dinocolumns.py that uses the dinodata module to do basically the same thing:

    #!/usr/bin/env python3

    import sys
    import dinodata
    import argparse

    descr = 'Calculates Prey-Predator Ratio of specified animals'
    examples = """Filters dinosaur data and writes to an (optionally encrypted) file."""

    parser = argparse.ArgumentParser(description=descr, epilog=examples, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('-d', dest='datfile_in', type=str, default='dinosaur.dat', help='data file to read')
    parser.add_argument('-o', dest='datfile_out', type=str, default='dinosmini.dat', help='data file to write')
    parser.add_argument('-e', dest='encryptpw', type=str, default='', help='encrypt, if specified, with given password')
    parser.add_argument('-c', dest='columns', type=str, required=True, help='columns to write')
    parser.add_argument('-l', dest='limit', type=int, default=10, help='maximum entries to write')
    args = parser.parse_args()

    encryptpw = args.encryptpw
    datfile_in = args.datfile_in
    datfile_out = args.datfile_out
    columns = args.columns
    limit = args.limit

    columns = columns.split(',')
    columns = [int(e) for e in columns]

    dinos = dinodata.dinodata([], [], encryptpw)

    dinos.readdinos(datfile_in)

    dinos.save_df(datfile_out, columns, limit)

You'd use this program like so:

    $ python3 dinocolumns.py -d dinosaur.dat -o dinosmini.dat -c 5,15,16 -l 10

This would write the first TEN rows (the -l flag) of data from columns 5, 15, and 16 of dinosaur.dat into dinosmini.dat, like so:

    identified_name max_ma  min_ma
    Aves indet.     55.8    37.2
    Aves indet.     55.8    37.2
    n. gen. Chaoyangosaurus n. sp. liaosiensis      150.8   132.9
    n. gen. Protarchaeopteryx n. sp. robusta        130     122.46
    n. gen. Caudipteryx n. sp. zoui 130     122.46
    Theropoda indet.        83.6    72.1
    Dinosauria indet.       145     113
    Gorgosaurus n. sp. sternbergi   83.5    70.6
    Hadrosauridae indet.    83.5    70.6
    Gorgosaurus libratus    83.5    70.6

Notice there are actually 11 lines in this file, because the HEADER of the columns is printed.  Note that the output file delimiter is a \t char.

# Task 1 - Printing to a file

Modify your dinodata module to work with the dinocolumns.py file I provide.  You'll notice there is a new function called save_df that takes the name of the output file, a list of the columns (example: [5, 15, 16], these are INTS not strings), and a limit of number of columns to print.

***A REQUIREMENT*** of this assignment is to add this function to your dinodata module and use only this function to write out to files (do not write to the file directly from save_df):

    def filewriteline(self, datfile, dat):
        fd = open(datfile, 'a')
        fd.write(dat)
        fd.write('\n')
        fd.close()
        
Notice what it does.  Given a filename and data, it opens the file in APPEND mode, writes the data, then writes a newline, then closes the file.  The append mode (the 'a' in open) means that every time you run the program, it will add more information onto the same file.  **Keep this in mind when testing your program.**

You need to write the save_df function so that it calls filewriteline to print out to a file.  You must NOT directly write to the file in save_df.  This sort of situation is very common, by the way.  It is very common that a program has a specific output function you have to call -- you can't just write out whatever you want whenever.  Why?  See the next task...

(Be SURE your Task 1 is working properly before moving on to Task 2.)

# Task 2 - Encryption

Very often, a program must comply with certain data standards, such as encryption, having the correct file format, following regulatory rules on data storage, or whatever.  So you have to call some given function for output.

Except, sometimes you want different functionality.  Sometimes you want to output in encrypted form, sometimes not.  Or sometimes you want different types of encryption.  One way to do this is to have a bunch of if statements in your code to call different functions.  But a nice way, a cleaner way, a more Pythonic way, is to use a decorator.

Add a decorator to the filewriteline like so:

    @dinoencrypt
    def filewriteline(self, datfile, dat):
        fd = open(datfile, 'a')
        fd.write(dat)
        fd.write('\n')
        fd.close()
        
Notice how dinoencrypt is now decorating filewriteline.  What this decorator should do is "surround" the filewriteline function and, if needed, encrypt the 'dat' input prior to calling the filewriteline function.

Your job is to write this decorator.

Look carefully at how dinocolumns.py is written.  Note the lines:

    parser.add_argument('-e', dest='encryptpw', type=str, default='', help='encrypt, if specified, with given password')
    ...
    encryptpw = args.encryptpw
    ...
    dinos = dinodata.dinodata([], [], encryptpw)

It means that if dinocolumns.py is called like this:

    $ python3 dinocolumns.py -d dinosaur.dat -o dinosmini.dat -c 5,15,16 -l 5 -e akagi

Then dinosmini.dat would be this:

    c2MAAiqAP/bSIaMkjcWQzHtIl6/TnTkyHqVzURm6nPy3wMTsVL6PEGXi+1ATALJTm0ix5z1TWNpxHGfTvKrX34ih2tLvd/B4FH4DWIIu+HbzMWznTGZC+IBoCIxQ3pmsUA==
    c2MAAhSVMbSIT1cxOBDF8uotr7uQWfwYFuOwTCjfF7KsvRf9urIu//Sxyv4N5WHpIoESCLrOGIkWT6iB6S19sIC6aGxAfZ/0AI2qx2IBMAUJd3tLaz5X3zs=
    c2MAAqSBgpfN/1mc3TRC1KcWEqdyYkKSN9QgC83PAa4Sr3QyRroMiD6bUzQPM0fsjA189vawR40FUERb28SNax9EpY3DG8cFJffUIyVKVrs/btPPvcXL8AM=
    c2MAAqwa1UlyJj+8QjrEdZHUEP5RGKG08tjwkjYWHd7GQKvhswK4B6yL4kXkg61AcQ8QBmmmQNI37MtsI3W8UPC3QTlJTaijh4+OUfnqTUeSimLHuFyN0Ep+BKIwTgloBPVJJuDEvcQp6T7G6hq4lnet1NpvxtECHh0=
    c2MAAq7rxlxGcsWCvG8paG0jyzIIzw1iASbHHq/xN2uNzP3Wo3uSV2p2cTZSc/KMeCzAddTQsuiQKflheFzhc41RrudX/pToLxqLqPgQqTCLXh4Y+5eq+KY1Qu/w0+Ds+7Jqn3053E+9xtQ+zE1k/1mQ4AO4NQ0=
    c2MAAknSvUfrIyAOek2orJj7wakBCuKyVya+IwY3ZUmLjAWnLO5WCE695dqptx5xLWP9A7XEHtfD54GKF/ztnha/ALrv8vBUishXBMR1nnp8LIZjmh6nZenclAA9XrOYoJX08jjEeUaqRDgeCFA=

There are still six lines here (-l 5, plus one for the header)!! But each line is encrypted with the password 'akagi'.

## OK PROFESSOR BUT HOW DO I ENCRYPT STUFF?

With a Python module, of course.  We don't need milspec, NSA-proof, alien-technology-enhanced encryption here.  We just need a simple mechanism to scramble the data using a short password.  Check this out:

    from simplecrypt import encrypt, decrypt
    
    edat = encrypt('akagi', 'secret message')

Now edat is an encrypted byte string that can be decrypted like so:

    dat = decrypt('akagi', edat)

That's all you need to encrypt and decrypt in a simple way in Python.  ***HOWEVER*** you also need to print this to a file.  The trouble with this is that simplecrypt gives you bytestrings that are really just bytes, not strings of chars as we usually think of them.  That means we can't print them out to a file in normal mode.  We could use binary file editing, but there are a variety of problems with that beyond the scope of this assignment (we can talk about it in class later).  A much easier solution is to just reencode the data into a string that can be printed in normal mode.

How?  Answer: yes, another module.  Check this out:
    
    from simplecrypt import encrypt, decrypt
    from base64 import b64encode, b64decode

    edat = encrypt('akagi', 'secret message')
    edat = b64encode(edat).decode('utf-8')
    
Now edat is a string in regular-ol' utf-8 charset that can be printed to a file easily in the normal way.

Take a look at how the grading script works.  First it calls your program telling it to encrypt something with a password.  Then it decrypts the file with code like this:

    from simplecrypt import encrypt, decrypt
    from base64 import b64encode, b64decode

    f = open('dinosmini.dat', 'r')

    for l in f:
        encoded_cipher = l.rstrip()

        cipher = b64decode(encoded_cipher)
        plaintext = decrypt('akagi', cipher).decode('utf-8')

        print(plaintext)

The above little program just reads each line, decrypts just that line, then prints the decrypted line.  Note that it does NOT read in the whole file and decrypt the whole file, just like dinodata is NOT supposed to create the whole file and then encrypt it.  The file is a normal text file with newlines.  Each LINE is what is encrypted.

## OK I THINK I GET IT BUT WHAT NOW, AGAIN?

Write a little practice program to make sure you understand encrypting and decrypting.  Make sure that your Task 1 is printing out what you think (see the test script for examples).

THEN, go about writing a decorator that encrypts the output.  Note that it should only encrypt the output if the -e flag is specified with a password.  If a blank password is provided (because -e is not specified, note that '' is the default of -e), then the data should NOT be encrypted.

# Testing

    $ bash d11test.sh akagi
    Testing D11 ...
    Sample 1, 1 points             ... Success
    Sample 2, 2 points             ... Success
    Sample 3, 3 points             ... Success
    Time: 27 seconds (max allowed=300)
    Score: 6 / 6

Be sure to read the code of this test script.  Notice how it uses *my* dinocolumns.py file and *my* easycrypt.py file.  But dinocolumns.py uses *your* dinodata module (because it imports it).  Do not modify dinocolumns.py or easycrypt.py.

A caveat to grading here, of course, is that you *must* use a decorator.  Samples 2 and 3 will receive a zero if you do not use a decorator, as specified above, to complete the assignment.  You can't just write some encrypted stuff with a bunch of if statements from save_df, for example.

