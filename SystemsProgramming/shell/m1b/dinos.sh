#!/bin/bash

OFS=";"
SORT="cat"

DATFILE="dinosaur.dat"

DINOA=$1
DINOB=$2

YES_COUNT=0
NO_COUNT=0
YN=0
# Do some initial filtering here with awk
DINOAoccur=$(cat $DATFILE | awk -v FS='\t' -v OFS='\t' -v IGNORECASE=1 '$6~/'"$DINOA"'/{print $16, $17;}' | sort -t $'\t' -h | uniq -c)

DINOBoccur=$(cat $DATFILE | awk -v FS='\t' -v OFS='\t' -v IGNORECASE=1 '$6~/'"$DINOB"'/{print $16, $17;}' | sort -t $'\t' -h | uniq -c)

overlap_ma(){
    dinoA_maxma=$(echo "$1/1" | bc)
    dinoA_minma=$(echo "$2/1" | bc)
    dinoB_maxma=$(echo "$3/1" | bc)
    dinoB_minma=$(echo "$4/1" | bc)
    YN=0
    if test $dinoA_minma -lt $dinoB_maxma -a $dinoB_minma -lt $dinoA_maxma; then
        YN=1
    fi
    #if(dinoa_max > dinob_min || dinob_max > dinoa_min)
}

# Recall the pseudocode from README.md:
#
#For each *unique* Allosaurus occurrence:
#      NUM_ALLOSAUR = number of times this Allosaurus timespan occurs
#      For each *unique* Stegosaurus occurrence:
#          NUM_STEGOSAUR = number of times this Stego timespan occurs
#          YN = overlap_ma(dinoA_maxma, dinoA_minma, dinoB_maxma, dinoB_minma)
#          if YN equals 1
#              yes_count += NUM_ALLOSAUR + NUM_STEGOSAUR
#          else
#              no_count += NUM_ALLOSAUR + NUM_STEGOSAUR

IFS=$'\n'

for lineA in $DINOAoccur; do
    NUM_A=$(echo "$lineA" | sed -nE 's/^\s+([0-9]+)\s[0-9].*/\1/p')
    for lineB in $DINOBoccur; do
        NUM_B=$(echo "$lineB" | sed -nE 's/^\s+([0-9]+)\s[0-9].*/\1/p')
        dinoA_maxma=$(echo "$lineA" | sed -nE 's/^\s+([0-9]+)\s+([0-9.]+)\s+([0-9.]+)\s*$/\2/p')
        dinoA_minma=$(echo "$lineA" | sed -nE 's/^\s+([0-9]+)\s+([0-9.]+)\s+([0-9.]+)\s*$/\3/p')
        dinoB_maxma=$(echo "$lineB" | sed -nE 's/^\s+([0-9]+)\s+([0-9.]+)\s+([0-9.]+)\s*$/\2/p')
        dinoB_minma=$(echo "$lineB" | sed -nE 's/^\s+([0-9]+)\s+([0-9.]+)\s+([0-9.]+)\s*$/\3/p')
        overlap_ma $dinoA_maxma $dinoA_minma $dinoB_maxma $dinoB_minma
        if test $YN -eq 1; then
            YES_COUNT=$(echo "$YES_COUNT+$NUM_A+$NUM_B" | bc)
        else
            NO_COUNT=$(echo "$NO_COUNT+$NUM_A+$NUM_B" | bc)
        fi
    done
done

# Use bc to calculate $OVERLAP

OVERLAP=$(echo "$YES_COUNT/($YES_COUNT+$NO_COUNT)*100" | bc -l)
OVERLAP=$(echo "$OVERLAP/1" | bc)

echo "dinoverlap between $DINOA and $DINOB is $OVERLAP%"

# Here's your ASCII art for this assignment!
#                __
#               / _)
#      _.----._/ /
#     /         /
#  __/ (  | (  |
# /__.-'|_|--|_|
#
# Imagine entering a time machine and setting the dial
# for -100 million years.  The door opens and humid air
# enters the machine.  Palm trees sway and a sauropod
# turns its long neck slowly toward you.  In the
# distance, a volcano emits steam and smoke.  A raptor
# suddenly leaps and runs toward you!  You look at the
# fuel gauge: if you jump again, you can make it home,
# but never return to the land of the dinosaurs.  Out
# of the corner of your eye you glance the emergency
# blaster pack. Fully charged, but locked behind the
# safety glass.  You just might have time to grab it,
# if you run now, right now.
#
# Do you punch JUMP or RUN?
#

